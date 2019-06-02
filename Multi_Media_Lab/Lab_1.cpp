#include<opencv2/core/core.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2\highgui.hpp>

#include<iostream>
#include<string>

using namespace std;
using namespace cv;

int main(int argc, char** argv) 
{
	string imageName("pusan.jpg");
	if (argc > 1)
		imageName = argv[1];

	Mat image;
	image = imread(imageName.c_str(), IMREAD_COLOR);
	if (image.empty())
	{
		cout << "Could not open or find the image" << endl;
		return -1;
	}
	
	namedWindow("Display window", WINDOW_AUTOSIZE);
	imshow("Display window", image);
	waitKey(0);
	return 0;
}