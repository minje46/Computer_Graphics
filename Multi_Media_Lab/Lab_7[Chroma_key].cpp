#include <iostream>
#include<math.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv) 
{
	Mat input = imread("Chroma_key.jpg", IMREAD_COLOR);				// Load the input(chroma key) image.
	if (input.empty()) 
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}
	resize(input, input, Size(450, 450));
	cvtColor(input, input, COLOR_BGR2YCrCb);		// Convert the color as YCrCb to extract Cb_key and Cr_key later.			

	Mat back_ground = imread("Chroma_bg.jpg", IMREAD_COLOR);	// Load the background image.	
	resize(back_ground, back_ground, cv::Size(input.size().width, input.size().height), 0, 0, INTER_LINEAR);	// Resize the background same as input.

	int Cr[255] = { 0, }, Cb[255] = { 0, };				// Store the Cr, Cb value.
	for (int i = 0; i <input.rows; i++)
	{
		for (int j = 0; j < input.cols; j++)
		{
			Cr[input.at<Vec3b>(i, j)[1]]++;
			Cb[input.at<Vec3b>(i, j)[2]]++;
		}
	}

	int Cr_max = 0, Cb_max = 0, Cr_key, Cb_key;
	for (int i = 0; i < 255; i++) 
	{
		if (Cr_max < Cr[i]) 
		{
			Cr_max = Cr[i];
			Cr_key = i;
		}
		if (Cb_max < Cb[i]) 
		{
			Cb_max = Cb[i];
			Cb_key = i;
		}
	}

	Mat output = Mat::zeros(input.size(), input.type());
	Mat original;
	cvtColor(input, original, COLOR_YCrCb2BGR);
	float inner_threshold = 45, outer_threshold = 50;
	for (int i = 0; i < input.rows; i++)
	{
		for (int j = 0; j < input.cols; j++)
		{
			float dist = sqrt((int)pow((input.at<Vec3b>(i, j)[1] - Cr_key), 2) + (int)pow((input.at<Vec3b>(i, j)[2] - Cb_key), 2));		// Apply to Euclid distance.
			float alpha;																								// Do alpha matting algorithm. 
			if (dist < inner_threshold)
				alpha = 0;																							// Between 0~
			else if (dist < outer_threshold)
				alpha = (dist - inner_threshold) / (outer_threshold - inner_threshold);			// Do linear interpolation based on inner and outer threshold.
			else
				alpha = 1;																							// ~1 of linear interpolation.

			output.at<Vec3b>(i, j) = (1 - alpha)*back_ground.at<Vec3b>(i, j) + alpha * original.at<Vec3b>(i, j);				// Output calculation.
		}
	}

	namedWindow("Chroma key", WINDOW_AUTOSIZE);
	imshow("Chroma key", output);
	waitKey(0);
	return 0;
}