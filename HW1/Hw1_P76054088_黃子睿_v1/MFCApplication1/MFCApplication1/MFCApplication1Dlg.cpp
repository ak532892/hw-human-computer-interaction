
// MFCApplication1Dlg.cpp : 實作檔
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include "opencv2\opencv.hpp"
#include "opencv2\highgui\highgui.hpp"
#define _USE_MATH_DEFINES
#include <math.h>
#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;
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
	ON_BN_CLICKED(IDC_BUTTON9, &CMFCApplication1Dlg::OnBnClickedButton9)
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
	char *filename = "database//1.bmp";
	IplImage *image = cvLoadImage( filename );
	
	cvNamedWindow( "Image", CV_WINDOW_AUTOSIZE );
	cvShowImage( "Image", image );

	CString imgData;

	imgData.Format( L"%d", image->width );
	GetDlgItem( IDC_EDIT1 )->SetWindowTextW( imgData );

	imgData.Format( L"%d", image->height );
	GetDlgItem( IDC_EDIT2 )->SetWindowTextW( imgData );

	imgData.Format( L"%d * %d", image->width, image->height );
	GetDlgItem( IDC_EDIT3 )->SetWindowTextW( imgData );

	//**bitmap**//
	typedef unsigned short WORD;
	typedef unsigned int BYTE; 
	typedef int DWORD;
	fstream file;

	WORD bmpId;
	BYTE fileSize;
	WORD bmpReserved1;
	WORD bmpReserved2;
	BYTE bmpOffset;
	BYTE bmpInfoHeaderSize;
	DWORD bmpWidth;
	DWORD bmpHeight;
	WORD bmpPlanes;
	WORD bmpbitCount;
	DWORD bmpCompression;
	DWORD bmpDataSize;
	DWORD bmpXPixelPerMeter;
	DWORD bmpYPixelPerMeter;
	BYTE bmpColorUsed;
	BYTE bmpColorImportant; 
	
	file.open(filename, ios::in|ios::binary);
	file.read((char*)&bmpId, sizeof(WORD));
	file.read((char*)&fileSize, sizeof(BYTE));
	file.read((char*)&bmpReserved1, sizeof(WORD));
	file.read((char*)&bmpReserved2, sizeof(WORD));
	file.read((char*)&bmpOffset, sizeof(BYTE));
	file.read((char*)&bmpInfoHeaderSize, sizeof(BYTE));
	file.read((char*)&bmpWidth, sizeof(DWORD));
	file.read((char*)&bmpHeight, sizeof(DWORD));
	file.read((char*)&bmpPlanes, sizeof(WORD));
	file.read((char*)&bmpbitCount, sizeof(WORD)); 
	file.read((char*)&bmpCompression, sizeof(DWORD));
	file.read((char*)&bmpDataSize, sizeof(DWORD)); 
	file.read((char*)&bmpXPixelPerMeter, sizeof(DWORD));
	file.read((char*)&bmpYPixelPerMeter, sizeof(DWORD));
	file.read((char*)&bmpColorUsed, sizeof(BYTE));
	file.read((char*)&bmpColorImportant, sizeof(BYTE));
	file.close();

	double meterToInch = 39.3701,
		   bmpXPixelPerInch = ceil( bmpXPixelPerMeter / meterToInch ),
		   bmpYPixelPerInch = ceil( bmpYPixelPerMeter / meterToInch );

	imgData.Format( L"%.0f",  bmpXPixelPerInch );
	GetDlgItem( IDC_EDIT4 )->SetWindowTextW( imgData );
	
	cvWaitKey( 0 );
	cvReleaseImage( &image );
	cvDestroyWindow( "Image" );
}

void CMFCApplication1Dlg::OnBnClickedButton2()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	char *filename = "database//1_2.png";
	IplImage *image = cvLoadImage( filename );
	
	cvNamedWindow( "BGR", CV_WINDOW_AUTOSIZE );
	cvShowImage( "BGR", image );

	for( int y = 0; y < image->height; y++ ) {
		uchar *ptr = (uchar*) ( image->imageData + y * image->widthStep );

		for( int x = 0; x < image->width; x++ ) {
			//bgr->rbg 
			//grb->brg 固定其中一個換兩個顏色值
			swap( ptr[3*x + 1], ptr[3*x + 3] );
			//brg->rbg
			swap( ptr[3*x + 1], ptr[3*x + 2] );
		}
	}

	cvNamedWindow( "RBG", CV_WINDOW_AUTOSIZE );
	cvShowImage( "RBG", image );

	cvWaitKey( 0 );
	cvReleaseImage( &image );
	cvDestroyWindow( "BGR" );
	cvDestroyWindow( "RBG" );
}

void mirror(IplImage *image)
{	
	int width = image->width;
	
	for( int y = 0; y < image->height; y++ ) {
		uchar *ptr = (uchar*) ( image->imageData + y * image->widthStep );

		for( int x = 0; x < width / 2; x++ ) {
			swap( ptr[3*width - 3*x + 1], ptr[3*x + 1] );
			swap( ptr[3*width - 3*x + 2], ptr[3*x + 2] );
			swap( ptr[3*width - 3*x + 3], ptr[3*x + 3] );
		}
	}
}

void CMFCApplication1Dlg::OnBnClickedButton3()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	char *filename = "database//1.bmp";
	IplImage *mirrorImage = cvLoadImage( filename );
	
	cvNamedWindow( "Image", CV_WINDOW_AUTOSIZE );
	cvShowImage( "Image", mirrorImage );
	
	mirror( mirrorImage );

	cvNamedWindow( "Mirror Image", CV_WINDOW_AUTOSIZE );
	cvShowImage( "Mirror Image", mirrorImage );

	cvWaitKey( 0 );
	cvReleaseImage( &mirrorImage );
	cvDestroyWindow( "Image" );
	cvDestroyWindow( "Mirror Image" );
}

IplImage *mirrorImage;
void onTrackbar4( int blend )
{
    char *filename = "database//1.bmp";
	IplImage *image = cvLoadImage( filename ),
			 *blendImage = cvCloneImage( image );
	double alpha = blend / 100.;

	cvAddWeighted( image, alpha, mirrorImage, 1 - alpha, 0, blendImage );
	cvShowImage( "Blend Image", blendImage );

	cvReleaseImage( &image );
	cvReleaseImage( &blendImage );
}

void CMFCApplication1Dlg::OnBnClickedButton4()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	char *fileneame = "database//1.bmp";
	
	mirrorImage = cvLoadImage( fileneame );

	cvNamedWindow( "Blend Image", CV_WINDOW_AUTOSIZE );
	mirror ( mirrorImage );
	cvShowImage( "Blend Image", mirrorImage );

	cvCreateTrackbar( "BLEND", "Blend Image", 0, 100, onTrackbar4 );

	cvWaitKey( 0 );
	cvReleaseImage( &mirrorImage );
	cvDestroyWindow( "Blend Image" );
}

CvSize eyeSize = cvGetSize( cvLoadImage( "database//eye.jpg" ));
IplImage *sobelXImage_16S, *sobelYImage_16S,
		 *sobelXImage_ABS_8U, *sobelYImage_ABS_8U,
		 *sobelImage, *sobelImage2;
void onTrackbar51( int angleThreshold )
{
	sobelImage = cvCloneImage( sobelImage2 );

	for( int y = 0; y < sobelImage->height; y++ ) {
		uchar *ptr = (uchar*) ( sobelImage->imageData + y * sobelImage->widthStep );
		
		for( int x = 0; x < sobelImage->width; x++ ) {
			double gx = cvGet2D( sobelXImage_16S, y, x ).val[0],
				   gy = cvGet2D( sobelYImage_16S, y, x ).val[0],
				   angle = atan( gy / gx ) * 180 / M_PI;

			if( angle < 0 )	angle += 180;

			if((( angleThreshold - 20 ) <= angle) && (angle <= ( angleThreshold + 20 )))
				ptr[x] = 255;
			else
				ptr[x] = 0;
		}
	}

	cvShowImage( "Sobel Image", sobelImage );
}

void onTrackbar52( int magnitudeThreshold )
{
	sobelImage = cvCloneImage( sobelImage2 );
	cvThreshold( sobelImage, sobelImage, magnitudeThreshold, 255, CV_THRESH_BINARY );
	cvShowImage( "Sobel2 Image", sobelImage );
}

void CMFCApplication1Dlg::OnBnClickedButton5()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	char *filename = "database//eye.jpg";
	IplImage *image = cvLoadImage( filename );
	IplImage *smoothImage = cvCreateImage( cvGetSize(image), IPL_DEPTH_8U, 1 );
	
	sobelXImage_16S = cvCreateImage( eyeSize, IPL_DEPTH_16S, 1 ),
	sobelYImage_16S = cvCloneImage( sobelXImage_16S ),
	sobelXImage_ABS_8U = cvCreateImage( eyeSize, IPL_DEPTH_8U, 1 ),
	sobelYImage_ABS_8U = cvCloneImage( sobelXImage_ABS_8U ),
	sobelImage = cvCloneImage( sobelXImage_ABS_8U ),
	sobelImage2 = cvCloneImage( sobelXImage_ABS_8U );

	//2.1
	cvNamedWindow( "Image", CV_WINDOW_AUTOSIZE );
	cvShowImage( "Image", image );
	
	cvCvtColor( image, smoothImage, CV_BGR2GRAY );
	cvSmooth( smoothImage, smoothImage, CV_GAUSSIAN, 17, 17 );

	cvNamedWindow( "Smooth Image", CV_WINDOW_AUTOSIZE );
	cvShowImage( "Smooth Image", smoothImage );

	//2.2
	cvNamedWindow( "Sobel Image", CV_WINDOW_AUTOSIZE );
	
	cvSobel( smoothImage, sobelXImage_16S, 1, 0, 3 );
	cvSobel( smoothImage, sobelYImage_16S, 0, 1, 3 );

	cvConvertScaleAbs( sobelXImage_16S, sobelXImage_ABS_8U );
	cvConvertScaleAbs( sobelYImage_16S, sobelYImage_ABS_8U );

	cvAddWeighted( sobelXImage_ABS_8U, 0.5, sobelYImage_ABS_8U, 0.5, 0, sobelImage );

	sobelImage2 = cvCloneImage( sobelImage );

	int initAngle = 90;

	onTrackbar51( initAngle );
	cvShowImage( "Sobel Image", sobelImage );
	cvCreateTrackbar( "ANGLE", "Sobel Image", 0, 180, onTrackbar51 );
	cvSetTrackbarPos( "ANGLE", "Sobel Image", initAngle );

	//2.3
	int initThreshold = 40;
	
	cvNamedWindow( "Sobel2 Image", CV_WINDOW_AUTOSIZE );
	onTrackbar52( initThreshold );
	cvShowImage( "Sobel2 Image", sobelImage );
	cvCreateTrackbar( "MAGNITUDE", "Sobel2 Image", 0, 255, onTrackbar52 );
	cvSetTrackbarPos( "MAGNITUDE", "Sobel2 Image", initThreshold );

	cvWaitKey( 0 );
	cvReleaseImage( &image ); cvReleaseImage( &smoothImage );
	cvReleaseImage( &sobelXImage_16S ); cvReleaseImage( &sobelYImage_16S );
	cvReleaseImage( &sobelXImage_ABS_8U ); cvReleaseImage( &sobelYImage_ABS_8U );
	cvReleaseImage( &sobelImage ); cvReleaseImage( &sobelImage2 );
	cvDestroyWindow( "Image" ); cvDestroyWindow( "Smooth Image" );
	cvDestroyWindow( "Sobel Image" ); cvDestroyWindow( "Sobel2 Image" );
}

IplImage *QRImage;
int clickCount = 0;
void on_mouse6( int event, int x, int y, int flags, void* param ) {	
	static CvPoint2D32f srcQuad[4];

	switch ( event ){
		case CV_EVENT_LBUTTONDOWN:
			srcQuad[clickCount++] = cvPointTo32f( cvPoint( x, y ) );
			cvCircle( QRImage, cvPoint( x, y ), 15, cvScalar(0, 0, 255), -1 );
			cvShowImage( "Image", QRImage );
		break;
	}
	
	if( clickCount == 4 ){
		CvPoint2D32f dstQuad[4];
		CvMat *warp_matrix = cvCreateMat( 3, 3, CV_32FC1 );

		dstQuad[0] = cvPoint2D32f( 0, 0 );
		dstQuad[1] = cvPoint2D32f( QRImage->width, 0 );
		dstQuad[2] = cvPoint2D32f( QRImage->width, QRImage->height );
		dstQuad[3] = cvPoint2D32f( 0, QRImage->height );

		cvGetPerspectiveTransform( srcQuad, dstQuad, warp_matrix );
		IplImage *dst = cvCloneImage( QRImage );

		cvWarpPerspective( QRImage, dst, warp_matrix );
		cvNamedWindow( "Perspective Transformation", CV_WINDOW_AUTOSIZE );
		cvShowImage( "Perspective Transformation", dst );

		cvWaitKey( 0 );
		cvReleaseImage( &dst );
		cvDestroyWindow( "Perspective Transformation" );
		clickCount = 0;
		QRImage = cvLoadImage( "database//QR.jpg" );
	}
}

void CMFCApplication1Dlg::OnBnClickedButton6()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	QRImage = cvLoadImage( "database//QR.jpg" );
	cvNamedWindow( "Image", CV_WINDOW_AUTOSIZE );
	cvShowImage( "Image", QRImage );

	cvSetMouseCallback( "Image", on_mouse6, 0 );

	cvWaitKey( 0 );
	cvReleaseImage( &QRImage );
	cvDestroyWindow( "Image" );
}

void on_mouse7( int event, int x, int y, int flags, void* param ) {	
	static CvPoint2D32f srcQuad[4];

	switch ( event ){
		case CV_EVENT_LBUTTONDOWN:
			srcQuad[clickCount++] = cvPointTo32f( cvPoint( x, y ) );
			cvCircle( QRImage, cvPoint( x, y ), 15, cvScalar(0, 0, 255), -1 );
			cvShowImage( "Image", QRImage );
		break;
	}
	
	if( clickCount == 4 ){
		CvPoint2D32f dstQuad[4];
		CvMat *warp_matrix = cvCreateMat( 3, 3, CV_32FC1 );

		dstQuad[0] = cvPoint2D32f( 0, 0 );
		dstQuad[1] = cvPoint2D32f( QRImage->width, 0 );
		dstQuad[2] = cvPoint2D32f( QRImage->width, QRImage->height );
		dstQuad[3] = cvPoint2D32f( 0, QRImage->height );

		//cvGetPerspectiveTransform( srcQuad, dstQuad, warp_matrix );
		//不會實作QQ

		IplImage *dst = cvCloneImage( QRImage );

		//cvWarpPerspective( QRImage, dst, warp_matrix );
		cvNamedWindow( "Perspective Transformation", CV_WINDOW_AUTOSIZE );
		cvShowImage( "Perspective Transformation", dst );

		cvWaitKey( 0 );
		cvReleaseImage( &dst );
		cvDestroyWindow( "Perspective Transformation" );
		clickCount = 0;
		QRImage = cvLoadImage( "database//QR.jpg" );
	}
}

void CMFCApplication1Dlg::OnBnClickedButton7()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	QRImage = cvLoadImage( "database//QR.jpg" );
	cvNamedWindow( "Image", CV_WINDOW_AUTOSIZE );
	cvShowImage( "Image", QRImage );

	cvSetMouseCallback( "Image", on_mouse7, 0 );

	cvWaitKey( 0 );
	cvReleaseImage( &QRImage );
	cvDestroyWindow( "Image" );
}

void CMFCApplication1Dlg::OnBnClickedButton8()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	char *filename = "database//shoes.jpg";
	IplImage *image = cvLoadImage( filename ),
			 *gloThImage = cvCreateImage( cvGetSize( image ), IPL_DEPTH_8U, 1 );
	
	cvNamedWindow( "Image", CV_WINDOW_AUTOSIZE );
	cvShowImage( "Image", image );

	cvCvtColor( image, gloThImage, CV_BGR2GRAY );
	cvThreshold( gloThImage, gloThImage, 256 / 2, 255, CV_THRESH_BINARY );
	cvNamedWindow( "Global Threshold", CV_WINDOW_AUTOSIZE );
	cvShowImage( "Global Threshold", gloThImage );

	cvWaitKey( 0 );
	cvReleaseImage( &image ); cvReleaseImage( &gloThImage );
	cvDestroyWindow( "Image" ); cvDestroyWindow( "Global Threshold" );
}

void CMFCApplication1Dlg::OnBnClickedButton9()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	char *filename = "database//shoes.jpg";
	IplImage *image = cvLoadImage( filename ),
			 *locThImage = cvLoadImage( filename, CV_LOAD_IMAGE_GRAYSCALE );

	cvNamedWindow( "Image", CV_WINDOW_AUTOSIZE );
	cvShowImage( "Image", image );

	cvNamedWindow( "Local Threshold", CV_WINDOW_AUTOSIZE );
	cvAdaptiveThreshold( locThImage, locThImage, 255, CV_ADAPTIVE_THRESH_MEAN_C,
		CV_THRESH_BINARY, locThImage->width/7 + 1, -50 );
	cvShowImage( "Local Threshold", locThImage );
	
	cvNamedWindow( "Gaussian Smooth", CV_WINDOW_AUTOSIZE );
	cvSmooth( locThImage, locThImage, CV_GAUSSIAN, 5, 5 );
	cvShowImage( "Gaussian Smooth", locThImage );

	cvNamedWindow( "Median Filter", CV_WINDOW_AUTOSIZE );
	cvSmooth( locThImage, locThImage, CV_MEDIAN, 5 );
	cvShowImage( "Median Filter", locThImage );

	cvWaitKey( 0 );
	cvReleaseImage( &image ); cvReleaseImage( &locThImage );
	cvDestroyWindow( "Image" ); cvDestroyWindow( "Local Threshold" );
	cvDestroyWindow( "Gaussian Smooth" ); cvDestroyWindow( "Median Filter" );
}