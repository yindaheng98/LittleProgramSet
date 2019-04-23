namespace FileTree
{
    partial class Form2
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
            this.NewFileName = new System.Windows.Forms.TextBox();
            this.NewFileType = new System.Windows.Forms.ComboBox();
            this.OK = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // NewFileName
            // 
            this.NewFileName.Location = new System.Drawing.Point(98, 6);
            this.NewFileName.Name = "NewFileName";
            this.NewFileName.Size = new System.Drawing.Size(141, 28);
            this.NewFileName.TabIndex = 0;
            // 
            // NewFileType
            // 
            this.NewFileType.FormattingEnabled = true;
            this.NewFileType.Items.AddRange(new object[] {
            "目录文件",
            "存储文件"});
            this.NewFileType.Location = new System.Drawing.Point(98, 39);
            this.NewFileType.Name = "NewFileType";
            this.NewFileType.Size = new System.Drawing.Size(141, 26);
            this.NewFileType.TabIndex = 1;
            // 
            // OK
            // 
            this.OK.Location = new System.Drawing.Point(15, 69);
            this.OK.Name = "OK";
            this.OK.Size = new System.Drawing.Size(224, 36);
            this.OK.TabIndex = 2;
            this.OK.Text = "OK";
            this.OK.UseVisualStyleBackColor = true;
            this.OK.Click += new System.EventHandler(this.OK_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(62, 18);
            this.label1.TabIndex = 3;
            this.label1.Text = "文件名";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 42);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(80, 18);
            this.label2.TabIndex = 4;
            this.label2.Text = "文件类型";
            // 
            // Form2
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 18F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(252, 121);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.OK);
            this.Controls.Add(this.NewFileType);
            this.Controls.Add(this.NewFileName);
            this.Name = "Form2";
            this.Text = "新建";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox NewFileName;
        private System.Windows.Forms.ComboBox NewFileType;
        private System.Windows.Forms.Button OK;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
    }
}