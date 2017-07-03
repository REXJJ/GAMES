#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include "opencv2/opencv.hpp"
#include <iostream> 
#include <time.h>
#include <fstream>

using namespace std;
using namespace cv;

/// Global variables

Mat src, src_gray;
Mat dst, detected_edges;

int edgeThresh = 1;
int lowThreshold;
int const max_lowThreshold = 100;
int ratio = 3;
int kernel_size = 3;
char* window_name = "Edge Map";
int x;
fstream f;
/**
 * @function CannyThreshold
 * @brief Trackbar callback - Canny thresholds input with a ratio 1:3
 */

Mat A,B;

/*void histogram()
{

    int s=600;
    int max=0;
    B.create(s,256,A.type());
    int a[256];
    for(int i=0;i<256;i++)
     a[i]=0;
    B = Scalar::all(255);
    for(int i=0;i<A.rows;i++)
    for(int j=0;j<A.cols;j++)
    {a[int(A.at<uchar>(i,j))]++;
     if(a[int(A.at<uchar>(i,j))]>max)
       max=a[int(A.at<uchar>(i,j))];}
   while(s<max)
{
    for(int i=0;i<256;i++)
    a[i]=a[i]/10;
    max=max/10;
}
    for(int i=0;i<200;i++)
    {
     for(int j=0;j<a[i];j++)
      B.at<uchar>(s-j,i)=i;
    }
    imshow("Histogram",B);
}*/

void CannyThreshold(int, void*)
{

char ch;
int sta=1;
  
  /// Reduce noise with a kernel 3x3
  blur( src_gray, detected_edges, Size(3,3) );

  /// Canny detector
  Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );

  /// Using Canny's output as a mask, we display our result
  dst = Scalar::all(0);

  src.copyTo( dst, detected_edges);
  x=dst.rows/2;
  for(int j=0;j<dst.rows&&sta;j++) 
{
  for (int i=0;i<dst.cols;i++)
  {
    if(int(dst.at<uchar>(j,i))>50)
      {
         
        (j>x)?ch='a':ch='q';
         x=j;
         f.open("NEW.txt",ios::out);
         f<<ch;
         f.close();
         sta=0;
         break;
      }
  }
}
   A=dst;
 // histogram();
 // imshow( window_name,dst );
 }

int main()
{
int status=1;
	VideoCapture cap(0);
	if ( !cap.isOpened() )  // isOpened() returns true if capturing has been initialized.
        {
		cout << "Cannot open the video file. \n";
		return -1;
        }

    double fps = cap.get(CV_CAP_PROP_FPS); //get the frames per seconds of the video
    //namedWindow("A_good_name",CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"
    while(1)
    {
    Mat frame1,frame2,frame3,frame4,frame,frame5;
    if (!cap.read(frame1)) // if not success, break loop
        {
	    cout<<"\n Cannot read the video file. \n";
            break;
        }
//cvtColor( frame1, frame2, COLOR_BGR2GRAY );
if (!cap.read(frame3)) // if not success, break loop
        {
			cout<<"\n Cannot read the video file. \n";
            break;
        }
//cvtColor( frame3, frame4, COLOR_BGR2GRAY );
frame=frame1-frame3;
//frame5=Scalar::all(255)-frame;
src=frame;
/// Create a matrix of the same type and size as src (for dst)
  dst.create( src.size(), src.type() );

  /// Convert the image to grayscale
  cvtColor( src, src_gray, CV_BGR2GRAY );
  /// Create a window
  namedWindow( window_name, CV_WINDOW_AUTOSIZE );

  /// Create a Trackbar for user to enter threshold
  createTrackbar( "Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold );

  /// Show the image
  CannyThreshold(0, 0);
if(waitKey(30) == 27) // Wait for 'esc' key press to exit
        { 
            f.close();
            break; 
        }
    }

    return 0;
}
// END OF PROGRAM
