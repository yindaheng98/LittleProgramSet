using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace StorageWithForm
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Convert_Click(object sender, EventArgs e)
        {
            try
            {
                int virtualaddr = int.Parse(Input.Value.ToString());
                GlobalClass.syncData(virtualaddr);
                SegmentData.DataSource = GlobalClass.SegmentData;
                PageData.DataSource = GlobalClass.PageData;
                Output.Value = GlobalClass.s.getAddress(virtualaddr);
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
    }
}
