#include<opencv2/core/core.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2\highgui.hpp>

#include<iostream>
#include<string>

using namespace std;
using namespace cv;

double alpha;		// Simple contrast control.
int beta;				// Simple birghtness control.

int main(int argc, char** argv)
{
	string back_ground("sea.jpg");			// ���ȭ�� ���� load.
	string out_ward("sample.png");				// ǥ�� ���� load.

	if (argc > 1)
	{
		out_ward = argv[1];
		back_ground = argv[1];
	}

	Mat in_img;										// Image�� memory�� load.
	in_img = imread(out_ward.c_str(), IMREAD_COLOR);
	Mat out_img;
	out_img = imread(back_ground.c_str(), IMREAD_COLOR);
	Mat new_img = Mat::zeros(in_img.size(), in_img.type());	// Memory �Ҵ�.

	if (out_ward.empty() || back_ground.empty())			// Exception ó��.
	{
		cout << "Could not open or find the in_img" << endl;
		return -1;
	}
	
	double w = 0.7;									// ���� ��.		
	for (int y = 0; y < in_img.rows; y++)		// ����
	{
		for (int x = 0; x < in_img.cols; x++)	// ����
		{
			for (int c = 0; c < in_img.channels(); c++)
				new_img.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(w*in_img.at<Vec3b>(y, x)[c] + (1.0 - w)*out_img.at<Vec3b>(y, x)[c]);
		}
	}

	namedWindow("New in_img", WINDOW_AUTOSIZE);		// ����� window ����.
	imshow("New in_img", new_img);									// Image display.

	waitKey(0);
	return 0;
}