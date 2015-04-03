#ifndef MI_BMP_H
#define MI_BMP_H 1
#ifndef _WINGDI_
//http://msdn.microsoft.com/en-us/library/dd183374(VS.85).aspx
typedef struct BITMAPFILEHEADER_ {
        unsigned short bfType;
        unsigned int	 bfSize;
        unsigned short bfReserved1;
        unsigned short bfReserved2;
        unsigned int	 bfOffBits;
} BITMAPFILEHEADER;
//http://msdn.microsoft.com/en-us/library/dd183376(VS.85).aspx
typedef struct BITMAPINFOHEADER_ {
        unsigned int biSize;
        int  biWidth;
        int  biHeight;
        unsigned short  biPlanes;
        unsigned short biBitCount;
        unsigned int biCompression;
        unsigned int biSizeImage;
        int  biXPelsPerMeter;
        int  biYPelsPerMeter;
        unsigned int biClrUsed;
        unsigned int biClrImportant;
} BITMAPINFOHEADER;
#endif //_WINGDI_
#endif// MI_BMP_H
