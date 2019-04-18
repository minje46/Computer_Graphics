// ------------------------------------------------------------------------------------------------
// Image class Header file
// ------------------------------------------------------------------------------------------------


#include "stdafx.h"

#ifndef __IMAGE_H
#define __IMAGE_H

// ------------------------------------------------------------------------------------------------
// BMP file header
// ------------------------------------------------------------------------------------------------

#pragma pack(push)
#pragma pack(1)
typedef struct _bmphdr
{
	char id[2];										// bmp id = 'B''M'
	int  size;                    // total size
	char reserved1[2];
	char reserved2[2];
	int  offset;                  // starting offset

	unsigned int   header_sz;
	int            width;
	int            height;
	unsigned short nplanes;
	unsigned short bitspp;
	unsigned int   compress_type;
	unsigned int   bmp_bytesz;
	int            hres;
	int            vres;
	unsigned int   ncolors;
	unsigned int   nimpcolors;
} BMPHdr;
#pragma pack(pop)

typedef unsigned char byte;

// ------------------------------------------------------------------------------------------------
// Image class
// ------------------------------------------------------------------------------------------------

class Image
{
protected:
	byte * m_pRGB;
	int   m_iWidth;
	int   m_iHeight;
	int   m_level;
public:
	// constructor / destructor
	Image() { m_pRGB = 0; m_iWidth = m_iHeight = m_level = 0; }
	~Image() { if (m_pRGB) delete[] m_pRGB; }

	// info functions
	int   getWidth() { return m_iWidth; }
	int   getHeight() { return m_iHeight; }
	byte* getRGB() { return m_pRGB; }

	// get/set functions
	int   getAddr(int x, int y)
	{
		return y * m_iWidth * 3 + x * 3;
	}
	void getPixel(int x, int y, byte& R, byte& G, byte& B);
	void setPixel(int x, int y, byte  R, byte  G, byte  B);
	void setRGB(byte * RGB) {
		byte* temp;
		temp = m_pRGB;
		m_pRGB = RGB;
		delete[] temp;
	}

	void setWidth(int width) {
		m_iWidth = width;
	}

	void setHeight(int height) {
		m_iHeight = height;
	}

	// load from BMP
	int loadFromBMP(const char* fname);
};

#endif