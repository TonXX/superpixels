
// SLICSuperpixelsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SLICSuperpixels.h"
#include "SLICSuperpixelsDlg.h"
#include "PictureHandler.h"
#include "SLIC.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSLICSuperpixelsDlg dialog




CSLICSuperpixelsDlg::CSLICSuperpixelsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSLICSuperpixelsDlg::IDD, pParent)
	, m_spcount(0)
	, m_compactness(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSLICSuperpixelsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SPCOUNT, m_spcount);
	DDV_MinMaxInt(pDX, m_spcount, 1, 100000);
	DDX_Text(pDX, IDC_EDIT_COMPACTNESS, m_compactness);
	DDV_MinMaxDouble(pDX, m_compactness, 1.0, 50.0);
}

BEGIN_MESSAGE_MAP(CSLICSuperpixelsDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_CREATESUPERPIXELS, &CSLICSuperpixelsDlg::OnBnClickedButtonCreatesuperpixels)
	ON_EN_CHANGE(IDC_EDIT_SPCOUNT, &CSLICSuperpixelsDlg::OnEnChangeEditSpcount)
	ON_EN_CHANGE(IDC_EDIT_COMPACTNESS, &CSLICSuperpixelsDlg::OnEnChangeEditCompactness)
END_MESSAGE_MAP()


// CSLICSuperpixelsDlg message handlers

BOOL CSLICSuperpixelsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_spcount = 200;
	m_compactness = 10.0;
	UpdateData(FALSE);//FALSE to set data, TRUE to retrieve data

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSLICSuperpixelsDlg::OnEnChangeEditSpcount()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	UpdateData(TRUE);//FALSE to set data, TRUE to retrieve data
}

void CSLICSuperpixelsDlg::OnEnChangeEditCompactness()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	UpdateData(TRUE);//FALSE to set data, TRUE to retrieve data
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSLICSuperpixelsDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSLICSuperpixelsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//=================================================================================
///	GetPictures
///
///	This function collects all the pictures the user chooses into a vector.
//=================================================================================
void CSLICSuperpixelsDlg::GetPictures(vector<string>& picvec)
{
	CFileDialog cfd(TRUE,NULL,NULL,OFN_OVERWRITEPROMPT,L"*.*|*.*|",NULL);
	cfd.m_ofn.Flags |= OFN_ALLOWMULTISELECT;

	//cfd.PostMessage(WM_COMMAND, 40964, NULL);
	
	CString strFileNames;
	cfd.m_ofn.lpstrFile = strFileNames.GetBuffer(2048);
	cfd.m_ofn.nMaxFile = 2048;

	BOOL bResult = cfd.DoModal() == IDOK ? TRUE : FALSE;
	strFileNames.ReleaseBuffer();

	//if(cfd.DoModal() == IDOK)
	if( bResult )
	{
		POSITION pos = cfd.GetStartPosition();
		while (pos) 
		{
			CString imgFile = cfd.GetNextPathName(pos);			
			PictureHandler ph;
			string name = ph.Wide2Narrow(imgFile.GetString());
			picvec.push_back(name);
		}
	}
	else return;
}

//===========================================================================
///	BrowseForFolder
///
///	The main function
//===========================================================================
bool CSLICSuperpixelsDlg::BrowseForFolder(string& folderpath)
{
	IMalloc* pMalloc = 0;
	if(::SHGetMalloc(&pMalloc) != NOERROR)
	return false;

	BROWSEINFO bi;
	memset(&bi, 0, sizeof(bi));

	bi.hwndOwner = m_hWnd;
	bi.lpszTitle = L"Please select a folder and press 'OK'.";

	LPITEMIDLIST pIDL = ::SHBrowseForFolder(&bi);
	if(pIDL == NULL)
	return false;

	TCHAR buffer[_MAX_PATH];
	if(::SHGetPathFromIDList(pIDL, buffer) == 0)
	return false;
	PictureHandler pichand;
	folderpath = pichand.Wide2Narrow(buffer);
	folderpath.append("\\");
	return true;
}

//===========================================================================
///	OnBnClickedButtonCreatesuperpixels
///
///	The main function
//===========================================================================
void CSLICSuperpixelsDlg::OnBnClickedButtonCreatesuperpixels()
{
	PictureHandler picHand;
	vector<string> picvec(0);
	picvec.resize(0);
	GetPictures(picvec);//user chooses one or more pictures
	string saveLocation = "C:\\rktemp\\";
	BrowseForFolder(saveLocation);

	int numPics( picvec.size() );

	//if(m_spcount < 0 || m_spcount < 20) m_spcount = 20;
	if(m_spcount < 0) m_spcount = 200;

	for( int k = 0; k < numPics; k++ )
	{
		UINT* img = NULL;
		int width(0);
		int height(0);

		picHand.GetPictureBuffer( picvec[k], img, width, height );
		int sz = width*height;
		if(m_spcount > sz) AfxMessageBox(L"Number of superpixels exceeds number of pixels in the image");

		int* labels = new int[sz];
		int numlabels(0);
		SLIC slic;
		slic.PerformSLICO_ForGivenK(img, width, height, labels, numlabels, m_spcount, m_compactness);//for a given number K of superpixels
		//slic.PerformSLICO_ForGivenStepSize(img, width, height, labels, numlabels, m_stepsize, m_compactness);//for a given grid step size
		//slic.DrawContoursAroundSegments(img, labels, width, height, 0);//for black contours around superpixels
		slic.DrawContoursAroundSegmentsTwoColors(img, labels, width, height);//for black-and-white contours around superpixels
		slic.SaveSuperpixelLabels(labels,width,height,picvec[k],saveLocation);
		if(labels) delete [] labels;
		
		picHand.SavePicture(img, width, height, picvec[k], saveLocation, 1, "_SLICO");// 0 is for BMP and 1 for JPEG)

		if(img) delete [] img;
	}
	AfxMessageBox(L"Done!", 0, 0);
}
