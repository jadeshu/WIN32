#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "afxext.h"


// CLogDlg 对话框

class CLogDlg : public CDialog
{
	DECLARE_DYNAMIC(CLogDlg)

public:
	CLogDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLogDlg();

// 对话框数据
	enum { IDD = IDD_LOGDLG };
	
	CBitmap m_bmBack;		//背景图片
	CBrush  m_brBack;		//背景画刷
	CImageList m_imageList; //图像列表
	
	TCHAR m_IpAddrS[32];	//用户IP地址字符串
	int m_imgNum;			//用户选择的图像索引


	/************************************************************************/
	/* 绑定变量                                                             */
	/************************************************************************/
	CIPAddressCtrl m_IpAddrCtrl;	//用户IP地址
    CComboBoxEx m_ComboBoxPhotoImg;	//用户图像
	CString m_UserName;				//用户名称	
	CBitmapButton m_bLogIn;			//登陆按钮
	CBitmapButton m_bCancel;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
		
	virtual void OnOK();
	
	
};
