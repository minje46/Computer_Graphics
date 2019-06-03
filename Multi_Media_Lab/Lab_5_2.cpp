//
//  Lab05_2.cpp
//  mulmi
//
//  Created by LSH on 03/05/2019.
//  Copyright © 2019 LSH. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;


int main(int argc, const char * argv[]) {
	string n_1("/Users/lsh/Downloads/Lena_color.png");
	if (argc>1) n_1 = argv[1];
	Mat image_1 = imread(n_1.c_str(), IMREAD_COLOR);
	double mul = 1.5;
	Mat n_image = Mat::zeros(image_1.rows*mul, image_1.cols*mul, image_1.type());
	if (image_1.empty()) {
		cout << "No image\n";
		return -1;
	}

	for (int i = 0; i<image_1.rows*mul; ++i)
		for (int j = 0; j<image_1.cols*mul; ++j)
			n_image.at<Vec3b>(i, j) = image_1.at<Vec3b>(round(i / mul), round(j / mul));

	namedWindow("Disp", WINDOW_AUTOSIZE);
	//resize(image_1, n_image, Size(), 1.5,1.5, INTER_LINEAR);
	imshow("org", n_image);
	imshow("dd", image_1);
	waitKey(0);
	return 0;
}