
// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "GFFViewerSDI v2.h"

#include "MainFrm.h"
#include"ClassGene.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_COMMAND(ID_FILE_OPEN, &CMainFrame::OnFileOpen)
END_MESSAGE_MAP()

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return TRUE;
}

// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame ��Ϣ�������



void CMainFrame::OnFileOpen()
{
	CString filepath;
	CFileDialog fdlg(TRUE, _T("gff"), NULL, NULL, _T("�ļ� (*.gff;)|*.gff||"), NULL);
	INT_PTR result = fdlg.DoModal();
	if (result == IDOK)filepath = fdlg.GetPathName();
	ifstream file(filepath);
	vector<CDataString>data;
	do
	{
		data.push_back(CDataString(file));
	} while (!file.eof());
	extern CGene gene;
	gene = CGene(data);
	// TODO: �ڴ���������������
}
