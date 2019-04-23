using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data;

namespace StorageWithForm
{
    class GlobalClass
    {
        static public SegmentPage s;
        static public DataTable SegmentData;
        static public DataTable PageData;
        static public void Init(int startaddr,int segmun,int pgenum,int pagelength)
        {
            s = new SegmentPage(startaddr, pagelength, RandomArray(segmun), RandomArray(segmun * pgenum));
        }
        static public void syncData(int virtualaddress)
        {
            SegmentData = SegmentArrayToDatatable(s.getSegmentNumber(virtualaddress), s.getSegment());
            PageData = PageArrayToDatatable(s.getPageNumber(virtualaddress),s.getPage(virtualaddress), virtualaddress);
        }

        static private DataTable SegmentArrayToDatatable(int segnum,int[] array)
        {
            DataTable dt = new DataTable();
            dt.Columns.Add("段号", typeof(int));
            dt.Columns.Add("在页表中的首地址", typeof(int));
            for (int j = segnum; j < array.Length; j++)
            {
                DataRow dr = dt.NewRow();
                dr[0] = j;
                dr[1] = array[j];
                dt.Rows.Add(dr);
            }
            return dt;
        }

        static private DataTable PageArrayToDatatable(int pgenum,int[] array, int virtualaddress)
        {
            DataTable dt = new DataTable();
            dt.Columns.Add("段内编号", typeof(int));
            dt.Columns.Add("页号", typeof(int));
            dt.Columns.Add("首地址", typeof(int));
            int headaddr = s.getPageAddress(virtualaddress);
            for (int j = pgenum; j < array.Length; j++)
            {
                DataRow dr = dt.NewRow();
                dr[0] = j;
                dr[1] = headaddr + j;
                dr[2] = array[j];
                dt.Rows.Add(dr);
            }
            return dt;
        }

        static private int[] RandomArray(int n)
        {
            Random rd = new Random();
            int[] arr = Enumerable.Range(0, n).ToArray();
            for (int i = 0; i < n; i++)
            {
                int j = rd.Next(0, n);
                int t = arr[i];
                arr[i] = arr[j];
                arr[j] = t;
            }
            return arr;
        }
    }
}
