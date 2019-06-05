#include <opencv2/opencv.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/core.hpp>
#include <cmath> 
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	Mat src = imread("sea.jpg", IMREAD_COLOR);
	if (src.empty())
	{
		cout << "Could not open or find the image" << endl;
		return -1;
	}

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

	imshow("Original", src);
	imshow("Image warping : Affien transformation", warp_dst);

	waitKey(0);
	return 0;
}