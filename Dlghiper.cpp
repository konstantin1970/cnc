// Dlghiper.cpp : implementation file
//

#include "stdafx.h"
#include "koord.h"
#include "Dlghiper.h"
#include "SerialPort.h"
#include "fstream.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlghiper dialog


CDlghiper::CDlghiper(CWnd* pParent /*=NULL*/)
	: CDialog(CDlghiper::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlghiper)
	//}}AFX_DATA_INIT
}


void CDlghiper::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlghiper)
	DDX_Control(pDX, IDC_LIST1, m_Output);
	DDX_Control(pDX, IDC_BTNWrite, m_BTNWrite);
	DDX_Control(pDX, IDC_BTNDisconnect, m_BTNDisconnect);
	DDX_Control(pDX, IDC_BTNConnect, m_BTNConnect);
	DDX_Control(pDX, IDC_EDITFileName, m_FileName);
	DDX_Control(pDX, IDC_MSFLEXGRID1, m_Grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlghiper, CDialog)
	//{{AFX_MSG_MAP(CDlghiper)
	ON_BN_CLICKED(IDC_BTNConnect, OnBTNConnect)
	ON_BN_CLICKED(IDC_BTNWrite, OnBTNWrite)
	ON_BN_CLICKED(IDC_BTNDisconnect, OnBTNDisconnect)
	ON_BN_CLICKED(IDC_BTNOpenFile, OnBTNOpenFile)
	ON_BN_CLICKED(IDC_BTNPause, OnBTNPause)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTNHome, OnBTNHome)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlghiper message handlers

void CDlghiper::OnBTNConnect() 
{
try {
   
    port.Open(8, 9600, CSerialPort::NoParity, 8, CSerialPort::OneStopBit, CSerialPort::XonXoffFlowControl);
m_BTNConnect.EnableWindow(FALSE);
m_BTNDisconnect.EnableWindow(TRUE);
}
catch (CSerialException* pEx)
{
    TRACE(_T("Handle Exception, Message:%s\n"), pEx->GetErrorMessage());
    pEx->Delete();
	AfxMessageBox("No Connect");
}

/*	CString s;
	BYTE* pBuf = new BYTE[10000];
	if (port.IsOpen() == TRUE)
	{
		char sRxBuf[10];
    DWORD dwRead = port.Read(sRxBuf, 10);
	//port.Read(pBuf,1);
	//s=*pBuf;
	m_output.AddString(s);
	}*/
}

void CDlghiper::OnBTNWrite() 
{
	flag=1;
/*CString text;
CString str;
	for (int i=1; i<= All_g; i++)
	{
		m_Grid.SetCol(1);
	    m_Grid.SetRow(i);
		m_Grid.SetCellBackColor(245);
		m_Grid.SetFocus();
		m_Grid.SetScrollTrack(TRUE);
		m_Grid.SetRedraw(TRUE);
		m_Grid.SetScrollPos(0,i,TRUE);
	
		text = m_Grid.GetText();
	    text = text +"~";
		Sleep(5000);
	    int l = strlen(text);
		if (port.IsOpen() == TRUE){
	    port.Write(text, l);
		}
		else
		{
		AfxMessageBox("Порт не открыт");
		}
	}*/
}

BOOL CDlghiper::OnInitDialog() 
{
	CDialog::OnInitDialog();
	cur_n=1;
	m_BTNDisconnect.EnableWindow(FALSE);
	m_BTNWrite.EnableWindow(FALSE);
 int m_nTimer = SetTimer (1, 2000, 0);

	m_Grid.SetRows(100000); 
	m_Grid.SetCols(2);
//m_gridtarif.SetColWidth(-1,1440);
	m_Grid.SetColWidth(0,500);
	m_Grid.SetColWidth(1,3000);
		
	m_Grid.SetRow(0); 
	m_Grid.SetCol(0); m_Grid.SetText("N");
	m_Grid.SetCol(1); m_Grid.SetText("Value");

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlghiper::OnBTNDisconnect() 
{
		if (port.IsOpen() == TRUE)
	{
	port.Flush();

    port.Close();
	m_BTNConnect.EnableWindow(TRUE);
	m_BTNDisconnect.EnableWindow(FALSE);
		}
		else AfxMessageBox("Port не открыт");
}



void CDlghiper::OnBTNOpenFile() 
{
	CString file;
	
 CFileDialog CurFileDlg(TRUE, NULL, "*.nc");
 
if(CurFileDlg.DoModal() == IDOK)
    {
	file = CurFileDlg.GetPathName();
	m_FileName.SetWindowText(file);
//	m_list.SetWindowText(file);
//	char s[100]= file;
	CString pszFileName = file;
	CStdioFile myFile;
//CFile myFile;
CFileException fileException;

if ( !myFile.Open( pszFileName, CFile::modeReadWrite, &fileException ) )
{
TRACE( "Can't open file %s, error = %u\n",
pszFileName, fileException.m_cause );
}
int len = myFile.GetLength();
//CString s;
CString text;
int CurRow =1;
while(myFile.ReadString(text))
//text=s;
{
//m_Grid.AddItem(text);
m_Grid.SetCol(1);
m_Grid.SetRow(CurRow);
m_Grid.SetText(text);
CurRow++;
}
All_g=CurRow;
//m_FileName.SetWindowText(text);

m_BTNWrite.EnableWindow(TRUE);
	//xMessageBox(s);
	 return;
	}

}



void CDlghiper::OnTimer(UINT nIDEvent) 
{
	CString str,str1;
	int LEN_BUF = 10000;
	CString text;
switch (flag)
{
case 0:
	
	if (port.IsOpen() == TRUE)
	{
	char sRxBuf[10000]; //65536
	port.Set0ReadTimeout();
    port.Read(sRxBuf, LEN_BUF);
	
	for (int i=0; i< LEN_BUF; i++)
		if (sRxBuf[i] != 13) {
			if (sRxBuf[i] == 38)
			{
				flag=1;
			}
			str = str + sRxBuf[i];
		}
		else
		{
			m_Output.AddString(str);
			//SendMessage(m_Output, WM_VSCROLL, SB_LINEDOWN);
			m_Output.SetCurSel(m_Output.GetCount()-1);
			str="";
		}
	}
	else
	{
	m_Output.AddString("Port Closed");
	}
break;
case 1:
	if (cur_n <= All_g)
	{
		for (int j=0; j <=7; j++)
		{
		m_Grid.SetCol(1);
	    m_Grid.SetRow(cur_n);
		m_Grid.SetCellBackColor(245);
		m_Grid.SetRowSel(cur_n);
		m_Grid.SetFocus();
		if (cur_n <=4)
		{
		m_Grid.SetTopRow(cur_n);
		}
		else 
		{
		m_Grid.SetTopRow(cur_n-3);
		}
		str1 = m_Grid.GetText();
		text = text +str1;
		cur_n++;
		}
	    text = text +"~";
		//text = text +"\n \r";
		if (port.IsOpen() == TRUE){
	    int l = strlen(text);
	    port.Write(text, l);
		flag=0;
		}
		else
		{
		AfxMessageBox("Порт не открыт");
		}
	}
break;
case 2:
	text = "n1 g91 n2 g1 x-1000 y-1000~";
	if (port.IsOpen() == TRUE){
	    int l = strlen(text);
	    port.Write(text, l);
		flag=0;
		}
break;
}
	CDialog::OnTimer(nIDEvent);
}

void CDlghiper::OnBTNPause() 
{
	flag=0;	
}

void CDlghiper::OnBTNHome() 
{
	flag=2;	
}
