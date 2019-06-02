#include <opencv2\core\core.hpp>
#include <opencv2\imgcodecs\imgcodecs.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

#include <iostream>
#include<string>

using namespace cv;
using namespace std;

void YCC(Mat src)
{
	double ycc[3][3] = { { 0.299, 0.587, 0.114 },{ -0.168736, -0.331264, 0.5 },{ 0.5, -0.418688, -0.081312 } };
	double last[3] = { 0, 0.5, 0.5 };

	Mat dst_YCC = Mat::zeros(src.size(), src.type());
	for (int y = 0; y < src.rows; y++)
	{
		for (int x = 0; x < src.cols; x++)
		{
			for (int i = 0; i < 3; i++)
			{
				double color = src.at<Vec3b>(y, x)[i];
				
				for (int j = 0; j < 3; j++)
				{
					double nc = color * ycc[i][j] + last[j];
					dst_YCC.at<Vec3b>(y, x)[i] = (2 * color > 255 ? 255 : 2 * color);
				}
			}
		}
	}
	imshow("YCC Color transformation", dst_YCC);
}

void RGB(Mat src)
{
	Mat dst_RGB = Mat::zeros(src.size(), src.type());
	for (int y = 0; y < src.rows; y++)
	{
		for (int x = 0; x < src.cols; x++)
		{
			for (int i = 0; i < 3; i++)
			{
				int color = src.at<Vec3b>(y, x)[i];
				dst_RGB.at<Vec3b>(y, x)[i] = (2 * color > 255 ? 255 : 2 * color);
			}
		}
	}
	imshow("RGB Color transformation", dst_RGB);
}

int main(int argc, char** argv)
{
	Mat src = imread("Lena_color.png", IMREAD_COLOR);
	if (src.empty())
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	imshow("Original", src);
	//RGB(src);
	YCC(src);

	waitKey(0);
	return 0;
}