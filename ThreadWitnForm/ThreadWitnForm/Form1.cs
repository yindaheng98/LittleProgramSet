using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ThreadWitnForm
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            GlobalClass.InitProgram();
            InitData.DataSource = GlobalClass.InitData;
            RunningData.DataSource = GlobalClass.RunningData;
            ReadyData.DataSource = GlobalClass.ReadyData;
            FinishData.DataSource = GlobalClass.FinishData;
        }

        private void Start_Click(object sender, EventArgs e)
        {
            GlobalClass.ReadInitData();
        }

        private void Run1s_Click(object sender, EventArgs e)
        {
            GlobalClass.Run1s();
        }
    }
}
