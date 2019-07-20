#pragma once
#include"stdafx.h"
#include"CDataString.h"
#include<vector>

#define Z00M_LONG_MAX 1200
#define ZOOM_LONG_MIN 200

#define SHADE_EXON 10
#define SHADE_CDS (SHADE_EXON*8/10)
#define SHADE_mRNA 10
#define SHADE_GENE 2
#define SHADE_UTR 5
#define SHADE_PORTEIN 5
#define SHADE_LEGEND 15

#define TEXT_HIGH_DISC 12
#define TEXT_HIGH_GENE -10
#define TEXT_HIGH_PORTEIN 20
#define TEXT_HIGH_mRNA -10
#define TEXT_HIGH_UTR -15
#define TEXT_HIGH_EXON -15
#define TEXT_HIGH_CDS 25

#define TEXT_LEGEND_PORTEIN 5
#define TEXT_LEGEND_GENE 20
#define TEXT_LEGEND_UTR 35
#define TEXT_LEGEND_mRNA 50
#define TEXT_LEGEND_EXON 65
#define TEXT_LEGEND_CDS 80
#define TEXT_COUNT_EXON_Y 200
#define TEXT_COUNT_EXON_X 200

#define COLOR_EXON RGB(0,0,255)
#define COLOR_CDS RGB(255,0,0)
#define COLOR_mRNA RGB(0,255,255)
#define COLOR_GENE RGB(0,0,0)
#define COLOR_UTR RGB(200,200,200)
#define COLOR_PORTEIN RGB(255,255,0)
#define COLOR_TEXT RGB(0,0,0)

#define INDENT_LEGEND 5
#define INDENT 25
#define LINE_SPACE_1 35
#define LINE_SPACE_2 50

using std::vector;

inline unsigned int zoom(const unsigned int&n, const unsigned int&gene_start, const unsigned int&gene_end)
{
	return (n - gene_start)*(Z00M_LONG_MAX - ZOOM_LONG_MIN) / (gene_end - gene_start) + ZOOM_LONG_MIN;
}

inline void paint_legend(const unsigned int&y, COLORREF&&color, CDC*&pDC, const char*name)
{
	pDC->SetBkMode(NULL);
	pDC->TextOutW(INDENT_LEGEND + SHADE_LEGEND, y, CString(name));
    CBrush brush(color);
	pDC->SelectObject(&brush);
	CRect rect(INDENT_LEGEND, y, INDENT_LEGEND + SHADE_LEGEND, y + SHADE_LEGEND);
	pDC->FillRect(&rect, &brush);
	pDC->SelectObject(brush);
}

class CChain
{
public:
	bool exist()const
	{
		if (m_start == 0 && m_end == 0)return false;
		else return true;
	}
	explicit CChain(const unsigned int&s
		, const unsigned int&e
		, const unsigned int&gene_start
		, const unsigned int&gene_end)
		:m_start(s), m_end(e)
		, m_dstart(zoom(m_start, gene_start, gene_end))
		, m_dend(zoom(m_end, gene_start, gene_end)) {}
	CChain() :m_start(0), m_end(0), m_dstart(0), m_dend(0) {}

protected:

	unsigned int m_start;
	unsigned int m_end;
	unsigned int m_dstart;
	unsigned int m_dend;

	virtual void paint(const unsigned int&y
		, CDC*&pDC
		, COLORREF&&color
		, const unsigned int&shade
		, const int&text_high)const
	{
		if (exist())
		{
			pDC->MoveTo(m_dstart + INDENT, y + shade);
			pDC->LineTo(m_dstart + INDENT, y + shade - text_high - TEXT_HIGH_DISC+8);
			pDC->MoveTo(m_dend + INDENT - 1, y + shade);
			pDC->LineTo(m_dend + INDENT - 1, y + shade - text_high+8);
			CBrush brush(color);
			pDC->SelectObject(&brush);
			CRect rect(m_dstart + INDENT, y, m_dend + INDENT, y + shade);
			pDC->FillRect(&rect, &brush);
			pDC->SelectObject(brush);
			CString str;
			pDC->SetBkMode(NULL);
			str.Format(_T("%d"), m_start);
			pDC->TextOutW(m_dstart + INDENT, y + shade - text_high - TEXT_HIGH_DISC, str);
			str.Format(_T("%d"), m_end);
			pDC->TextOutW(m_dend + INDENT, y + shade - text_high, str);
		}
	}
};

class CCDS final :public CChain
{
public:
	virtual void paint(const unsigned int&y, CDC*&pDC)const
	{
		CChain::paint(y, pDC, COLOR_CDS, SHADE_CDS, TEXT_HIGH_CDS);
	}
	explicit CCDS(const unsigned int s
		, const unsigned int e
		, const unsigned int gene_start
		, unsigned int gene_end) :CChain(s, e, gene_start, gene_end) {}
	CCDS() {}
};


class CExon final :public CChain
{
public:
	static unsigned int count;
	virtual void paint(const unsigned int&y, CDC*&pDC)const
	{
		CChain::paint(y, pDC, COLOR_EXON, SHADE_EXON, TEXT_HIGH_EXON);
		m_CDS.paint(y + SHADE_EXON/10, pDC);
	}

	explicit CExon(const unsigned int&s
		, const unsigned int&e
		, const unsigned int&gene_start
		, const unsigned int&gene_end, CCDS&&cds)
		:CChain(s, e, gene_start, gene_end)
		, m_CDS(cds)
	{
		count++;
	}
	explicit CExon(const unsigned int&s
		, const unsigned int&e
		, const unsigned int&gene_start
		, const unsigned int&gene_end)
		:CChain(s, e, gene_start, gene_end)
		, m_CDS() 
	{
		count++;
	}

private:
	CCDS m_CDS;
};

class CUTR final :public CChain
{
public:
	virtual void paint(const unsigned int y, CDC*&pDC)const
	{
		CChain::paint(y, pDC, COLOR_UTR, SHADE_UTR, -TEXT_HIGH_UTR);
	}
	explicit CUTR(const unsigned int s
		, const unsigned int e
		, const unsigned int gene_start
		, unsigned int gene_end)
		:CChain(s, e, gene_start, gene_end) {}
	CUTR() {}
};


class CChain_Name :public CChain
{
	friend void paint_legend(const unsigned int&, COLORREF&&, CDC*&, char*);
public:
	virtual void paint(const unsigned int y
		, CDC*&pDC
		, COLORREF&&color
		, const int shade
		, const int text_high
		, const int legend_high)const
	{
		if (exist())
		{
			paint_legend(legend_high, std::forward<COLORREF>(color), pDC, m_name.data());
			CChain::paint(y, pDC, std::forward<COLORREF>(color), shade, text_high);
		}
	}

	explicit CChain_Name(const unsigned int s
		, const unsigned int e
		, const unsigned int gene_start
		, unsigned int gene_end
		, string&str) :CChain(s, e, gene_start, gene_end), m_name(str) {}
	CChain_Name():m_name(string("No Name")) {}

protected:
	string m_name;
};

class CmRNA final:public CChain_Name
{
public:
	virtual void paint(const unsigned int&y, CDC*&pDC)const
	{
		CChain_Name::paint(y, pDC, COLOR_mRNA, SHADE_mRNA,TEXT_HIGH_mRNA,TEXT_LEGEND_mRNA);
		for (const CExon&n : m_exon)
			n.paint(y + LINE_SPACE_2, pDC);
	}

	explicit CmRNA(const unsigned int&s
		, const unsigned int&e
		, const unsigned int&gene_start
		, unsigned int&gene_end
		, string&name) 
		:CChain_Name(s, e, gene_start, gene_end, name) {}
	CmRNA() {}

	void add_exon(CExon&ex)
	{
		m_exon.push_back(ex);
	}

private:
	vector<CExon>m_exon;
};


class CPortein final:public CChain_Name
{
public:
	virtual void paint(const unsigned int&y, CDC*&pDC)const
	{

		CChain_Name::paint(y, pDC, COLOR_PORTEIN, SHADE_PORTEIN, TEXT_HIGH_PORTEIN, TEXT_LEGEND_PORTEIN);
	}
	explicit CPortein(const unsigned int&s
		, const unsigned int&e
		, const unsigned int&gene_start
		, unsigned int&gene_end
		, string&name)
		:CChain_Name(s, e, gene_start, gene_end, name) {}
	CPortein() {}
};


class CGene:public CChain_Name
{
public:
	virtual void paint(const unsigned int&y, CDC*&pDC)const
	{
		pDC->SetBkMode(NULL);
		pDC->TextOutW(TEXT_COUNT_EXON_X, TEXT_COUNT_EXON_Y, CString("There are ") + CString(std::to_string(CExon::count).c_str()) + CString(" exons in this gene."));
		paint_legend(TEXT_LEGEND_CDS, COLOR_CDS, pDC, "CDS");
		paint_legend(TEXT_LEGEND_UTR, COLOR_UTR, pDC, "UTR");
		paint_legend(TEXT_LEGEND_EXON, COLOR_EXON, pDC, "EXON");
		m_portein.paint(y - SHADE_PORTEIN, pDC);
		CChain_Name::paint(y, pDC, COLOR_GENE, SHADE_GENE, TEXT_HIGH_GENE, TEXT_LEGEND_GENE);
		m_RNA.paint(y + LINE_SPACE_1, pDC);
		for (const CUTR&u : m_UTR)u.paint(y + LINE_SPACE_1, pDC);
	}
	CGene() {}
	explicit CGene(const vector<CDataString>&data)
		:CChain_Name(atoi(data[0].str[3].c_str())
			, atoi(data[0].str[4].c_str())
			, atoi(data[0].str[3].c_str())
			, atoi(data[0].str[4].c_str())
			, string("Gene-"))
	{
		//CExon::count = 0;
		CCDS m_tempCDS;
		size_t start(data[0].str[8].find("Name") + 5);
		size_t end(data[0].str[8].find(';', start));
		m_name += string(data[0].str[8].substr(start, end - start));
		for (const CDataString&s : data)
		{
			if (s.str[2] == "mRNA")
			{
				size_t start(s.str[8].find("Name") + 5);
				size_t end(s.str[8].find(';', start));
				m_RNA = CmRNA(atoi(s.str[3].c_str()), atoi(s.str[4].c_str()), m_start, m_end, string("mRNA-") + string(s.str[8].substr(start, end - start)));
			}
			else if (s.str[2].find("UTR") != string::npos)
			{
				m_UTR.push_back(CUTR(atoi(s.str[3].c_str()), atoi(s.str[4].c_str()), m_start, m_end));
			}
			else if (s.str[2] == "protein")
			{
				size_t start(s.str[8].find("Name") + 5);
				size_t end(s.str[8].find(';', start));
				m_portein = CPortein(atoi(s.str[3].c_str()), atoi(s.str[4].c_str()), m_start, m_end, string("portein-") + string(s.str[8].substr(start, end - start)));
			}
		}
		for (auto s=data.crbegin();s!=data.crend();++s)
		{
			if (s->str[2] == "CDS")
			{
				m_tempCDS = CCDS(atoi(s->str[3].c_str()), atoi(s->str[4].c_str()), m_start, m_end);
			}
			else if (s->str[2] == "exon")
			{
				if (m_tempCDS.exist())
				{
					m_RNA.add_exon(CExon(atoi(s->str[3].c_str()), atoi(s->str[4].c_str()), m_start, m_end, CCDS(m_tempCDS)));
					m_tempCDS = CCDS();
				}
				else
				{
					m_RNA.add_exon(CExon(atoi(s->str[3].c_str()), atoi(s->str[4].c_str()), m_start, m_end));
				}
			}
		}
	}

private:
	CmRNA m_RNA;
	CPortein m_portein;
	vector<CUTR> m_UTR;
};
