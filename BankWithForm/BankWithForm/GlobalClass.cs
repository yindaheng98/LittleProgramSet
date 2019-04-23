using System;
using System.Data;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BankWithForm
{
    class GlobalClass
    {
        public static Banker banker;
        public static int[] REQUEST;
        public static int[] AVAILABLE;                    /*可用资源数组*/
        public static int[,] MAX;            /*最大需求矩阵*/
        public static int[,] ALLOCATION;    /*分配矩阵*/

        public static DataTable request;
        public static DataTable available;
        public static DataTable max;
        public static DataTable allocation;

        public static void SyncToDataTable()
        {
            request = ArrayToDatatable(REQUEST);
            available =ArrayToDatatable(AVAILABLE);
            max = MatrixToDatatable(MAX);
            allocation = MatrixToDatatable(ALLOCATION);
        }

        public static void SyncToMartix()
        {
            REQUEST = DatatableToArray(request);
            AVAILABLE = DatatableToArray(available);
            MAX = DatatableToMatrix(max);
            ALLOCATION = DatatableToMatrix(allocation);
        }

        public static DataTable ArrayToDatatable(int[] array)
        {
            DataTable dt = new DataTable();
            for (int i = 0; i < array.Length; i++)
            {
                dt.Columns.Add("资源" + i, typeof(int));
            }
            DataRow dr = dt.NewRow();
            for (int j = 0; j < array.Length; j++)
            {
                dr[j] = array[j];
            }
            dt.Rows.Add(dr);
            return dt;
        }

        public static int[] DatatableToArray(DataTable data)
        {
            int[] array = new int[data.Columns.Count];
            for (int j = 0; j < data.Columns.Count; j++)
            {
                array[j] = int.Parse(data.Rows[0][j].ToString());
            }
            return array;
        }

        public static DataTable MatrixToDatatable(int[,] matrix)
        {
            DataTable dt = new DataTable();
            dt.Columns.Add("进程号", typeof(string));
            for (int i=0;i < matrix.GetLength(1); i++)
            {
                dt.Columns.Add("资源"+i, typeof(int));
            }
            for (int i = 0; i < matrix.GetLength(0); i++)
            {
                DataRow dr = dt.NewRow();
                dr[0] = "进程" + i;
                for (int j = 0; j < matrix.GetLength(1); j++)
                {
                    dr[j + 1] = matrix[i, j];
                }
                dt.Rows.Add(dr);
            }
            return dt;
        }

        public static int[,] DatatableToMatrix(DataTable data)
        {
            int[,] matrix = new int[data.Rows.Count, data.Columns.Count - 1];
            for (int i = 0; i < data.Rows.Count; i++)
            {
                for (int j = 1; j < data.Columns.Count; j++)
                {
                    matrix[i, j-1] = int.Parse(data.Rows[i][j].ToString());
                }
            }
            return matrix;
        }
    }
}
