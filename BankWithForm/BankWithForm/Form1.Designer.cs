namespace BankWithForm
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
            this.MAXdata = new System.Windows.Forms.DataGridView();
            this.MAXlabel = new System.Windows.Forms.Label();
            this.ALLOCATIONlabel = new System.Windows.Forms.Label();
            this.ALLOCATIONdata = new System.Windows.Forms.DataGridView();
            this.Threadnum = new System.Windows.Forms.NumericUpDown();
            this.REQUESTdata = new System.Windows.Forms.DataGridView();
            this.REQUEST = new System.Windows.Forms.Button();
            this.SAFE = new System.Windows.Forms.Button();
            this.REQUESTThreadlabel = new System.Windows.Forms.Label();
            this.REQUESTlabel = new System.Windows.Forms.Label();
            this.AVAILABLElabel = new System.Windows.Forms.Label();
            this.AVAILBLEdata = new System.Windows.Forms.DataGridView();
            ((System.ComponentModel.ISupportInitialize)(this.MAXdata)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ALLOCATIONdata)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Threadnum)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.REQUESTdata)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.AVAILBLEdata)).BeginInit();
            this.SuspendLayout();
            // 
            // MAXdata
            // 
            this.MAXdata.AllowUserToAddRows = false;
            this.MAXdata.AllowUserToDeleteRows = false;
            this.MAXdata.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.MAXdata.Location = new System.Drawing.Point(12, 30);
            this.MAXdata.Name = "MAXdata";
            this.MAXdata.RowTemplate.Height = 30;
            this.MAXdata.Size = new System.Drawing.Size(800, 400);
            this.MAXdata.TabIndex = 0;
            // 
            // MAXlabel
            // 
            this.MAXlabel.AutoSize = true;
            this.MAXlabel.Location = new System.Drawing.Point(12, 9);
            this.MAXlabel.Name = "MAXlabel";
            this.MAXlabel.Size = new System.Drawing.Size(35, 18);
            this.MAXlabel.TabIndex = 1;
            this.MAXlabel.Text = "MAX";
            // 
            // ALLOCATIONlabel
            // 
            this.ALLOCATIONlabel.AutoSize = true;
            this.ALLOCATIONlabel.Location = new System.Drawing.Point(815, 9);
            this.ALLOCATIONlabel.Name = "ALLOCATIONlabel";
            this.ALLOCATIONlabel.Size = new System.Drawing.Size(98, 18);
            this.ALLOCATIONlabel.TabIndex = 2;
            this.ALLOCATIONlabel.Text = "ALLOCATION";
            // 
            // ALLOCATIONdata
            // 
            this.ALLOCATIONdata.AllowUserToAddRows = false;
            this.ALLOCATIONdata.AllowUserToDeleteRows = false;
            this.ALLOCATIONdata.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.ALLOCATIONdata.Location = new System.Drawing.Point(818, 30);
            this.ALLOCATIONdata.Name = "ALLOCATIONdata";
            this.ALLOCATIONdata.RowTemplate.Height = 30;
            this.ALLOCATIONdata.Size = new System.Drawing.Size(800, 400);
            this.ALLOCATIONdata.TabIndex = 4;
            // 
            // Threadnum
            // 
            this.Threadnum.Location = new System.Drawing.Point(124, 556);
            this.Threadnum.Name = "Threadnum";
            this.Threadnum.Size = new System.Drawing.Size(120, 28);
            this.Threadnum.TabIndex = 6;
            // 
            // REQUESTdata
            // 
            this.REQUESTdata.AllowUserToAddRows = false;
            this.REQUESTdata.AllowUserToDeleteRows = false;
            this.REQUESTdata.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.REQUESTdata.Location = new System.Drawing.Point(12, 459);
            this.REQUESTdata.Name = "REQUESTdata";
            this.REQUESTdata.RowTemplate.Height = 30;
            this.REQUESTdata.Size = new System.Drawing.Size(800, 93);
            this.REQUESTdata.TabIndex = 7;
            // 
            // REQUEST
            // 
            this.REQUEST.Location = new System.Drawing.Point(250, 558);
            this.REQUEST.Name = "REQUEST";
            this.REQUEST.Size = new System.Drawing.Size(562, 74);
            this.REQUEST.TabIndex = 8;
            this.REQUEST.Text = "发出请求";
            this.REQUEST.UseVisualStyleBackColor = true;
            this.REQUEST.Click += new System.EventHandler(this.REQUEST_Click);
            // 
            // SAFE
            // 
            this.SAFE.Location = new System.Drawing.Point(818, 558);
            this.SAFE.Name = "SAFE";
            this.SAFE.Size = new System.Drawing.Size(800, 74);
            this.SAFE.TabIndex = 9;
            this.SAFE.Text = "测试安全性";
            this.SAFE.UseVisualStyleBackColor = true;
            this.SAFE.Click += new System.EventHandler(this.SAFE_Click);
            // 
            // REQUESTThreadlabel
            // 
            this.REQUESTThreadlabel.AutoSize = true;
            this.REQUESTThreadlabel.Location = new System.Drawing.Point(11, 558);
            this.REQUESTThreadlabel.Name = "REQUESTThreadlabel";
            this.REQUESTThreadlabel.Size = new System.Drawing.Size(107, 18);
            this.REQUESTThreadlabel.TabIndex = 10;
            this.REQUESTThreadlabel.Text = "REQUEST进程";
            // 
            // REQUESTlabel
            // 
            this.REQUESTlabel.AutoSize = true;
            this.REQUESTlabel.Location = new System.Drawing.Point(12, 438);
            this.REQUESTlabel.Name = "REQUESTlabel";
            this.REQUESTlabel.Size = new System.Drawing.Size(71, 18);
            this.REQUESTlabel.TabIndex = 11;
            this.REQUESTlabel.Text = "REQUEST";
            // 
            // AVAILABLElabel
            // 
            this.AVAILABLElabel.AutoSize = true;
            this.AVAILABLElabel.Location = new System.Drawing.Point(815, 438);
            this.AVAILABLElabel.Name = "AVAILABLElabel";
            this.AVAILABLElabel.Size = new System.Drawing.Size(89, 18);
            this.AVAILABLElabel.TabIndex = 13;
            this.AVAILABLElabel.Text = "AVAILABLE";
            // 
            // AVAILBLEdata
            // 
            this.AVAILBLEdata.AllowUserToAddRows = false;
            this.AVAILBLEdata.AllowUserToDeleteRows = false;
            this.AVAILBLEdata.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.AVAILBLEdata.Location = new System.Drawing.Point(818, 459);
            this.AVAILBLEdata.Name = "AVAILBLEdata";
            this.AVAILBLEdata.RowTemplate.Height = 30;
            this.AVAILBLEdata.Size = new System.Drawing.Size(800, 93);
            this.AVAILBLEdata.TabIndex = 12;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 18F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1745, 700);
            this.Controls.Add(this.AVAILABLElabel);
            this.Controls.Add(this.AVAILBLEdata);
            this.Controls.Add(this.REQUESTlabel);
            this.Controls.Add(this.REQUESTThreadlabel);
            this.Controls.Add(this.SAFE);
            this.Controls.Add(this.REQUEST);
            this.Controls.Add(this.REQUESTdata);
            this.Controls.Add(this.Threadnum);
            this.Controls.Add(this.ALLOCATIONdata);
            this.Controls.Add(this.ALLOCATIONlabel);
            this.Controls.Add(this.MAXlabel);
            this.Controls.Add(this.MAXdata);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.MAXdata)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ALLOCATIONdata)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Threadnum)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.REQUESTdata)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.AVAILBLEdata)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView MAXdata;
        private System.Windows.Forms.Label MAXlabel;
        private System.Windows.Forms.Label ALLOCATIONlabel;
        private System.Windows.Forms.DataGridView ALLOCATIONdata;
        private System.Windows.Forms.NumericUpDown Threadnum;
        private System.Windows.Forms.DataGridView REQUESTdata;
        private System.Windows.Forms.Button REQUEST;
        private System.Windows.Forms.Button SAFE;
        private System.Windows.Forms.Label REQUESTThreadlabel;
        private System.Windows.Forms.Label REQUESTlabel;
        private System.Windows.Forms.Label AVAILABLElabel;
        private System.Windows.Forms.DataGridView AVAILBLEdata;
    }
}

