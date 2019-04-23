namespace FileTree
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
            this.FileTree = new System.Windows.Forms.TreeView();
            this.FileContent = new System.Windows.Forms.RichTextBox();
            this.New = new System.Windows.Forms.Button();
            this.Delete = new System.Windows.Forms.Button();
            this.Open = new System.Windows.Forms.Button();
            this.Close = new System.Windows.Forms.Button();
            this.Read = new System.Windows.Forms.Button();
            this.Write = new System.Windows.Forms.Button();
            this.Cut = new System.Windows.Forms.Button();
            this.Copy = new System.Windows.Forms.Button();
            this.Paste = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // FileTree
            // 
            this.FileTree.Location = new System.Drawing.Point(12, 12);
            this.FileTree.Name = "FileTree";
            this.FileTree.Size = new System.Drawing.Size(400, 493);
            this.FileTree.TabIndex = 0;
            // 
            // FileContent
            // 
            this.FileContent.Location = new System.Drawing.Point(12, 511);
            this.FileContent.Name = "FileContent";
            this.FileContent.Size = new System.Drawing.Size(400, 178);
            this.FileContent.TabIndex = 1;
            this.FileContent.Text = "";
            // 
            // New
            // 
            this.New.Location = new System.Drawing.Point(418, 12);
            this.New.Name = "New";
            this.New.Size = new System.Drawing.Size(136, 54);
            this.New.TabIndex = 2;
            this.New.Text = "新建";
            this.New.UseVisualStyleBackColor = true;
            this.New.Click += new System.EventHandler(this.New_Click);
            // 
            // Delete
            // 
            this.Delete.Location = new System.Drawing.Point(418, 72);
            this.Delete.Name = "Delete";
            this.Delete.Size = new System.Drawing.Size(136, 54);
            this.Delete.TabIndex = 3;
            this.Delete.Text = "删除";
            this.Delete.UseVisualStyleBackColor = true;
            this.Delete.Click += new System.EventHandler(this.Delete_Click);
            // 
            // Open
            // 
            this.Open.Location = new System.Drawing.Point(418, 312);
            this.Open.Name = "Open";
            this.Open.Size = new System.Drawing.Size(136, 92);
            this.Open.TabIndex = 4;
            this.Open.Text = "打开";
            this.Open.UseVisualStyleBackColor = true;
            this.Open.Click += new System.EventHandler(this.Open_Click);
            // 
            // Close
            // 
            this.Close.Location = new System.Drawing.Point(418, 413);
            this.Close.Name = "Close";
            this.Close.Size = new System.Drawing.Size(136, 92);
            this.Close.TabIndex = 5;
            this.Close.Text = "关闭";
            this.Close.UseVisualStyleBackColor = true;
            this.Close.Click += new System.EventHandler(this.Close_Click);
            // 
            // Read
            // 
            this.Read.Location = new System.Drawing.Point(418, 511);
            this.Read.Name = "Read";
            this.Read.Size = new System.Drawing.Size(136, 86);
            this.Read.TabIndex = 6;
            this.Read.Text = "读出";
            this.Read.UseVisualStyleBackColor = true;
            this.Read.Click += new System.EventHandler(this.Read_Click);
            // 
            // Write
            // 
            this.Write.Location = new System.Drawing.Point(418, 603);
            this.Write.Name = "Write";
            this.Write.Size = new System.Drawing.Size(136, 86);
            this.Write.TabIndex = 7;
            this.Write.Text = "写入";
            this.Write.UseVisualStyleBackColor = true;
            this.Write.Click += new System.EventHandler(this.Write_Click);
            // 
            // Cut
            // 
            this.Cut.Location = new System.Drawing.Point(418, 132);
            this.Cut.Name = "Cut";
            this.Cut.Size = new System.Drawing.Size(136, 54);
            this.Cut.TabIndex = 8;
            this.Cut.Text = "剪切";
            this.Cut.UseVisualStyleBackColor = true;
            this.Cut.Click += new System.EventHandler(this.Cut_Click);
            // 
            // Copy
            // 
            this.Copy.Location = new System.Drawing.Point(418, 192);
            this.Copy.Name = "Copy";
            this.Copy.Size = new System.Drawing.Size(136, 54);
            this.Copy.TabIndex = 9;
            this.Copy.Text = "复制";
            this.Copy.UseVisualStyleBackColor = true;
            this.Copy.Click += new System.EventHandler(this.Copy_Click);
            // 
            // Paste
            // 
            this.Paste.Location = new System.Drawing.Point(418, 252);
            this.Paste.Name = "Paste";
            this.Paste.Size = new System.Drawing.Size(136, 54);
            this.Paste.TabIndex = 10;
            this.Paste.Text = "粘贴";
            this.Paste.UseVisualStyleBackColor = true;
            this.Paste.Click += new System.EventHandler(this.Paste_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 18F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(566, 701);
            this.Controls.Add(this.Paste);
            this.Controls.Add(this.Copy);
            this.Controls.Add(this.Cut);
            this.Controls.Add(this.Write);
            this.Controls.Add(this.Read);
            this.Controls.Add(this.Close);
            this.Controls.Add(this.Open);
            this.Controls.Add(this.Delete);
            this.Controls.Add(this.New);
            this.Controls.Add(this.FileContent);
            this.Controls.Add(this.FileTree);
            this.Name = "Form1";
            this.Text = "FileSystem";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TreeView FileTree;
        private System.Windows.Forms.RichTextBox FileContent;
        private System.Windows.Forms.Button New;
        private System.Windows.Forms.Button Delete;
        private System.Windows.Forms.Button Open;
        private System.Windows.Forms.Button Close;
        private System.Windows.Forms.Button Read;
        private System.Windows.Forms.Button Write;
        private System.Windows.Forms.Button Cut;
        private System.Windows.Forms.Button Copy;
        private System.Windows.Forms.Button Paste;
    }
}

