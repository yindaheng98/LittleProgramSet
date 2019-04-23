using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Threading;
using System.Windows.Forms;

namespace LittleServerWithForm
{
    class ConsoleHelper : TextWriter
    {
        private System.Windows.Forms.TextBox _textBox { set; get; }
        private System.Windows.Forms.TreeView _treeViewer { set; get; }
        private System.Windows.Forms.TextBox _clients { set; get; }
        private int maxRowLenght = 200;//treeViewer中显示的最大行数，若不限制，则置为0  
        public ConsoleHelper(System.Windows.Forms.TextBox textBox,System.Windows.Forms.TreeView treeViewer, System.Windows.Forms.TextBox clients)
        {
            this._treeViewer = treeViewer;
            this._textBox = textBox;
            this._clients = clients;
            Console.SetOut(this);
        }
        public override void Write(string value)
        {
            if (value.IndexOf("客户端") == 0)//如果输出与客户端有关
            {
                TreeViewOutput(value);
            }
            else TextBoxWrite(value);
        }

        public override void WriteLine(string value)
        {
            if (value.IndexOf("客户端") == 0)//如果输出与客户端有关
            {
                this._treeViewer.Invoke(new Action(()=>TreeViewOutput(value)));
            }
            else TextBoxWriteLine(value);
        }

        private void TreeViewOutput(string value)//"客户端_[连接/离线/请求/响应]_[客户端地址]_[正文]"
        {
            string[]token = value.Split(new char[] { '_' }, 4);
            if(token[1] == "连接")
            {
                _treeViewer.Nodes.Add(token[2]);
            }
            if (token[1] == "离线")
                _treeViewer.Nodes.Add("离线：" + token[2]);
            if (token[1] == "请求" || token[1] == "响应")
            {
                TreeNode tn;
                tn = new TreeNode();
                if (token[1] == "请求")
                    tn.Name = "请求";
                else tn.Name = "响应";
                tn.Text = tn.Name + ":" + token[3];
                foreach (TreeNode node in _treeViewer.Nodes)
                {
                    if (node.Text == token[2])
                    {
                        node.Nodes.Add(tn);
                        break;
                    }
                }
            }
        }

        private void TextBoxWrite(string value)
        {
            value = value.Split('_')[1];
            if (value.IndexOf("当前客户端数量:") != -1)
            {
                _clients.Text = value.Split(':')[1];
                return;
            }
            if (_textBox.IsHandleCreated)
                _textBox.BeginInvoke(new ThreadStart(() =>
                {
                    if (maxRowLenght > 0 && _textBox.Lines.Length > maxRowLenght)
                    {
                        int strat = _textBox.GetFirstCharIndexFromLine(0);//获取第0行第一个字符的索引  
                        int end = _textBox.GetFirstCharIndexFromLine(10);
                        _textBox.Select(strat, end);//选择文本框中的文本范围  
                        _textBox.SelectedText = "";//将当前选定的文本内容置为“”  
                        _textBox.AppendText(value + " ");
                    }
                    else
                    {
                        _textBox.AppendText(value + " ");
                    }
                }));
        }

        private void TextBoxWriteLine(string value)
        {
            value = value.Split('_')[1];
            if (value.IndexOf("当前客户端数量:") != -1)
            {
                _clients.Text = value.Split(':')[1];
                return;
            }
            if (_textBox.IsHandleCreated)
                _textBox.BeginInvoke(new ThreadStart(() =>
                {
                    if (maxRowLenght > 0 && _textBox.Lines.Length > maxRowLenght)
                    {
                        int strat = _textBox.GetFirstCharIndexFromLine(0);//获取第0行第一个字符的索引  
                        int end = _textBox.GetFirstCharIndexFromLine(10);
                        _textBox.Select(strat, end);//选择文本框中的文本范围  
                        _textBox.SelectedText = "";//将当前选定的文本内容置为“”  
                        _textBox.AppendText(value + "\r\n");
                    }
                    else
                    {
                        _textBox.AppendText(value + "\r\n");
                    }
                }));
        }

        public override Encoding Encoding//这里要注意,重写wirte必须也要重写编码类型  
        {
            get { return Encoding.UTF8; }
        }
    }
}
