namespace ThreadWitnForm
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
            this.InitData = new System.Windows.Forms.DataGridView();
            this.Start = new System.Windows.Forms.Button();
            this.RunningData = new System.Windows.Forms.DataGridView();
            this.Run1s = new System.Windows.Forms.Button();
            this.ReadyData = new System.Windows.Forms.DataGridView();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.FinishData = new System.Windows.Forms.DataGridView();
            this.label4 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.InitData)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.RunningData)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ReadyData)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.FinishData)).BeginInit();
            this.SuspendLayout();
            // 
            // InitData
            // 
            this.InitData.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.InitData.Location = new System.Drawing.Point(13, 81);
            this.InitData.Name = "InitData";
            this.InitData.RowTemplate.Height = 30;
            this.InitData.Size = new System.Drawing.Size(517, 630);
            this.InitData.TabIndex = 0;
            // 
            // Start
            // 
            this.Start.Location = new System.Drawing.Point(12, 12);
            this.Start.Name = "Start";
            this.Start.Size = new System.Drawing.Size(517, 44);
            this.Start.TabIndex = 1;
            this.Start.Text = "调度初始化";
            this.Start.UseVisualStyleBackColor = true;
            this.Start.Click += new System.EventHandler(this.Start_Click);
            // 
            // RunningData
            // 
            this.RunningData.AllowUserToAddRows = false;
            this.RunningData.AllowUserToDeleteRows = false;
            this.RunningData.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.RunningData.Location = new System.Drawing.Point(535, 81);
            this.RunningData.Name = "RunningData";
            this.RunningData.ReadOnly = true;
            this.RunningData.RowTemplate.Height = 30;
            this.RunningData.Size = new System.Drawing.Size(666, 154);
            this.RunningData.TabIndex = 2;
            // 
            // Run1s
            // 
            this.Run1s.Location = new System.Drawing.Point(535, 12);
            this.Run1s.Name = "Run1s";
            this.Run1s.Size = new System.Drawing.Size(666, 44);
            this.Run1s.TabIndex = 3;
            this.Run1s.Text = "运行+1s";
            this.Run1s.UseVisualStyleBackColor = true;
            this.Run1s.Click += new System.EventHandler(this.Run1s_Click);
            // 
            // ReadyData
            // 
            this.ReadyData.AllowUserToAddRows = false;
            this.ReadyData.AllowUserToDeleteRows = false;
            this.ReadyData.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.ReadyData.Location = new System.Drawing.Point(536, 259);
            this.ReadyData.Name = "ReadyData";
            this.ReadyData.ReadOnly = true;
            this.ReadyData.RowTemplate.Height = 30;
            this.ReadyData.Size = new System.Drawing.Size(666, 214);
            this.ReadyData.TabIndex = 4;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(13, 60);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(98, 18);
            this.label1.TabIndex = 5;
            this.label1.Text = "初始化数据";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(536, 60);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(80, 18);
            this.label2.TabIndex = 6;
            this.label2.Text = "运行队列";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(536, 238);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(80, 18);
            this.label3.TabIndex = 7;
            this.label3.Text = "就绪队列";
            // 
            // FinishData
            // 
            this.FinishData.AllowUserToAddRows = false;
            this.FinishData.AllowUserToDeleteRows = false;
            this.FinishData.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.FinishData.Location = new System.Drawing.Point(535, 497);
            this.FinishData.Name = "FinishData";
            this.FinishData.ReadOnly = true;
            this.FinishData.RowTemplate.Height = 30;
            this.FinishData.Size = new System.Drawing.Size(666, 214);
            this.FinishData.TabIndex = 8;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(536, 476);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(80, 18);
            this.label4.TabIndex = 9;
            this.label4.Text = "完成队列";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 18F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1218, 723);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.FinishData);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.ReadyData);
            this.Controls.Add(this.Run1s);
            this.Controls.Add(this.RunningData);
            this.Controls.Add(this.Start);
            this.Controls.Add(this.InitData);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.InitData)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.RunningData)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ReadyData)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.FinishData)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView InitData;
        private System.Windows.Forms.Button Start;
        private System.Windows.Forms.DataGridView RunningData;
        private System.Windows.Forms.Button Run1s;
        private System.Windows.Forms.DataGridView ReadyData;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.DataGridView FinishData;
        private System.Windows.Forms.Label label4;
    }
}

