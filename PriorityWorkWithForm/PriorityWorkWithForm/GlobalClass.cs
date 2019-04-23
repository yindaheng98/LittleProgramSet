using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data;

namespace PriorityWorkWithForm
{
    class GlobalClass
    {
        static private string[] Names;
        static public DataTable Processes;
        static public DataTable Results;
        static public DataTable Flow;
        static public double ATT;
        static public double AWTT;

        static public void Init()
        {
            Processes = new DataTable();
            Processes.Columns.Add("作业名", typeof(string));
            Processes.Columns.Add("到达时间", typeof(double));
            Processes.Columns.Add("预计占用CPU时间", typeof(double));
            Processes.Columns.Add("预计I/O时间", typeof(double));
            Processes.Columns.Add("优先数", typeof(int));

            Results = new DataTable();
            Results.Columns.Add("作业名", typeof(string));
            Results.Columns.Add("开始运行时间", typeof(double));
            Results.Columns.Add("结束运行时间", typeof(double));
            Results.Columns.Add("周转时间", typeof(double));
            Results.Columns.Add("带权周转时间", typeof(double));

            Flow = new DataTable();
            Flow.Columns.Add("时间片", typeof(double));
            Flow.Columns.Add("运行作业名", typeof(string));
            Flow.Columns.Add("该进程已运行时间", typeof(double));
            Flow.Columns.Add("该进程剩余运行时间", typeof(double));
            Flow.Columns.Add("进程状态", typeof(string));
        }

        static public void Run(double timepiece = 0.5)
        {
            ReadInput(timepiece);
            GetOutput();
        }



        static private void ReadInput(double timepiece=0.5)
        {
            int processesnum = Processes.Rows.Count;//读取作业数量
            Names = new string[processesnum];//新建作业名列表
            double[,] processinfo = new double[processesnum, 4];//新建作业信息矩阵
            for (int i = 0; i < processesnum; i++)//循环读取作业信息
            {
                DataRow dr = Processes.Rows[i];
                Names[i] = dr[0].ToString();
                processinfo[i, 0] = double.Parse(dr[1].ToString());
                processinfo[i, 1] = double.Parse(dr[2].ToString());
                processinfo[i, 2] = double.Parse(dr[3].ToString());
                processinfo[i, 3] = double.Parse(dr[4].ToString());
            }
            PriorityCore.Run(processinfo, timepiece);
        }

        static private void GetOutput()
        {
            int processesnum = PriorityCore.result.GetLength(0);//读取作业数量
            Results.Clear();//清空结果表
            for(int i=0;i<processesnum;i++)//循环读取结果表
            {
                DataRow dr = Results.NewRow();
                dr[0] = Names[i];
                dr[1] = PriorityCore.result[i, 0];
                dr[2] = PriorityCore.result[i, 1];
                dr[3] = PriorityCore.result[i, 2];
                dr[4] = PriorityCore.result[i, 3];
                Results.Rows.Add(dr);
            }

            int flownum = PriorityCore.Workingflow_ID.Length;//读取流程长度
            Flow.Clear();//清空流程表
            for(int i=0;i<flownum;i++)//循环读取流程
            {
                DataRow dr = Flow.NewRow();
                dr[0] = PriorityCore.Workingflow_Info[i, 0];
                dr[1] = Names[PriorityCore.Workingflow_ID[i]];
                dr[2] = PriorityCore.Workingflow_Info[i, 1];
                dr[3] = PriorityCore.Workingflow_Info[i, 2];
                dr[4] = PriorityCore.Workingflow_Info[i, 3] > 0 ? "已完成" : "未完成";
                Flow.Rows.Add(dr);
            }

            ATT = PriorityCore.AverageTurnaroundTime;
            AWTT = PriorityCore.AverageWeightedTurnaroundTime;
            //读取平均周转时间
        }
    }
}
