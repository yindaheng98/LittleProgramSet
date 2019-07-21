using System;
using System.Windows.Forms;
using System.Net;
using System.Net.Sockets;

namespace TCPserver5
{
    static class Program
    {
        const int port = 2000;
        public static Socket s;
        /// <summary>
        /// 应用程序的主入口点。
        /// </summary>
        [STAThread]
        static void Main()
        {
            s = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            IPEndPoint ipe = new IPEndPoint(IPAddress.Any, port);//用指定的端口和ip初始化IPEndPoint类的新实例
            s.Bind(ipe);//绑定EndPoint对像（2000端口和ip地址）  
            s.Listen(0);//开始监听
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());
            s.Close();
        }
    }
}
