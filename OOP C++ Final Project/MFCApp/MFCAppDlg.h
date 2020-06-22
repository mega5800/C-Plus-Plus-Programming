#pragma once
#include <iostream>
#include <vector>
#include "Shape.h"
#include "Line.h"
#include"Circle.h"
#include "Graph_Matrix.h"
#include <fstream>
#include <string>

using namespace std;

// CMFCAppDlg dialog
class CMFCAppDlg : public CDialogEx
{
// Construction
public:
	vector<Circle*> circ;
	vector<Line*> lin;
	vector<int> clique;

	CMFCAppDlg(CWnd* pParent = nullptr);
	Shape* s = nullptr;
	Circle* tmp = nullptr;
	Graph_Matrix mat;

	bool count_L_click = true;
	bool is_move = false;
	bool is_delete = false;
	bool is_rebuild = false;

	CRect drawArea;
	CRect windowSize;

	void Update_Info();
	bool Line_Check(Shape*, Shape*);
	vector<Circle*>::iterator Check_Circ(const CPoint&);

	~CMFCAppDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedOk();
};