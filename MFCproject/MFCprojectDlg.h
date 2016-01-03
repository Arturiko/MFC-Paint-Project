
// MFCprojectDlg.h : header file
//

#pragma once
#include "afx.h"
//#include <vector>
//#include <stack>
#include "Shapes.h"
#include "afxwin.h"

using namespace std;
// CMFCprojectDlg dialog
class CMFCprojectDlg : public CDialogEx
{
private:
	/*For dialog*/
	CToolBar m_ToolBar;
	CMFCColorButton m_Color; //Color Taking from the button
	CComboBox m_ComboPenWidth;
	CEdit test;			//For tasting only,need to remove

/*For painting....*/
	int m_PenWidth;
	enum FIGURES { RECTANGLE,ELLIPSE };
	FIGURES ChosenShape;
	int chosenFigure;
	COLORREF curColor;
	CTypedPtrArray< CObArray, Shapes*> sh;
	CTypedPtrArray< CObArray, Shapes*> temp; // for Undo & Redo
/*Boolian*/

	bool cursorPressed; //check if the button for moving is pressed
	bool isPressed;
	bool ShapePressed; // checking if i'm still on shape
	bool ShapeType1;
	bool ShapeType2;
	bool ShapeType3;
/*Points*/
	CPoint startP;
	CPoint endP;
	CPoint TLX; //TOP LEFT Point,for Proportion to moving

	/* From System :*/
	// Construction
public:
	CMFCprojectDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CMFCprojectDlg();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	
// Dialog Data
	enum { IDD = IDD_MFCPROJECT_DIALOG };
// Implementation

protected:
	// Generated message map functions
	HICON m_hIcon;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnClickedMfccolorbutton1();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnChooseRectangle();
	afx_msg void OnChooseEllipse();
	afx_msg void OnChooseSave();
	afx_msg void OnChooseLoad();
	afx_msg void OnChooseUndo();
	afx_msg void OnChooseRedo();
	afx_msg void OnNewWindow();
	afx_msg void OnChooseCursor();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnChooseRandom();
	afx_msg BOOL OnToolTipText(UINT nID, NMHDR* pNMHDR, LRESULT* pResult);
};