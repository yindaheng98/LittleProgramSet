#pragma once


// CShortPathDlg 对话框

class CShortPathDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CShortPathDlg)

public:
	CShortPathDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CShortPathDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_start;
	CString m_end;
};
