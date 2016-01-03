
// MFCprojectDlg.cpp : implementation file
//
#include "afx.h"
#include "stdafx.h"
#include "MFCproject.h"
#include "MFCprojectDlg.h"
#include "afxdialogex.h"
#include "Shapes.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CMFCprojectDlg::CMFCprojectDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCprojectDlg::IDD, pParent)
{

	m_PenWidth=1;
	ChosenShape=RECTANGLE;
	isPressed=false;
	cursorPressed=false;
	ShapePressed=false;
	ShapeType1 = false;
	ShapeType2 = false;
	ShapeType3 = false;
	curColor=RGB(0,0,0);
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
CMFCprojectDlg::~CMFCprojectDlg()
{
	sh.RemoveAll();
	temp.RemoveAll();
}
void CMFCprojectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_ComboPenWidth);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON1, m_Color);
	DDX_Control(pDX, IDC_EDIT1, test);
}

BEGIN_MESSAGE_MAP(CMFCprojectDlg, CDialogEx)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipText)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipText)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON1, &CMFCprojectDlg::OnClickedMfccolorbutton1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CMFCprojectDlg::OnSelchangeCombo1)
	ON_COMMAND(ID_CHOOSE_RECTANGLE, &CMFCprojectDlg::OnChooseRectangle)
	ON_COMMAND(ID_CHOOSE_ELLIPSE, &CMFCprojectDlg::OnChooseEllipse)
	ON_COMMAND(ID_CHOOSE_SAVE, &CMFCprojectDlg::OnChooseSave)
	ON_COMMAND(ID_CHOOSE_LOAD, &CMFCprojectDlg::OnChooseLoad)
	ON_COMMAND(ID_CHOOSE_UNDO, &CMFCprojectDlg::OnChooseUndo)
	ON_COMMAND(ID_CHOOSE_REDO, &CMFCprojectDlg::OnChooseRedo)
	ON_COMMAND(ID_NEW_WINDOW, &CMFCprojectDlg::OnNewWindow)
	ON_COMMAND(ID_CHOOSE_CURSOR, &CMFCprojectDlg::OnChooseCursor)
	ON_COMMAND(ID_Choose_Random, &CMFCprojectDlg::OnChooseRandom)
	ON_EN_CHANGE(IDC_EDIT1, &CMFCprojectDlg::OnEnChangeEdit1)

END_MESSAGE_MAP()


// CMFCprojectDlg message handlers

BOOL CMFCprojectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	if(!m_ToolBar.CreateEx(this, TBSTYLE_FLAT,
		WS_VISIBLE | CBRS_TOP  | CBRS_TOOLTIPS | 
		CBRS_FLYBY | CBRS_SIZE_DYNAMIC) || 
		!m_ToolBar.LoadToolBar(IDR_TOOLBAR1))
	{
		EndDialog(IDCANCEL);
	}
	m_ToolBar.EnableToolTips(true);
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST,0);

	m_ComboPenWidth.SetItemData( m_ComboPenWidth.AddString(L"0.1 mm"), 1 );
	m_ComboPenWidth.SetItemData( m_ComboPenWidth.AddString(L"0.2 mm"), 2 );
	m_ComboPenWidth.SetItemData( m_ComboPenWidth.AddString(L"0.4 mm"), 4 );
	m_ComboPenWidth.SetItemData( m_ComboPenWidth.AddString(L"0.8 mm"), 8 );
	m_ComboPenWidth.SetItemData( m_ComboPenWidth.AddString(L"1 mm"), 10 );
	m_ComboPenWidth.SetCurSel( 0 );
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCprojectDlg::OnPaint()
{
	//CPaintDC dc (this);
	//CPen old(PS_SOLID, m_PenWidth, curColor);
	//CPen old(PS_SOLID, 9, RGB(255,174,201));
	//dc.SelectObject(&old);
	CPaintDC dc(this);
	CPen old(PS_SOLID, m_PenWidth, curColor);
	CPen my_pen(PS_DOT, 1, curColor);
	CBrush Br_o(curColor);
	for(int i=0;i<sh.GetSize();i++)
		sh[i]->Draw(&dc);

	if(cursorPressed==true && ShapePressed==true &&  ShapeType1==false &&  ShapeType2 == false && ShapeType3 == false )
	{ //From corner left up
		dc.SelectObject(&my_pen);
		dc.SelectObject(&Br_o);
		dc.MoveTo(sh[chosenFigure]->getx1()-5,sh[chosenFigure]->gety1()-5);
		dc.LineTo(sh[chosenFigure]->getx1()-5,sh[chosenFigure]->gety2()+5);
		dc.LineTo(sh[chosenFigure]->getx2()+5,sh[chosenFigure]->gety2()+5);
		dc.LineTo(sh[chosenFigure]->getx2()+5,sh[chosenFigure]->gety1()-5);
		dc.LineTo(sh[chosenFigure]->getx1()-5,sh[chosenFigure]->gety1()-5);
		dc.SelectObject(&old);
	}
	
	else if(cursorPressed && ShapePressed && ShapeType1) //From corner right down
	{
		dc.SelectObject(&my_pen);
		dc.SelectObject(&Br_o);
		dc.MoveTo(sh[chosenFigure]->getx1()+5,sh[chosenFigure]->gety1()+5);
		dc.LineTo(sh[chosenFigure]->getx1()+5,sh[chosenFigure]->gety2()-5);
		dc.LineTo(sh[chosenFigure]->getx2()-5,sh[chosenFigure]->gety2()-5);
		dc.LineTo(sh[chosenFigure]->getx2()-5,sh[chosenFigure]->gety1()+5);
		dc.LineTo(sh[chosenFigure]->getx1()+5,sh[chosenFigure]->gety1()+5);
		dc.SelectObject(&old);
	}
	else if(cursorPressed && ShapePressed && ShapeType2)//From corner right up
	{
		dc.SelectObject(&my_pen);
		dc.SelectObject(&Br_o);
		dc.MoveTo(sh[chosenFigure]->getx1()+5,sh[chosenFigure]->gety1()-5);
		dc.LineTo(sh[chosenFigure]->getx1()+5,sh[chosenFigure]->gety2()+5);
		dc.LineTo(sh[chosenFigure]->getx2()-5,sh[chosenFigure]->gety2()+5);
		dc.LineTo(sh[chosenFigure]->getx2()-5,sh[chosenFigure]->gety1()-5);
		dc.LineTo(sh[chosenFigure]->getx1()+5,sh[chosenFigure]->gety1()-5);
		dc.SelectObject(&old);
	}
		else if(cursorPressed && ShapePressed && ShapeType3)//From corner left down
	{
		dc.SelectObject(&my_pen);
		dc.SelectObject(&Br_o);
		dc.MoveTo(sh[chosenFigure]->getx1()-5,sh[chosenFigure]->gety1()+5);
		dc.LineTo(sh[chosenFigure]->getx1()-5,sh[chosenFigure]->gety2()-5);
		dc.LineTo(sh[chosenFigure]->getx2()+5,sh[chosenFigure]->gety2()-5);
		dc.LineTo(sh[chosenFigure]->getx2()+5,sh[chosenFigure]->gety1()+5);
		dc.LineTo(sh[chosenFigure]->getx1()-5,sh[chosenFigure]->gety1()+5);
		dc.SelectObject(&old);
	}
	if ((isPressed) && (cursorPressed == false))
	{
		dc.SelectObject(&old);
		dc.MoveTo(startP.x,startP.y);
		dc.LineTo(startP.x,endP.y);
		dc.LineTo(endP.x,endP.y);
		dc.LineTo(endP.x,startP.y);
		dc.LineTo(startP.x,endP.y);
	}
	CDialogEx::OnPaint();
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCprojectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void CMFCprojectDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	endP=startP=point;
	isPressed=true;
	TLX =point;
	test.SetWindowTextW(_T("TEST"));
	if(cursorPressed)
	{
		
		for (int i=sh.GetSize()-1;i>=0;i--)
		{

			if (point.x >= sh[i]->getx1() && point.x <= sh[i]->getx2() && point.y >= sh[i]->gety1() && point.y <= sh[i]->gety2())
			{
				ShapePressed=true;
				chosenFigure=i;
				CString s;
				s.Format(_T("%d"),chosenFigure+1);
				test.SetWindowTextW(s);
				ShapeType1 = false;
				ShapeType2 = false;
				ShapeType3 = false;
				break;
			}
			else if (point.x <= sh[i]->getx1() && point.x >= sh[i]->getx2() && point.y <= sh[i]->gety1() && point.y >= sh[i]->gety2())
			{
				ShapePressed=true;
				chosenFigure=i;
				CString s;
				s.Format(_T("%d"),chosenFigure+1);
				test.SetWindowTextW(s);
				ShapeType1=true;
				break;
			}
			else if (point.x <= sh[i]->getx1() && point.x >= sh[i]->getx2() && point.y >= sh[i]->gety1() && point.y <= sh[i]->gety2())
			{
				ShapePressed=true;
				chosenFigure=i;
				CString s;
				s.Format(_T("%d"),chosenFigure+1);
				test.SetWindowTextW(s);
				ShapeType2=true;
				break;
			}
			else if (point.x >= sh[i]->getx1() && point.x <= sh[i]->getx2() && point.y <= sh[i]->gety1() && point.y >= sh[i]->gety2())
			{
				ShapePressed=true;
				chosenFigure=i;
				CString s;
				s.Format(_T("%d"),chosenFigure+1);
				test.SetWindowTextW(s);
				ShapeType3=true;
				break;
			}
			ShapePressed=false;	
		}
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}

void CMFCprojectDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if ((isPressed) && (cursorPressed==false))
	{
		endP=point;
		isPressed=false;
		switch(ChosenShape)
		{
		case RECTANGLE:
			sh.Add(new draw_rect(startP.x,startP.y,endP.x,endP.y,m_PenWidth,curColor));
			break;
		case ELLIPSE:
			sh.Add(new draw_ellipse(startP.x,startP.y,endP.x,endP.y,m_PenWidth,curColor));
			break;
		}
		Invalidate();
	}
	if ((isPressed) && (ShapePressed) && (cursorPressed))
	{
		isPressed=(false);
		ShapePressed=false;
		Invalidate();
		ShapeType1=false;
		ShapeType2 = false;
		ShapeType3 = false;
	}
	CDialogEx::OnLButtonUp(nFlags, point);
}

void CMFCprojectDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	if ((isPressed) && (ShapePressed==false) && (cursorPressed==false))
	{
		CClientDC dc(this);
		//CBrush myBrush,*oldBrush;
		//myBrush.CreateSolidBrush(curColor);
		//oldBrush=dc.SelectObject( &myBrush );  
		CPen myPen1(PS_SOLID, m_PenWidth, curColor);
		CPen *oldPen;
		oldPen=dc.SelectObject( &myPen1 ); 
		switch(ChosenShape)
		{
		case RECTANGLE:
			dc.SetROP2(R2_NOTXORPEN);
			//dc.SelectStockObject(NULL_BRUSH);
			dc.Rectangle(startP.x, startP.y,endP.x, endP.y);
			endP=point;
			dc.Rectangle(startP.x, startP.y,endP.x, endP.y);
			break;
		case ELLIPSE:
			dc.SetROP2(R2_NOTXORPEN);  
			//dc.SelectStockObject(NULL_BRUSH);
			dc.Ellipse(startP.x,startP.y,endP.x,endP.y);
			endP=point;
			dc.Ellipse(startP.x,startP.y,endP.x,endP.y);
			break;
		}
		dc.SelectObject( oldPen ); 
		dc.SetROP2(R2_COPYPEN);
	}
	else if ((isPressed) && (cursorPressed) && (ShapePressed))
	{
		RECT r;
		int x,y;
		int xx,yy;
		xx = TLX.x, yy = TLX.y;
		TLX = point;
		x = (TLX.x - xx);
		y = (TLX.y - yy);
		sh[chosenFigure]->setx1(sh[chosenFigure]->getx1() + x);
		sh[chosenFigure]->sety1(sh[chosenFigure]->gety1() + y);
		sh[chosenFigure]->setx2(sh[chosenFigure]->getx2() + x);
		sh[chosenFigure]->sety2(sh[chosenFigure]->gety2() + y);
		r.left=min(sh[chosenFigure]->getx1(),sh[chosenFigure]->getx2())-50;
		r.right=max(sh[chosenFigure]->getx1(),sh[chosenFigure]->getx2())+50;
		r.top=min(sh[chosenFigure]->gety1(),sh[chosenFigure]->gety2())-50;
		r.bottom=max(sh[chosenFigure]->gety1(),sh[chosenFigure]->gety2())+50;
		InvalidateRect(&r);


	}
	CDialogEx::OnMouseMove(nFlags, point);
}


void CMFCprojectDlg::OnClickedMfccolorbutton1()
{
	// TODO: Add your control notification handler code here
	curColor = m_Color.GetColor();
}
void CMFCprojectDlg::OnSelchangeCombo1()
{
	// TODO: Add your control notification handler code here
	m_PenWidth = m_ComboPenWidth.GetItemData( m_ComboPenWidth.GetCurSel() );
}

void CMFCprojectDlg::OnChooseRectangle()
{
	// TODO: Add your command handler code here
	ChosenShape=RECTANGLE;
	isPressed=false;
	ShapePressed=false;
	cursorPressed=false;
}

void CMFCprojectDlg::OnChooseEllipse()
{
	// TODO: Add your command handler code here
	ChosenShape=ELLIPSE;
	isPressed=false;
	ShapePressed=false;
	cursorPressed=false;
}

void CMFCprojectDlg::OnChooseSave()
{
	// TODO: Add your command handler code here
	CFile file(_T("File.$$"), CFile::modeWrite | CFile::modeCreate);
	CArchive ar (&file, CArchive::store);
	sh.Serialize(ar);
	ar.Close();
	file.Close();
}

void CMFCprojectDlg::OnChooseLoad()
{
	// TODO: Add your command handler code here
	CFile file(_T("File.$$"), CFile::modeRead);
	CArchive ar (&file, CArchive::load);
	sh.Serialize(ar);
	ar.Close();
	file.Close();
	Invalidate();





}


void CMFCprojectDlg::OnChooseUndo()
{
	// TODO: Add your command handler code here
	if(sh.GetSize()!=0)
	{
		temp.Add(sh[sh.GetSize()-1]);
		sh.RemoveAt(sh.GetSize()-1);
		Invalidate();
	}
}


void CMFCprojectDlg::OnChooseRedo()
{
	// TODO: Add your command handler code here
	if(temp.GetSize() !=0 )
	{
		sh.InsertAt(sh.GetSize(),temp.GetAt(temp.GetSize()-1));
		temp.RemoveAt(temp.GetSize()-1);
		Invalidate();
	}

}

void CMFCprojectDlg::OnNewWindow()
{
	// TODO: Add your command handler code here
	sh.RemoveAll();
	temp.RemoveAll();
	isPressed=false;
	ShapePressed=false;
	cursorPressed=false;
	Invalidate();
}


void CMFCprojectDlg::OnChooseCursor()
{
	// TODO: Add your command handler code here
	cursorPressed=true;
}


	void CMFCprojectDlg::OnChooseRandom()
{
	srand (time(NULL));

	int i=0;
	int x,x1,y,y1,width,green,blue,red;
	x = rand() % 875 + 1;
	
	y = rand() % 520 + 1;
	x1 = rand() % 700 + 1;
	y1 = rand() % 500+36;
	
	 width = rand() %10+1;
	 red = rand () %254 +1;
	 green = rand () %254 +1;
	 blue = rand () %254 +1;

	sh.Add(new draw_rect(x,y,x1,y1,width,RGB(red,green,blue)));
	
	
	Invalidate();

	width = rand() %10+1;
	red = rand () %254 +1;
	green = rand () %254 +1;
	blue = rand () %254 +1;
	x = rand() % 800 + 1;
	y = rand() % 500 + 1;
	x1 = rand() % 400 + 1;
	y1 = rand() % 500 +36;
	

	sh.Add(new draw_ellipse(x,y,x1,y1,width,RGB(red,green,blue))); 

	Invalidate();


}
void CMFCprojectDlg::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not

}
/*Making A Tool Tip......*/
BOOL CMFCprojectDlg::OnToolTipText(UINT, NMHDR* pNMHDR, LRESULT* pResult)
{
	ASSERT(pNMHDR->code == TTN_NEEDTEXTA || pNMHDR->code == TTN_NEEDTEXTW);

	// if there is a top level routing frame then let it handle the message
	if (GetRoutingFrame() != NULL) return FALSE;

	// to be thorough we will need to handle UNICODE versions of the message also !!
	TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pNMHDR;
	TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pNMHDR;
	TCHAR szFullText[512];
	CString strTipText;
	UINT nID = pNMHDR->idFrom;

	if (pNMHDR->code == TTN_NEEDTEXTA && (pTTTA->uFlags & TTF_IDISHWND) ||
		pNMHDR->code == TTN_NEEDTEXTW && (pTTTW->uFlags & TTF_IDISHWND))
	{
		// idFrom is actually the HWND of the tool 
		nID = ::GetDlgCtrlID((HWND)nID);
	}

	if (nID != 0) // will be zero on a separator
	{
		AfxLoadString(nID, szFullText);
		strTipText=szFullText;

#ifndef _UNICODE
		if (pNMHDR->code == TTN_NEEDTEXTA)
		{
			lstrcpyn(pTTTA->szText, strTipText, sizeof(pTTTA->szText));
		}
		else
		{
			_mbstowcsz(pTTTW->szText, strTipText, sizeof(pTTTW->szText));
		}
#else
		if (pNMHDR->code == TTN_NEEDTEXTA)
		{
			_wcstombsz(pTTTA->szText, strTipText,sizeof(pTTTA->szText));
		}
		else
		{
			lstrcpyn(pTTTW->szText, strTipText, sizeof(pTTTW->szText));
		}
#endif

		*pResult = 0;

		// bring the tooltip window above other popup windows
		::SetWindowPos(pNMHDR->hwndFrom, HWND_TOP, 0, 0, 0, 0,
			SWP_NOACTIVATE|SWP_NOSIZE|SWP_NOMOVE|SWP_NOOWNERZORDER);

		return TRUE;
	}

	return FALSE;
}



