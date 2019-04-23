namespace BankWithForm
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
            this.Threadsnum = new System.Windows.Forms.NumericUpDown();
            this.Sourcesnum = new System.Windows.Forms.NumericUpDown();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.OK_button = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.Threadsnum)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Sourcesnum)).BeginInit();
            this.SuspendLayout();
            // 
            // Threadsnum
            // 
            this.Threadsnum.Location = new System.Drawing.Point(80, 7);
            this.Threadsnum.Name = "Threadsnum";
            this.Threadsnum.Size = new System.Drawing.Size(120, 28);
            this.Threadsnum.TabIndex = 0;
            // 
            // Sourcesnum
            // 
            this.Sourcesnum.Location = new System.Drawing.Point(80, 49);
            this.Sourcesnum.Name = "Sourcesnum";
            this.Sourcesnum.Size = new System.Drawing.Size(120, 28);
            this.Sourcesnum.TabIndex = 1;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(62, 18);
            this.label1.TabIndex = 2;
            this.label1.Text = "进程数";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 49);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(62, 18);
            this.label2.TabIndex = 3;
            this.label2.Text = "资源数";
            // 
            // OK_button
            // 
            this.OK_button.Location = new System.Drawing.Point(12, 83);
            this.OK_button.Name = "OK_button";
            this.OK_button.Size = new System.Drawing.Size(188, 43);
            this.OK_button.TabIndex = 4;
            this.OK_button.Text = "OK";
            this.OK_button.UseVisualStyleBackColor = true;
            this.OK_button.Click += new System.EventHandler(this.OK_button_Click);
            // 
            // Form2
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 18F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(210, 139);
            this.Controls.Add(this.OK_button);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.Sourcesnum);
            this.Controls.Add(this.Threadsnum);
            this.Name = "Form2";
            this.Text = "Form2";
            ((System.ComponentModel.ISupportInitialize)(this.Threadsnum)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Sourcesnum)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.NumericUpDown Threadsnum;
        private System.Windows.Forms.NumericUpDown Sourcesnum;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button OK_button;
    }
}