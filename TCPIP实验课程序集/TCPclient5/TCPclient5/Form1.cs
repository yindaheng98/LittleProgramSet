using System;
using System.Text;
using System.Windows.Forms;
using System.Net;
using System.Net.Sockets;

namespace TCPclient5
{
    public partial class Form1 : Form
    {
        Socket c;
        const int port = 2000;
        public Form1()
        {
            InitializeComponent();
        }

        private void buttonConnect_Click(object sender, EventArgs e)
        {
            string ip_str = textBoxIP.Text;
            IPEndPoint ipe = new IPEndPoint(IPAddress.Parse(ip_str), port);
            c = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);//创建Socket
            c.Connect(ipe);
            MessageBox.Show("连接成功");
            buttonConnect.Enabled = false;
            buttonRecv.Enabled = true;
            buttonExit.Enabled = true;
        }

        private void buttonRecv_Click(object sender, EventArgs e)
        {
            buttonRecv.Enabled = false;
            byte[] recvBytes = new byte[1024];
            int bytes = c.Receive(recvBytes, recvBytes.Length, 0);//从服务器端接受返回信息;
            textBoxRecv.Text = Encoding.ASCII.GetString(recvBytes, 0, bytes);
            buttonRecv.Enabled = true;
        }

        private void buttonExit_Click(object sender, EventArgs e)
        {
            c.Close();
            buttonConnect.Enabled = true;
            buttonRecv.Enabled = false;
            buttonExit.Enabled = false;
        }
    }
}
