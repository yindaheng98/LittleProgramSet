#pragma once
#include<utility>
#include<vector>
#include"stdafx.h"
#include"CDataString.h"
using std::vector;

class CChain//�������ࣺ������������ͨ�õ��������ͺ��������ĺ���
{
public:
	virtual void travel(CListCtrl&m_list, CString&chr, int&n) = 0;								//�ڱ���б���
	virtual HTREEITEM paint(CTreeCtrl&m_control, HTREEITEM hInsertAfter = TVI_LAST) = 0;		//�������
protected:
	void travel_self(CListCtrl&m_list, CString&chr, CString&&type, int&n)						//�ڱ�����������
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
	HTREEITEM paint_self(CString&&name, CTreeCtrl&m_control, HTREEITEM hInsertAfter = TVI_LAST)	//�������
	{
		hInsertAfter = m_control.InsertItem(name, hInsertAfter);								//����ڵ�
		m_control.SetItemData(hInsertAfter, code);												//�����ı����ú�����
		return hInsertAfter;																	//���ؽڵ���
	}
	CChain(__int32 c = 0, int s = 0, int e = 0, bool st = 0) :code(c), start(s), end(e), strand(st) {}
protected:
	__int32 code;   //���ݱ��
	int start;      //��ʼ��
	int end;        //��ֹ��
	bool strand;
};

class CMainChain :public CChain//���������ࣺ��ר��������ֻ���������
{
public:
	virtual HTREEITEM paint(CTreeCtrl&m_control, HTREEITEM hInsertAfter = TVI_LAST)
	{
		return paint_self(std::forward<CString>(name), m_control, hInsertAfter);
	}
	CMainChain(
		CString n = CString('#')	//Ĭ������
		, __int32 c = 0				//32λ����
		, int s = 0					//���
		, int e = 0					//������
		, bool st = 0)				//�յ�
		:name(n)					//����
		, CChain(c, s, e, st) {}
protected:
	CString name;
};

class CUTR :public CChain          //UTR�ࣺ��ר��������ֻ���������
{
public:
	virtual void travel(CListCtrl&m_list, CString&chr, int&n)						//���ر���
	{
		travel_self(m_list, chr, CString("UTR"), n);
	}
	virtual HTREEITEM paint(CTreeCtrl&m_control, HTREEITEM hInsertAfter = TVI_LAST)	//�����������
	{
		return paint_self(_T("UTR"), m_control, hInsertAfter);						//�����"UTR"
	}
	CUTR(__int32 c, int s, int e, bool st) :CChain(c, s, e, st) {}
	CUTR() {}
};

class CCDS:public CChain          //CDS�ࣺ��ר��������ֻ���������
{
public:
	virtual void travel(CListCtrl&m_list, CString&chr, int&n)						//���ر���
	{
		travel_self(m_list, chr, CString("CDS"), n);
	}
	virtual HTREEITEM paint(CTreeCtrl&m_control, HTREEITEM hInsertAfter = TVI_LAST)	//�����������
	{
		return paint_self(_T("CDS"), m_control, hInsertAfter);						//�����"CDS"
	}
	CCDS(__int32 c = 0, int s = 0, int e = 0, bool st = 0) :CChain(c, s, e, st) {}
};

class CExon :public CChain         //Exon�ࣺ��ר��������������������������CDS��
{
public:
	void add(CCDS c)               //��Exon�м���CDS
	{
		CDS = c;
	}
	virtual void travel(CListCtrl&m_list, CString&chr, int&n)						//���ر���
	{
		travel_self(m_list, chr, CString("exon"), n);
		CDS.travel(m_list, chr, n);
	}
	virtual HTREEITEM paint(CTreeCtrl&m_control, HTREEITEM hInsertAfter = TVI_LAST)	//�����������
	{
		return CDS.paint(m_control,paint_self(_T("Exon"), m_control, hInsertAfter));//�����"Exon"
	}
	CExon(__int32 c = 0, int s = 0, int e = 0, bool st = 0) :CChain(c, s, e, st) {}
private:
	CCDS CDS;
};

class CRNA :public CMainChain      //RNA�ࣺ�����ͣ�������������������Exon��
{
public:
	void add(CExon e)              //��mRNA�м���Exon
	{
		exon.push_back(e);
	}
	virtual void travel(CListCtrl&m_list, CString&chr, int&n)						//���ر���
	{
		travel_self(m_list, chr, CString("RNA"), n);
		for (CExon e : exon)e.travel(m_list, chr, n);
	}
	virtual HTREEITEM paint(CTreeCtrl&m_control, HTREEITEM hInsertAfter = TVI_LAST)	//�����������
	{
		HTREEITEM temph = paint_self(std::forward<CString>(name), m_control, hInsertAfter);	//�������
		for (CExon e:exon)
		{
			e.paint(m_control, temph);//���exon
		}
		return temph;
	}
	CRNA(
		CString n = CString('#')//Ĭ������
		, __int32 c = 0
		, int s = 0
		, int e = 0
		, bool st = 0)
		:CMainChain(CString(_T("mRNA-")) + n, c, s, e, st)//ȡ��"mRNA-"+ID��
	{}
private:
	vector<CExon>exon;
};

class CProtein :public CMainChain//�������ࣺ�����ͣ�ֻ���������
{
public:
	virtual void travel(CListCtrl&m_list, CString&chr, int&n)//���ر���
	{
		travel_self(m_list, chr, CString("protein"), n);
	}
	CProtein(
		CString n = CString('#')
		, __int32 c = 0
		, int s = 0
		, int e = 0
		, bool st = 0)
		:CMainChain(CString(_T("Protein-")) + n, c, s, e)//ȡ��"Protein-"+ID��
	{}
};

class CGene:public CMainChain//�����ࣺ�����ͣ���������UTR,mRNA,������
{
public:
	virtual void travel(CListCtrl&m_list, CString&chr, int&n)//���ر���
	{
		travel_self(m_list, chr, CString("Gene"), n);
		protein.travel(m_list, chr, n);
		UTRs.travel(m_list, chr, n);
		mRNA.travel(m_list, chr, n);
		UTRe.travel(m_list, chr, n);
	}
	void travel(CListCtrl&m_list, int&n)//���ر���
	{
		travel(m_list, chr, n);
	}
	virtual HTREEITEM paint(CTreeCtrl&m_control, HTREEITEM hInsertAfter = TVI_LAST)	//�����������
	{
		HTREEITEM temph = paint_self(std::forward<CString>(name), m_control, hInsertAfter);//�������
		protein.paint(m_control, temph);			//���������
		UTRs.paint(m_control, temph);				//���UTR���
		mRNA.paint(m_control, temph);				//���mRNA
		UTRe.paint(m_control, temph);				//���UTR�յ�
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
			if (d.type == L"gene")							//�����ַ���"gene"
			{
				chr = d.chr.c_str();
				code = i;
				start = d.start;
				end = d.end;
				strand = d.strand;
				size_t start(d.note.find(L"Name") + 5);		//����ID
				name += d.note.substr(start, d.note.find(';', start) - start).c_str();//ȡ��"Gene-"+ID��
			}
			else if (d.type == L"mRNA")						//�����ַ���"gene"
			{
				size_t start(d.note.find(L"Name") + 5);		//����ID
				mRNA = CRNA(CString(d.note.substr(start, d.note.find(';', start) - start).c_str()), i, d.start, d.end, d.strand);			//�洢mRNA��
			}
			else if (d.type == L"protein")					//�����ַ���"gene"
			{
				size_t start(d.note.find(L"Name") + 5);		//����ID
				protein = CProtein(CString(d.note.substr(start, d.note.find(';', start) - start).c_str()), i, d.start, d.end, d.strand);	//�洢��������
			}
			else if (d.type == L"exon")						//�����ַ���"gene"
			{
				texon = CExon(i, d.start, d.end, d.strand);			//����һ��������
			}
			else if (d.type == L"CDS")						//�����ַ���"gene"
			{
				texon.add(CCDS(i, d.start, d.end, d.strand));			//��֮ǰ������������м�CDS
				mRNA.add(texon);							//��mRNA���м���exon
				texon = CExon();							//����
			}
			else if (d.type.find(L"UTR") != wstring::npos)	//�����ַ���"gene"
			{
				utr++ ? UTRe = CUTR(i, d.start, d.end, d.strand) : UTRs = CUTR(i, d.start, d.end, d.strand);		//�洢UTR
			}
			i++;//��ȡ��һ��
		}
	}
private:
	CString chr;
	CUTR UTRs,UTRe;	//UTR
	CRNA mRNA;			//mRNA
	CProtein protein;	//������
};
