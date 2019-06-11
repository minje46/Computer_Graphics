#include <iostream>
#include<math.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int block_size = 16;
int search_range = 31;

int main(int argc, char** argv)
{
	Mat input1 = imread("caltrain002.png", IMREAD_COLOR);
	cvtColor(input1, input1, COLOR_BGR2GRAY);
	Mat input2 = imread("caltrain004.png", IMREAD_COLOR);
	cvtColor(input2, input2, COLOR_BGR2GRAY);

	Mat output = Mat::zeros(input1.size(), input1.type());
	
	for (int m = block_size; m<input1.rows - block_size; m += block_size) 
	{
		for (int n = block_size; n<input1.cols - block_size; n += block_size) 
		{
			int MAD = 256 * block_size * block_size;
			int min_x = 0;
			int min_y = 0;
			for (int i = m - search_range / 2; i<m + search_range / 2; i++) 
			{
				for (int j = n - search_range / 2; j<n + search_range / 2; j++) 
				{
					double sum = 0;
					for (int x = 0; x<block_size; x++) 
					{
						for (int y = 0; y<block_size; y++) 
						{
							//sum += abs(input1.at<uchar>(i+x, j+y) - input2.at<uchar>(i+x, j+y));
							sum += input1.at<uchar>(i + x, j + y) - input2.at<uchar>(i + x, j + y);
						}
					}

					sum = abs(sum);
					if (sum < MAD) 
					{
						MAD = sum;
						min_x = i;
						min_y = j;
					}
					else if (sum == MAD)
					{
						if ((m - min_x)*(m - min_x) + (n - min_y)*(n - min_y) >(m - i)*(m - i) + (n - j)*(n - j)) 
						{
							min_x = i;
							min_y = j;
						}
					}
				}
			}

			output.at<uchar>(m, n) = sqrt((m - min_x)*(m - min_x) + (n - min_y)*(n - min_y)) * 255 /	(block_size*1.414);
		}
	}

	namedWindow("input1", WINDOW_AUTOSIZE);
	imshow("input1", input1);
	namedWindow("input2", WINDOW_AUTOSIZE);
	imshow("input2", input2);
	namedWindow("Block Estimation", WINDOW_AUTOSIZE);
	imshow("Block Estimation", output);
	waitKey(0);
	return 0;
}