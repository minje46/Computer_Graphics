#include<iostream>
#include<cmath>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int xGradient(Mat image, int x, int y)
{			// 왼쪽 위 대각선(+1), 왼쪽 방향(+2), 왼쪽 아래 대각선(+1), 오른쪽 위 대각선(-1), 오른쪽(-2), 오른쪽 아래 대각선(-1)
	return image.at<uchar>(y - 1, x - 1) +
		2 * image.at<uchar>(y, x - 1) +
		image.at<uchar>(y + 1, x - 1) -
		image.at<uchar>(y - 1, x + 1) -
		2 * image.at<uchar>(y, x + 1) -
		image.at<uchar>(y + 1, x + 1);
}

int yGradient(Mat image, int x, int y)
{			// 왼쪽 위 대각선(+1), 위쪽 방향(+2), 오른쪽 위 대각선(+1), 왼쪽 아래 대각선(-1), 아래쪽(-2), 오른쪽 아래 대각선(-1)
	return image.at<uchar>(y - 1, x - 1) +
		2 * image.at<uchar>(y - 1, x) +
		image.at<uchar>(y - 1, x + 1) -
		image.at<uchar>(y + 1, x - 1) -
		2 * image.at<uchar>(y + 1, x) -
		image.at<uchar>(y + 1, x + 1);
}

int main(int argc, char** argv)
{
	Mat src, dst;
	int gx, gy, sum;

	string imageName("lena512_gray.bmp");
	if (argc > 1)
		imageName = argv[1];

	src = imread(imageName.c_str(), IMREAD_GRAYSCALE);	
	dst = src.clone();
	if (!src.data)
		return -1;


	for (int y = 0; y < src.rows; y++)
		for (int x = 0; x < src.cols; x++)
			dst.at<uchar>(y, x) = 0.0;

	for (int y = 1; y < src.rows - 1; y++)
	{
		for (int x = 1; x < src.cols - 1; x++)
		{
			gx = xGradient(src, x, y);
			gy = yGradient(src, x, y);
			sum = abs(gx) + abs(gy);
			sum = sum > 255 ? 255 : sum;
			sum = sum < 0 ? 0 : sum;
			dst.at<uchar>(y, x) = sum;
		}
	}

	namedWindow("Sobel filter");
	imshow("Sobel filter", dst);
	namedWindow("Original");
	imshow("Original", src);

	waitKey();
	return 0;
}