// NetUsbDemo4VC6Dlg.cpp : implementation file
//
/*  This file is part of NetUsbDemo.
    NetUsbDemo is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    NetUsbDemo  is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.

    Editors: Paolo & Elio @ www.norduino.com

*/

#include "stdafx.h"
#include "NetUsbDemo4VC6.h"
#include "NetUsbDemo4VC6Dlg.h"

#include "netusb.h"
#include "dbt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL



// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// CNetusbDemo4VCDlg dialog
#define RCV_MSG	(WM_USER + 0x0800)
extern HWND hwnd=NULL;
static void __stdcall TheCallbackFunc(unsigned char* buf, size_t n)
{
    // this post the message in the text area
    // buf contains the payload and n is the payload length
	PostMessage(hwnd,RCV_MSG,(WPARAM)buf,(LPARAM)(n) );
}

/////////////////////////////////////////////////////////////////////////////
// CNetUsbDemo4VC6Dlg dialog

CNetUsbDemo4VC6Dlg::CNetUsbDemo4VC6Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNetUsbDemo4VC6Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNetUsbDemo4VC6Dlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNetUsbDemo4VC6Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNetUsbDemo4VC6Dlg)
	DDX_Control(pDX, IDC_BUTTON_TX2, m_btntx2);
	DDX_Control(pDX, IDC_BUTTON_TX1, m_btntx1);
	DDX_Control(pDX, IDC_BUTTON_RX2, m_btnrx2);
	DDX_Control(pDX, IDC_BUTTON_RX1, m_btnrx1);
	DDX_Control(pDX, IDC_BUTTON_LINK, m_btnlink);
	DDX_Control(pDX, IDC_BUTTON_FRE2, m_btnfre2);
	DDX_Control(pDX, IDC_BUTTON_FRE1, m_btnfre1);
	DDX_Control(pDX, IDC_BUTTON_CLR, m_btnclr);
	DDX_Control(pDX, IDC_STATIC_Text, m_status);
	DDX_Control(pDX, IDC_BUTTON_LED2, m_led2);
	DDX_Control(pDX, IDC_BUTTON_LED1, m_led1);
	DDX_Control(pDX, IDC_LIST_RECI, m_RecivedData);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CNetUsbDemo4VC6Dlg, CDialog)
	//{{AFX_MSG_MAP(CNetUsbDemo4VC6Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_LED1, OnBnClickedBtnLed1)
	ON_BN_CLICKED(IDC_BUTTON_LED2, OnBnClickedBtnLed2)
	ON_BN_CLICKED(IDC_BUTTON_LINK, OnBnClickedBtnLink)
	ON_BN_CLICKED(IDC_BUTTON_CLR, OnBnClickedBtnClr)
	ON_BN_CLICKED(IDC_BUTTON_TX1, OnButtonTx1)
	ON_BN_CLICKED(IDC_BUTTON_TX2, OnButtonTx2)
	ON_BN_CLICKED(IDC_BUTTON_RX1, OnButtonRx1)
	ON_BN_CLICKED(IDC_BUTTON_RX2, OnButtonRx2)
	ON_BN_CLICKED(IDC_BUTTON_FRE1, OnButtonFre1)
	ON_BN_CLICKED(IDC_BUTTON_FRE2, OnButtonFre2)
	//}}AFX_MSG_MAP
	ON_MESSAGE(RCV_MSG, OnNewMsg)
	ON_WM_DEVICECHANGE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetUsbDemo4VC6Dlg message handlers

BOOL CNetUsbDemo4VC6Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	DisableLedButton();
	NetusbRegisterNotification(GetSafeHwnd());
    hwnd=GetSafeHwnd();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CNetUsbDemo4VC6Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CNetUsbDemo4VC6Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CNetUsbDemo4VC6Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


/********************************************************/
//May be some of variables need change its name,
//for this version is not critically the same with version of VC7
/********************************************************/




void CNetUsbDemo4VC6Dlg::AttemptConnection(void)
{

	if (m_IsConnected ==true)
	{
		MessageBox(_T("Already connected!"));
		return;
	}
	DWORD results;
	// Check for connected devices
	results = NetusbGetNumDevices(VID_NETUSB, PID_NETUSB24L01);
	// Only proceed if 1 device is found
	if (results ==1)
	{
		// Open connection to device
		results = NetusbOpen(0,VID_NETUSB, PID_NETUSB24L01);
		// If device connection not established, output failure
		if (results != HID_DEVICE_SUCCESS)
		{
			MessageBox(_T("Error in connecting to device."));
		}
		else
		{
			m_IsConnected = true;
			//m_nTimer =SetTimer (1,10,NULL);	// Create timer to be used to
			EnableLedButton();

			//HID_RX_THREAD = CreateThread (NULL,NULL,InterruptThreadProc,this,0,0);

		}
	}
	else
	{
		MessageBox(_T("No device found."));
	}
}

/*******************************************************/
/*
	CButton	m_btntx2;
	CButton	m_btntx1;
	CButton	m_btnrx2;
	CButton	m_btnrx1;
	CButton	m_btnlink;
	CButton	m_btnfre2;
	CButton	m_btnfre1;
	CButton	m_btnclr;
	CStatic	m_status;
	CButton	m_led2;
	CButton	m_led1;
	CListBox	m_RecivedData;
*/
/*******************************************************/
void CNetUsbDemo4VC6Dlg::EnableLedButton()
{
	m_btnfre1.EnableWindow(true);
	m_btnfre2.EnableWindow(true);
	m_btntx1.EnableWindow(true);
	m_btntx2.EnableWindow(true);
	m_btnrx1.EnableWindow(true);
	m_btnrx2.EnableWindow(true);
	m_led1.EnableWindow(true);
	m_led2.EnableWindow(true);

	m_status.SetWindowText(_T("Already connected!"));
	//m_nTimer =SetTimer(1,200,0);
	m_IsConnected = true ;

	NetusbSetCallback(TheCallbackFunc);
	NetusbStartListen();
}

void CNetUsbDemo4VC6Dlg::DisableLedButton()
{

	m_btnfre1.EnableWindow(false);
	m_btnfre2.EnableWindow(false);
	m_btntx1.EnableWindow(false);
	m_btntx2.EnableWindow(false);
	m_btnrx1.EnableWindow(false);
	m_btnrx2.EnableWindow(false);
	m_led1.EnableWindow(false);
	m_led2.EnableWindow(false);
	m_status.SetWindowText(_T("Disconnect"));

	m_IsConnected = false;
	NetusbStopListen();
	//KillTimer(m_nTimer);
}


BOOL CNetUsbDemo4VC6Dlg::OnDeviceChange(UINT nEventType, DWORD dwData)
{
	DWORD results;

	switch(nEventType)
	{
		// A device has been inserted and is now available.
	case DBT_DEVICEARRIVAL:
		AttemptConnection();
		break;

		// A device has been removed from USB.
	case DBT_DEVICEREMOVECOMPLETE:
		// Check for  devices
		results = NetusbGetNumDevices(VID_NETUSB, PID_NETUSB24L01);
		if (results == 0)
		{
			// Close device if found
			//RXthreadmaycontinue =false;
			Sleep(10);
			DisableLedButton();
			NetusbClose();
			//HID_RX_THREAD =NULL;
		}
		break;

	default:
		break;
	}

	return TRUE;
}


void CNetUsbDemo4VC6Dlg::AddRecievedData(CString NewData)
{

	m_RecivedData.AddString( NewData );

	// display only last 100 messages recieved
	if(m_RecivedData.GetCount()>100) {
		m_RecivedData.DeleteString(0);
	}

	// Set Focus on Last Element
	int nCount = m_RecivedData.GetCount();
	if (nCount > 0) m_RecivedData.SetCurSel(nCount-1);

}

static DWORD WINAPI InterruptThreadProc(LPVOID lpParameter)
{
	CNetUsbDemo4VC6Dlg* dlg;
	dlg = (CNetUsbDemo4VC6Dlg*)lpParameter;

	BYTE reportbuffer[255];
	DWORD status;
    BYTE byteReceved;
	dlg->RXthreadmaycontinue = TRUE;   // Variable will be cleared whenever
	// device is disconnected

	while (dlg->RXthreadmaycontinue == TRUE)
	{
		// Attempt to retrieve a report
		status = NetusbGetData(reportbuffer,&byteReceved);
		// If a report has been recieved, call the callback routine
		// to process the data stored in reportbuffer
		if (status == HID_DEVICE_SUCCESS)
		{
			dlg->HIDcallback (reportbuffer);
		}
		else
		{
			Sleep(5);
		}
	}

	return 1;
}

void CNetUsbDemo4VC6Dlg::HIDcallback (BYTE* reportbuffer)
{

	if(reportbuffer[1]==1)
	{
		AddRecievedData(_T("Button1 has been pressed"));
	}
	if(reportbuffer[2]==1)
	{
		AddRecievedData(_T("Button2 has been pressed"));
	}

}

void CNetUsbDemo4VC6Dlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	NetusbUnregisterNotification();
	NetusbClose();
	CDialog::OnClose();
}

LRESULT CNetUsbDemo4VC6Dlg::OnNewMsg (WPARAM wParam, LPARAM lParam)
{
	BYTE* reportbuffer =(BYTE* )wParam;
/*
	if(reportbuffer[1]==1)
	{
		AddRecievedData(_T("Button1 has been pressed"));
	}
	if(reportbuffer[2]==1)
	{
		AddRecievedData(_T("Button2 has been pressed"));
	}
*/
   char                   temp[128]  = "";
	char                   temp2[128]  = "";
	ULONG	i;
	//ULONG   j;
	PUCHAR	ptr;

	unsigned char* buf=(unsigned char*)wParam;
	ptr = (PUCHAR) (buf);
	unsigned	length=(size_t)32;

	for(i=1;i<length;++i)
	{
		wsprintf(temp2,"%02X ",*ptr++);
		strcat(temp,temp2);
	}
	AddRecievedData(temp);
	UpdateData(FALSE);
    return 0;
}

void CNetUsbDemo4VC6Dlg::OnBnClickedBtnLed1()
{
	// TODO: Add your control notification handler code here
	unsigned char buf[32];
	memset(buf,0,32);
    //buf[0]=0xaa;
	buf[30]=1;
	buf[31]=0;
//	for(int i=0;i<32;i++)
//	{
//		buf[i]=1;
//	}
		buf[1]=1;
	buf[2]=0;
	DWORD r =NetusbSendData(buf,32);

}

void CNetUsbDemo4VC6Dlg::OnBnClickedBtnLed2()
{
	// TODO: Add your control notification handler code here
	unsigned char buf[32];
	memset(buf,0,32);
	buf[30]=0;
	buf[31]=1;

		buf[1]=0;
	buf[2]=1;

	NetusbSendData(buf,32);

}

void CNetUsbDemo4VC6Dlg::OnBnClickedBtnLink()
{
	// TODO: Add your control notification handler code here
	AttemptConnection();

}


void CNetUsbDemo4VC6Dlg::OnBnClickedBtnClr()
{
	// TODO: Add your control notification handler code here
	while(m_RecivedData.GetCount()>0) {
		m_RecivedData.DeleteString(0);
	}

}

void CNetUsbDemo4VC6Dlg::OnButtonTx1()
{
	// TODO: Add your control notification handler code here
	NetusbSetTxaddr(0x34,0x43,0x10,0x10);
}



void CNetUsbDemo4VC6Dlg::OnButtonTx2()
{
	// TODO: Add your control notification handler code here
	NetusbSetTxaddr(0XCC,0XCC,0XCC,0XCC);

}

void CNetUsbDemo4VC6Dlg::OnButtonRx1()
{
	// TODO: Add your control notification handler code here
	NetusbSetRxaddr(0x34,0x43,0x10,0x10);

}

void CNetUsbDemo4VC6Dlg::OnButtonRx2()
{
	// TODO: Add your control notification handler code here
	NetusbSetRxaddr(0XCC,0XCC,0XCC,0XCC);

}

void CNetUsbDemo4VC6Dlg::OnButtonFre1()
{
	// TODO: Add your control notification handler code here
	NetusbSetFrequence(1); //433

}

void CNetUsbDemo4VC6Dlg::OnButtonFre2()
{
	// TODO: Add your control notification handler code here
	NetusbSetFrequence(8); //433

}
