#pragma once


// CAddEdgeDlg 对话框

class CAddEdgeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddEdgeDlg)

public:
	CAddEdgeDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAddEdgeDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_start;
	CString m_end;
	int m_weight;
};
