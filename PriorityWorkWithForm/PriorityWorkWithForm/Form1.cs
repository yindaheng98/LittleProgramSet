using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace PriorityWorkWithForm
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            GlobalClass.Init();
            Processes.DataSource = GlobalClass.Processes;
            Results.DataSource = GlobalClass.Results;
            Flow.DataSource = GlobalClass.Flow;
        }

        private void Start_Click(object sender, EventArgs e)
        {
            if (GlobalClass.Processes.Rows.Count <= 0)
                MessageBox.Show("请输入要调度的作业", "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            else
            {
                GlobalClass.Run(double.Parse(TimePiece.Value.ToString()));
                AverageTime.Text = GlobalClass.ATT.ToString();
                AverageWeightedTime.Text = GlobalClass.AWTT.ToString();
            }
        }
    }
}
