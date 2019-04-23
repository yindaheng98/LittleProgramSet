using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace PriorityWorkWithForm
{
    class PriorityCore
    {
        static private double timepiece;
        static private double CPUmaxtime;
        static private bool isRun=false;//是否已运行
        static private double[,] _result;
        static private int[] _Workingflow_ID;
        static private double[,] _Workingflow_Info;
        static private double _ATT;
        static private double _AWTT;

        static public double[,] result//开始/结束/周转/带权周转
        {
            get
            {
                if (!isRun) throw new Exception("算法未运行");
                return _result;
            }
        }
        static public int[] Workingflow_ID//作业调度ID流
        {
            get
            {
                if (!isRun) throw new Exception("算法未运行");
                return _Workingflow_ID;
            }
        }
        static public double[,] Workingflow_Info//当前时间片/已运行时间/剩余时间/是否完成(完成为1，未完成为-1)
        {
            get
            {
                if (!isRun) throw new Exception("算法未运行");
                return _Workingflow_Info;
            }
        }

        static public double AverageTurnaroundTime//平均周转时间
        {
            get
            {
                return _ATT;
            }
        }
        static public double AverageWeightedTurnaroundTime//平均带权周转时间
        {
            get
            {
                return _AWTT;
            }
        }


        static public void Run(double[,] processinfo,double tp=0.5)//作业数，到达时间/CPU时间/IO时间/优先级，时间片长度
        {
            CPUmaxtime = 10;
            timepiece = tp;
            int processnum = processinfo.GetLength(0);
            if (processinfo.GetLength(1) != 4) throw new Exception("输入的进程信息有误");
            SetTimePiece(timepiece);
            SetCPUMaxtime(CPUmaxtime);
            Init(processnum, processinfo);
            isRun = false;
            Priority();
            isRun = true;
            ReadResult(processnum);
        }

        static private void ReadResult(int processnum)
        {
            _result = new double[processnum, 4];
            GetResult(_result);
            CalculateTurnaroundTimes();
            int WorkFlowLength = GetPathLength();
            _Workingflow_ID = new int[WorkFlowLength];
            double[,] Info = new double[WorkFlowLength, 3];
            int[] isFinish = new int[WorkFlowLength];
            GetWorkingPath(_Workingflow_ID, isFinish, Info);
            _Workingflow_Info = new double[WorkFlowLength, 4];
            for (int i = 0; i < WorkFlowLength; i++)
            {
                _Workingflow_Info[i, 0] = Info[i, 0];
                _Workingflow_Info[i, 1] = Info[i, 1];
                _Workingflow_Info[i, 2] = Info[i, 2];
                _Workingflow_Info[i, 3] = isFinish[i] == 0 ? -1 : 1;
            }
        }

        static private void CalculateTurnaroundTimes()
        {
            _ATT = _AWTT = 0;
            int processnum = _result.GetLength(0);
            for (int i=0;i< processnum; i++)
            {
                _ATT += _result[i, 2];
                _AWTT += _result[i, 3];
            }
            _ATT /= processnum;
            _AWTT /= processnum;
        }

        [DllImport(@"../../../Release/PriorityDll.dll", EntryPoint = "SetTimePiece")]
        extern static private void SetTimePiece(double timepiece);
        //设定时间片大小

        [DllImport(@"../../../Release/PriorityDll.dll", EntryPoint = "SetCPUMaxtime")]
        extern static private void SetCPUMaxtime(double maxtime);
        //设定CPU时间

        [DllImport(@"../../../Release/PriorityDll.dll", EntryPoint = "Init")]
        extern static private void Init(int nn, double[,] processes);
        //初始化作业块：process[]到达时间/CPU时间/IO时间/优先级，n：作业数量

        [DllImport(@"../../../Release/PriorityDll.dll", EntryPoint = "Priority")]
        extern static private void Priority();
        //运行出结果

        [DllImport(@"../../../Release/PriorityDll.dll", EntryPoint = "GetPathLength")]
        extern static private int GetPathLength();
        //获取工作路径长度

        [DllImport(@"../../../Release/PriorityDll.dll", EntryPoint = "GetResult")]
        extern static private void GetResult(double[,] res);
        //开始/结束/周转/带权周转

        [DllImport(@"../../../Release/PriorityDll.dll", EntryPoint = "GetWorkingPath")]
        extern static private void GetWorkingPath(int[] ID, int[] isFinish, double[,] info);
        //ID，是否完成，当前时间片/已运行时间/剩余时间


    }
}
