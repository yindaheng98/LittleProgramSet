#pragma once


// CAddEdgeDlg �Ի���

class CAddEdgeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddEdgeDlg)

public:
	CAddEdgeDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAddEdgeDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_start;
	CString m_end;
	int m_weight;
};
