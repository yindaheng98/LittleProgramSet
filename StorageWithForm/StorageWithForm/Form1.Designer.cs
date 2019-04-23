namespace StorageWithForm
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
            this.Convert = new System.Windows.Forms.Button();
            this.InputLabel = new System.Windows.Forms.Label();
            this.SegmentData = new System.Windows.Forms.DataGridView();
            this.PageData = new System.Windows.Forms.DataGridView();
            this.OutputLabel = new System.Windows.Forms.Label();
            this.SegDataLabel = new System.Windows.Forms.Label();
            this.PageDataLabel = new System.Windows.Forms.Label();
            this.Input = new System.Windows.Forms.NumericUpDown();
            this.Output = new System.Windows.Forms.NumericUpDown();
            ((System.ComponentModel.ISupportInitialize)(this.SegmentData)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.PageData)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Input)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Output)).BeginInit();
            this.SuspendLayout();
            // 
            // Convert
            // 
            this.Convert.Location = new System.Drawing.Point(1039, 65);
            this.Convert.Name = "Convert";
            this.Convert.Size = new System.Drawing.Size(100, 100);
            this.Convert.TabIndex = 1;
            this.Convert.Text = "转换";
            this.Convert.UseVisualStyleBackColor = true;
            this.Convert.Click += new System.EventHandler(this.Convert_Click);
            // 
            // InputLabel
            // 
            this.InputLabel.AutoSize = true;
            this.InputLabel.Location = new System.Drawing.Point(1036, 10);
            this.InputLabel.Name = "InputLabel";
            this.InputLabel.Size = new System.Drawing.Size(116, 18);
            this.InputLabel.TabIndex = 2;
            this.InputLabel.Text = "输入虚拟地址";
            // 
            // SegmentData
            // 
            this.SegmentData.AllowUserToAddRows = false;
            this.SegmentData.AllowUserToDeleteRows = false;
            this.SegmentData.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.SegmentData.Location = new System.Drawing.Point(12, 36);
            this.SegmentData.Name = "SegmentData";
            this.SegmentData.ReadOnly = true;
            this.SegmentData.RowTemplate.Height = 30;
            this.SegmentData.Size = new System.Drawing.Size(400, 550);
            this.SegmentData.TabIndex = 4;
            // 
            // PageData
            // 
            this.PageData.AllowUserToAddRows = false;
            this.PageData.AllowUserToDeleteRows = false;
            this.PageData.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.PageData.Location = new System.Drawing.Point(418, 36);
            this.PageData.Name = "PageData";
            this.PageData.ReadOnly = true;
            this.PageData.RowTemplate.Height = 30;
            this.PageData.Size = new System.Drawing.Size(615, 550);
            this.PageData.TabIndex = 5;
            // 
            // OutputLabel
            // 
            this.OutputLabel.AutoSize = true;
            this.OutputLabel.Location = new System.Drawing.Point(1036, 168);
            this.OutputLabel.Name = "OutputLabel";
            this.OutputLabel.Size = new System.Drawing.Size(116, 18);
            this.OutputLabel.TabIndex = 6;
            this.OutputLabel.Text = "输出实际地址";
            // 
            // SegDataLabel
            // 
            this.SegDataLabel.AutoSize = true;
            this.SegDataLabel.Location = new System.Drawing.Point(12, 9);
            this.SegDataLabel.Name = "SegDataLabel";
            this.SegDataLabel.Size = new System.Drawing.Size(116, 18);
            this.SegDataLabel.TabIndex = 7;
            this.SegDataLabel.Text = "地址所在段表";
            // 
            // PageDataLabel
            // 
            this.PageDataLabel.AutoSize = true;
            this.PageDataLabel.Location = new System.Drawing.Point(415, 9);
            this.PageDataLabel.Name = "PageDataLabel";
            this.PageDataLabel.Size = new System.Drawing.Size(116, 18);
            this.PageDataLabel.TabIndex = 8;
            this.PageDataLabel.Text = "地址所在页表";
            // 
            // Input
            // 
            this.Input.Location = new System.Drawing.Point(1039, 31);
            this.Input.Maximum = new decimal(new int[] {
            1073741824,
            0,
            0,
            0});
            this.Input.Name = "Input";
            this.Input.Size = new System.Drawing.Size(120, 28);
            this.Input.TabIndex = 9;
            // 
            // Output
            // 
            this.Output.Location = new System.Drawing.Point(1040, 190);
            this.Output.Maximum = new decimal(new int[] {
            1073741824,
            0,
            0,
            0});
            this.Output.Name = "Output";
            this.Output.Size = new System.Drawing.Size(120, 28);
            this.Output.TabIndex = 10;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 18F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1176, 596);
            this.Controls.Add(this.Output);
            this.Controls.Add(this.Input);
            this.Controls.Add(this.PageDataLabel);
            this.Controls.Add(this.SegDataLabel);
            this.Controls.Add(this.OutputLabel);
            this.Controls.Add(this.PageData);
            this.Controls.Add(this.SegmentData);
            this.Controls.Add(this.InputLabel);
            this.Controls.Add(this.Convert);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.SegmentData)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.PageData)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Input)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Output)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Button Convert;
        private System.Windows.Forms.Label InputLabel;
        private System.Windows.Forms.DataGridView SegmentData;
        private System.Windows.Forms.DataGridView PageData;
        private System.Windows.Forms.Label OutputLabel;
        private System.Windows.Forms.Label SegDataLabel;
        private System.Windows.Forms.Label PageDataLabel;
        private System.Windows.Forms.NumericUpDown Input;
        private System.Windows.Forms.NumericUpDown Output;
    }
}

