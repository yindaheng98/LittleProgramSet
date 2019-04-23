using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace LittleServerWithForm
{
    public partial class Form1 : Form
    {
        private FuckServer server;
        public Form1()
        {
            InitializeComponent();
            CheckForIllegalCrossThreadCalls = false;
            new ConsoleHelper(textBox, treeView,clients);
            server = new FuckServer(8080, "StupiedServer","login.html");
            serverName.Text = server.name;
            port.Text = server.port.ToString();
        }

        private void Startup_Click(object sender, EventArgs e)
        {
            server.Startup();
        }

        private void Shutdown_Click(object sender, EventArgs e)
        {
            server.Shutdown();
        }
    }
}
