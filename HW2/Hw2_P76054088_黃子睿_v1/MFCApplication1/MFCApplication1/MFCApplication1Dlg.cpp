
// MFCApplication1Dlg.cpp : 實作檔
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include "opencv2\opencv.hpp"
#include "opencv2\highgui\highgui.hpp"

//
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 對 App About 使用 CAboutDlg 對話方塊

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 對話方塊資料
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

// 程式碼實作
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 對話方塊



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCApplication1Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication1Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication1Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplication1Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCApplication1Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CMFCApplication1Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CMFCApplication1Dlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CMFCApplication1Dlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CMFCApplication1Dlg::OnBnClickedButton8)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 訊息處理常式

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 將 [關於...] 功能表加入系統功能表。

	// IDM_ABOUTBOX 必須在系統命令範圍之中。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 設定此對話方塊的圖示。當應用程式的主視窗不是對話方塊時，
	// 框架會自動從事此作業
	SetIcon(m_hIcon, TRUE);			// 設定大圖示
	SetIcon(m_hIcon, FALSE);		// 設定小圖示

	// TODO: 在此加入額外的初始設定
	// _CRT_SECURE_NO_WARNINGS
	// http://stackoverflow.com/questions/16883037/remove-secure-warnings-crt-secure-no-warnings-from-projects-by-default-in-vis
	AllocConsole();
	freopen ("CONOUT$", "w", stdout );

	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果將最小化按鈕加入您的對話方塊，您需要下列的程式碼，
// 以便繪製圖示。對於使用文件/檢視模式的 MFC 應用程式，
// 框架會自動完成此作業。

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 繪製的裝置內容

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 將圖示置中於用戶端矩形
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 描繪圖示
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 當使用者拖曳最小化視窗時，
// 系統呼叫這個功能取得游標顯示。
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCApplication1Dlg::OnBnClickedButton1()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	// Corner detection

	int n_boards = 1;
	int board_w = 11;
	int board_h = 8;
	int board_n = board_w * board_h;
	CvSize board_sz = cvSize( board_w, board_h );

	CvPoint2D32f *corners = new CvPoint2D32f[ board_n ];
	int corner_count;
	int successes = 0;
	IplImage *image;

	while( successes < n_boards ) {
		char filename[50];
		sprintf( filename, "database//%d.bmp", successes + 1 );
		image = cvLoadImage( filename, CV_LOAD_IMAGE_GRAYSCALE );

		//Find chessboard corners:
		int found = cvFindChessboardCorners(
			image, board_sz, corners, &corner_count,
			CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS
		);

		//Get Subpixel accuracy on those corners
		cvFindCornerSubPix( image, corners, corner_count,
			cvSize(11, 11),cvSize(-1, -1),
			cvTermCriteria( CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 30, 0.1 ) 
		);

		//Draw it
		IplImage *imageRGB = cvCreateImage( cvGetSize(image), IPL_DEPTH_8U, 3 );
		cvCvtColor( image, imageRGB, CV_GRAY2RGB );
		cvDrawChessboardCorners( imageRGB, board_sz, corners, corner_count, found );

		cvNamedWindow( "Calibration" );
		cvShowImage( "Calibration", imageRGB );
		cvWaitKey( 0 );
		cvReleaseImage( &imageRGB );
		successes++;
	}
	cvReleaseImage( &image );
	cvDestroyWindow( "Calibration" );
}

CvMat *rotation_vector;
CvMat *translation_vector;
CvMat *intrinsic_matrix;
CvMat *distortion_coeffs;

void CMFCApplication1Dlg::OnBnClickedButton2()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	// Find the intrinsic matrix

	if( !intrinsic_matrix ){
		int n_boards = 21;
		const int board_dt = 21;
		int board_w = 11;
		int board_h = 8;
		int board_n = board_w * board_h;
		CvSize board_sz = cvSize( board_w, board_h );

		//ALLOCATE STORAGE
		CvMat* image_points = cvCreateMat( n_boards * board_n, 2, CV_32FC1 );
		CvMat* object_points = cvCreateMat( n_boards * board_n, 3, CV_32FC1 );
		CvMat* point_counts = cvCreateMat( n_boards, 1, CV_32SC1 );
		intrinsic_matrix = cvCreateMat( 3, 3, CV_32FC1 );
		distortion_coeffs = cvCreateMat( 5, 1, CV_32FC1 );

		CvPoint2D32f* corners = new CvPoint2D32f[ board_n ];
		int corner_count;
		int successes = 0;
		int step, frame = 0;
		IplImage *image;

		while(successes < n_boards) {
			char filename[50];
			sprintf( filename, "database//%d.bmp", successes + 1 );
			image = cvLoadImage( filename, CV_LOAD_IMAGE_GRAYSCALE );
		
			//Skip every board_dt frames to allow user to move chessboard
			if( frame++ % board_dt == 0 ) {
				//Find chessboard corners:
				int found = cvFindChessboardCorners(
					image, board_sz, corners, &corner_count,
					CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS
				);

				//Get Subpixel accuracy on those corners
				cvFindCornerSubPix( image, corners, corner_count,
					cvSize(11, 11),cvSize(-1, -1),
					cvTermCriteria( CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 30, 0.1 ) 
				);

				//Draw it
				IplImage *imageRGB = cvCreateImage( cvGetSize(image), IPL_DEPTH_8U, 3 );
				cvCvtColor( image, imageRGB, CV_GRAY2RGB );
				cvDrawChessboardCorners( imageRGB, board_sz, corners, corner_count, found );

				// If we got a good board, add it to our data
				if( corner_count == board_n ) {
					step = successes * board_n;
					for( int i = step, j = 0; j < board_n; ++i,++j ) {
						CV_MAT_ELEM( *image_points, float, i, 0 ) = corners[j].x;
						CV_MAT_ELEM( *image_points, float, i, 1 ) = corners[j].y;
						CV_MAT_ELEM( *object_points, float, i, 0 ) = j / board_w;
						CV_MAT_ELEM( *object_points, float, i, 1 ) = j % board_w;
						CV_MAT_ELEM( *object_points, float, i, 2 ) = 0.0f;
					}
					CV_MAT_ELEM( *point_counts, int, successes, 0 ) = board_n;
					successes++;
				}
			} //end skip board_dt between chessboard capture
		} //END COLLECTION WHILE LOOP.

		//ALLOCATE MATRICES ACCORDING TO HOW MANY CHESSBOARDS FOUND
		CvMat* image_points2 = cvCreateMat( successes * board_n, 2, CV_32FC1 );
		CvMat* object_points2 = cvCreateMat( successes * board_n, 3, CV_32FC1 );
		CvMat* point_counts2 = cvCreateMat( successes, 1, CV_32SC1 );
		//TRANSFER THE POINTS INTO THE CORRECT SIZE MATRICES
		//Below, we write out the details in the next two loops. We could
		//instead have written:
		//image_points->rows = object_points->rows = \
		//successes*board_n; point_counts->rows = successes;
		//
		for(int i = 0; i < successes * board_n; ++i) {
			CV_MAT_ELEM( *image_points2, float, i, 0) =
			CV_MAT_ELEM( *image_points, float, i, 0);
			CV_MAT_ELEM( *image_points2, float,i,1) =
			CV_MAT_ELEM( *image_points, float, i, 1);
			CV_MAT_ELEM( *object_points2, float, i, 0) =
			CV_MAT_ELEM( *object_points, float, i, 0) ;
			CV_MAT_ELEM( *object_points2, float, i, 1) =
			CV_MAT_ELEM( *object_points, float, i, 1) ;
			CV_MAT_ELEM( *object_points2, float, i, 2) =
			CV_MAT_ELEM( *object_points, float, i, 2) ;
		}
		for( int i = 0; i < successes; ++i ){ //These are all the same number
			CV_MAT_ELEM( *point_counts2, int, i, 0) =
			CV_MAT_ELEM( *point_counts, int, i, 0);
		}
		cvReleaseMat( &object_points );
		cvReleaseMat( &image_points );
		cvReleaseMat( &point_counts );
		// At this point we have all of the chessboard corners we need.
		// Initialize the intrinsic matrix such that the two focal
		// lengths have a ratio of 1.0
		//
		CV_MAT_ELEM( *intrinsic_matrix, float, 0, 0 ) = 1.0f;
		CV_MAT_ELEM( *intrinsic_matrix, float, 1, 1 ) = 1.0f;
		//CALIBRATE THE CAMERA!

		rotation_vector = cvCreateMat( n_boards, 9, CV_32FC1 );
		translation_vector = cvCreateMat( n_boards, 3, CV_32FC1 );

		cvCalibrateCamera2(
			object_points2, image_points2,
			point_counts2, cvGetSize( image ),
			intrinsic_matrix, distortion_coeffs,
			rotation_vector, translation_vector, 0 //CV_CALIB_FIX_ASPECT_RATIO
		);
	}

	printf("\nintrinsic_matrix\n[");
	for( int i = 0; i < 3; i++ ){
		for( int j = 0; j < 3; j++ ){
			if(j)	printf(", ");
			printf("%.6f",cvGet2D( intrinsic_matrix, i, j ).val[0]);
		}
		printf("%c\n", i==2 ? ']' : ';');
	}
}

void CMFCApplication1Dlg::OnBnClickedButton3()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	// Find the extrinsic matrix
	
	if( !rotation_vector ){
		int n_boards = 21;
		const int board_dt = 21;
		int board_w = 11;
		int board_h = 8;
		int board_n = board_w * board_h;
		CvSize board_sz = cvSize( board_w, board_h );

		//ALLOCATE STORAGE
		CvMat* image_points = cvCreateMat( n_boards * board_n, 2, CV_32FC1 );
		CvMat* object_points = cvCreateMat( n_boards * board_n, 3, CV_32FC1 );
		CvMat* point_counts = cvCreateMat( n_boards, 1, CV_32SC1 );
		intrinsic_matrix = cvCreateMat( 3, 3, CV_32FC1 );
		distortion_coeffs = cvCreateMat( 5, 1, CV_32FC1 );

		CvPoint2D32f* corners = new CvPoint2D32f[ board_n ];
		int corner_count;
		int successes = 0;
		int step, frame = 0;
		IplImage *image;

		while(successes < n_boards) {
			char filename[50];
			sprintf( filename, "database//%d.bmp", successes + 1 );
			image = cvLoadImage( filename, CV_LOAD_IMAGE_GRAYSCALE );
		
			//Skip every board_dt frames to allow user to move chessboard
			if(frame++ % board_dt == 0) {
				//Find chessboard corners:
				int found = cvFindChessboardCorners(
					image, board_sz, corners, &corner_count,
					CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS
				);

				//Get Subpixel accuracy on those corners
				cvFindCornerSubPix( image, corners, corner_count,
					cvSize(11, 11),cvSize(-1, -1),
					cvTermCriteria( CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 30, 0.1 ) 
				);

				//Draw it
				IplImage *imageRGB = cvCreateImage( cvGetSize(image), IPL_DEPTH_8U, 3 );
				cvCvtColor( image, imageRGB, CV_GRAY2RGB );
				cvDrawChessboardCorners( imageRGB, board_sz, corners,corner_count, found );

				// If we got a good board, add it to our data
				if( corner_count == board_n ) {
					step = successes * board_n;
					for( int i = step, j = 0; j < board_n; ++i,++j ) {
						CV_MAT_ELEM( *image_points, float, i, 0 ) = corners[j].x;
						CV_MAT_ELEM( *image_points, float, i, 1 ) = corners[j].y;
						CV_MAT_ELEM( *object_points, float, i, 0 ) = j / board_w;
						CV_MAT_ELEM( *object_points, float, i, 1 ) = j % board_w;
						CV_MAT_ELEM( *object_points, float, i, 2 ) = 0.0f;
					}
					CV_MAT_ELEM( *point_counts, int, successes, 0 ) = board_n;
					successes++;
				}
			} //end skip board_dt between chessboard capture
		} //END COLLECTION WHILE LOOP.

		//ALLOCATE MATRICES ACCORDING TO HOW MANY CHESSBOARDS FOUND
		CvMat* object_points2 = cvCreateMat(successes * board_n, 3, CV_32FC1);
		CvMat* image_points2 = cvCreateMat(successes * board_n, 2, CV_32FC1);
		CvMat* point_counts2 = cvCreateMat(successes, 1, CV_32SC1);
		//TRANSFER THE POINTS INTO THE CORRECT SIZE MATRICES
		//Below, we write out the details in the next two loops. We could
		//instead have written:
		//image_points->rows = object_points->rows = \
		//successes*board_n; point_counts->rows = successes;
		//
		for(int i = 0; i < successes * board_n; ++i) {
			CV_MAT_ELEM( *image_points2, float, i, 0) =
			CV_MAT_ELEM( *image_points, float, i, 0);
			CV_MAT_ELEM( *image_points2, float,i,1) =
			CV_MAT_ELEM( *image_points, float, i, 1);
			CV_MAT_ELEM( *object_points2, float, i, 0) =
			CV_MAT_ELEM( *object_points, float, i, 0) ;
			CV_MAT_ELEM( *object_points2, float, i, 1) =
			CV_MAT_ELEM( *object_points, float, i, 1) ;
			CV_MAT_ELEM( *object_points2, float, i, 2) =
			CV_MAT_ELEM( *object_points, float, i, 2) ;
		}
		for( int i = 0; i < successes; ++i ){ //These are all the same number
			CV_MAT_ELEM( *point_counts2, int, i, 0) =
			CV_MAT_ELEM( *point_counts, int, i, 0);
		}
		cvReleaseMat(&object_points);
		cvReleaseMat(&image_points);
		cvReleaseMat(&point_counts);
		// At this point we have all of the chessboard corners we need.
		// Initialize the intrinsic matrix such that the two focal
		// lengths have a ratio of 1.0
		//
		CV_MAT_ELEM( *intrinsic_matrix, float, 0, 0 ) = 1.0f;
		CV_MAT_ELEM( *intrinsic_matrix, float, 1, 1 ) = 1.0f;
		//CALIBRATE THE CAMERA!

		rotation_vector = cvCreateMat( n_boards, 9, CV_32FC1 );
		translation_vector = cvCreateMat( n_boards, 3, CV_32FC1 );

		cvCalibrateCamera2(
			object_points2, image_points2,
			point_counts2, cvGetSize( image ),
			intrinsic_matrix, distortion_coeffs,
			rotation_vector, translation_vector, 0 //CV_CALIB_FIX_ASPECT_RATIO
		);
	}

	int extrinsic_n = 1;
	printf("\nextrinsic_matrix\n");
	for( int i = 0; i < 1; i++ ){
		printf("[");
		for( int j = 0; j < 9; j++ ){
			if( (j+1)%3 != 1 )	printf(", ");
			printf("%.6f", cvGet2D( rotation_vector, i, j ).val[0]);
			if( !((j+1)%3) )	{
				printf(", %.6f%c\n", cvGet2D( translation_vector, i, j/3 ).val[0], 
					j == 8 ? ']' : ';');
			}
		}
	}
}

void CMFCApplication1Dlg::OnBnClickedButton4()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	// Finde the distortion matrix

	if( !distortion_coeffs ){
		int n_boards = 21;
		const int board_dt = 21;
		int board_w = 11;
		int board_h = 8;
		int board_n = board_w * board_h;
		CvSize board_sz = cvSize( board_w, board_h );

		//ALLOCATE STORAGE
		CvMat* image_points = cvCreateMat( n_boards * board_n, 2, CV_32FC1 );
		CvMat* object_points = cvCreateMat( n_boards * board_n, 3, CV_32FC1 );
		CvMat* point_counts = cvCreateMat( n_boards, 1, CV_32SC1 );
		intrinsic_matrix = cvCreateMat( 3, 3, CV_32FC1 );
		distortion_coeffs = cvCreateMat( 5, 1, CV_32FC1 );

		CvPoint2D32f* corners = new CvPoint2D32f[ board_n ];
		int corner_count;
		int successes = 0;
		int step, frame = 0;
		IplImage *image;

		while(successes < n_boards) {
			char filename[50];
			sprintf( filename, "database//%d.bmp", successes + 1 );
			image = cvLoadImage( filename, CV_LOAD_IMAGE_GRAYSCALE );
		
			//Skip every board_dt frames to allow user to move chessboard
			if(frame++ % board_dt == 0) {
				//Find chessboard corners:
				int found = cvFindChessboardCorners(
					image, board_sz, corners, &corner_count,
					CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS
				);

				//Get Subpixel accuracy on those corners
				cvFindCornerSubPix( image, corners, corner_count,
					cvSize(11, 11),cvSize(-1, -1),
					cvTermCriteria( CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 30, 0.1 ) 
				);

				//Draw it
				IplImage *imageRGB = cvCreateImage( cvGetSize(image), IPL_DEPTH_8U, 3 );
				cvCvtColor( image, imageRGB, CV_GRAY2RGB );
				cvDrawChessboardCorners( imageRGB, board_sz, corners,corner_count, found );

				// If we got a good board, add it to our data
				if( corner_count == board_n ) {
					step = successes * board_n;
					for( int i = step, j = 0; j < board_n; ++i,++j ) {
						CV_MAT_ELEM( *image_points, float, i, 0 ) = corners[j].x;
						CV_MAT_ELEM( *image_points, float, i, 1 ) = corners[j].y;
						CV_MAT_ELEM( *object_points, float, i, 0 ) = j / board_w;
						CV_MAT_ELEM( *object_points, float, i, 1 ) = j % board_w;
						CV_MAT_ELEM( *object_points, float, i, 2 ) = 0.0f;
					}
					CV_MAT_ELEM( *point_counts, int, successes, 0 ) = board_n;
					successes++;
				}
			} //end skip board_dt between chessboard capture
		} //END COLLECTION WHILE LOOP.

		//ALLOCATE MATRICES ACCORDING TO HOW MANY CHESSBOARDS FOUND
		CvMat* object_points2 = cvCreateMat(successes * board_n, 3, CV_32FC1);
		CvMat* image_points2 = cvCreateMat(successes * board_n, 2, CV_32FC1);
		CvMat* point_counts2 = cvCreateMat(successes, 1, CV_32SC1);
		//TRANSFER THE POINTS INTO THE CORRECT SIZE MATRICES
		//Below, we write out the details in the next two loops. We could
		//instead have written:
		//image_points->rows = object_points->rows = \
		//successes*board_n; point_counts->rows = successes;
		//
		for(int i = 0; i < successes * board_n; ++i) {
			CV_MAT_ELEM( *image_points2, float, i, 0) =
			CV_MAT_ELEM( *image_points, float, i, 0);
			CV_MAT_ELEM( *image_points2, float,i,1) =
			CV_MAT_ELEM( *image_points, float, i, 1);
			CV_MAT_ELEM( *object_points2, float, i, 0) =
			CV_MAT_ELEM( *object_points, float, i, 0) ;
			CV_MAT_ELEM( *object_points2, float, i, 1) =
			CV_MAT_ELEM( *object_points, float, i, 1) ;
			CV_MAT_ELEM( *object_points2, float, i, 2) =
			CV_MAT_ELEM( *object_points, float, i, 2) ;
		}
		for( int i = 0; i < successes; ++i ){ //These are all the same number
			CV_MAT_ELEM( *point_counts2, int, i, 0) =
			CV_MAT_ELEM( *point_counts, int, i, 0);
		}
		cvReleaseMat(&object_points);
		cvReleaseMat(&image_points);
		cvReleaseMat(&point_counts);
		// At this point we have all of the chessboard corners we need.
		// Initialize the intrinsic matrix such that the two focal
		// lengths have a ratio of 1.0
		//
		CV_MAT_ELEM( *intrinsic_matrix, float, 0, 0 ) = 1.0f;
		CV_MAT_ELEM( *intrinsic_matrix, float, 1, 1 ) = 1.0f;
		//CALIBRATE THE CAMERA!
		cvCalibrateCamera2(
			object_points2, image_points2,
			point_counts2, cvGetSize( image ),
			intrinsic_matrix, distortion_coeffs,
			NULL, NULL,0 //CV_CALIB_FIX_ASPECT_RATIO
		);
	}
	printf("\ndistortion_coeffs\n[");
	for( int i = 0; i < 5; i++ ){
		if(i)	printf(", ");
		for( int j = 0; j < 1; j++ )
			printf("%.6f",cvGet2D( distortion_coeffs, i, j ).val[0]);
		if(i == 4)	printf("]\n");
	}
}

void CMFCApplication1Dlg::OnBnClickedButton5()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	// AR

	int n_boards = 21;
	const int board_dt = 21;
	int board_w = 11;
	int board_h = 8;
	int board_n = board_w * board_h;
	CvSize board_sz = cvSize( board_w, board_h );

	//ALLOCATE STORAGE
	CvMat* image_points = cvCreateMat( n_boards * board_n, 2, CV_32FC1 );
	CvMat* object_points = cvCreateMat( n_boards * board_n, 3, CV_32FC1 );
	CvMat* point_counts = cvCreateMat( n_boards, 1, CV_32SC1 );
	intrinsic_matrix = cvCreateMat( 3, 3, CV_32FC1 );
	distortion_coeffs = cvCreateMat( 5, 1, CV_32FC1 );

	CvPoint2D32f* corners = new CvPoint2D32f[ board_n ];
	int corner_count;
	int successes = 0;
	int step, frame = 0;
	IplImage *image;

	while(successes < n_boards) {
		char filename[50];
		sprintf( filename, "database//%d.bmp", successes + 1 );
		image = cvLoadImage( filename, CV_LOAD_IMAGE_GRAYSCALE );
		
		//Skip every board_dt frames to allow user to move chessboard
		if(frame++ % board_dt == 0) {
			//Find chessboard corners:
			int found = cvFindChessboardCorners(
				image, board_sz, corners, &corner_count,
				CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS
			);

			//Get Subpixel accuracy on those corners
			cvFindCornerSubPix( image, corners, corner_count,
				cvSize(11, 11),cvSize(-1, -1),
				cvTermCriteria( CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 30, 0.1 ) 
			);

			// If we got a good board, add it to our data
			if( corner_count == board_n ) {
				step = successes * board_n;
				for( int i = step, j = 0; j < board_n; ++i,++j ) {
					CV_MAT_ELEM( *image_points, float, i, 0 ) = corners[j].x;
					CV_MAT_ELEM( *image_points, float, i, 1 ) = corners[j].y;
					CV_MAT_ELEM( *object_points, float, i, 0 ) = j / board_w;
					CV_MAT_ELEM( *object_points, float, i, 1 ) = j % board_w;
					CV_MAT_ELEM( *object_points, float, i, 2 ) = 0.0f;
				}
				CV_MAT_ELEM( *point_counts, int, successes, 0 ) = board_n;
				successes++;
			}
		} //end skip board_dt between chessboard capture
	} //END COLLECTION WHILE LOOP.

	//ALLOCATE MATRICES ACCORDING TO HOW MANY CHESSBOARDS FOUND
	CvMat* object_points2 = cvCreateMat(successes * board_n, 3, CV_32FC1);
	CvMat* image_points2 = cvCreateMat(successes * board_n, 2, CV_32FC1);
	CvMat* point_counts2 = cvCreateMat(successes, 1, CV_32SC1);
	//TRANSFER THE POINTS INTO THE CORRECT SIZE MATRICES
	//Below, we write out the details in the next two loops. We could
	//instead have written:
	//image_points->rows = object_points->rows = \
	//successes*board_n; point_counts->rows = successes;
	//
	for(int i = 0; i < successes * board_n; ++i) {
		CV_MAT_ELEM( *image_points2, float, i, 0) =
		CV_MAT_ELEM( *image_points, float, i, 0);
		CV_MAT_ELEM( *image_points2, float, i, 1) =
		CV_MAT_ELEM( *image_points, float, i, 1);
		CV_MAT_ELEM( *object_points2, float, i, 0) =
		CV_MAT_ELEM( *object_points, float, i, 0) ;
		CV_MAT_ELEM( *object_points2, float, i, 1) =
		CV_MAT_ELEM( *object_points, float, i, 1) ;
		CV_MAT_ELEM( *object_points2, float, i, 2) =
		CV_MAT_ELEM( *object_points, float, i, 2) ;
	}
	for( int i = 0; i < successes; ++i ){ //These are all the same number
		CV_MAT_ELEM( *point_counts2, int, i, 0) =
		CV_MAT_ELEM( *point_counts, int, i, 0);
	}
	cvReleaseMat( &object_points );
	cvReleaseMat( &image_points );
	cvReleaseMat( &point_counts );
	// At this point we have all of the chessboard corners we need.
	// Initialize the intrinsic matrix such that the two focal
	// lengths have a ratio of 1.0
	//
	CV_MAT_ELEM( *intrinsic_matrix, float, 0, 0 ) = 1.0f;
	CV_MAT_ELEM( *intrinsic_matrix, float, 1, 1 ) = 1.0f;
	//CALIBRATE THE CAMERA!

	rotation_vector = cvCreateMat( n_boards, 9, CV_32FC1 );
	translation_vector = cvCreateMat( n_boards, 3, CV_32FC1 );	//1 channel

	//intrinsic_matrix, distortion_coeffs
	cvCalibrateCamera2(
		object_points2, image_points2,
		point_counts2, cvGetSize( image ),
		intrinsic_matrix, distortion_coeffs,
		rotation_vector, translation_vector, 0 //CV_CALIB_FIX_ASPECT_RATIO
	);
	
	//cvFindExtrinsicCameraParams2
	CvMat* rotation_vector2 = cvCreateMat( 3, 1, CV_32FC1 );
	CvMat* translation_vector2 = cvCreateMat( 3, 1, CV_32FC1 );
	CvMat* image_pointsSingle = cvCreateMat( 1 * board_n, 2, CV_32FC1 );
	CvMat* object_pointsSingle = cvCreateMat( 1 * board_n, 3, CV_32FC1 );

	//cvProjectPoints2
	CvMat* image_points3D = cvCreateMat( 5, 2, CV_32FC1 );
	CvMat* object_points3D = cvCreateMat( 5, 3, CV_32FC1 );

	//0, 0, 2 not 0, 0, -2
	CV_MAT_ELEM( *object_points3D, float, 0, 0) = 0;
	CV_MAT_ELEM( *object_points3D, float, 0, 1) = 0;
	CV_MAT_ELEM( *object_points3D, float, 0, 2) = 2;

	CV_MAT_ELEM( *object_points3D, float, 1, 0) = -1;
	CV_MAT_ELEM( *object_points3D, float, 1, 1) = -1;
	CV_MAT_ELEM( *object_points3D, float, 1, 2) = 0;

	CV_MAT_ELEM( *object_points3D, float, 2, 0) = 1;
	CV_MAT_ELEM( *object_points3D, float, 2, 1) = -1;
	CV_MAT_ELEM( *object_points3D, float, 2, 2) = 0;

	CV_MAT_ELEM( *object_points3D, float, 3, 0) = 1;
	CV_MAT_ELEM( *object_points3D, float, 3, 1) = 1;
	CV_MAT_ELEM( *object_points3D, float, 3, 2) = 0;

	CV_MAT_ELEM( *object_points3D, float, 4, 0) = -1;
	CV_MAT_ELEM( *object_points3D, float, 4, 1) = 1;
	CV_MAT_ELEM( *object_points3D, float, 4, 2) = 0;

	int show_boards = 5;
	for(int now_boards = 0; now_boards < show_boards; now_boards++){
		for(int i = 0, j = now_boards * board_n; i < board_n; ++i, ++j) {
			CV_MAT_ELEM( *image_pointsSingle, float, i, 0) =
			CV_MAT_ELEM( *image_points2, float, j, 0);
			CV_MAT_ELEM( *image_pointsSingle, float, i, 1) =
			CV_MAT_ELEM( *image_points2, float, j, 1);
			CV_MAT_ELEM( *object_pointsSingle, float, i, 0) =
			CV_MAT_ELEM( *object_points2, float, j, 0) ;
			CV_MAT_ELEM( *object_pointsSingle, float, i, 1) =
			CV_MAT_ELEM( *object_points2, float, j, 1) ;
			CV_MAT_ELEM( *object_pointsSingle, float, i, 2) =
			CV_MAT_ELEM( *object_points2, float, j, 2) ;
		}

		//rotation_vector2, translation_vector2
		cvFindExtrinsicCameraParams2(
			object_pointsSingle,
			image_pointsSingle,
			intrinsic_matrix,
			distortion_coeffs,
			rotation_vector2,
			translation_vector2
		);

		cvProjectPoints2( object_points3D,
			rotation_vector2, translation_vector2,
			intrinsic_matrix, distortion_coeffs,
			image_points3D);

		CvPoint Point3D[5];

		for(int i = 0; i < 5; i++)
			Point3D[i] = cvPoint( cvGet2D( image_points3D, i, 0 ).val[0], cvGet2D( image_points3D, i, 1 ).val[0] );

		char filename[50];
		sprintf( filename, "database//%d.bmp", now_boards + 1 );
		image = cvLoadImage( filename, CV_LOAD_IMAGE_GRAYSCALE );
		IplImage *imageRGB = cvCreateImage( cvGetSize(image), IPL_DEPTH_8U, 3 );
		cvCvtColor( image, imageRGB, CV_GRAY2RGB );

		for(int i = 1; i < 5; i++){
			cvLine( imageRGB, Point3D[i-1], Point3D[i], CV_RGB(255, 0, 0), 2, 8);
			cvLine( imageRGB, Point3D[0], Point3D[i], CV_RGB(255, 0, 0), 2, 8);
		}
		cvLine( imageRGB, Point3D[1], Point3D[4], CV_RGB(255, 0, 0), 2, 8);

		cvNamedWindow( "Calibration" );
		cvShowImage( "Calibration", imageRGB );
		cvWaitKey( 500 ); //0.5s = 500ms
		cvReleaseImage( &imageRGB );
	}
	cvWaitKey( 0 );
	cvDestroyWindow( "Calibration" );
}

void CMFCApplication1Dlg::OnBnClickedButton6()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	// Median Smooth

	char *filename = "database//Eyes.png";
	IplImage *image = cvLoadImage( filename );
	IplImage *smoothImage = cvCloneImage( image );

	cvNamedWindow( "Image", CV_WINDOW_AUTOSIZE );
	cvShowImage( "Image", image );
	
	cvSmooth( image, smoothImage, CV_MEDIAN, 3, 3 );

	cvNamedWindow( "Smooth Image", CV_WINDOW_AUTOSIZE );
	cvShowImage( "Smooth Image", smoothImage );

	cvWaitKey( 0 );
	cvReleaseImage( &image );
	cvReleaseImage( &smoothImage );
	cvDestroyWindow( "Image" );
	cvDestroyWindow( "Smooth Image" );
}

void CMFCApplication1Dlg::OnBnClickedButton7()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	// Canny

	char *filename = "database//Eyes.png";
	IplImage *image = cvLoadImage( filename, CV_LOAD_IMAGE_GRAYSCALE );
	IplImage *detected_edges = cvCreateImage( cvGetSize(image), IPL_DEPTH_8U, 1 );
	int lowThreshold = 600, ratio = 3, kernel_size = 5;

	cvSmooth( image, detected_edges, CV_MEDIAN,	3, 3 );
	cvCanny( detected_edges, detected_edges, lowThreshold, lowThreshold * ratio, kernel_size );

	cvNamedWindow( "Canny Edge", CV_WINDOW_AUTOSIZE );
	cvShowImage( "Canny Edge", detected_edges );

	cvWaitKey( 0 );
	cvReleaseImage( &image );
	cvReleaseImage( &detected_edges );
	cvDestroyWindow( "Canny Edge" );
}

void CMFCApplication1Dlg::OnBnClickedButton8()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	// HoughCircle + cvCircle

	char *filename = "database//Eyes.png";
	IplImage *image = cvLoadImage( filename, CV_LOAD_IMAGE_GRAYSCALE );
	IplImage *smoothImage = cvCloneImage( image );

	// CHANGE SMOOTH TO 3 CHANNEL IN ORDER TO DRAW RED CIRCLE
	// HOUGH CIRCLE DETECTION FAIL BECAUSE PARAMETER
	cvSmooth( image, smoothImage, CV_MEDIAN, 3, 3 );

	CvMemStorage* circle_storage = cvCreateMemStorage(0);
	CvSeq* circles = cvHoughCircles( smoothImage, circle_storage,
		CV_HOUGH_GRADIENT, 2, smoothImage->width / 8, 200, 40 );

	IplImage *smoothImageRGB = cvCreateImage( cvGetSize(image), IPL_DEPTH_8U, 3 );
	cvCvtColor(smoothImage, smoothImageRGB, CV_GRAY2RGB);

	for( int i = 0; i < circles->total; i++ ) {
		float *center = (float*) cvGetSeqElem( circles, i );
		cvCircle( smoothImageRGB, cvPoint( cvRound( center[0] ), cvRound( center[1] ) ),
					20, CV_RGB( 255, 0, 0 ), 2, CV_AA );
	}

	cvNamedWindow( "Hough Circle", CV_WINDOW_AUTOSIZE );
    cvShowImage( "Hough Circle", smoothImageRGB );

	cvWaitKey( 0 );
	cvReleaseImage( &image );
	cvReleaseImage( &smoothImage );
	cvReleaseImage( &smoothImageRGB );
	cvDestroyWindow( "Hough Circle" );
}