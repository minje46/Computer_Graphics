#include <opencv2\core\core.hpp>
#include <opencv2\imgcodecs\imgcodecs.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

#include <iostream>
#include<string>

using namespace cv;
using namespace std;

double alpha;
int DIRECTIONS[8][2] = { { 1, 0 },{ -1, 0 },{ 0, 1 },{ 0, -1 },{ 1, 1 },{ 1, -1 },{ -1, 1 },{ -1, -1 } };

int main(int argc, char** argv) 
{
	string imageName("lena512_gray.bmp");
	if (argc > 1) 
		imageName = argv[1];

	Mat original;
	original = imread(imageName.c_str(), IMREAD_GRAYSCALE);
	if (original.empty())
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	Mat new_image = Mat::zeros(original.size(), original.type());
	for (int y = 0; y < original.rows; y++)
	{
		for (int x = 0; x < original.cols; x++)
		{
			int total = original.at<uchar>(y, x);
			for (int a = 0; a < 8; a++) 
			{
				int nextRow = y + DIRECTIONS[a][0];
				int nextCol = x + DIRECTIONS[a][1];

				if (nextRow < 0 || nextRow > original.rows - 1 || nextCol < 0 || nextCol > original.cols - 1) 
					continue;

				total += original.at<uchar>(nextRow, nextCol);
			}
			new_image.at<uchar>(y, x) = total / 9;
		}
	}

	namedWindow("Smoothing filter : Average.", 1);
	imshow("original", original);
	imshow("Smoothing filter : Average.", new_image);

	waitKey(0);
	return 0;
}