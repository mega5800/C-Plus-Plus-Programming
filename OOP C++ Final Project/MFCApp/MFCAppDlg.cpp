// MFCAppDlg.cpp : implementation file
//
#include "resource.h"
#include "stdafx.h"
#include "MFCApp.h"
#include "MFCAppDlg.h"
#include "afxdialogex.h"
#include "Shape.h"
#include "Line.h"
#include"Circle.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCAppDlg dialog

CMFCAppDlg::CMFCAppDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//this->mat = Graph_Matrix(0, lin);
}

void CMFCAppDlg::Update_Info()
{
	unsigned int tmp_size = 0;
	int max = 0, min = 0;
	CString msg;
	msg.Format(_T("Vertices: %d"), circ.size());
	SetDlgItemText(ID_SEPARATOR, msg);

	msg.Format(_T("Edges: %d"), this->mat.Get_Num_Edges());
	SetDlgItemText(ID_RECORD_PREV, msg);

	if (circ.size() == 0)
		tmp_size = 0;
	else
	{
		if (lin.size() == 0)
			tmp_size = 1;
		else
		{
			clique.clear();
			clique.shrink_to_fit();
			this->mat.Find_Max_Clique(&tmp_size, clique);

			this->mat.Write_File();

			ifstream file("cliques.txt");
			string temp, final_str="Clique list:\n";
			while (getline(file, temp)) 
			{
				final_str += temp;
				final_str += '\n';
			}

			msg = final_str.c_str();
			SetDlgItemText(ID_WINDOW_TILE_VERT, msg);
		}
	}
	msg.Format(_T("Max clique : %d"), tmp_size);
	SetDlgItemText(IDABORT, msg);

	msg.Format(_T("ꭓ(G): %d"), tmp_size);
	SetDlgItemText(ID_WIZNEXT, msg);

	if (lin.size() != 0)
	{
		this->mat.Find_Max_Min_Deg(&max, &min);
		msg.Format(_T("Δ(G): %d"), max);
		SetDlgItemText(ID_WIZBACK, msg);
		msg.Format(_T("δ(G): %d"), min);
		SetDlgItemText(ID_WIZFINISH, msg);
	}
	else
	{
		msg.Format(_T("Δ(G): 0"));
		SetDlgItemText(ID_WIZBACK, msg);
		msg.Format(_T("δ(G): 0"));
		SetDlgItemText(ID_WIZFINISH, msg);
	}
}

bool CMFCAppDlg::Line_Check(Shape *a, Shape *b)
{
	vector<Line*>::iterator n = lin.begin();
	while (n != lin.end())
	{
		if (((*n)->c_one == a) && ((*n)->c_two == b))
			return false;
		else
			if (((*n)->c_one == b) && ((*n)->c_two == a))
				return false;
		n++;
	}
	return true;
}

CMFCAppDlg::~CMFCAppDlg()
{
	for (unsigned int i = 0; i < circ.size(); i++)
		delete circ[i];

	for (unsigned int i = 0; i < lin.size(); i++)
		delete lin[i];

	lin.clear();
	circ.clear();
	clique.clear();
}

vector<Circle*>::iterator CMFCAppDlg::Check_Circ(const CPoint &p)
{
	vector<Circle*>::iterator i = circ.begin();
	while (i !=circ.end())
	{
		if (**i == p)
		{
			return i;
			break;
		}
		else
			++i;
	}
	return circ.end();
}

void CMFCAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCAppDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
ON_WM_MBUTTONDBLCLK()
ON_WM_LBUTTONDBLCLK()
ON_WM_MOUSEMOVE()
ON_BN_CLICKED(IDOK, &CMFCAppDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CMFCAppDlg message handlers

BOOL CMFCAppDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	HICON hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON1));
	SetIcon(hIcon, FALSE);
	//SetIcon(m_hIcon, TRUE);			// Set big icon
	//SetIcon(m_hIcon, FALSE);		// Set small icon
	// TODO: Add extra initialization here
	GetClientRect(&windowSize);
	drawArea.SetRect(windowSize.Width() / 10, 0, windowSize.Width() - 123, windowSize.Height());
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCAppDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
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
		CDialogEx::OnPaint();
		CDC dcBackBuffer;
		CClientDC dc(this);
		CString str;
		dc.Rectangle(drawArea);
		unsigned int i, n;
		CPen pen, pen_clique;
		pen.CreatePen(PS_SOLID, 4, (COLORREF)RGB(0, 201, 87));
		pen_clique.CreatePen(PS_SOLID, 2, (COLORREF)RGB(205, 0, 205));

		Update_Info();

		for (i = 0; i < lin.size(); i++)
			lin[i]->Draw(&dc);

		for (i = 0; i < circ.size(); i++)
		{
			if (tmp == circ[i])
				dc.SelectObject(&pen);
			else
			{
				bool cliq = false;
				for (n= 0; n < clique.size(); n++)
					if (circ[i]->index - 1 == clique[n])
						cliq = true;

				if (cliq)
					dc.SelectObject(&pen_clique);
				else
					dc.SelectStockObject(BLACK_PEN);
			}

			circ[i]->Draw(&dc);
			circ[i]->index = i + 1;
			str.Format(_T("%d"), i + 1);
			dc.TextOutW(circ[i]->GetX() - 3, circ[i]->GetY() - 9, str);

			dc.SelectStockObject(BLACK_PEN);
		}
		if (is_rebuild)
		{
			this->mat.Rebuild_Mat(circ.size(), lin);
			is_rebuild = false;
		}
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCAppDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	CDialogEx::OnLButtonUp(nFlags, point);

	if (point.x > drawArea.right)
		return;
	if (point.x < drawArea.left)
		return;

	if (!is_delete)
	{
		vector<Circle*>::iterator i = circ.end();
		if ((i = Check_Circ(point)) == circ.end())
		{
			circ.push_back(new Circle(point.x, point.y));
			is_rebuild = true;
		}
		else
		{
			if (!is_move)
			{
				if (count_L_click)
					tmp = *i;
				else
				{
					if (tmp != *i)
					{
						if (Line_Check(tmp, *i))
						{
							if ((tmp->index >= 0) && ((*i)->index >= 0))
								lin.push_back(new Line(tmp, *i));
							this->mat.Update_Mat(lin);
						}
						else
							AfxMessageBox(_T("There's already edge here!"));
					}
					tmp = nullptr;
				}
				count_L_click = !count_L_click;
			}
		}
	}
	is_move = false;
	is_delete = false;
	s = nullptr;
	InvalidateRect(&drawArea);
	//Invalidate();
}

void CMFCAppDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CDialogEx::OnLButtonDown(nFlags, point);
	vector<Circle*>::iterator i;
	if ((i = Check_Circ(point)) != circ.end())
		s = *i;
}

void CMFCAppDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	CDialogEx::OnMouseMove(nFlags, point);
	if (s)
	{
		s->SetX(point.x);
		s->SetY(point.y);
		InvalidateRect(&drawArea);
		is_move = true;
	}
}

void CMFCAppDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CDialogEx::OnLButtonDblClk(nFlags, point);

	vector<Circle*>::iterator i;
	vector<Line*>::iterator n = lin.begin();
	if ((i = Check_Circ(point)) != circ.end())
	{
		while (n != lin.end())
		{
			if (((*n)->c_one == *i) || (((*n)->c_two == *i)))
			{
				delete *n;
				n = lin.erase(n);
			}
			else
				n++;
		}

		delete *i;
		is_delete = true;
		circ.erase(i);
		is_rebuild = true;
		InvalidateRect(&drawArea);
	}
}

void CMFCAppDlg::OnBnClickedOk()
{
	CDialogEx::OnOK();
}
