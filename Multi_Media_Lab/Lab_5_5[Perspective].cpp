#include <opencv2/opencv.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/core.hpp>
#include <cmath> 
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	// Inputpoints
	Point2f inputQuad[4];
	// Corresponding points
	Point2f outputQuad[4];
	// warpMatrix
	Mat warp_mat(2, 4, CV_32FC1);
	//Loadtheimage
	Mat input = imread("sea.jpg", IMREAD_COLOR);
	Mat output = Mat::zeros(input.rows, input.cols, input.type());
	// Thesefourptsarethesidesof therectboxusedasinput(from top-left in clockwise order)
	inputQuad[0] = Point2f(-30, -60);
	inputQuad[1] = Point2f(input.cols + 50, -50);
	inputQuad[2] = Point2f(input.cols + 100, input.rows + 50);
	inputQuad[3] = Point2f(-50, input.rows + 50);
	// The 4 pointswherethemappingistobedone, fromtop-leftinclockwiseorder
	outputQuad[0] = Point2f(0, 0);
	outputQuad[1] = Point2f(input.cols - 1, 0);
	outputQuad[2] = Point2f(input.cols - 1, input.rows - 1);
	outputQuad[3] = Point2f(0, input.rows - 1);
	// GetthePerspectiveTransformMatrixi.e. lambda
	warp_mat = getPerspectiveTransform(inputQuad, outputQuad);
	// ApplythePerspectiveTransformjustfoundtothesrcimage
	warpPerspective(input, output, warp_mat, output.size());

	imshow("Original", input);
	imshow("Image warping : Perspective transformation", output);

	waitKey(0);
	return 0;
}