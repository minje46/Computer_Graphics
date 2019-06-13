#include <iostream>
#include<math.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d.hpp>

using namespace std;
using namespace cv;

int window_size = 3;
int search_area = 16;

int main(int argc, char** argv)
{
	Mat left = imread("scene1.row3.col2.png", IMREAD_GRAYSCALE);
	Mat right = imread("scene1.row3.col3.png", IMREAD_GRAYSCALE);
	Mat output = Mat::zeros(right.rows, right.cols, CV_8U);

	int half = window_size / 2;
	for (int y = half; y < right.rows - half - search_area; y++)
	{
		for (int x = half; x < right.cols - half - search_area; x++)
		{
			int SSD[16];
			int idx = 0;
			for (int k = x; k < x + search_area; k++)
			{
				SSD[idx] = 0;
				for (int dy = -half; dy <= half; dy++)
				{
					for (int dx = -half; dx <= half; dx++)
					{
						int dis = abs(right.at<uchar>(y + dy, x + dx) - left.at<uchar>(y + dy, k + dx));
						SSD[idx] += (dis*dis);
					}
				}
				idx++;
			}

			int min_idx = 0, min_val = SSD[min_idx];
			for (int i = 1; i < idx; i++)
			{
				if (SSD[i] < min_val)
				{
					min_idx = i;
					min_val = SSD[i];
				}
			}
			output.at<uchar>(y, x) = min_idx * 16;
		}
	}

	namedWindow("Original image", WINDOW_AUTOSIZE);
	imshow("Original image", right);

	namedWindow("Disparity Map : Window Based Matching", WINDOW_AUTOSIZE);
	imshow("Disparity Map : Window Based Matching", output);
	waitKey(0);
	return 0;
}
