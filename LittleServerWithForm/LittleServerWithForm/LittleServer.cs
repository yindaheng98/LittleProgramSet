using System;
using System.Text;
using System.Collections.Generic;
using System.Linq;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Threading;

namespace LittleServerWithForm
{
    class FuckServer
    {
        public int port { get; }
        private IPEndPoint addr;
        private Socket serverSocket;
        private Thread thread;
        private bool status;
        private uint clients;
        public string name { get; }
        private string HeaderInfo;
        private string DefaultPage;

        public FuckServer(int p = 80, string n = "FuckServer", string d = "index.html")
        {
            DefaultPage = d;
            name = n;
            port = p;//指定端口号
            status = false;//服务器初始状态为关机
            addr = new IPEndPoint(IPAddress.Any, port);//设置服务器端IP地址和端口号
            serverSocket = new Socket(addr.AddressFamily, SocketType.Stream, ProtocolType.Tcp);//创建流式套接字
            serverSocket.Bind(addr);//服务器IP端口和服务器端套接字绑定

            Console.WriteLine("服务器_"+ "已创建");
            HeaderInfoConstruct();
        }

        private void HeaderInfoConstruct()//构造固定的头部项
        {
            HeaderInfo = "";
            HeaderInfo += "Server: " + name + '\r' + '\n';
            HeaderInfo += "Content-Type: text/html; charset=UTF-8" + '\r' + '\n';
        }

        public void Startup()//开机
        {
            status = true;//修改服务器状态为开机
            serverSocket.Listen(10);//开始监听
            Console.WriteLine("服务器_"+ "开始端口监听");
            clients = 0;//客户端数量为0
            thread = new Thread(new ThreadStart(AcceptThread));
            thread.Start();//启动连接接收进程
        }

        private void AcceptThread()//此进程用于接收连接请求
        {
            Console.WriteLine("服务器_"+ "开始接收连接请求");
            while (status)//如果开机则持续接收请求，否则退出
            {

                Console.WriteLine("服务器_"+ "等待连接");
                try
                {
                    Socket clientSocket = serverSocket.Accept();//如果有连接请求则接收连接
                    if (status)
                    {
                        Console.WriteLine("服务器_"+ "收到连接请求");
                        thread = new Thread(() => ResponseThread(clientSocket));
                        thread.Start();//然后启动一个客户端连接进程
                        Console.WriteLine("服务器_"+ "会话开始");
                    }
                }
                catch
                {
                    Console.WriteLine("服务器_"+ "已停止监听");
                }
            }
            Console.WriteLine("服务器_"+ "已停止接收连接请求");
        }

        private void ResponseThread(Socket s)//此进程用于响应客户端
        {

            clients++;//连接数加1
            s.ReceiveTimeout = 60;
            IPEndPoint ipEndPoint = (IPEndPoint)s.RemoteEndPoint;//读取客户端信息
            //string address = ipEndPoint.Address.ToString();//读取客户的IP地址
            //string port = ipEndPoint.Port.ToString();//读取客户的端口号
            string client = ipEndPoint.Address.ToString() + ":" + ipEndPoint.Port.ToString();
            Console.WriteLine("服务器_客户端" + client + "已连接");
            Console.WriteLine("客户端_连接_" + client);
            Console.WriteLine("服务器_当前客户端数量:" + clients);

            byte[] inBuffer = new byte[4096];
            Dictionary<string, string> parsedRequest;

            while (true)
            {
                if (!status)//如果服务器要关机了就直接发关机信息然后退出
                {
                    byte[] outBuffer = Encoding.UTF8.GetBytes(name + " has stopped");
                    try
                    { s.Send(outBuffer, outBuffer.Length, SocketFlags.None); }
                    catch
                    { break; }//要是这时客户端离线了就直接退出
                    break;//退出
                }

                try//没关机，接收用户请求
                {
                    s.Receive(inBuffer, 4096, SocketFlags.None);//如果用户一直不发数据这里会报错
                }
                catch (SocketException socketException)//receive报错
                {
                    if (socketException.ErrorCode == 10060)
                        continue;//10060错误是超时,不退出，继续接收数据
                    //else if (socketException.ErrorCode == 10053&& socketException.ErrorCode == 10112) break;
                    else//10112和10053错误是用户主动中断连接和强制中断连接，退出
                    {
                        Console.WriteLine("服务器_"+socketException.ErrorCode + ':' + socketException.Message);
                        break;//其他错误也退出
                    }
                }
                catch (Exception e)//其他错误也退出
                {
                    Console.WriteLine("服务器_Error:" + e.Message);
                    break;
                }
                byte[] t = Encoding.UTF8.GetBytes(Encoding.UTF8.GetString(inBuffer).TrimEnd('\0'));
                Console.WriteLine("服务器_收到来自" + client + "一个" + t.Length + "字节的数据包");
                Console.WriteLine("客户端_请求_"+client+"_" + Encoding.UTF8.GetString(inBuffer).TrimEnd('\0'));

                try
                {
                    parsedRequest = parseRequest(inBuffer);//解析
                    //Console.WriteLine("是一个http请求");
                    byte[] outBuffer = ResponseHttpRequest(parsedRequest);//构造响应
                    s.Send(outBuffer, outBuffer.Length, SocketFlags.None);//发送响应
                    Console.WriteLine("服务器_响应" + client + "一个" + outBuffer.Length + "字节的数据包");
                    Console.WriteLine("客户端_响应_" + client + "_" + Encoding.UTF8.GetString(outBuffer));
                    if (!(parsedRequest.ContainsKey("Connection") && parsedRequest["Connection"].IndexOf("Keep-Alive") != -1))
                        break;//如果不用保持连接就退出
                }
                catch (SocketException socketException)
                {
                    Console.WriteLine("服务器_"+socketException.ErrorCode + ':' + socketException.Message);
                    break;
                }
                catch (Exception)
                {
                    //Console.WriteLine("不是HTTP请求");
                    string Body = "";
                    try
                    {
                        Body = getHtml("400.html");
                    }
                    catch
                    {
                        Body = "<html><head><title>400 Bad Request</title></head><body bgcolor='white'><center><h1>400 Bad Request</h1><h2>毫 无 要 素<h3><a herf='index.html'>自 裁</a><h4>请</h4></h3></h2></center><hr><center>FuckServer</center></body></html>";
                    }
                    string Header = "HTTP/1.1 400 Bad Request" + '\r' + '\n';
                    Header += "Connection: close" + '\r' + '\n';
                    Header += HeaderInfo;
                    byte[] outBuffer = Encoding.UTF8.GetBytes(Header + System.Environment.NewLine + Body);
                    try
                    { s.Send(outBuffer, outBuffer.Length, SocketFlags.None); }//发送响应 
                    catch { break; }
                    Console.WriteLine("服务器_响应" + client + "一个" + outBuffer.Length + "字节的数据包");
                    Console.WriteLine("客户端_响应_" + client + "_" + Encoding.UTF8.GetString(outBuffer));
                    break;
                }
            }
            s.Close();//退出时关闭连接
            clients--;//客户端数量减一
            Console.WriteLine("服务器_客户端" + client + "已离线");
            Console.WriteLine("客户端_离线_" + client);
            Console.WriteLine("服务器_当前客户端数量:" + clients);
        }

        private byte[] ResponseHttpRequest(Dictionary<string, string> HttpRequest)//构造响应
        {
            string Header = "";
            string Body = "";
            try
            {
                Body = getHtml(HttpRequest["url"]);
                Header = "HTTP/1.1 200 OK" + '\r' + '\n';
            }
            catch (FileNotFoundException)
            {
                try
                {
                    Body = getHtml("404.html");
                }
                catch
                {
                    Body = "<html><head><title>404 Not Found</title></head><body bgcolor='white'><center><h1>404 Not Found</h1><h2>要 素 缺 失<h3><a herf='index.html'>回 城</a><h4>请</h4></h3></h2></center><hr><center>FuckServer</center></body></html>";
                }
                Header = "HTTP/1.1 404 Not Found" + '\r' + '\n';
            }
            if (HttpRequest.ContainsKey("Connection"))
                Header += "Connection: " + HttpRequest["Connection"] + '\r' + '\n';
            Header += HeaderInfo;
            return Encoding.UTF8.GetBytes(Header + System.Environment.NewLine + Body);
        }

        private string getHtml(string url)//从指定路径获取html
        {
            string html = "";
            if (url.IndexOf('.') == -1)//如果请求的不是文件,就加一个index.html
            {
                if (url.LastIndexOf('/') != (url.Length - 1))//最后一个不是斜杠/就加一个斜杠
                    url += "/";
                url += DefaultPage;
            }
            url = url.Remove(0, 1);
            if (File.Exists(url))
            {
                while (true)
                {
                    try
                    {
                        FileStream HtmlFile = new FileStream(url, FileMode.Open);
                        byte[] HtmlByteData = new byte[HtmlFile.Length];
                        HtmlFile.Seek(0, SeekOrigin.Begin);
                        HtmlFile.Read(HtmlByteData, 0, HtmlByteData.Length);
                        HtmlFile.Close();
                        html = Encoding.UTF8.GetString(HtmlByteData);
                        break;
                    }
                    catch (IOException)
                    {
                        if (status)
                        {
                            Thread.Sleep(100);
                            continue;
                        }
                        else break;
                    }
                }
            }
            else throw new FileNotFoundException();
            return html;
        }

        private Dictionary<string, string> parseRequest(byte[] inBuffer)//解析http请求
        {
            string httpreqstr = Encoding.UTF8.GetString(inBuffer);
            string[] tokens = httpreqstr.Split(new char[] { '\r', '\n' }, StringSplitOptions.RemoveEmptyEntries);
            string[] headers = tokens[0].Split(' ');
            if (headers.Length != 3 || headers[2].IndexOf("HTTP") == -1) throw new Exception(httpreqstr + "不是HTTP请求");
            Dictionary<string, string> parsedRequest = new Dictionary<string, string>();
            parsedRequest["method"] = headers[0];
            parsedRequest["url"] = headers[1];
            parsedRequest["httpversion"] = headers[2];
            foreach (string t in tokens)
            {
                if (t.IndexOf(':') != -1)
                {
                    string[] kv = t.Split(new char[] { ':' },2);
                    parsedRequest[kv[0]] = kv[1];
                }
            }
            return parsedRequest;
        }

        public void Shutdown()//关机
        {
            status = false;
            Console.WriteLine("服务器_"+ "已关机");
            if (serverSocket == null)
                return;
            try
            {
                serverSocket.Shutdown(SocketShutdown.Both);
                serverSocket.Close();
            }
            catch
            {
            }
        }
    }
}
