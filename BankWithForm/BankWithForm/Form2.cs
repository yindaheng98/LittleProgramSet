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
    public partial class Form2 : Form
    {
        public Form2()
        {
            InitializeComponent();
        }

        private void OK_button_Click(object sender, EventArgs e)
        {
            int Threads = int.Parse(Threadsnum.Value.ToString());
            int Sources = int.Parse(Sourcesnum.Value.ToString());
            GlobalClass.banker = new Banker(Threads, Sources);
            GlobalClass.REQUEST= new int[Sources];
            GlobalClass.AVAILABLE = new int[Sources];
            GlobalClass.MAX = new int[Threads, Sources];
            GlobalClass.ALLOCATION = new int[Threads, Sources];
            GlobalClass.SyncToDataTable();
            this.Close();
        }
    }
}
