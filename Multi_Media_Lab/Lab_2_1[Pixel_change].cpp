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
	//image = imread(argv[1]);		// 디버깅에서 실행 코드를 넣어줘야 argv로 받아올 수 있다.
	
;	if (image.empty())
	{
		cout << "Could not open or find the image" << endl;
		return -1;
	}

	Mat new_img = Mat::zeros(image.size(), image.type());	// Memory 할당.

	cout << "Basic Linear Transforms " << endl;
	cout << "====================" << endl;
	cout << "Enter the alpha value [1.0 - 3.0] : ";
	cin >> alpha;
	cout << "Enter the beta value [0 - 100] : " ;
	cin >> beta;

	for (int y = 0; y < image.rows; y++)		// 가로
	{
		for (int x = 0; x < image.cols; x++)		// 세로
		{
			for (int c = 0; c < 3; c++)
				new_img.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(alpha*(image.at<Vec3b>(y, x)[c]) + beta);
				// Bitmap의 경우, [w*h*bit]으로 표현되기 때문에, y,x,c로 표현 하는 것.
				// Pixel 한 inch당 data를 가지고 있으므로, 변화를 주기 위해서 pixel을 (0,0)~(w,h)까지 한개씩 변화를 주는 것.	
		}
	}

	namedWindow("Original Image", WINDOW_AUTOSIZE);
	namedWindow("New Image", WINDOW_AUTOSIZE);
	
	imshow("Original Image", image);
	imshow("New Image", new_img);

	waitKey(0);
	return 0;
}