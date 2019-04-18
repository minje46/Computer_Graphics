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
	string imageName("sample.png");
	if (argc > 1)
		imageName = argv[1];

	Mat image;
	image = imread(imageName.c_str(), IMREAD_COLOR);
	//image = imread(argv[1]);		// ����뿡�� ���� �ڵ带 �־���� argv�� �޾ƿ� �� �ִ�.
	
;	if (image.empty())
	{
		cout << "Could not open or find the image" << endl;
		return -1;
	}

	Mat new_img = Mat::zeros(image.size(), image.type());	// Memory �Ҵ�.

	cout << "Basic Linear Transforms " << endl;
	cout << "====================" << endl;
	cout << "Enter the alpha value [1.0 - 3.0] : ";
	cin >> alpha;
	cout << "Enter the beta value [0 - 100] : " ;
	cin >> beta;

	for (int y = 0; y < image.rows; y++)		// ����
	{
		for (int x = 0; x < image.cols; x++)		// ����
		{
			for (int c = 0; c < 3; c++)
				new_img.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(alpha*(image.at<Vec3b>(y, x)[c]) + beta);
				// Bitmap�� ���, [w*h*bit]���� ǥ���Ǳ� ������, y,x,c�� ǥ�� �ϴ� ��.
				// Pixel �� inch�� data�� ������ �����Ƿ�, ��ȭ�� �ֱ� ���ؼ� pixel�� (0,0)~(w,h)���� �Ѱ��� ��ȭ�� �ִ� ��.	
		}
	}

	namedWindow("Original Image", WINDOW_AUTOSIZE);
	namedWindow("New Image", WINDOW_AUTOSIZE);
	
	imshow("Original Image", image);
	imshow("New Image", new_img);

	waitKey(0);
	return 0;
}