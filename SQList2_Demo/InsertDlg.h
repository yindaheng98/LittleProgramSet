#pragma once


// CInsertDlg �Ի���

class CInsertDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInsertDlg)

public:
	CInsertDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CInsertDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INSERT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_start;
	int m_end;
	CString m_chr;
	CString m_type;
	int m_strand;
};
