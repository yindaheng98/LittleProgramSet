using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace FileTree
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            GlobalClass.fs = new FileSystem();
            GlobalClass.fs.Show(FileTree);


            //测试用
            GlobalClass.test();
            GlobalClass.fs.Show(FileTree);
        }

        private void New_Click(object sender, EventArgs e)
        {
            if (FileTree.SelectedNode == null)
            {
                MessageBox.Show("请选择节点");
                return;
            }
            string path=GlobalClass.getPath(FileTree.SelectedNode);
            try
            {
                GlobalClass.fs.SetNewFilePath(path);
                Form2 form=new Form2();
                form.ShowDialog();
                GlobalClass.fs.CreateNewFile();
                GlobalClass.fs.Show(FileTree);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void Delete_Click(object sender, EventArgs e)
        {
            if (FileTree.SelectedNode == null)
            {
                MessageBox.Show("请选择节点");
                return;
            }
            string path = GlobalClass.getPath(FileTree.SelectedNode);
            try
            {
                GlobalClass.fs.DeleteFile(path);
                GlobalClass.fs.Show(FileTree);
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);

            }

        }

        private void Open_Click(object sender, EventArgs e)
        {
            if (FileTree.SelectedNode == null)
            {
                MessageBox.Show("请选择节点");
                return;
            }
            string path = GlobalClass.getPath(FileTree.SelectedNode);
            try
            {
                GlobalClass.fs.Open(path);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);

            }
        }

        private void Close_Click(object sender, EventArgs e)
        {
            if (FileTree.SelectedNode == null)
            {
                MessageBox.Show("请选择节点");
                return;
            }
            string path = GlobalClass.getPath(FileTree.SelectedNode);
            try
            {
                GlobalClass.fs.Close(path);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void Read_Click(object sender, EventArgs e)
        {
            if (FileTree.SelectedNode == null)
            {
                MessageBox.Show("请选择节点");
                return;
            }
            string path = GlobalClass.getPath(FileTree.SelectedNode);
            try
            {
                FileContent.Text = GlobalClass.fs.Read(path);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void Write_Click(object sender, EventArgs e)
        {
            if (FileTree.SelectedNode == null)
            {
                MessageBox.Show("请选择节点");
                return;
            }
            string path = GlobalClass.getPath(FileTree.SelectedNode);
            try
            {
                GlobalClass.fs.Write(path, FileContent.Text);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void Cut_Click(object sender, EventArgs e)
        {
            if (FileTree.SelectedNode == null)
            {
                MessageBox.Show("请选择节点");
                return;
            }
            string path = GlobalClass.getPath(FileTree.SelectedNode);
            try
            {
                GlobalClass.fs.SetCutFile(path);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void Copy_Click(object sender, EventArgs e)
        {
            if (FileTree.SelectedNode == null)
            {
                MessageBox.Show("请选择节点");
                return;
            }
            string path = GlobalClass.getPath(FileTree.SelectedNode);
            try
            {
                GlobalClass.fs.SetCopyFile(path);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void Paste_Click(object sender, EventArgs e)
        {
            if (FileTree.SelectedNode == null)
            {
                MessageBox.Show("请选择节点");
                return;
            }
            string path = GlobalClass.getPath(FileTree.SelectedNode);
            try
            {
                GlobalClass.fs.Paste(path);
                GlobalClass.fs.Show(FileTree);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
    }
}
