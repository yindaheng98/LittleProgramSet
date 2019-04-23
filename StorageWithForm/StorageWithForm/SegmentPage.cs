using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace StorageWithForm
{
    class SegmentPage
    {
        public int StartAddress;//起始地址
        private int TotalAddress;//总地址数
        private int TotalSegments;//总段数
        private int Pages_pre_Segment;//每段页面数
        private int Addresses_pre_Page;//每页地址数
        private int[] SegmentsList;//段-页地址表
        private int[] PagesList;//页-实际地址表
        public SegmentPage(int startaddress, int pagelength, int seglength, int totalsegments)//输入每页地址数，每段页面数，段数
        {
            if (startaddress < 0 || !is2Square(startaddress)) throw new Exception("起始地址应为2的正整数次方且大于等于0");
            if (pagelength <= 1 || !is2Square(pagelength)) throw new Exception("页面大小应为2的正整数次方且大于1");
            if (seglength <= 1 || !is2Square(seglength)) throw new Exception("每段页数应为2的正整数次方且大于1");
            if (totalsegments <= 1 || !is2Square(totalsegments)) throw new Exception("总段数应为2的正整数次方且大于1");
            StartAddress = startaddress;
            Addresses_pre_Page = pagelength;
            Pages_pre_Segment = seglength;
            TotalSegments = totalsegments;
            TotalAddress = Addresses_pre_Page * Pages_pre_Segment * TotalSegments;
            if(TotalAddress<=0) throw new Exception("内存总量过大");
            SegmentsList = new int[TotalSegments];
            PagesList = new int[TotalSegments * Pages_pre_Segment];
            for (int i = 0; i < TotalSegments; i++)//一段一段来
            {
                SegmentsList[i] = i * Pages_pre_Segment;
                for (int j = 0; j < Pages_pre_Segment; j++)//一页一页来
                {
                    PagesList[SegmentsList[i] + j] = (SegmentsList[i] + j) * Addresses_pre_Page + StartAddress;
                }
            }
        }

        public SegmentPage(int startaddress, int pagelength, int[] segmentarray, int[] pagematrix)//输入地址矩阵int[段址,页址]
        {
            if (startaddress < 0 || !is2Square(startaddress)) throw new Exception("起始地址应为2的正整数次方且大于等于0");
            if (pagelength <= 1 || !is2Square(pagelength)) throw new Exception("页面大小应为2的正整数次方且大于1");
            if (segmentarray.Length <= 1 || !is2Square(TotalSegments)) throw new Exception("总段数应为2的正整数次方且大于1");
            if ((pagematrix.Length / segmentarray.Length) <= 1 || !is2Square(Pages_pre_Segment)) throw new Exception("每段页数应为2的正整数次方且大于1");
            if (pagematrix.Length % segmentarray.Length != 0) throw new Exception("矩阵维数不符");
            StartAddress = startaddress;
            Addresses_pre_Page = pagelength;
            Pages_pre_Segment = (pagematrix.Length / segmentarray.Length);
            TotalSegments = segmentarray.Length;
            TotalAddress = Addresses_pre_Page * Pages_pre_Segment * TotalSegments;
            if (TotalAddress <= 0) throw new Exception("内存总量过大");
            
            SegmentsList = new int[TotalSegments];
            PagesList = new int[TotalSegments * Pages_pre_Segment];
            for (int i = 0; i < TotalSegments; i++)//一段一段来
            {
                SegmentsList[i] = segmentarray[i] * Pages_pre_Segment;
                for (int j = 0; j < Pages_pre_Segment; j++)//一页一页来
                {
                    PagesList[i * Pages_pre_Segment + j] = pagematrix[i * Pages_pre_Segment + j] * Addresses_pre_Page + StartAddress;
                }
            }
        }

        public int getAddress(int virtualaddress)
        {
            if (virtualaddress >= TotalAddress+StartAddress|| virtualaddress< StartAddress) throw new Exception("地址越界");
            int page_dev1ation = virtualaddress % Addresses_pre_Page;//找页内地址偏移
            virtualaddress /= Addresses_pre_Page;//取下段页号
            int page_num = virtualaddress % Pages_pre_Segment;//找段内地址偏移
            virtualaddress /= Pages_pre_Segment;//取下段号
            int segment_num = virtualaddress % TotalSegments;
            return PagesList[SegmentsList[segment_num] + page_num] + page_dev1ation;
        }

        public int[] getSegment()
        {
            return SegmentsList;
        }

        public int getPageNumber(int virtualaddress)
        {
            if (virtualaddress >= TotalAddress + StartAddress || virtualaddress < StartAddress) throw new Exception("地址越界");
            virtualaddress /= Addresses_pre_Page;//取下段页号
            int page_num = virtualaddress % Pages_pre_Segment;//找段内地址偏移
            return page_num;
        }

        public int getSegmentNumber(int virtualaddress)//获取段号
        {
            if (virtualaddress >= TotalAddress + StartAddress || virtualaddress < StartAddress) throw new Exception("地址越界");
            virtualaddress /= Addresses_pre_Page;//取下段页号
            int page_num = virtualaddress % Pages_pre_Segment;//找段内地址偏移
            virtualaddress /= Pages_pre_Segment;//取下段号
            int segment_num = virtualaddress % TotalSegments;
            return segment_num;
        }

        public int getPageAddress(int virtualaddress)//获取在页表中的首地址
        {
            if (virtualaddress >= TotalAddress+StartAddress|| virtualaddress< StartAddress) throw new Exception("地址越界");
            virtualaddress /= Addresses_pre_Page;//取下段页号
            int page_num = virtualaddress % Pages_pre_Segment;//找段内地址偏移
            virtualaddress /= Pages_pre_Segment;//取下段号
            int segment_num = virtualaddress % TotalSegments;
            return SegmentsList[segment_num];
        }
        
        public int[] getPage(int virtualaddress)//获取这一页
        {
            if (virtualaddress >= TotalAddress+StartAddress|| virtualaddress< StartAddress) throw new Exception("地址越界");
            virtualaddress /= Addresses_pre_Page;//取下段页号
            int page_num = virtualaddress % Pages_pre_Segment;//找段内地址偏移
            virtualaddress /= Pages_pre_Segment;//取下段号
            int segment_num = virtualaddress % TotalSegments;
            return PagesList.Skip(SegmentsList[segment_num]).Take(Addresses_pre_Page).ToArray();
        }

        private bool is2Square(int n)
        {
            while (n > 1)
            {
                if (n % 2 == 0) n /= 2;
                else return false;
            }
            return true;
        }
    }
}
