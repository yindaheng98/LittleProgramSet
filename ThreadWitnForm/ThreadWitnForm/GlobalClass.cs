using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Data;

namespace ThreadWitnForm
{
    class GlobalClass
    {
        [DllImport(@"../../../Release/DLLs.dll", EntryPoint = "INIT")]//, SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.StdCall)]
        extern static void INIT(int num, int[,] initdata);//int initdata[][2]
        [DllImport(@"../../../Release/DLLs.dll", EntryPoint = "RUN")]
        extern static void RUN(int[,] status);//int status[][5]
        [DllImport(@"../../../Release/DLLs.dll", EntryPoint = "ISFINISH")]
        extern static void ISFINISH(ref bool isf);

        public static DataTable InitData;
        public static DataTable RunningData;
        public static DataTable ReadyData;
        public static DataTable FinishData;

        public static void InitProgram()
        {
            InitData = new DataTable();
            RunningData = new DataTable();
            ReadyData = new DataTable();
            FinishData = new DataTable();

            InitData.Columns.Add("进程名", typeof(string));
            InitData.Columns.Add("进程优先数", typeof(int));
            InitData.Columns.Add("预计运行时间片", typeof(int));

            RunningData.Columns.Add("进程名", typeof(string));
            RunningData.Columns.Add("进程优先数", typeof(int));
            RunningData.Columns.Add("预计运行时间片", typeof(int));
            RunningData.Columns.Add("已运行时间片", typeof(int));

            ReadyData.Columns.Add("进程名", typeof(string));
            ReadyData.Columns.Add("进程优先数", typeof(int));
            ReadyData.Columns.Add("预计运行时间片", typeof(int));
            ReadyData.Columns.Add("已运行时间片", typeof(int));

            FinishData.Columns.Add("进程名", typeof(string));
            FinishData.Columns.Add("进程优先数", typeof(int));
            FinishData.Columns.Add("预计运行时间片", typeof(int));
            FinishData.Columns.Add("已运行时间片", typeof(int));
        }

        public static string[] Names;//名字
        public static int[,] Init;//初始化数据
        public static int[,] Status;//状态矩阵

        public static void ReadInitData()
        {
            Status = new int[InitData.Rows.Count, 5];
            Names = new string[InitData.Rows.Count];
            Init = new int[InitData.Rows.Count, 2];//状态数据只有两列
            for (int i = 0; i < InitData.Rows.Count; i++)
            {
                DataRow dr = InitData.Rows[i];
                Names[i] = dr[0].ToString();
                for (int j = 1; j < 3; j++)//数据表格只有三列
                {
                    Init[i, j - 1] = int.Parse(dr[j].ToString());
                }
            }
            INIT(InitData.Rows.Count, Init);
            //将Init数据输入C++函数进行初始化
        }

        public static void Run1s()
        {
            RUN(Status);
            ReadStatus(ref Status);
            //运行C++中的运行一个时间片函数并修改datatable
        }
        
        public static void ReadStatus(ref int[,] status)
        {
            InitData.Rows.Clear();
            RunningData.Rows.Clear();
            ReadyData.Rows.Clear();
            FinishData.Rows.Clear();
            for (int i = 0; i < status.GetLength(0); i++)//一行一行操作
            {
                if (status[i, 0] == 1)
                    ArrayAddToDataTable(getArray(status, i), ref RunningData);
                else if (status[i, 0] == 0)
                    ArrayAddToDataTable(getArray(status, i), ref ReadyData);
                else if (status[i, 0] == -1)
                    ArrayAddToDataTable(getArray(status, i), ref FinishData);
            }
        }

        public static int[] getArray(int[,] matrix, int i)
        {
            int[] array = new int[matrix.GetLength(1)];
            for (int j = 0; j < matrix.GetLength(1); j++)
                array[j] = matrix[i, j];
            return array;
        }

        public static void ArrayAddToDataTable(int[] array, ref DataTable dt)
        {
            DataRow dr = dt.NewRow();
            dr[0] = Names[array[1]];
            dr[1] = array[2];
            dr[2] = array[3];
            dr[3] = array[4];
            dt.Rows.Add(dr);
        }
    }
}


/*数据表操作参考
DataRow dr = GlobalClass.InitData.NewRow();
dr[0] = "aaa";
dr[1] = 1;
dr[2] = 2;
GlobalClass.InitData.Rows.Add(dr);
//GlobalClass.InitData.Clear();
GlobalClass.InitData.Rows.Clear();
//GlobalClass.InitData.AcceptChanges();
//InitData.DataSource = GlobalClass.InitData;
*/
/*函数使用方略
 * string[] names = { "a", "b", "c" };
            int[,] mt = { { 2, 3 }, { 4, 6 }, { 1, 7 } };
            GlobalClass.MatrixToDataTable(ref names, ref mt, ref GlobalClass.InitData);
            */
