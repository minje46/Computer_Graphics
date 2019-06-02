#include <opencv2/opencv.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/core.hpp>
#include <cmath> 
#include <iostream>
#include <vector>
#include <string>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	Mat src = imread("sea.jpg", IMREAD_COLOR);
	resize(src, src, Size(512, 512), 0, 0);
	Mat dst = Mat::zeros(src.size(), src.type());
	
	// Existed functions.
	//resize(src, dst, Size(), 1.5, 1.5, INTER_NEAREST);
	//resize(src, dst, Size(), 1.5, 1.5, INTER_LINEAR);
	//resize(src, dst, Size(), 1.5, 1.5, INTER_CUBIC);
	if (src.empty())
	{
		cout << "Could not open or find the image" << endl;
		return -1;
	}


	for (int y = 0; y < src.rows; y++)
	{
		for (int x = 0; x < src.cols; x++)
		{
			
		}
	}

	imshow("Original", src);
	imshow("Interpolation : Nearest", dst);

	waitKey(0);
	return 0;
}