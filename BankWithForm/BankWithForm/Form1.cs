using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace BankWithForm
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            REQUESTdata.DataSource = GlobalClass.request;
            AVAILBLEdata.DataSource = GlobalClass.available;
            MAXdata.DataSource = GlobalClass.max;
            ALLOCATIONdata.DataSource = GlobalClass.allocation;
        }

        private void SAFE_Click(object sender, EventArgs e)
        {
            GlobalClass.SyncToMartix();
            try
            {
                GlobalClass.banker.Init(GlobalClass.MAX, GlobalClass.ALLOCATION, GlobalClass.AVAILABLE);
                if (GlobalClass.banker.isSafe)
                    MessageBox.Show("系统安全\n安全序列为" + GlobalClass.banker.SafeLine, "安全状况", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
                else
                    MessageBox.Show("系统不安全\n", "安全状况", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
            catch
            {
                MessageBox.Show("数据有误，请重新输入", "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void REQUEST_Click(object sender, EventArgs e)
        {
            GlobalClass.SyncToMartix();
            try
            {
                GlobalClass.banker.Init(GlobalClass.MAX, GlobalClass.ALLOCATION, GlobalClass.AVAILABLE);
                GlobalClass.banker.Request(int.Parse(Threadnum.Value.ToString()), GlobalClass.REQUEST);
                if (GlobalClass.banker.isSafe)
                    MessageBox.Show("接收请求\n安全序列为" + GlobalClass.banker.SafeLine, "请求", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
                else
                    MessageBox.Show("拒绝请求\n", "请求", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
            catch
            {
                MessageBox.Show("数据有误，请重新输入", "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
    }
}
