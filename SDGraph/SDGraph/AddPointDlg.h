#pragma once


// CAddPointDlg �Ի���

class CAddPointDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddPointDlg)

public:
	CAddPointDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAddPointDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_name;
};
