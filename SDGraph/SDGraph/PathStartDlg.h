#pragma once


// CPathStartDlg �Ի���

class CPathStartDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPathStartDlg)

public:
	CPathStartDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPathStartDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_start;
};
