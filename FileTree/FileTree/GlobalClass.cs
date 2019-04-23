using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace FileTree
{
    class GlobalClass
    {
        public static FileSystem fs;

        public static void test()
        {
            fs.NewFile("root", "aaa", FileType.Index);
            fs.NewFile("root", "bbb", FileType.Index);
            fs.NewFile("root/bbb", "ccc", FileType.Storage);
            fs.NewFile("root", "ccc", FileType.Index);
            fs.NewFile("root/ccc", "ccc", FileType.Index);
            fs.NewFile("root/ccc/ccc", "ddd", FileType.Storage);
            //fs.DeleteFile("root/ccc/ccc/ddd");
            fs.Open("root/ccc/ccc/ddd");
            fs.Write("root/ccc/ccc/ddd", "Hello World");
            Console.WriteLine(fs.Read("root/ccc/ccc/ddd"));
            fs.Close("root/ccc/ccc/ddd");

            fs.CutFromTo("root/ccc/ccc/ddd", "root/bbb");
        }
        public static string getPath(TreeNode filenode)
        {
            if (filenode.Parent != null)
                return getPath(filenode.Parent) + "/" + filenode.Name;
            else return filenode.Name;
        }
    }
}
