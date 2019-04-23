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
    public partial class StartForm : Form
    {
        public StartForm()
        {
            InitializeComponent();
            StartAddress.Value = 0;
            TotalSegments.Value = 16;
            Pages_pre_Segment.Value = 512;
            Addresses_pre_Page.Value = 4;
        }

        private void OK_Click(object sender, EventArgs e)
        {
            try
            {
                GlobalClass.Init(int.Parse(StartAddress.Value.ToString()), int.Parse(TotalSegments.Value.ToString()), int.Parse(Pages_pre_Segment.Value.ToString()), int.Parse(Addresses_pre_Page.Value.ToString())*1024);
                this.Close();
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        private void Cal_Total()
        {
            long addr = long.Parse(TotalSegments.Value.ToString()) * long.Parse(Pages_pre_Segment.Value.ToString()) * long.Parse(Addresses_pre_Page.Value.ToString()) * 1024;
            double addrtotal = addr;
            if (addr / 1024 != 0)
            {
                TotalLabel.Text = "KB";
                addr /= 1024;addrtotal /= 1024;
                if (addr / 1024 != 0)
                {
                    TotalLabel.Text = "MB";
                    addr /= 1024;addrtotal /= 1024;
                    if (addr / 1024 != 0)
                    {
                        TotalLabel.Text = "GB";
                        addr /= 1024;addrtotal /= 1024;
                        if (addr / 1024 != 0)
                        {
                            TotalLabel.Text = "TB";
                            addr /= 1024;addrtotal /= 1024;
                            if (addr / 1024 != 0)
                            {
                                TotalLabel.Text = "PB";
                                addr /= 1024;addrtotal /= 1024;
                                if (addr / 1024 != 0)
                                {
                                    TotalLabel.Text = "EB";
                                    addr /= 1024;addrtotal /= 1024;
                                }
                            }
                        }
                    }
                }
            }
            TotalAddress.Value = decimal.Parse(addrtotal.ToString());
        }
        private void StartAddress_ValueChanged(object sender, EventArgs e)
        {
            Cal_Total();
        }
        private void TotalSegments_ValueChanged(object sender, EventArgs e)
        {
            Cal_Total();
        }
        private void Pages_pre_Segment_ValueChanged(object sender, EventArgs e)
        {
            Cal_Total();
        }
        private void Addresses_pre_Page_ValueChanged(object sender, EventArgs e)
        {
            Cal_Total();
        }
    }
}
