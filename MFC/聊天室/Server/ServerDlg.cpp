
// ServerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Server.h"
#include "ServerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CServerDlg �Ի���



CServerDlg::CServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CServerDlg::IDD, pParent)
	, m_Ctx(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PLAYER_LIST, m_List);
	DDX_Text(pDX, IDC_CTX, m_Ctx);
}

BEGIN_MESSAGE_MAP(CServerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_EXIT, &CServerDlg::OnBnClickedExitBtn)
	ON_WM_CTLCOLOR()
	ON_MESSAGE(SOCKET_EVENT,&CServerDlg::OnSocket)
END_MESSAGE_MAP()


// CServerDlg ��Ϣ�������

BOOL CServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	//AfxSocketInit();

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_List.InsertColumn(0,_T("��ν"),LVCFMT_LEFT,120);		//��һ�б�ͷ
	m_List.InsertColumn(1,_T("IP"),LVCFMT_LEFT,100);		//�ڶ��б�ͷ
	m_List.InsertColumn(2,_T("��Ϣ��"),LVCFMT_LEFT,60);		//�����б�ͷ
	m_List.InsertColumn(3,_T("ͷ��"),LVCFMT_LEFT,60);		//�����б�ͷ

	m_socket.AttachCWnd(this);							//��Socket�󶨵�����
	m_socket.Create(0x8123,SOCK_STREAM);				//SOCK_STREAM��ʾTCP����
	m_socket.Listen();									//�ȴ�����

	m_brBack.DeleteObject();
	m_bmBack.DeleteObject();
	m_bmBack.LoadBitmap(IDB_BKSERVER);
	m_brBack.CreatePatternBrush(&m_bmBack);

	 m_bExit.AutoLoad(IDC_EXIT,this);
	 m_bExit.SizeToContent();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CServerDlg::OnPaint()
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
HCURSOR CServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CServerDlg::OnBnClickedExitBtn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnOK();
}

void CServerDlg::OnCancel() 
{
	CDialog::OnCancel();
}

void CServerDlg::OnOK() 
{
	//	CDialog::OnOK();
}

HBRUSH CServerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if(nCtlColor == CTLCOLOR_DLG)
		return m_brBack;
	return hbr;
}

LRESULT CServerDlg::OnSocket(WPARAM wParam,LPARAM lParam)
{
	CMySocket *socketFrom = (CMySocket*)wParam;
	//����Э��
	switch (lParam)	
	{
	case ACCEPT:
		{
			CMySocket *pSocketClient = new CMySocket();
			pSocketClient->AttachCWnd(this);
			SOCKADDR_IN sockAddr;
			int nSize = sizeof(sockAddr);
			BOOL res = socketFrom->Accept(*pSocketClient,(SOCKADDR*)&sockAddr,&nSize);
			if (res==FALSE)
			{
				MessageBox(_T("���տͻ���ʧ�ܣ�"));
			}
			break;
		}
	case CLOSE:
		{
			ClosePlayer(socketFrom);
			break;
		}
	case RETR:
		{
			ParserPkt(socketFrom);
			break;
		}
	}

	return TRUE;
}

void CServerDlg::ClosePlayer(CMySocket* socketFrom)
{
	int		i,msg_len;
	TCHAR	out_msg[200];
	TCHAR	nbuf[100];
	nbuf[0] = 0x41;									//�û��˳��������
	msg_len = _stprintf_s(out_msg,_T(" %s �˳�������\r\n"),socketFrom->m_Player) + sizeof(TCHAR);

	m_criticalSection.Lock();
	for(i = 0; i < m_List.GetItemCount(); i++)		//ɾ���˳��û�����Ϣ
	{
		if(m_List.GetItemData(i) == (DWORD)socketFrom)
		{
			delete socketFrom;							//ɾ���׽���
			m_List.GetItemText(i,0,nbuf + 1, 90);	 
			m_List.DeleteItem(i);					//ɾ���˳��û����б��е���Ϣ
			break;
		}
	}

	for(i = 0; i < m_List.GetItemCount(); i++)		//���û��˳���Ϣ���͸������û�
	{
		CMySocket *s;

		s = (CMySocket*)m_List.GetItemData(i);
		s->Send(nbuf,90);							//������Ϣ
	}
	m_criticalSection.Unlock();

	Append(out_msg);
}

void CServerDlg::ParserPkt(CMySocket *socketFrom)
{
	TCHAR SendBuff[4096];		//���ͻ���
	TCHAR ShowBuff[4096];		//��ʾ����
	int len;					//��¼���ͳ���
	int item;					//�б����
	TCHAR pic[2];				//ͼ�����		
	CString ipaddr;				//IP�ַ���	
	UINT port;					//�˿ں�
	CMySocket *s1;				//����һ����Ϣ��Socket		
	CMySocket *s;				//�����û�������Ϣ��Socket
	TCHAR nbuf[100];				//��ʱ������
	//��ʼ����������
	memset(SendBuff,0,4096);
	memset(ShowBuff,0,4096);
	memset(nbuf,0,100);

	len = socketFrom->Receive(SendBuff,4096);				//��ȡ����
	if(len < 1)												//��ȡʧ��
		return;

	if(SendBuff[0] == 0x11)									//���û�����
	{
		socketFrom->GetPeerName(ipaddr,port);						//ȡ������׽������ӵĶԷ���IP��ַ���˿ں�


		socketFrom->m_Player = SendBuff + 2;						//��SOCKETͨ�ŵ��û��ĳ�ν
		pic[0] = SendBuff[1] + 0x30;
		pic[1] = _T('\0');										//ͷ�����

		m_criticalSection.Lock();
		item = m_List.InsertItem(0,SendBuff+2);				//�б��в���һ�У����ز�����к�
		m_List.SetItemData(item,(DWORD)socketFrom);				//�����SOCKETָ�뵽���еĸ���������
		m_List.SetItemText(item,1,ipaddr);					//���õ�2�У�IP��ַ��
		m_List.SetItemText(item,3,pic);						//���õ�3�У��û�ͷ��
		m_criticalSection.Unlock();

		len = _stprintf_s(ShowBuff ,_T(" %s �������ҡ�\r\n"),socketFrom->m_Player);

		s1 = (CMySocket*)m_List.GetItemData(item);
		m_criticalSection.Lock();
		for(item = 0; item < m_List.GetItemCount(); item++)
		{
			s = (CMySocket*)m_List.GetItemData(item);		//ȡ�������ݣ�SOCKETָ�룩
			s->Send(SendBuff,len);							//֪ͨ�����û������û�����
			Sleep(200);
			if(s != socketFrom)	
			{	//�������û�������Ϣ

				m_List.GetItemText(item,3,&pic[0],2);
				nbuf[0] = 0x31;
				nbuf[1] = pic[0];
				m_List.GetItemText(item,0,nbuf+2,100);
				len = _tcslen(nbuf);
				s1->Send(nbuf,14);
			}
			else
			{	//���û���Ϣ��1
				TCHAR tot[10];

				_stprintf_s(tot,_T("%u"),socketFrom->m_Total);
				m_List.SetItemText(item,2,tot);				//���õ�2�У���Ϣ����
			}
		}
		m_criticalSection.Unlock();
	}
	else if(SendBuff[0] == 0x51)							//˽����Ϣ
	{
		TCHAR pName[100],bName[100];
		memset(pName,0,100);
		memset(bName,0,100);
		_tcscpy_s(pName,SendBuff +sizeof(TCHAR));
		for(item = 0; item < m_List.GetItemCount(); item++)
		{
			m_List.GetItemText(item,0,bName,100);
			if(0 == _tcscmp(pName,bName))
			{
				s = (CMySocket*)m_List.GetItemData(item);	//ȡ�������ݣ�SOCKETָ�룩
				s->Send(SendBuff + 99 ,len);
			}
		}
		memcpy(ShowBuff,SendBuff+99,3996);
	}
	else													//������Ϣ
	{
		m_criticalSection.Lock();
		for(item = 0; item < m_List.GetItemCount(); item++)
		{
			s = (CMySocket*)m_List.GetItemData(item);		//ȡ�������ݣ�SOCKETָ�룩
			s->Send(SendBuff,len);

			if(s == socketFrom)
			{
				TCHAR tot[10];

				_stprintf_s(tot,_T("%u"),socketFrom->m_Total);
				m_List.SetItemText(item,2,tot);				//���õ�2�У���Ϣ����
			}
		}
		m_criticalSection.Unlock();
	}
	Append(ShowBuff);
}

void CServerDlg::Append(TCHAR *msg)
{
	CEdit	*pEd = (CEdit*)GetDlgItem(IDC_CTX);		//��ȡ��Ϣ�������� ����Ϣ

	if(m_Ctx.GetLength() > 8196)					//�������Ϣ����
		m_Ctx.Empty();								//�����Ϣ
	m_Ctx += msg;									//׷������Ϣ
	UpdateData(FALSE);								//��ʾ

	pEd->LineScroll(1000);
}