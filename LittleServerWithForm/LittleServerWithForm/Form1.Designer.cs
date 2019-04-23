namespace LittleServerWithForm
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.Startup = new System.Windows.Forms.Button();
            this.Shutdown = new System.Windows.Forms.Button();
            this.treeView = new System.Windows.Forms.TreeView();
            this.textBox = new System.Windows.Forms.TextBox();
            this.serverName = new System.Windows.Forms.TextBox();
            this.port = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.clients = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // Startup
            // 
            this.Startup.Location = new System.Drawing.Point(746, 115);
            this.Startup.Name = "Startup";
            this.Startup.Size = new System.Drawing.Size(250, 250);
            this.Startup.TabIndex = 0;
            this.Startup.Text = "Startup";
            this.Startup.UseVisualStyleBackColor = true;
            this.Startup.Click += new System.EventHandler(this.Startup_Click);
            // 
            // Shutdown
            // 
            this.Shutdown.Location = new System.Drawing.Point(745, 371);
            this.Shutdown.Name = "Shutdown";
            this.Shutdown.Size = new System.Drawing.Size(250, 250);
            this.Shutdown.TabIndex = 1;
            this.Shutdown.Text = "Shutdown";
            this.Shutdown.UseVisualStyleBackColor = true;
            this.Shutdown.Click += new System.EventHandler(this.Shutdown_Click);
            // 
            // treeView
            // 
            this.treeView.Location = new System.Drawing.Point(357, 12);
            this.treeView.Name = "treeView";
            this.treeView.Size = new System.Drawing.Size(378, 608);
            this.treeView.TabIndex = 2;
            // 
            // textBox
            // 
            this.textBox.Location = new System.Drawing.Point(12, 12);
            this.textBox.Multiline = true;
            this.textBox.Name = "textBox";
            this.textBox.Size = new System.Drawing.Size(339, 609);
            this.textBox.TabIndex = 3;
            // 
            // serverName
            // 
            this.serverName.Enabled = false;
            this.serverName.HideSelection = false;
            this.serverName.Location = new System.Drawing.Point(828, 12);
            this.serverName.Name = "serverName";
            this.serverName.Size = new System.Drawing.Size(167, 28);
            this.serverName.TabIndex = 4;
            // 
            // port
            // 
            this.port.Enabled = false;
            this.port.Location = new System.Drawing.Point(828, 46);
            this.port.Name = "port";
            this.port.Size = new System.Drawing.Size(167, 28);
            this.port.TabIndex = 5;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(742, 15);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(80, 18);
            this.label1.TabIndex = 6;
            this.label1.Text = "服务器名";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(742, 49);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(80, 18);
            this.label2.TabIndex = 7;
            this.label2.Text = "监听端口";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(742, 84);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(80, 18);
            this.label3.TabIndex = 8;
            this.label3.Text = "当前连接";
            // 
            // clients
            // 
            this.clients.Enabled = false;
            this.clients.Location = new System.Drawing.Point(828, 81);
            this.clients.Name = "clients";
            this.clients.Size = new System.Drawing.Size(167, 28);
            this.clients.TabIndex = 9;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 18F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1008, 632);
            this.Controls.Add(this.clients);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.port);
            this.Controls.Add(this.serverName);
            this.Controls.Add(this.textBox);
            this.Controls.Add(this.treeView);
            this.Controls.Add(this.Shutdown);
            this.Controls.Add(this.Startup);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button Startup;
        private System.Windows.Forms.Button Shutdown;
        private System.Windows.Forms.TreeView treeView;
        private System.Windows.Forms.TextBox textBox;
        private System.Windows.Forms.TextBox serverName;
        private System.Windows.Forms.TextBox port;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox clients;
    }
}

