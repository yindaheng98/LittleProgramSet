#pragma once


// CShortPathDlg �Ի���

class CShortPathDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CShortPathDlg)

public:
	CShortPathDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CShortPathDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_start;
	CString m_end;
};
