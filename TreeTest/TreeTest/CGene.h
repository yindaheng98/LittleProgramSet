#pragma once
#include<utility>
#include<vector>
#include"stdafx.h"
#include"CDataString.h"
using std::vector;

class CChain//基础链类：定义所有链类通用的数据类型和输出自身的函数
{
public:
	virtual void travel(CListCtrl&m_list, CString&chr, int&n) = 0;								//在表格中遍历
	virtual HTREEITEM paint(CTreeCtrl&m_control, HTREEITEM hInsertAfter = TVI_LAST) = 0;		//完整输出
protected:
	void travel_self(CListCtrl&m_list, CString&chr, CString&&type, int&n)						//在表格中输出自身
	{
		CString str;
		m_list.InsertItem(n, chr);
		m_list.SetItemText(n, 1, type);
		str.Format(_T("%d"), start);
		m_list.SetItemText(n, 2, str);
		str.Format(_T("%d"), end);
		m_list.SetItemText(n, 3, str);
		str.Format(_T("%c"), strand ? L'+' : L'-');
		m_list.SetItemText(n, 4, str);
		n++;
	}
	HTREEITEM paint_self(CString&&name, CTreeCtrl&m_control, HTREEITEM hInsertAfter = TVI_LAST)	//自身输出
	{
		hInsertAfter = m_control.InsertItem(name, hInsertAfter);								//插入节点
		m_control.SetItemData(hInsertAfter, code);												//设置文本设置和数据
		return hInsertAfter;																	//返回节点句柄
	}
	CChain(__int32 c = 0, int s = 0, int e = 0, bool st = 0) :code(c), start(s), end(e), strand(st) {}
protected:
	__int32 code;   //数据编号
	int start;      //起始点
	int end;        //终止点
	bool strand;
};

class CMainChain :public CChain//基础主链类：有专有链名且只需输出自身
{
public:
	virtual HTREEITEM paint(CTreeCtrl&m_control, HTREEITEM hInsertAfter = TVI_LAST)
	{
		return paint_self(std::forward<CString>(name), m_control, hInsertAfter);
	}
	CMainChain(
		CString n = CString('#')	//默认链名
		, __int32 c = 0				//32位编码
		, int s = 0					//起点
		, int e = 0					//正负链
		, bool st = 0)				//终点
		:name(n)					//链名
		, CChain(c, s, e, st) {}
protected:
	CString name;
};

class CUTR :public CChain          //UTR类：无专有链名且只需输出自身
{
public:
	virtual void travel(CListCtrl&m_list, CString&chr, int&n)						//重载遍历
	{
		travel_self(m_list, chr, CString("UTR"), n);
	}
	virtual HTREEITEM paint(CTreeCtrl&m_control, HTREEITEM hInsertAfter = TVI_LAST)	//重载输出函数
	{
		return paint_self(_T("UTR"), m_control, hInsertAfter);						//输出名"UTR"
	}
	CUTR(__int32 c, int s, int e, bool st) :CChain(c, s, e, st) {}
	CUTR() {}
};

class CCDS:public CChain          //CDS类：无专有链名且只需输出自身
{
public:
	virtual void travel(CListCtrl&m_list, CString&chr, int&n)						//重载遍历
	{
		travel_self(m_list, chr, CString("CDS"), n);
	}
	virtual HTREEITEM paint(CTreeCtrl&m_control, HTREEITEM hInsertAfter = TVI_LAST)	//重载输出函数
	{
		return paint_self(_T("CDS"), m_control, hInsertAfter);						//输出名"CDS"
	}
	CCDS(__int32 c = 0, int s = 0, int e = 0, bool st = 0) :CChain(c, s, e, st) {}
};

class CExon :public CChain         //Exon类：无专有链名且需输出自身和所包含的CDS类
{
public:
	void add(CCDS c)               //向Exon中加入CDS
	{
		CDS = c;
	}
	virtual void travel(CListCtrl&m_list, CString&chr, int&n)						//重载遍历
	{
		travel_self(m_list, chr, CString("exon"), n);
		CDS.travel(m_list, chr, n);
	}
	virtual HTREEITEM paint(CTreeCtrl&m_control, HTREEITEM hInsertAfter = TVI_LAST)	//重载输出函数
	{
		return CDS.paint(m_control,paint_self(_T("Exon"), m_control, hInsertAfter));//输出名"Exon"
	}
	CExon(__int32 c = 0, int s = 0, int e = 0, bool st = 0) :CChain(c, s, e, st) {}
private:
	CCDS CDS;
};

class CRNA :public CMainChain      //RNA类：主链型，需输出自身和所包含的Exon类
{
public:
	void add(CExon e)              //向mRNA中加入Exon
	{
		exon.push_back(e);
	}
	virtual void travel(CListCtrl&m_list, CString&chr, int&n)						//重载遍历
	{
		travel_self(m_list, chr, CString("RNA"), n);
		for (CExon e : exon)e.travel(m_list, chr, n);
	}
	virtual HTREEITEM paint(CTreeCtrl&m_control, HTREEITEM hInsertAfter = TVI_LAST)	//重载输出函数
	{
		HTREEITEM temph = paint_self(std::forward<CString>(name), m_control, hInsertAfter);	//输出自身
		for (CExon e:exon)
		{
			e.paint(m_control, temph);//输出exon
		}
		return temph;
	}
	CRNA(
		CString n = CString('#')//默认链名
		, __int32 c = 0
		, int s = 0
		, int e = 0
		, bool st = 0)
		:CMainChain(CString(_T("mRNA-")) + n, c, s, e, st)//取名"mRNA-"+ID号
	{}
private:
	vector<CExon>exon;
};

class CProtein :public CMainChain//蛋白质类：主链型，只需输出自身
{
public:
	virtual void travel(CListCtrl&m_list, CString&chr, int&n)//重载遍历
	{
		travel_self(m_list, chr, CString("protein"), n);
	}
	CProtein(
		CString n = CString('#')
		, __int32 c = 0
		, int s = 0
		, int e = 0
		, bool st = 0)
		:CMainChain(CString(_T("Protein-")) + n, c, s, e)//取名"Protein-"+ID号
	{}
};

class CGene:public CMainChain//基因类：主链型，输出自身和UTR,mRNA,蛋白质
{
public:
	virtual void travel(CListCtrl&m_list, CString&chr, int&n)//重载遍历
	{
		travel_self(m_list, chr, CString("Gene"), n);
		protein.travel(m_list, chr, n);
		UTRs.travel(m_list, chr, n);
		mRNA.travel(m_list, chr, n);
		UTRe.travel(m_list, chr, n);
	}
	void travel(CListCtrl&m_list, int&n)//重载遍历
	{
		travel(m_list, chr, n);
	}
	virtual HTREEITEM paint(CTreeCtrl&m_control, HTREEITEM hInsertAfter = TVI_LAST)	//重载输出函数
	{
		HTREEITEM temph = paint_self(std::forward<CString>(name), m_control, hInsertAfter);//输出自身
		protein.paint(m_control, temph);			//输出蛋白质
		UTRs.paint(m_control, temph);				//输出UTR起点
		mRNA.paint(m_control, temph);				//输出mRNA
		UTRe.paint(m_control, temph);				//输出UTR终点
		return temph;
	}
	CGene() {}
	CGene(CDataString Data)
	{
		name = L"Gene-";
		int i = 0;
		int u = 0;
		bool utr = 0;
		CExon texon;
		for (CData d : Data.data)
		{
			if (d.type == L"gene")							//读到字符串"gene"
			{
				chr = d.chr.c_str();
				code = i;
				start = d.start;
				end = d.end;
				strand = d.strand;
				size_t start(d.note.find(L"Name") + 5);		//查找ID
				name += d.note.substr(start, d.note.find(';', start) - start).c_str();//取名"Gene-"+ID号
			}
			else if (d.type == L"mRNA")						//读到字符串"gene"
			{
				size_t start(d.note.find(L"Name") + 5);		//查找ID
				mRNA = CRNA(CString(d.note.substr(start, d.note.find(';', start) - start).c_str()), i, d.start, d.end, d.strand);			//存储mRNA类
			}
			else if (d.type == L"protein")					//读到字符串"gene"
			{
				size_t start(d.note.find(L"Name") + 5);		//查找ID
				protein = CProtein(CString(d.note.substr(start, d.note.find(';', start) - start).c_str()), i, d.start, d.end, d.strand);	//存储蛋白质类
			}
			else if (d.type == L"exon")						//读到字符串"gene"
			{
				texon = CExon(i, d.start, d.end, d.strand);			//构造一个外显子
			}
			else if (d.type == L"CDS")						//读到字符串"gene"
			{
				texon.add(CCDS(i, d.start, d.end, d.strand));			//在之前构造的外显子中加CDS
				mRNA.add(texon);							//在mRNA类中加入exon
				texon = CExon();							//归零
			}
			else if (d.type.find(L"UTR") != wstring::npos)	//读到字符串"gene"
			{
				utr++ ? UTRe = CUTR(i, d.start, d.end, d.strand) : UTRs = CUTR(i, d.start, d.end, d.strand);		//存储UTR
			}
			i++;//读取下一条
		}
	}
private:
	CString chr;
	CUTR UTRs,UTRe;	//UTR
	CRNA mRNA;			//mRNA
	CProtein protein;	//蛋白质
};
