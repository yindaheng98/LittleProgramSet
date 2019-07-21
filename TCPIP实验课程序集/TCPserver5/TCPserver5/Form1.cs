using System;
using System.Text;
using System.Windows.Forms;
using System.Net.Sockets;

namespace TCPserver5
{
    public partial class Form1 : Form
    {
        Socket temp;
        public Form1()
        {
            InitializeComponent();
        }

        private void buttonPrepare_Click(object sender, EventArgs e)
        {
            buttonPrepare.Enabled = false;
            temp = Program.s.Accept();
            MessageBox.Show("已连接");
            buttonSend.Enabled = true;
            buttonExit.Enabled = true;
        }

        private void buttonSend_Click(object sender, EventArgs e)
        {
            string msg = textBoxMsg.Text;
            byte[] bs = Encoding.ASCII.GetBytes(msg);
            temp.Send(bs, bs.Length, 0);
            MessageBox.Show("发送完成");
        }


        private void buttonExit_Click(object sender, EventArgs e)
        {
            temp.Close();
            buttonSend.Enabled = false;
            buttonExit.Enabled = false;
            buttonPrepare.Enabled = true;
        }
    }
}
