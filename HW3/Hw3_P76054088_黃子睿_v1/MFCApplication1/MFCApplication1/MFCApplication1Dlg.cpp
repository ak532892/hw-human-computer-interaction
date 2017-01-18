
// MFCApplication1Dlg.cpp : 實作檔
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include <opencv2/opencv.hpp> 
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/features2d.hpp> 
#include <opencv2/video/background_segm.hpp>
#include <iostream>
#include <string>
#include <map>
using namespace cv;
using namespace std;
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
	AllocConsole();
	freopen("CONIN$", "r", stdin); 
	freopen ( "CONOUT$", "w", stdout );

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

void DrawFeaturePoint( char *filename )
{
	Mat image = imread( filename );
    SiftFeatureDetector detector;
    vector<KeyPoint> keypoints;

    detector.detect( image, keypoints );
	drawKeypoints( image, keypoints, image );

	printf( "Total image %c feature point: %d\n", filename[15], keypoints.size() );
    imshow( filename + 10, image );	
}

void CMFCApplication1Dlg::OnBnClickedButton1()
{
	// TODO: 在此加入控制項告知處理常式程式碼

	DrawFeaturePoint( "database//plane1.jpg" );
	DrawFeaturePoint( "database//plane2.jpg" );
}


void CMFCApplication1Dlg::OnBnClickedButton2()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	
	char *filename = "database//bgSub_video.mp4";
	VideoCapture cap( filename );

	Mat frame, foreground;
	BackgroundSubtractorMOG2 mog2( 3, 450, true ); //shadow

	while( cap.read( frame ) ){
		mog2( frame, foreground, 0.0001 );  

		imshow( "video", frame );
		imshow( "foreground", foreground );
		waitKey( 10 );
	}
	waitKey( 0 );
	destroyWindow( "video" ); destroyWindow( "foreground" );
}


IplImage *trackingFrame;
int clickCount, windowSize;
void on_mouse3( int event, int x, int y, int flags, void* fPtr ) 
{	
	static CvPoint2D32f srcQuad[7];

	if( event == CV_EVENT_LBUTTONDOWN ){
		srcQuad[clickCount++] = cvPointTo32f( cvPoint( x, y ) );
		fprintf( (FILE *)fPtr, "Point%d: (%.0f, %.0f)\n", clickCount, srcQuad[clickCount-1].x, srcQuad[clickCount-1].y );
		printf("Point%d: (%.0f, %.0f)\n", clickCount, srcQuad[clickCount-1].x, srcQuad[clickCount-1].y );

		cvCircle( trackingFrame, cvPoint( x, y ), 6, cvScalar(0, 0, 255), -1 );
		cvShowImage( "Preprocessing", trackingFrame );
	}
	
	if( clickCount == 7 ){
		cvDestroyWindow( "Preprocessing" );

		AfxMessageBox( _T( "請在console介面輸入Window size" ) );	

		printf( "Window size = " ); scanf( "%d", &windowSize );
		fprintf( (FILE *)fPtr, "Window size: %d\n", windowSize );
		fclose( (FILE *)fPtr );

		cvShowImage( "First frame", trackingFrame );
		cvWaitKey( 0 );
		cvDestroyWindow( "First frame" );
	}
}

void CMFCApplication1Dlg::OnBnClickedButton3()
{
	// TODO: 在此加入控制項告知處理常式程式碼

	char *filename = "database//tracking_video.mp4";
	CvCapture *capture = cvCaptureFromFile( filename );
	
	trackingFrame = cvQueryFrame( capture );
	cvNamedWindow( "Preprocessing", CV_WINDOW_AUTOSIZE );
	cvShowImage( "Preprocessing", trackingFrame );

	AfxMessageBox( _T( "請直接點選7個追蹤點" ) );

	FILE *fPtr = fopen( "database//hw3_1.txt", "w" );
	clickCount = 0;
	cvSetMouseCallback( "Preprocessing", on_mouse3,  (void*)fPtr );
}


void CMFCApplication1Dlg::OnBnClickedButton4()
{
	// TODO: 在此加入控制項告知處理常式程式碼

	const int MAX_CORNERS = 7;
	char *filename = "database//tracking_video.mp4";
	CvCapture *capture = cvCaptureFromFile( filename );

	FILE *fPtr1 = fopen( "database//hw3_1.txt", "r" );
	CvPoint2D32f *cornersA = new CvPoint2D32f[ MAX_CORNERS ];
	char trash[200];
	for(int i = 0; i < MAX_CORNERS; i++)
		fscanf( fPtr1, "%s (%f,%f)" , &trash, &cornersA[i].x, &cornersA[i].y );
	int win_size;
	fscanf( fPtr1, "%s%s%d", &trash, &trash, &win_size );
	fclose( fPtr1 );

	IplImage *img1 = cvQueryFrame( capture );
	IplImage *imgA = cvCreateImage( cvGetSize( img1 ), IPL_DEPTH_8U, 1 );
	cvCvtColor( img1, imgA, CV_BGR2GRAY );
	IplImage *img2;

	FILE *fPtr2 = fopen( "database//hw3_2.txt", "w" );
	int frameNum = 0;
	int corner_count;
	while( img2 = cvQueryFrame( capture ) ){
		frameNum++;
		IplImage* imgB = cvCreateImage( cvGetSize( img2 ), IPL_DEPTH_8U, 1 );
		cvCvtColor( img2, imgB, CV_BGR2GRAY );

		CvSize img_sz = cvGetSize( imgA );
		// The first thing we need to do is get the features
		// we want to track.
		//
		corner_count = MAX_CORNERS;

		// Call the Lucas Kanade algorithm
		//
		char features_found[ MAX_CORNERS ];
		float feature_errors[ MAX_CORNERS ];
		CvSize pyr_sz = cvSize( imgA->width+8, imgB->height/3 );
		IplImage* pyrA = cvCreateImage( pyr_sz, IPL_DEPTH_32F, 1 );
		IplImage* pyrB = cvCreateImage( pyr_sz, IPL_DEPTH_32F, 1 );
		CvPoint2D32f* cornersB = new CvPoint2D32f[ MAX_CORNERS ];

		cvCalcOpticalFlowPyrLK(
			imgA,
			imgB,
			pyrA,
			pyrB,
			cornersA,
			cornersB,
			corner_count,
			cvSize( win_size,win_size ),
			5,
			features_found,
			feature_errors,
			cvTermCriteria( CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, .3 ),
			0
		);
		// Now make some image of what we are looking at:
		//
		for( int i=0; i<corner_count; i++ ) {
			if( features_found[i]==0|| feature_errors[i]>550 ) {
				printf("Error is %f\n",feature_errors[i]);
				continue;
			}
			//printf("Got it\n");
			CvPoint p0 = cvPoint(
				cvRound( cornersA[i].x ),
				cvRound( cornersA[i].y )
			);
			CvPoint p1 = cvPoint(
				cvRound( cornersB[i].x ),
				cvRound( cornersB[i].y )
			);
		}
		
		fprintf( fPtr2, "frame %d:(%.0f, %.0f)", frameNum, cornersB[0].x, cornersB[0].y );
		cornersA[0].x = cornersB[0].x,
		cornersA[0].y = cornersB[0].y;
		for(int i = 1; i < corner_count; i++){
			fprintf( fPtr2, ", (%.0f, %.0f)", cornersB[i].x, cornersB[i].y );
			cornersA[i].x = cornersB[i].x,
			cornersA[i].y = cornersB[i].y;
		}
		fprintf( fPtr2, "\n" );
		imgA = cvCloneImage( imgB );
	}
	fclose( fPtr2 );

	CvCapture *capture2 = cvCaptureFromFile( filename );
	IplImage *draw = cvQueryFrame( capture2 );
	
	CvPoint2D32f *cornersC = new CvPoint2D32f[ MAX_CORNERS ];
	CvPoint2D32f *cornersD = new CvPoint2D32f[ MAX_CORNERS ];

	int trash2;
	frameNum = 0;
	FILE *fPtr3 = fopen( "database//hw3_2.txt", "r" );
	while( draw = cvQueryFrame( capture2 ) ){
		frameNum++;
		rewind(fPtr3);
		
		fscanf( fPtr3, "%s %d:(%f,%f)" , &trash, &trash2, &cornersC[0].x, &cornersC[0].y );
		for(int i = 1; i < corner_count; i++)
			fscanf( fPtr3, ", (%f, %f)", &cornersC[i].x, &cornersC[i].y );
		for(int i = 0; i < frameNum; i++){
			fscanf( fPtr3, "%s %d:(%f,%f)" , &trash, &trash2, &cornersD[0].x, &cornersD[0].y );
			for(int i = 1; i < corner_count; i++)
				fscanf( fPtr3, ", (%f, %f)", &cornersD[i].x, &cornersD[i].y );
		
			for(int i = 0; i < corner_count; i++){
				CvPoint p0 = cvPoint(
					cvRound( cornersC[i].x ),
					cvRound( cornersC[i].y )
				);
				CvPoint p1 = cvPoint(
					cvRound( cornersD[i].x ),
					cvRound( cornersD[i].y )
				);
				cvLine( draw, p0, p1, CV_RGB(0,255,255), 2 );
				cornersC[i].x = cornersD[i].x;
				cornersC[i].y = cornersD[i].y;
			}
		}
		for(int i = 0; i < corner_count; i++)
			cvCircle( draw, cvPoint( (int)cornersC[i].x, (int)cornersC[i].y ), 6, cvScalar(0, 0, 255), -1 );
		cvNamedWindow( "Optical Flow tracking", CV_WINDOW_AUTOSIZE );
		cvShowImage( "Optical Flow tracking", draw );
		cvWaitKey( 10 );
	}
	fclose( fPtr3 );
	cvWaitKey( 0 );
	cvDestroyWindow( "Optical Flow tracking" );
}

static Mat norm_0_255(InputArray _src)
{
	Mat src = _src.getMat();
	// Create and return normalized image:
	Mat dst;
	switch(src.channels()) {
		case 1:
		cv::normalize(_src, dst, 0, 255, NORM_MINMAX, CV_8UC1);
		break;
		case 3:
		cv::normalize(_src, dst, 0, 255, NORM_MINMAX, CV_8UC3);
		break;
		default:
		src.copyTo(dst);
		break;
	}
	return dst;
}

Ptr<FaceRecognizer> model;
map<int, string> trainname;
int trainsizeRow, trainsizeCol;

void train()
{
	// These vectors hold the images and corresponding labels.
	vector<Mat> images;
	vector<int> labels;
	
	// Read in the data. This can fail if no valid

	int trainImageCount = 3;

	for(int i = 0; i < trainImageCount; i++) {
		char filename[50];
		sprintf( filename, "database//%d.jpg", i%3 );
		
		Mat trainImage = imread( filename, IMREAD_GRAYSCALE );
		equalizeHist( trainImage, trainImage );

		images.push_back( trainImage );
		labels.push_back(i%3);

		trainsizeRow = images[i].rows;
		trainsizeCol = images[i].cols;
	}
	trainname[0] = "Harry Potter";
	trainname[1] = "Hermione Granger";
	trainname[2] = "Ron Weasley";
	
	model = createEigenFaceRecognizer( 80 );
	model->train(images, labels);
}

void CMFCApplication1Dlg::OnBnClickedButton5()
{
	// TODO: 在此加入控制項告知處理常式程式碼

	train();
	
	// The following line predicts the label of a given
	// test image:
	Mat testSample = imread( "database//test.jpg", IMREAD_GRAYSCALE );
	int predictedLabel = model->predict(testSample);

	string result_message = "the image is : " + trainname[predictedLabel];
	cout << result_message << endl;

	Mat mean = model->getMat("mean");

	imshow( "mean", norm_0_255(mean.reshape(1, testSample.rows)) );
	waitKey( 0 );
	destroyWindow( "mean" );
}

Mat frame;
char *filename = "database//face.jpg";
vector<Rect> faces;
vector<Mat> ROIimages;

 void detectAndDisplay()
{	
	Mat frame_gray;

	cvtColor( frame, frame_gray, CV_BGR2GRAY );
	equalizeHist( frame_gray, frame_gray );

	//-- load
	CascadeClassifier face_cascade;
	String face_cascade_name = "database//haarcascade_frontalface_alt.xml";

	face_cascade.load( face_cascade_name );
	face_cascade.detectMultiScale( frame_gray, faces, 1.05, 3, 0|CV_HAAR_SCALE_IMAGE, Size(50, 50) );

	//-- Detect faces
	cout << faces.size() << " faces detect\n";

	for( size_t i = 0; i < faces.size(); i++ ){
		Mat roi = frame( faces[i] ), reRoi;
		Mat ROIgray;

		resize( roi, reRoi, Size(trainsizeCol, trainsizeRow ) );
		cvtColor( reRoi, ROIgray, CV_BGR2GRAY );
		equalizeHist( ROIgray, ROIgray );

		ROIimages.push_back( ROIgray );

		rectangle( frame, faces[i], Scalar( 0, 0, 255 ), 3 );
	}
	imshow( "Detection", frame );
}

void CMFCApplication1Dlg::OnBnClickedButton6()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	
	//-- 1. Read
	frame = imread( filename );

	//-- 2. Apply the classifier to the frame
	detectAndDisplay( ); 

	imshow( "Detection", frame );
	waitKey( 0 );
	destroyWindow( "Detection" );
}


void CMFCApplication1Dlg::OnBnClickedButton7()
{
	// TODO: 在此加入控制項告知處理常式程式碼

	if( frame.empty() ){
		frame = imread( filename );
		train();
		detectAndDisplay();
	}

	for(int i = 0; i < faces.size(); i++){
		int predictedLabel = model->predict( ROIimages[i] );

		putText( frame, trainname[predictedLabel], Point( faces[i].width + faces[i].x - 130, faces[i].height + faces[i].y + 30), FONT_HERSHEY_TRIPLEX|FONT_ITALIC, 0.8, Scalar(0, 70, 255), 2, CV_AA);
	}

	imshow( "Detection + Recognition", frame );
	waitKey( 0 );
	destroyWindow( "Detection + Recognition" );
}
