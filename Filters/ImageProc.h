// ------------------------------------------------------------------------------------------------
// Image class Header file
// ------------------------------------------------------------------------------------------------

#include "stdafx.h"

#ifndef __IMAGEPROC_H
#define __IMAGEPROC_H

#include "Image.h"

// ------------------------------------------------------------------------------------------------
// ImageProc class
// ------------------------------------------------------------------------------------------------

class ImageProc : public Image
{
private:
	byte xClip(double x)
	{
		if (x < 0) return 0;
		if (x > 255) return 255;
		return (byte)x;
	}
public:
	// pixel processing
	void convertToGray();
	void convertToSepia();

	// sampling & quantization
	void samplingBy2();
	void quantization(int step);

	// Image Enhancement
	void gammaCorrection();
	void contrastStretch();
	void histoEqual();

	// Filter
	void embossing();
	void bluring();
	void sharpening();
	void noise();
	void median();
	void gaussian();
	void kuwahara();
	byte* maskProcess(double mask[3][3]);	// Use for filter mask.

	// GeometryTransformation
	void upScale();
	void downScale();
	void mirroring();
	void rotation(double);

	// ColorImage
	double Min(double, double);
	unsigned char Sol_H(unsigned char, unsigned char, unsigned char);
	unsigned char Sol_S(unsigned char, unsigned char, unsigned char);
	unsigned char Sol_I(unsigned char, unsigned char, unsigned char);
	void HSItoRGB();
	void kmeans();
};

#endif