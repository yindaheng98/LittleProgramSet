using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BankWithForm
{
    class Banker
    {
        public int MAXPROCESS;                        /*最大进程数*/
        public int MAXRESOURCE;                        /*最大资源数*/
        private int[] AVAILABLE;                    /*可用资源数组*/
        private int[,] MAX;            /*最大需求矩阵*/
        private int[,] ALLOCATION;    /*分配矩阵*/
        private int[,] NEED;            /*需求矩阵*/
        private bool[] FINISH;                        /*系统是否有足够的资源分配*/
        private int[] p;                             /*记录序列*/
        private int m, n;                                    /*m 个进程,n 个资源*/
        public bool isSafe;//是否安全
        public string SafeLine;//安全序列

        public Banker(int threads, int sources)
        {
            m = MAXPROCESS = threads;
            n = MAXRESOURCE = sources;
            AVAILABLE = new int[MAXRESOURCE];
            MAX = new int[MAXPROCESS, MAXRESOURCE];
            ALLOCATION = new int[MAXPROCESS, MAXRESOURCE];
            NEED = new int[MAXPROCESS, MAXRESOURCE];
            FINISH = new bool[MAXPROCESS];
            p = new int[MAXPROCESS];
            isSafe = false;
            SafeLine = "";
        }

        public void Init(int[,] max, int[,] allocation, int[] available)
        {
            int i, j;
            for (i = 0; i < m; i++) for (j = 0; j < n; j++) MAX[i, j] = max[i, j];//进程最多所需的各资源数
            for (i = 0; i < m; i++)//每个进程已分配的各资源数
            {
                for (j = 0; j < n; j++)
                {
                    ALLOCATION[i, j] = allocation[i, j];
                    NEED[i, j] = MAX[i, j] - ALLOCATION[i, j];
                    if (NEED[i, j] < 0)
                    {
                        throw new Exception("您输入的第" + (i + 1) + "个进程所拥有的第" + (j + 1) + "个资源数错误,请重新 输入:");
                    }
                }

            }
            for (i = 0; i < n; i++) { AVAILABLE[i] = available[i]; }//各个资源现有的数目
            Safe();
        }

        public void Request(int thread, int[] REQUEST)
        {
            int i;
            for (i = 0; i < n; i++)
            {
                if (REQUEST[i] > NEED[thread, i])
                {
                    throw new Exception("您输入的请求数超过进程的需求量!请重新输入!");
                }
                if (REQUEST[i] > AVAILABLE[i])
                {
                    throw new Exception("您输入的请求数超过系统有的资源数!请重新输入!");
                }
            }
            for (i = 0; i < n; i++)
            {
                AVAILABLE[i] -= REQUEST[i];
                ALLOCATION[thread, i] += REQUEST[i];
                NEED[thread, i] -= REQUEST[i];
            }
            Safe();
        }

        public bool testRequest(int thread, int[] REQUEST)
        {
            Banker testBanker = new Banker(m, n);
            testBanker.Init(MAX, ALLOCATION, AVAILABLE);
            testBanker.Request(thread, REQUEST);
            return testBanker.isSafe;
        }

        private void Safe()                                    /*安全性算法*/
        {
            int i, j, k, l = 0;
            int[] Work = new int[MAXRESOURCE];                    /*工作数组*/
            for (i = 0; i < n; i++) Work[i] = AVAILABLE[i];
            for (i = 0; i < m; i++) { FINISH[i] = false; }
            for (i = 0; i < m; i++)
            {
                if (FINISH[i]) { continue; }
                else
                {
                    for (j = 0; j < n; j++)
                    {
                        if (NEED[i, j] > Work[j])
                        {
                            break;
                        }
                    }
                    if (j == n)
                    {
                        FINISH[i] = true;
                        for (k = 0; k < n; k++) { Work[k] += ALLOCATION[i, k]; }
                        p[l++] = i;
                        i = -1;
                    }
                    else { continue; }
                }
                SafeLine = "";
                if (l == m)
                {
                    for (i = 0; i < l; i++)
                    {
                        SafeLine += p[i];
                        if (i != l - 1) { SafeLine += "->"; }
                    }
                    isSafe = true;
                    return;
                }
            }
            isSafe = false;
            return;
        }
    }
}
