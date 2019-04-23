using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace FileTree
{
    enum FileType { Index, Storage };
    class File
    {
        private string _Name;//文件名--只读
        public string Name
        {
            get
            {
                return _Name;
            }
        }
        private FileType _Type;//文件类型:目录文件/存储文件--只读
        public FileType Type
        {
            get
            {
                return _Type;
            }
        }
        private List<File> _Files;//子文件目录，get是引用，set是深拷贝
        public List<File> Files
        {
            set
            {
                if (Type != FileType.Index) throw new Exception("此文件不是目录文件");
                foreach (File f in value)//只有目录文件可以操作Files
                    _Files.Add(new File(f));//这里深拷贝源文件
            }
            get
            {
                if (Type != FileType.Index) throw new Exception("此文件不是目录文件");
                return _Files;//只有目录文件可以操作Files
            }
        }
        private bool isOpen;//是否打开
        private string Content;//存储内容

        public File(string name, FileType type)//文件初始化
        {
            if (name.IndexOf("/") != -1 || name == "") throw new Exception("文件名不合法");
            _Name = name;
            _Type = type;
            isOpen = false;
            _Files = new List<File>();
        }
        public File(File file)//文件复制
        {
            _Name = file.Name;
            _Type = file.Type;
            isOpen = false;
            _Files = new List<File>();
            if (Type == FileType.Index)
                foreach (File f in file.Files)
                    Files.Add(new File(f));
            else
            {
                file.Open();
                Content = file.Read();
                file.Close();//打开-读取-关闭
            }
        }
        public File(string newname, File file)//文件重命名所用的构造函数(生成一个重命名后的副本)
        {
            _Name = newname;
            _Type = file.Type;
            isOpen = false;
            _Files = new List<File>();
            if (Type == FileType.Index)
                foreach (File f in file.Files)
                    Files.Add(new File(f));
            else
            {
                file.Open();
                Content = file.Read();
                file.Close();//打开-读取-关闭
            }
        }


        public void Open()
        {
            if (Type != FileType.Storage) throw new Exception("此文件不是存储文件");
            if (isOpen) throw new Exception("文件已被占用");
            isOpen = true;
        }
        public void Close()
        {
            if (Type != FileType.Storage) throw new Exception("此文件不是存储文件");
            if (!isOpen) throw new Exception("文件未被打开");
            isOpen = false;
        }

        public void Write(string content)//写入内容
        {
            if (Type != FileType.Storage) throw new Exception("此文件不是存储文件");
            if (!isOpen) throw new Exception("文件未打开");
            Content = content;
        }
        public string Read()//读取内容
        {
            if (Type != FileType.Storage) throw new Exception("此文件不是存储文件");
            if (!isOpen) throw new Exception("文件未打开");
            return Content;
        }

        public void NewFile(string fname, FileType ftype)//在此目录下新建文件
        {
            if (Type != FileType.Index) throw new Exception("此文件不是目录文件");
            foreach (File f in Files)
                if (f.Name == fname)//如果有重名的文件则报错
                    throw new Exception("文件已存在");
            Files.Add(new File(fname, ftype));
        }

        public void CopyFile(File file)//复制文件到此处
        {
            if (Type != FileType.Index) throw new Exception("此文件不是目录文件");
            foreach (File f in Files)
                if (f.Name == file.Name)//如果有重名的文件则报错
                    throw new Exception("文件已存在");
            Files.Add(new File(file));
        }

        public void DeleteFile(string fname)//从此文件夹删除名为fname的文件
        {
            if (Type != FileType.Index) throw new Exception("此文件不是目录文件");
            foreach (File f in Files)
                if (f.Name == fname)//找到这个文件
                {
                    f.Clear();//先将子文件夹清空
                    Files.Remove(f);//再删除
                    return;
                }
            throw new Exception("文件不存在");
        }

        private void Clear()//清空文件夹
        {
            if (Type == FileType.Index)
            {
                foreach (File f in Files)//全部清空
                {
                    if (f.Type == FileType.Storage)//如果是存储文件
                        f.Open();//检查文件是否被占用
                    else
                        f.Clear();
                }
                Files.Clear();//删
            }
        }

        public File Find(string fname)//在此目录下查找文件//返回值为引用？
        {
            if (Type != FileType.Index) throw new Exception("此文件不是目录文件");
            foreach (File f in Files)
                if (f.Name == fname)
                {
                    return f;
                }
            throw new Exception("文件不存在");
        }

        public TreeNode CreateNode()
        {
            TreeNode node = new TreeNode();
            node.Name = Name;
            node.Text = "存储文件"+ Name;
            if (Type == FileType.Index)
            {
                node.Text = "目录文件" + Name;
                foreach (File f in Files)
                    node.Nodes.Add(f.CreateNode());
            }
            return node;
        }
    }
}
