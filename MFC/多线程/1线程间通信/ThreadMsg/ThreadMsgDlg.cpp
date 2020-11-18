
// ThreadMsgDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ThreadMsg.h"
#include "ThreadMsgDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CThreadMsgDlg �Ի���



CThreadMsgDlg::CThreadMsgDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_THREADMSG_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CThreadMsgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CThreadMsgDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CREATE_THREAD_BTN, &CThreadMsgDlg::OnBnClickedCreateThreadBtn)
END_MESSAGE_MAP()


// CThreadMsgDlg ��Ϣ�������

BOOL CThreadMsgDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CThreadMsgDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CThreadMsgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int g_num = 100; // 1ȫ�ֱ��������̼߳�

UINT  th1(LPVOID)
{
	while (TRUE)
	{
		g_num++;
		Sleep(4000);
	}
	return 0;
}

UINT  th2(LPVOID)
{
	while (TRUE)
	{
		CString msgStr;
		msgStr.Format(_T("%d\n"), g_num);
		OutputDebugString(msgStr);
		Sleep(2000);
	}
	return 0;
}
void CThreadMsgDlg::OnBnClickedCreateThreadBtn()
{
	AfxBeginThread(th1, 0);
	AfxBeginThread(th2, 0);
}
