#include "Bmp.hpp"
#include <string>
#include <vector>

bool write_header ( const int width, const int height, std::ofstream& fout) {
	BITMAPFILEHEADER fileheader;
	fileheader.bfType = 0x4D42;//'BM'
	int size = 54 + height * static_cast<int> ( ( width * 3 + 3 ) / 4 * 4 );
	fileheader.bfSize = static_cast<unsigned int> ( size );
	fileheader.bfReserved1 = 0;
	fileheader.bfReserved2 = 0;
	fileheader.bfOffBits = 54;
	fout.write ( ( char* ) ( &fileheader.bfType ), 2 );
	fout.write ( ( char* ) ( &fileheader.bfSize ), 4 );
	fout.write ( ( char* ) ( &fileheader.bfReserved1 ), 2 );
	fout.write ( ( char* ) ( &fileheader.bfReserved2 ), 2 );
	fout.write ( ( char* ) ( &fileheader.bfOffBits ), 4 );
	
	
	BITMAPINFOHEADER infoheader;
	infoheader.biSize	= 40;
	infoheader.biWidth	= width;
	infoheader.biHeight	= height;
	infoheader.biPlanes	= 1;
	infoheader.biBitCount	= 24;
	infoheader.biSizeImage	= width * height * 3;
	infoheader.biClrImportant = 0;
	infoheader.biClrUsed	= 0;
	infoheader.biCompression = 0;
	infoheader.biXPelsPerMeter = 0;
	infoheader.biYPelsPerMeter = 0;
	
	fout.write ( ( char* ) ( &infoheader.biSize ), 4 );
	fout.write ( ( char* ) ( &infoheader.biWidth ), 4 );
	fout.write ( ( char* ) ( &infoheader.biHeight ), 4 );
	fout.write ( ( char* ) ( &infoheader.biPlanes ), 2 );
	fout.write ( ( char* ) ( &infoheader.biBitCount ), 2 );
	fout.write ( ( char* ) ( &infoheader.biCompression ), 4 );
	fout.write ( ( char* ) ( &infoheader.biSizeImage ), 4 );
	fout.write ( ( char* ) ( &infoheader.biXPelsPerMeter ), 4 );
	fout.write ( ( char* ) ( &infoheader.biYPelsPerMeter ), 4 );
	fout.write ( ( char* ) ( &infoheader.biClrUsed ), 4 );
	fout.write ( ( char* ) ( &infoheader.biClrImportant ), 4 );
	return fout.good();
}

bool write_body ( std::vector<unsigned char>& image, const int width, const int height, std::ofstream &fout ) {
	const int bytePerLine = static_cast<int> ( ( width * 3 + 3 ) / 4 * 4 );
	std::vector<unsigned char> line ( bytePerLine, 0x00 );
	for ( int y = 0 ; y < height ; y++ ) {
		for ( int x = 0 ; x < width ; x++ ) {
			const int index = x + y * width;
			line[3*x+2] = image[index * 3 + 0];
			line[3*x+1] = image[index * 3 + 1];
			line[3*x+0] = image[index * 3 + 2];
		}
		fout.write ( ( char* ) & ( line[0] ), bytePerLine );
	}
	return fout.good();
}
int write_bmp ( std::vector<unsigned char>& image, const int w, const int h, const std::string& name ) {
	std::ofstream fout(name.c_str(), std::ios::binary);
	if ( !fout ) return -1;
	if ( !write_header (w, h, fout) ) return -1;
	if ( !write_body ( image, w, h, fout) ) return -1;
	return 0;
}

