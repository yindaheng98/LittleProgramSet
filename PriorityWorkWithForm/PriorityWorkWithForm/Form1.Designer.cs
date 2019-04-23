namespace PriorityWorkWithForm
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
            this.Processes = new System.Windows.Forms.DataGridView();
            this.Start = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.Results = new System.Windows.Forms.DataGridView();
            this.Flow = new System.Windows.Forms.DataGridView();
            this.TimePiece = new System.Windows.Forms.NumericUpDown();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.AverageWeightedTime = new System.Windows.Forms.Label();
            this.AverageTime = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.Processes)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Results)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Flow)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.TimePiece)).BeginInit();
            this.SuspendLayout();
            // 
            // Processes
            // 
            this.Processes.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.Processes.Location = new System.Drawing.Point(12, 30);
            this.Processes.Name = "Processes";
            this.Processes.RowTemplate.Height = 30;
            this.Processes.Size = new System.Drawing.Size(818, 261);
            this.Processes.TabIndex = 0;
            // 
            // Start
            // 
            this.Start.Location = new System.Drawing.Point(143, 297);
            this.Start.Name = "Start";
            this.Start.Size = new System.Drawing.Size(378, 83);
            this.Start.TabIndex = 1;
            this.Start.Text = "开始调度";
            this.Start.UseVisualStyleBackColor = true;
            this.Start.Click += new System.EventHandler(this.Start_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(152, 18);
            this.label1.TabIndex = 2;
            this.label1.Text = "输入要调度的作业";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 383);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(80, 18);
            this.label2.TabIndex = 3;
            this.label2.Text = "调度结果";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(833, 9);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(80, 18);
            this.label3.TabIndex = 4;
            this.label3.Text = "调度序列";
            // 
            // Results
            // 
            this.Results.AllowUserToAddRows = false;
            this.Results.AllowUserToDeleteRows = false;
            this.Results.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.Results.Location = new System.Drawing.Point(12, 404);
            this.Results.Name = "Results";
            this.Results.ReadOnly = true;
            this.Results.RowTemplate.Height = 30;
            this.Results.Size = new System.Drawing.Size(818, 261);
            this.Results.TabIndex = 5;
            // 
            // Flow
            // 
            this.Flow.AllowUserToAddRows = false;
            this.Flow.AllowUserToDeleteRows = false;
            this.Flow.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.Flow.Location = new System.Drawing.Point(836, 30);
            this.Flow.Name = "Flow";
            this.Flow.ReadOnly = true;
            this.Flow.RowTemplate.Height = 30;
            this.Flow.Size = new System.Drawing.Size(851, 635);
            this.Flow.TabIndex = 6;
            // 
            // TimePiece
            // 
            this.TimePiece.DecimalPlaces = 2;
            this.TimePiece.Increment = new decimal(new int[] {
            25,
            0,
            0,
            131072});
            this.TimePiece.Location = new System.Drawing.Point(15, 342);
            this.TimePiece.Maximum = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.TimePiece.Minimum = new decimal(new int[] {
            25,
            0,
            0,
            131072});
            this.TimePiece.Name = "TimePiece";
            this.TimePiece.Size = new System.Drawing.Size(120, 28);
            this.TimePiece.TabIndex = 7;
            this.TimePiece.Value = new decimal(new int[] {
            5,
            0,
            0,
            65536});
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(12, 312);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(125, 18);
            this.label4.TabIndex = 8;
            this.label4.Text = "CPU时间片长度";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(527, 312);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(116, 18);
            this.label5.TabIndex = 9;
            this.label5.Text = "平均周转时间";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(527, 362);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(152, 18);
            this.label6.TabIndex = 10;
            this.label6.Text = "平均带权周转时间";
            // 
            // AverageWeightedTime
            // 
            this.AverageWeightedTime.AutoSize = true;
            this.AverageWeightedTime.Location = new System.Drawing.Point(679, 362);
            this.AverageWeightedTime.Name = "AverageWeightedTime";
            this.AverageWeightedTime.Size = new System.Drawing.Size(0, 18);
            this.AverageWeightedTime.TabIndex = 11;
            // 
            // AverageTime
            // 
            this.AverageTime.AutoSize = true;
            this.AverageTime.Location = new System.Drawing.Point(679, 312);
            this.AverageTime.Name = "AverageTime";
            this.AverageTime.Size = new System.Drawing.Size(0, 18);
            this.AverageTime.TabIndex = 12;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 18F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1699, 715);
            this.Controls.Add(this.AverageTime);
            this.Controls.Add(this.AverageWeightedTime);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.TimePiece);
            this.Controls.Add(this.Flow);
            this.Controls.Add(this.Results);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.Start);
            this.Controls.Add(this.Processes);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.Processes)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Results)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Flow)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.TimePiece)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView Processes;
        private System.Windows.Forms.Button Start;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.DataGridView Results;
        private System.Windows.Forms.DataGridView Flow;
        private System.Windows.Forms.NumericUpDown TimePiece;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label AverageWeightedTime;
        private System.Windows.Forms.Label AverageTime;
    }
}

