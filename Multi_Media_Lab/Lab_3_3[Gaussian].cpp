#include <opencv2/opencv.hpp>
#include <cmath> 
#include <iostream>
#include <vector>
#include <string>

#define PI 3.14159265358979323846 

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	Mat src = imread("lena512_gray.bmp", IMREAD_GRAYSCALE);
	int N;
	double sigma;

	if (src.empty())
	{
		cout << "Could not open or find the image" << endl;
		return -1;
	}

	cout << "Type the N and Sigma : ";
	cin >> N >> sigma;

	double** mean = new double*[N];
	for (int i = 0; i < N; i++)
		mean[i] = new double[N];

	int padding = N % 2 == 0 ? N / 2 - 1 : N / 2;
	double s = 2.0 * pow(sigma, 2), sum = 0.0;

	for (int x = -padding; x <= padding; x++)
	{
		for (int y = -padding; y <= padding; y++)
		{
			double r = sqrt(pow(x, 2) + pow(y, 2));
			mean[x + padding][y + padding] = (exp(-(r * r) / s)) / (PI * s);
			sum += mean[x + padding][y + padding];
		}
	}

	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			mean[i][j] /= sum;

	Mat dst = Mat::zeros(src.size(), src.type());

	int h_val, h_limit, w_val, w_limit;
	for (int y = 0; y < src.rows; y++)
	{
		for (int x = 0; x < src.cols; x++)
		{
			h_val = y < padding ? -1 * y : -1 * padding;
			h_limit = (y >= src.rows - padding) ? src.rows - 1 - y : padding;
			w_val = x < padding ? -1 * x : -1 * padding;
			w_limit = (x >= src.cols - padding) ? src.cols - 1 - x : padding;

			for (int h = h_val; h <= h_limit; h++)
				for (int w = w_val; w <= w_limit; w++)
					dst.at<uchar>(y, x) += src.at<uchar>(h + y, w + x) *mean[h + padding][w + padding];
		}
	}

	for (int i = 0; i < N; i++)
		delete[] mean[i];
	delete mean;

	imshow("Original", src);
	imshow("Smoothing filter : Gaussian", dst);

	waitKey(0);
	return 0;
}