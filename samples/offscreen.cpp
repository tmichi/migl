#include <fstream>
#include <mi/OffScreenRenderer.hpp>
#include <mi/glconf.hpp>
#include "BmpImage.hpp"

int main()
{
        mi::OffScreenRenderer renderer( 640, 480 );
        ::glEnable( GL_DEPTH_TEST );
        ::glClearColor( 1, 0,0,1 );
        ::glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        renderer.swapBuffers();
        renderer.swapBuffers();

	std::vector<unsigned char> image;
        renderer.getImage( image );
	return write_bmp(image, 640, 480, "hoge.bmp");
}
