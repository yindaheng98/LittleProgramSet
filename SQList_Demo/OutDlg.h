#pragma once


// COutDlg �Ի���

class COutDlg : public CDialogEx
{
	DECLARE_DYNAMIC(COutDlg)

public:
	COutDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~COutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OUT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_outtype;
};
