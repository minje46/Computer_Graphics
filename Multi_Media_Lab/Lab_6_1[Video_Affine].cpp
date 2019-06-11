#include <opencv2/opencv.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/core.hpp>
#include <cmath> 
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

Mat Affine(Mat src)
{
	Point2f srcTri[3];
	Point2f dstTri[3];
	srcTri[0] = Point2f(0, 0);
	srcTri[1] = Point2f(src.cols - 1, 0);
	srcTri[2] = Point2f(0, src.rows - 1);
	dstTri[0] = Point2f(src.cols*0.0, src.rows*0.33);
	dstTri[1] = Point2f(src.cols*0.85, src.rows*0.25);
	dstTri[2] = Point2f(src.cols*0.15, src.rows*0.7);

	Mat warp_mat(2, 3, CV_32FC1);
	Mat warp_dst = Mat::zeros(src.rows, src.cols, src.type());

	warp_mat = getAffineTransform(srcTri, dstTri);
	warpAffine(src, warp_dst, warp_mat, warp_dst.size());

	return warp_dst;
}

int main(int, char **)
{
	VideoCapture cap(0);		// Open the default camera.
	if (!cap.isOpened())			// Check if we succeeded.
		return -1;

	Mat edges;
	namedWindow("edges", 1);
	for (;;) 
	{
		Mat frame;
		cap >> frame;			// Get a new frame from camera.
		cvtColor(frame, edges, COLOR_BGR2GRAY);
		GaussianBlur(edges, edges, Size(7, 7), 1.5, 1.5);
		Canny(edges, edges, 0, 30, 3);
		//imshow("Edges", edges);

		Mat affine = Affine(frame);
		imshow("Frame", affine);

		if (waitKey(30) >= 0)
			break;
	}	
	// The camera will be deinitialized automatically in VideoCapture destructor.
	return 0;
}