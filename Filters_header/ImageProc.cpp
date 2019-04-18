// ------------------------------------------------------------------------------------------------
// Image class Implementation file
// ------------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "ImageProc.h"

// ------------------------------------------------------------------------------------------------
// Convert to gray-scale
// ------------------------------------------------------------------------------------------------

void byteSort(byte *target, int n) {
	int i, j;
	byte temp;

	for (i = 0; i < n - 1; i++) {
		for (j = i + 1; j < n; j++) {
			if (target[i] > target[j]) {
				temp = target[i];
				target[i] = target[j];
				target[j] = temp;
			}
		}
	}
}

void ImageProc::convertToGray()
{
	int  x, y;
	byte R, G, B;
	byte Gray;

	for (y = 0; y < getHeight(); y++) {
		for (x = 0; x < getWidth(); x++) {
			getPixel(x, y, R, G, B);

			Gray = xClip(0.299*R + 0.587*G + 0.114*B);

			setPixel(x, y, Gray, Gray, Gray);
		}
	}
}

void ImageProc::convertToSepia()
{
	int  x, y;
	byte R, G, B;
	byte sepiaR, sepiaG, sepiaB;

	for (y = 0; y < getHeight(); y++) {
		for (x = 0; x < getWidth(); x++) {
			getPixel(x, y, R, G, B);

			sepiaR = xClip(0.393*R + 0.769*G + 0.189*B);

			sepiaG = xClip(0.349*R + 0.686*G + 0.168*B);

			sepiaB = xClip(0.272*R + 0.534*G + 0.131*B);

			setPixel(x, y, sepiaR, sepiaG, sepiaB);
		}
	}
}

void ImageProc::samplingBy2()
{
	m_level *= 2;
	int  x, y;
	byte R, G, B;

	for (y = 0; y < getHeight(); y += m_level) {
		for (x = 0; x < getWidth(); x += m_level) {
			getPixel(x, y, R, G, B);
			for (int i = 0; i < m_level; i++) {
				for (int j = 0; j < m_level; j++) {
					if (x + i < getWidth() && y + j < getHeight()) {
						setPixel(x + i, y + j, R, G, B);
					}
				}
			}
		}
	}
}

void ImageProc::quantization(int step)
{
	int  x, y;
	byte R, G, B;
	byte tmpR, tmpG, tmpB;
	int level = 256;
	int value = (int)pow(2, (8 - step));

	for (y = 0; y < m_iHeight; y++) {
		for (x = 0; x < m_iWidth; x++) {
			getPixel(x, y, R, G, B);

			tmpR = R;
			tmpG = G;
			tmpB = B;

			for (int i = 0; i < value; i++) {
				if ((int)R >= (level / value)*i && (int)R < (level / value)*(i + 1))
					tmpR = xClip(level / value * i);
				if ((int)G >= (level / value)*i && (int)G < (level / value)*(i + 1))
					tmpG = xClip(level / value * i);
				if ((int)B >= (level / value)*i && (int)B < (level / value)*(i + 1))
					tmpB = xClip(level / value * i);
			}

			setPixel(x, y, tmpR, tmpG, tmpB);
		}
	}
}

void ImageProc::gammaCorrection() {
	int x, y, i;
	byte R, G, B;
	double *LUT = new double[256];
	double gamma = 0.9;

	for (i = 0; i < 256; i++)
		LUT[i] = pow((double)i, 1.0 / gamma);

	for (y = 0; y<getHeight(); y++)
		for (x = 0; x < getWidth(); x++) {
			getPixel(x, y, R, G, B);
			setPixel(x, y, xClip(LUT[(int)R]), xClip(LUT[(int)G]), xClip(LUT[(int)B]));
		}

	delete[] LUT;
}

void ImageProc::contrastStretch() {
	int lowR, lowG, lowB, highR, highG, highB;
	byte R, G, B;
	byte *LUTR = new byte[256];
	byte *LUTG = new byte[256];
	byte *LUTB = new byte[256];
	int *histoR = new int[256];
	int *histoG = new int[256];
	int *histoB = new int[256];
	int pixcount = getHeight()*getWidth();
	int lowFactor = 10, highFactor = 10;


	for (int i = 0; i < 256; i++)
		histoR[i] = histoG[i] = histoB[i] = 0;

	for (int y = 0; y < getHeight(); y++)
		for (int x = 0; x < getWidth(); x++) {
			getPixel(x, y, R, G, B);
			histoR[(int)R]++;
			histoG[(int)G]++;
			histoB[(int)B]++;
		}

	unsigned int sumR = 0, sumG = 0, sumB = 0;
	bool flagR = 1, flagG = 1, flagB = 1;

	for (int i = 0; i < 256; i++) {
		if (!flagR && !flagG && !flagB)
			break;
		sumR += histoR[i];
		sumG += histoG[i];
		sumB += histoB[i];

		if (((sumR*100.0) / pixcount >= lowFactor) && flagR) {
			lowR = i;
			flagR = 0;
		}
		if (((sumG*100.0) / pixcount >= lowFactor) && flagG) {
			lowG = i;
			flagG = 0;
		}
		if (((sumB*100.0) / pixcount >= lowFactor) && flagB) {
			lowB = i;
			flagB = 0;
		}
	}

	flagR = flagG = flagB = 1;

	for (int i = 255; i >= 0; i--) {
		sumR += histoR[i];
		sumG += histoG[i];
		sumB += histoB[i];

		if (((sumR*100.0) / pixcount >= highFactor) && flagR) {
			highR = i;
			flagR = 0;
		}
		if (((sumG*100.0) / pixcount >= highFactor) && flagG) {
			highG = i;
			flagG = 0;
		}
		if (((sumB*100.0) / pixcount >= highFactor) && flagB) {
			highB = i;
			flagB = 0;
		}
	}

	for (int i = 0; i < 256; i++) {
		if (i < lowR)
			LUTR[i] = xClip(0);
		else if (i > highR)
			LUTR[i] = xClip(255);
		else
			LUTR[i] = xClip((i - lowR) / (double)(highR - lowR)*255.0);
		if (i < lowG)
			LUTG[i] = xClip(0);
		else if (i > highG)
			LUTG[i] = xClip(255);
		else
			LUTG[i] = xClip((i - lowG) / (double)(highG - lowG)*255.0);
		if (i < lowB)
			LUTB[i] = xClip(0);
		else if (i > highB)
			LUTB[i] = xClip(255);
		else
			LUTB[i] = xClip((i - lowB) / (double)(highB - lowB)*255.0);
	}

	for (int y = 0; y < getHeight(); y++) {
		for (int x = 0; x < getWidth(); x++) {
			getPixel(x, y, R, G, B);
			setPixel(x, y, LUTR[(int)R], LUTG[(int)G], LUTB[(int)B]);
		}
	}

	delete[] histoR;
	delete[] histoG;
	delete[] histoB;
	delete[] LUTR;
	delete[] LUTG;
	delete[] LUTB;
}

void ImageProc::histoEqual() {
	int i, x, y;
	int mWidth = getWidth(), mHeight = getHeight();
	byte R, G, B;
	byte *LUTR = new byte[256];
	byte *LUTG = new byte[256];
	byte *LUTB = new byte[256];
	int *histoR = new int[256];
	int *histoG = new int[256];
	int *histoB = new int[256];
	int pixcount = mWidth * mHeight;
	unsigned int sumR = 0, sumG = 0, sumB = 0;

	for (i = 0; i < 256; i++)
		histoR[i] = histoG[i] = histoB[i] = 0;

	for (y = 0; y < mHeight; y++)
		for (x = 0; x < mWidth; x++) {
			getPixel(x, y, R, G, B);
			histoR[(int)R]++;
			histoG[(int)G]++;
			histoB[(int)B]++;
		}

	for (i = 0; i < 256; i++) {
		sumR += histoR[i];
		sumG += histoG[i];
		sumB += histoB[i];

		LUTR[i] = xClip(((double)sumR / (double)pixcount * 255.0) + 0.5);
		LUTG[i] = xClip(((double)sumG / (double)pixcount * 255.0) + 0.5);
		LUTB[i] = xClip(((double)sumB / (double)pixcount * 255.0) + 0.5);
	}

	for (y = 0; y < mHeight; y++) {
		for (x = 0; x < mWidth; x++) {
			getPixel(x, y, R, G, B);
			setPixel(x, y, LUTR[(int)R], LUTG[(int)G], LUTB[(int)B]);
		}
	}

	delete[] histoR;
	delete[] histoG;
	delete[] histoB;
	delete[] LUTR;
	delete[] LUTG;
	delete[] LUTB;
}

byte *ImageProc::maskProcess(double mask[3][3]) {
	int x, y;
	int mWidth = getWidth(), mHeight = getHeight();
	double sumR, sumG, sumB;
	byte R, G, B;
	byte *temp = new byte[(mHeight + 2)*(mWidth + 2) * 3];
	byte *newRGB = new byte[mWidth*mHeight * 3];

	for (y = 0; y < mHeight; y++) {
		for (x = 0; x < mWidth; x++) {
			getPixel(x, y, R, G, B);

			temp[(y + 1) * mWidth * 3 + (x + 1) * 3 + 0] = R;
			temp[(y + 1) * mWidth * 3 + (x + 1) * 3 + 1] = G;
			temp[(y + 1) * mWidth * 3 + (x + 1) * 3 + 2] = B;
		}
	}

	for (y = 0; y < mHeight; y++) {
		for (x = 0; x < mWidth; x++) {
			sumR = 0.0;
			sumG = 0.0;
			sumB = 0.0;
			for (int m = 0; m < 3; m++) {
				for (int n = 0; n < 3; n++) {
					sumR += mask[m][n] * temp[(y + m) * mWidth * 3 + (x + n) * 3 + 0];
					sumG += mask[m][n] * temp[(y + m) * mWidth * 3 + (x + n) * 3 + 1];
					sumB += mask[m][n] * temp[(y + m) * mWidth * 3 + (x + n) * 3 + 2];
				}
			}
			newRGB[y * mWidth * 3 + x * 3 + 0] = xClip(sumR);
			newRGB[y * mWidth * 3 + x * 3 + 1] = xClip(sumG);
			newRGB[y * mWidth * 3 + x * 3 + 2] = xClip(sumB);
		}
	}

	delete[] temp;

	return newRGB;
}

void ImageProc::mirroring() {
	int x, y;
	int mWidth = getWidth(), mHeight = getHeight();
	byte *newRGB = new byte[m_iWidth*m_iHeight * 3];
	byte R, G, B;

	for (y = 0; y < mHeight; y++) {
		for (x = 0; x < mWidth; x++) {
			getPixel(x, y, R, G, B);
			newRGB[y * mWidth * 3 + (mWidth - x - 1) * 3 + 0] = R;
			newRGB[y * mWidth * 3 + (mWidth - x - 1) * 3 + 1] = G;
			newRGB[y * mWidth * 3 + (mWidth - x - 1) * 3 + 2] = B;
		}
	}

	setRGB(newRGB);
}

void ImageProc::embossing() {
	int x, y;
	int mWidth = getWidth(), mHeight = getHeight();
	double mask[3][3] = { { -1., 0., 0. }, { 0., 0., 0. }, { 0., 0., 1. } };
	byte *newRGB;
	byte R, G, B, tmpR, tmpG, tmpB;

	newRGB = maskProcess(mask);
	setRGB(newRGB);

	for (y = 0; y<mHeight; y++) {
		for (x = 0; x < mWidth; x++) {
			getPixel(x, y, R, G, B);
			tmpR = xClip(R + 128.0);
			tmpG = xClip(G + 128.0);
			tmpB = xClip(B + 128.0);
			setPixel(x, y, tmpR, tmpG, tmpB);
		}
	}
}

void ImageProc::bluring() {
	double mask[3][3] = { { 1. / 9., 1. / 9., 1. / 9. }, { 1. / 9., 1. / 9., 1. / 9. }, { 1. / 9., 1. / 9., 1. / 9. } };
	byte *newRGB;

	newRGB = maskProcess(mask);

	setRGB(newRGB);
}

void ImageProc::sharpening() {
	double mask[3][3] = { { 0., -1., 0. }, { -1., 5., -1. }, { 0., -1., 0. } };
	byte *newRGB;

	newRGB = maskProcess(mask);

	setRGB(newRGB);
}

void ImageProc::noise() {
	int tmpX, tmpY;
	int mWidth = getWidth(), mHeight = getHeight();

	srand(time(NULL));

	for (int i = 0; i < 50; i++) {
		tmpX = rand() % (mWidth - 1);
		tmpY = rand() % (mHeight - 1);

		setPixel(tmpX, tmpY, xClip(0.0), xClip(0.0), xClip(0.0));
		setPixel(tmpX + 1, tmpY, xClip(0.0), xClip(0.0), xClip(0.0));
		setPixel(tmpX, tmpY + 1, xClip(0.0), xClip(0.0), xClip(0.0));
		setPixel(tmpX + 1, tmpY + 1, xClip(0.0), xClip(0.0), xClip(0.0));
	}
}

void ImageProc::median() {
	int x, y;
	int mWidth = getWidth(), mHeight = getHeight();
	byte *newRGB = new byte[mWidth*mHeight * 3];
	byte *temp = new byte[(mWidth + 2)*(mHeight + 2) * 3];
	byte R, G, B;
	byte maskR[9], maskG[9], maskB[9];

	addNoise();

	for (y = 0; y < mHeight; y++) {
		for (x = 0; x < mWidth; x++) {
			getPixel(x, y, R, G, B);

			temp[(y + 1) * mWidth * 3 + (x + 1) * 3 + 0] = R;
			temp[(y + 1) * mWidth * 3 + (x + 1) * 3 + 1] = G;
			temp[(y + 1) * mWidth * 3 + (x + 1) * 3 + 2] = B;
		}
	}

	for (y = 0; y < mHeight; y++) {
		for (x = 0; x < mWidth; x++) {
			for (int m = 0; m < 3; m++) {
				for (int n = 0; n < 3; n++) {
					maskR[m * 3 + n] = temp[(y + m) * mWidth * 3 + (x + n) * 3 + 0];
					maskG[m * 3 + n] = temp[(y + m) * mWidth * 3 + (x + n) * 3 + 1];
					maskB[m * 3 + n] = temp[(y + m) * mWidth * 3 + (x + n) * 3 + 2];
				}
			}

			byteSort(maskR, 9);
			byteSort(maskG, 9);
			byteSort(maskB, 9);
			newRGB[y * mWidth * 3 + x * 3 + 0] = xClip(maskR[4]);
			newRGB[y * mWidth * 3 + x * 3 + 1] = xClip(maskG[4]);
			newRGB[y * mWidth * 3 + x * 3 + 2] = xClip(maskB[4]);
		}
	}

	delete[] temp;
	setRGB(newRGB);
}

void ImageProc::gaussian() {
	double mask[3][3] = { { 1. / 16., 1. / 8., 1. / 16. }, { 1. / 8., 1. / 4., 1. / 8. }, { 1. / 16., 1. / 8., 1. / 16. } };
	byte *newRGB;

	newRGB = maskProcess(mask);

	setRGB(newRGB);
}

void ImageProc::kuwahara() {
	int dR[5][5], dG[5][5], dB[5][5];
	int x, y;
	byte R, G, B;
	byte *newRGB = new byte[m_iWidth*m_iHeight * 3];
	for (y = 0; y < m_iHeight; y++) {
		for (x = 0; x < m_iWidth; x++) {
			for (int i = -2; i < 3; i++) {
				for (int j = -2; j < 3; j++) {
					if (x + j < 0 || x + j>m_iWidth - 1 || y + i < 0 || y + i>m_iHeight - 1) {
						dR[i + 2][j + 2] = 0;
						dG[i + 2][j + 2] = 0;
						dB[i + 2][j + 2] = 0;
						continue;
					}
					getPixel(x + j, y + i, R, G, B);
					dR[i + 2][j + 2] = R;
					dG[i + 2][j + 2] = G;
					dB[i + 2][j + 2] = B;
				}
			}
			int meanR[4] = {}, meanG[4] = {}, meanB[4] = {};
			int vR[4] = {}, vG[4] = {}, vB[4] = {}, V[4];
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < 2; j++) {
					for (int k = 0; k < 3; k++) {
						for (int h = 0; h < 3; h++) {
							meanR[i * 2 + j] += dR[(i * 2) + k][(j * 2) + h];
							meanG[i * 2 + j] += dG[(i * 2) + k][(j * 2) + h];
							meanB[i * 2 + j] += dB[(i * 2) + k][(j * 2) + h];
						}
					}
					meanR[i * 2 + j] /= 9;
					meanG[i * 2 + j] /= 9;
					meanB[i * 2 + j] /= 9;
					for (int k = 0; k < 3; k++) {
						for (int h = 0; h < 3; h++) {
							vR[i * 2 + j] += pow(dR[(i * 2) + k][(j * 2) + h] - meanR[i * 2 + j], 2);
							vG[i * 2 + j] += pow(dG[(i * 2) + k][(j * 2) + h] - meanG[i * 2 + j], 2);
							vB[i * 2 + j] += pow(dB[(i * 2) + k][(j * 2) + h] - meanB[i * 2 + j], 2);
						}
					}
					vR[i * 2 + j] /= 8;
					vG[i * 2 + j] /= 8;
					vB[i * 2 + j] /= 8;
					V[i * 2 + j] = vR[i * 2 + j] + vG[i * 2 + j] + vB[i * 2 + j];
				}
			}
			int index = 0;
			for (int i = 0; i < 4; i++) {
				if (V[i] < V[index])
					index = i;
			}
			newRGB[(y * m_iWidth * 3 + x * 3) + 0] = meanR[index];
			newRGB[(y * m_iWidth * 3 + x * 3) + 1] = meanG[index];
			newRGB[(y * m_iWidth * 3 + x * 3) + 2] = meanB[index];
		}
	}

	setRGB(newRGB);
}

void ImageProc::rotation(double theta) {
	int x, y;
	int mWidth = getWidth(), mHeight = getHeight();
	double rad = M_PI / 180.0;
	int dx, dy;
	byte *newRGB = new byte[mWidth*mHeight * 3];
	byte R, G, B;
	double c = cos(theta*rad), s = sin(theta*rad);
	double x_center = (double)mWidth / 2.0, y_center = (double)mHeight / 2.0;

	for (int y = 0; y < mHeight; y++) {
		for (int x = 0; x < mWidth; x++) {
			//dx = (int)((y - y_center)*s + (x - x_center)*s + x_center);
			//dy = (int)((y - y_center)*c - (x - x_center)*s + y_center);
			dx = (int)(x_center + ((double)(mHeight - y) - y_center)*s + ((double)x - x_center)*c);
			dy = (int)(y_center + ((double)(mHeight - (mHeight - y)) - y_center)*c + ((double)x - x_center)*s);

			if (dx < 0 || dx >= mWidth || dy < 0 || dy >= mHeight) {
				R = xClip(0.0);
				G = xClip(0.0);
				B = xClip(0.0);
			}
			else {
				getPixel(dx, dy, R, G, B);
			}

			newRGB[y * m_iWidth * 3 + x * 3 + 0] = R;
			newRGB[y * m_iWidth * 3 + x * 3 + 1] = G;
			newRGB[y * m_iWidth * 3 + x * 3 + 2] = B;
		}
	}

	setRGB(newRGB);
}

void ImageProc::upScale() {
	int x, y, i_H, i_W;
	double rate = 2.0, r_H, r_W, s_H, s_W;
	int mWidth = getWidth(), mHeight = getHeight();
	int newWidth = (int)(mWidth*rate), newHeight = (int)(mHeight*rate);
	byte *newRGB = new byte[newWidth*newHeight * 3];
	byte tmpR[4], tmpG[4], tmpB[4];

	for (y = 0; y < newHeight; y++) {
		for (x = 0; x < newWidth; x++) {
			r_H = (double)(y / rate);
			r_W = (double)(x / rate);
			i_H = (int)floor(r_H);
			i_W = (int)floor(r_W);
			s_H = r_H - i_H;
			s_W = r_W - i_W;
			if (i_H < 0 || i_H >= (mHeight - 1) || i_W < 0 || i_W >= (mWidth - 1)) {
				newRGB[y * newWidth * 3 + x * 3 + 0] = xClip(255.0);
				newRGB[y * newWidth * 3 + x * 3 + 1] = xClip(255.0);
				newRGB[y * newWidth * 3 + x * 3 + 2] = xClip(255.0);
			}
			else {
				getPixel(i_W, i_H, tmpR[0], tmpG[0], tmpB[0]);
				getPixel(i_W + 1, i_H, tmpR[1], tmpG[1], tmpB[1]);
				getPixel(i_W + 1, i_H + 1, tmpR[2], tmpG[2], tmpB[2]);
				getPixel(i_W, i_H + 1, tmpR[3], tmpG[3], tmpB[3]);

				newRGB[y * newWidth * 3 + x * 3 + 0] = xClip(tmpR[0] * (1. - s_H)*(1. - s_W) + tmpR[1] * s_W*(1. - s_H) + tmpR[2] * s_W*s_H + tmpR[3] * (1. - s_W)*s_H);
				newRGB[y * newWidth * 3 + x * 3 + 1] = xClip(tmpG[0] * (1. - s_H)*(1. - s_W) + tmpG[1] * s_W*(1. - s_H) + tmpG[2] * s_W*s_H + tmpG[3] * (1. - s_W)*s_H);
				newRGB[y * newWidth * 3 + x * 3 + 2] = xClip(tmpB[0] * (1. - s_H)*(1. - s_W) + tmpB[1] * s_W*(1. - s_H) + tmpB[2] * s_W*s_H + tmpB[3] * (1. - s_W)*s_H);
			}
		}
	}

	setWidth(newWidth);
	setHeight(newHeight);
	setRGB(newRGB);
}

void ImageProc::downScale() {
	int x, y, m, n, rate = 2;
	int mWidth = getWidth(), mHeight = getHeight();
	int newWidth = (mWidth + 1) / 2, newHeight = (mHeight + 1) / 2;
	byte *temp = new byte[(mWidth + 1)*(mHeight + 1) * 3];
	byte *newRGB = new byte[newWidth*newHeight * 3];
	byte R, G, B;
	byte maskR[4], maskG[4], maskB[4];
	int count;

	for (y = 0; y < mHeight; y++) {
		for (x = 0; x < mWidth; x++) {
			getPixel(x, y, R, G, B);
			temp[y * mWidth * 3 + x * 3 + 0] = R;
			temp[y * mWidth * 3 + x * 3 + 1] = G;
			temp[y * mWidth * 3 + x * 3 + 2] = B;
		}
	}

	for (y = 0; y < mHeight - 1; y += rate) {
		for (x = 0; x < mWidth - 1; x += rate) {
			for (m = 0; m < rate; m++) {
				for (n = 0; n < rate; n++) {
					getPixel(x + n, y + m, maskR[m * 2 + n], maskG[m * rate + n], maskB[m * rate + n]);
					maskR[m*rate + n] = temp[(y + m) * mWidth * 3 + (x + n) * 3 + 0];
					maskG[m*rate + n] = temp[(y + m) * mWidth * 3 + (x + n) * 3 + 1];
					maskB[m*rate + n] = temp[(y + m) * mWidth * 3 + (x + n) * 3 + 2];
				}
			}

			byteSort(maskR, rate*rate);
			byteSort(maskG, rate*rate);
			byteSort(maskB, rate*rate);

			newRGB[(int)(y / 2) * newWidth * 3 + (int)(x / 2) * 3 + 0] = maskR[(int)(rate*rate / 2)];
			newRGB[(int)(y / 2) * newWidth * 3 + (int)(x / 2) * 3 + 1] = maskG[(int)(rate*rate / 2)];
			newRGB[(int)(y / 2) * newWidth * 3 + (int)(x / 2) * 3 + 2] = maskB[(int)(rate*rate / 2)];
		}
	}

	delete[] temp;

	setWidth(newWidth);
	setHeight(newHeight);
	setRGB(newRGB);
}

void ImageProc::kmeans() {
	const int K = 8;
	int loop = 1;
	int **cluster;
	int preCluster;
	double sum[K][3];
	double center[K][3];
	double min = 9999999999.9;
	int minIndex;
	int number[K];
	double dist;
	byte R, G, B;

	srand(time(NULL));

	cluster = (int **)malloc(m_iHeight * sizeof(int *));

	for (int i = 0; i < m_iHeight; i++) {
		cluster[i] = (int *)malloc(m_iWidth * sizeof(int));
		for (int j = 0; j < m_iWidth; j++) {
			cluster[i][j] = K + 1;
		}
	}

	for (int k = 0; k < K; k++) {
		int x, y;

		x = rand() % m_iWidth;
		y = rand() % m_iHeight;
		getPixel(x, y, R, G, B);
		center[k][0] = (double)R;
		center[k][1] = (double)G;
		center[k][2] = (double)B;
	}

	while (loop == 1) {
		loop = 0;

		for (int y = 0; y < m_iHeight; y++) {
			for (int x = 0; x < m_iWidth; x++) {
				preCluster = cluster[y][x];
				getPixel(x, y, R, G, B);
				min = 9999999999.9;
				for (int k = 0; k < K; k++) {
					dist = sqrt(pow((double)R - center[k][0], 2.0) + pow((double)G - center[k][1], 2.0) + pow((double)B - center[k][2], 2.0));

					if (dist < min) {
						min = dist;
						minIndex = k;
					}
				}
				cluster[y][x] = minIndex;
				if (cluster[y][x] != preCluster) loop = 1;
			}
		}

		for (int k = 0; k < K; k++) {
			sum[k][0] = 0.0; sum[k][1] = 0.0; sum[k][2] = 0.0;
			number[k] = 0.0;
		}

		for (int y = 0; y < m_iHeight; y++) {
			for (int x = 0; x < m_iWidth; x++) {
				getPixel(x, y, R, G, B);
				sum[cluster[y][x]][0] += (double)R;
				sum[cluster[y][x]][1] += (double)G;
				sum[cluster[y][x]][2] += (double)B;
				number[cluster[y][x]]++;
			}
		}

		for (int k = 0; k < K; k++) {
			center[k][0] = sum[k][0] / number[k];
			center[k][1] = sum[k][1] / number[k];
			center[k][2] = sum[k][2] / number[k];
		}
	}

	for (int i = 0; i < m_iHeight; i++) {
		for (int j = 0; j < m_iWidth; j++) {
			setPixel(j, i, (byte)center[cluster[i][j]][0], (byte)center[cluster[i][j]][1], (byte)center[cluster[i][j]][2]);
		}
	}

	for (int i = 0; i < m_iHeight; i++) {
		free(cluster[i]);
	}

	free(cluster);
}

double ImageProc::Min(double a, double b) {
	if (a >= b)
		return b;
	else
		return a;
}

void ImageProc::HSItoRGB() {
	byte R, G, B;
	double H, S, I;
	double RR, GG, BB;
	double angle1, angle2;

	for (int i = 0; i < m_iWidth; i++) {
		for (int j = 0; j < m_iHeight; j++) {
			getPixel(i, j, R, G, B);

			H = (double)((Sol_H(R, G, B) / 255.0)*360.0);
			S = (double)(Sol_S(R, G, B) / 255.0);
			I = (double)(Sol_I(R, G, B) / 255.0);

			if (I <= 0.0) {
				setPixel(i, j, (byte)0.0, (byte)0.0, (byte)0.0);
				continue;
			}

			if (I >= 1.0) {
				setPixel(i, j, (byte)255.0, (byte)255.0, (byte)255.0);
				continue;
			}

			if (H < 0.0)
				H += 360;

			if (H <= 120.0) {
				angle1 = H * 0.017453293;
				angle2 = (60 - H)*0.017453293;
				BB = (1.0 - S) / 3.0;
				RR = (1.0 + (S*cos(angle1) / cos(angle2))) / 3.0;
				GG = 1.0 - RR - BB;
			}
			else if (120.0 < H&&H <= 240.0) {
				H = H - 120.0;
				angle1 = H * 0.017453293;
				angle2 = (60 - H)*0.017453293;
				RR = (1.0 - S) / 3.0;
				GG = (1.0 + (S*cos(angle1) / cos(angle2))) / 3.0;
				BB = 1.0 - RR - GG;
			}
			else {
				H = H - 240.0;
				angle1 = H * 0.017453293;
				angle2 = (60 - H)*0.017453293;
				GG = (1.0 - S) / 3.0;
				BB = (1.0 + (S*cos(angle1) / cos(angle2))) / 3.0;
				RR = 1.0 - GG - BB;
			}

			RR *= 255.0*3.0*I;
			GG *= 255.0*3.0*I;
			BB *= 255.0*3.0*I;

			if (RR > 255.0)
				RR = 255.0;
			if (GG > 255.0)
				GG = 255.0;
			if (BB > 255.0)
				BB = 255.0;

			setPixel(i, j, unsigned char(RR), unsigned char(GG), unsigned char(BB));
		}
	}
}

unsigned char ImageProc::Sol_H(unsigned char R, unsigned char G, unsigned char B) {
	double angle;
	double RR, GG, BB;

	if (R == G && G == B)
		return 0;

	RR = R / 255.0;
	GG = G / 255.0;
	BB = B / 255.0;

	angle = (RR - 0.5*GG - 0.5*BB) / (float)sqrt((RR - GG)*(RR - GG) + (RR - BB)*(GG - BB));
	angle = acos(angle);
	angle *= 57.29577951;

	if (B > G)
		angle = 360.0 - angle;

	return (unsigned char)((angle / 360.0)*255.0);
}

unsigned char ImageProc::Sol_S(unsigned char R, unsigned char G, unsigned char B) {
	double minc;
	double RR, GG, BB;

	RR = R / 255.0;
	GG = G / 255.0;
	BB = B / 255.0;

	if (RR + GG + BB == 0)
		return 0;

	minc = Min(RR, GG);
	minc = Min(minc, BB);

	return (unsigned char)((1.0 - (3.0 / (RR + GG + BB))*minc)*255.0);
}

unsigned char ImageProc::Sol_I(unsigned char R, unsigned char G, unsigned char B) {
	return (unsigned char)((R + G + B) / 3.0);
}
