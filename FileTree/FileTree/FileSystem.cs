using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace FileTree
{
    class FileSystem
    {
        static private File root;//根目录是静态变量，多个线程共享
        private List<string> OpenList;//记录进程打开了哪些文件

        private string FileToPaste;//要拷贝或者剪切的文件路径
        private bool CutOrCopy;//拷贝还是剪切

        private bool isCreating;//正在新建吗
        private string IndexToNew;//在哪新建
        private string NewFileName;//新文件名
        private FileType NewFileType;//新文件类型

        public FileSystem()//初始化文件系统
        {
            root = new File("root", FileType.Index);
            OpenList = new List<string>();
        }

        private File Find(string pathstr)//查找文件//返回值为引用？
        {
            string[] path = pathstr.Split(new char[] { '/' }, StringSplitOptions.RemoveEmptyEntries);
            File file = root;
            for (int i = 1; i < path.Length; i++)
                file = file.Find(path[i]);
            return file;
        }

        public void NewFile(string pathstr, string fname, FileType ftype)//在pathstr路径下新建文件
        {
            Find(pathstr).NewFile(fname, ftype);
        }

        private void CopyFile(string pathstr, File f)//将文件f拷贝到pathstr路径下
        {
            Find(pathstr).CopyFile(f);
        }

        public void CopyFromTo(string frompath, string topath)
        {
            CopyFile(topath, Find(frompath));
        }

        public void DeleteFile(string pathstr)//删除指定文件
        {
            string[] path = pathstr.Split(new char[] { '/' }, StringSplitOptions.RemoveEmptyEntries);
            File file = root;
            for (int i = 1; i < path.Length - 1; i++)//找他的上一级目录
                file = file.Find(path[i]);
            file.DeleteFile(path[path.Length - 1]);//在他的上一级目录调用删除
        }

        public void CutFromTo(string frompath, string topath)
        {
            CopyFromTo(frompath, topath);
            DeleteFile(frompath);
        }

        public void Open(string pathstr)//打开文件//仅用于read和write之前
        {
            Find(pathstr).Open();//打开文件
            OpenList.Add(pathstr);//记入打开列表
        }

        public void Close(string pathstr)//关闭文件//仅用于read和write之后
        {
            if (!OpenList.Contains(pathstr)) throw new Exception("未打开此文件");//检查是否打开
            Find(pathstr).Close();//关闭
            OpenList.Remove(pathstr);//从打开列表中删除
        }

        public string Read(string pathstr)//读
        {
            if (!OpenList.Contains(pathstr)) throw new Exception("未打开此文件");//检查是否打开
            return Find(pathstr).Read();
        }

        public void Write(string pathstr, string content)//写
        {
            if (!OpenList.Contains(pathstr)) throw new Exception("未打开此文件");//检查是否打开
            Find(pathstr).Write(content);
        }

        public void Rename(string pathstr, string newname)//重命名
        {
            File temp = new File(newname, Find(pathstr));//生成该文件的重命名副本
            DeleteFile(pathstr);//删除该文件
            string[] path = pathstr.Split(new char[] { '/' }, StringSplitOptions.RemoveEmptyEntries);
            pathstr = "";
            for (int i = 0; i < path.Length - 1; i++)
                pathstr += path[i] + "/";//去除路径中的最后一项
            CopyFile(pathstr, temp);//再拷贝来的副本复制回去
        }

        public void SetCutFile(string path)
        {
            FileToPaste = path;
            CutOrCopy = false;
        }

        public void SetCopyFile(string path)
        {
            FileToPaste = path;
            CutOrCopy = true;
        }

        public void Paste(string path)
        {
            if (CutOrCopy) CopyFromTo(FileToPaste, path);
            else CutFromTo(FileToPaste, path);
        }

        public void SetNewFilePath(string path)
        {
            if (Find(path).Type != FileType.Index) throw new Exception("此文件不是目录文件");
            IndexToNew = path;
        }

        public void SetNewFile(string name,FileType type)
        {
            NewFileName = name;
            NewFileType = type;
            isCreating = true;
        }

        public void CreateNewFile()
        {
            if (!isCreating) throw new Exception("请指定新的文件名和文件类型");
            NewFile(IndexToNew, NewFileName, NewFileType);
            isCreating = false;
        }

        public void Show(TreeView FileTree)
        {
            FileTree.Nodes.Clear();
            FileTree.Nodes.Add(root.CreateNode());
        }
    }
}
