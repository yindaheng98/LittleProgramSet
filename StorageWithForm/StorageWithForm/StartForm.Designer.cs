namespace StorageWithForm
{
    partial class StartForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.Addresses_pre_Page = new System.Windows.Forms.NumericUpDown();
            this.TotalSegments = new System.Windows.Forms.NumericUpDown();
            this.Pages_pre_Segment = new System.Windows.Forms.NumericUpDown();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.OK = new System.Windows.Forms.Button();
            this.label8 = new System.Windows.Forms.Label();
            this.StartAddress = new System.Windows.Forms.NumericUpDown();
            this.label7 = new System.Windows.Forms.Label();
            this.TotalLabel = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.TotalAddress = new System.Windows.Forms.NumericUpDown();
            ((System.ComponentModel.ISupportInitialize)(this.Addresses_pre_Page)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.TotalSegments)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Pages_pre_Segment)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.StartAddress)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.TotalAddress)).BeginInit();
            this.SuspendLayout();
            // 
            // Addresses_pre_Page
            // 
            this.Addresses_pre_Page.Location = new System.Drawing.Point(111, 107);
            this.Addresses_pre_Page.Maximum = new decimal(new int[] {
            1048576,
            0,
            0,
            0});
            this.Addresses_pre_Page.Name = "Addresses_pre_Page";
            this.Addresses_pre_Page.Size = new System.Drawing.Size(120, 28);
            this.Addresses_pre_Page.TabIndex = 0;
            this.Addresses_pre_Page.ValueChanged += new System.EventHandler(this.Addresses_pre_Page_ValueChanged);
            // 
            // TotalSegments
            // 
            this.TotalSegments.Location = new System.Drawing.Point(111, 39);
            this.TotalSegments.Maximum = new decimal(new int[] {
            1073741824,
            0,
            0,
            0});
            this.TotalSegments.Name = "TotalSegments";
            this.TotalSegments.Size = new System.Drawing.Size(120, 28);
            this.TotalSegments.TabIndex = 1;
            this.TotalSegments.ValueChanged += new System.EventHandler(this.TotalSegments_ValueChanged);
            // 
            // Pages_pre_Segment
            // 
            this.Pages_pre_Segment.Location = new System.Drawing.Point(111, 73);
            this.Pages_pre_Segment.Maximum = new decimal(new int[] {
            1073741824,
            0,
            0,
            0});
            this.Pages_pre_Segment.Name = "Pages_pre_Segment";
            this.Pages_pre_Segment.Size = new System.Drawing.Size(120, 28);
            this.Pages_pre_Segment.TabIndex = 2;
            this.Pages_pre_Segment.ValueChanged += new System.EventHandler(this.Pages_pre_Segment_ValueChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(25, 109);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(80, 18);
            this.label1.TabIndex = 3;
            this.label1.Text = "页面大小";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(238, 109);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(26, 18);
            this.label2.TabIndex = 4;
            this.label2.Text = "KB";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(79, 41);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(26, 18);
            this.label3.TabIndex = 5;
            this.label3.Text = "分";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(43, 75);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(62, 18);
            this.label4.TabIndex = 6;
            this.label4.Text = "每段分";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(238, 75);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(26, 18);
            this.label5.TabIndex = 7;
            this.label5.Text = "页";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(238, 41);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(26, 18);
            this.label6.TabIndex = 8;
            this.label6.Text = "段";
            // 
            // OK
            // 
            this.OK.Location = new System.Drawing.Point(12, 175);
            this.OK.Name = "OK";
            this.OK.Size = new System.Drawing.Size(254, 61);
            this.OK.TabIndex = 9;
            this.OK.Text = "OK";
            this.OK.UseVisualStyleBackColor = true;
            this.OK.Click += new System.EventHandler(this.OK_Click);
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(25, 8);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(80, 18);
            this.label8.TabIndex = 11;
            this.label8.Text = "起始地址";
            // 
            // StartAddress
            // 
            this.StartAddress.Location = new System.Drawing.Point(111, 6);
            this.StartAddress.Maximum = new decimal(new int[] {
            1024,
            0,
            0,
            0});
            this.StartAddress.Name = "StartAddress";
            this.StartAddress.Size = new System.Drawing.Size(120, 28);
            this.StartAddress.TabIndex = 10;
            this.StartAddress.ValueChanged += new System.EventHandler(this.StartAddress_ValueChanged);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(238, 8);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(17, 18);
            this.label7.TabIndex = 12;
            this.label7.Text = "B";
            // 
            // TotalLabel
            // 
            this.TotalLabel.AutoSize = true;
            this.TotalLabel.Location = new System.Drawing.Point(238, 143);
            this.TotalLabel.Name = "TotalLabel";
            this.TotalLabel.Size = new System.Drawing.Size(17, 18);
            this.TotalLabel.TabIndex = 15;
            this.TotalLabel.Text = "B";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(25, 143);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(80, 18);
            this.label10.TabIndex = 14;
            this.label10.Text = "内存总量";
            // 
            // TotalAddress
            // 
            this.TotalAddress.DecimalPlaces = 4;
            this.TotalAddress.Location = new System.Drawing.Point(111, 141);
            this.TotalAddress.Maximum = new decimal(new int[] {
            1024,
            0,
            0,
            0});
            this.TotalAddress.Name = "TotalAddress";
            this.TotalAddress.ReadOnly = true;
            this.TotalAddress.Size = new System.Drawing.Size(120, 28);
            this.TotalAddress.TabIndex = 13;
            // 
            // StartForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 18F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(277, 250);
            this.Controls.Add(this.TotalLabel);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.TotalAddress);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.StartAddress);
            this.Controls.Add(this.OK);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.Pages_pre_Segment);
            this.Controls.Add(this.TotalSegments);
            this.Controls.Add(this.Addresses_pre_Page);
            this.Name = "StartForm";
            this.Text = "StartForm";
            ((System.ComponentModel.ISupportInitialize)(this.Addresses_pre_Page)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.TotalSegments)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Pages_pre_Segment)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.StartAddress)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.TotalAddress)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.NumericUpDown Addresses_pre_Page;
        private System.Windows.Forms.NumericUpDown TotalSegments;
        private System.Windows.Forms.NumericUpDown Pages_pre_Segment;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Button OK;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.NumericUpDown StartAddress;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label TotalLabel;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.NumericUpDown TotalAddress;
    }
}