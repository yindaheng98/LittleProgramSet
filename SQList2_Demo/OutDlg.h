#pragma once


// COutDlg 对话框

class COutDlg : public CDialogEx
{
	DECLARE_DYNAMIC(COutDlg)

public:
	COutDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~COutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OUT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_outtype;
};
