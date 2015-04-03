#include <mi/OffScreenRenderer.hpp>
#include <mi/glconf.hpp>
#include <iostream>
#include <GLFW/glfw3.h>

namespace mi
{
	OffScreenRenderer::OffScreenRenderer ( const int width, const int height ) {
		this->_isOK = this->init ( width,height );
		return;
	}
	
	OffScreenRenderer::~OffScreenRenderer ( void ) {
		return;
	}
	
	bool 
	OffScreenRenderer::init ( const int width, const int height ) {
		this->_width = width;
		this->_height = height;
		
		if ( ::glfwInit() == GL_FALSE )  return false;
		::glfwWindowHint( GLFW_VISIBLE, 0 );
		this->_window = ::glfwCreateWindow( width, height, "tmp", NULL, NULL );
		::glfwMakeContextCurrent( this->_window );
		if ( !this->_window ) {
			std::cerr<<"window cannot be created."<<std::endl;
			return false;
		}
		return true;
	}
	
	int 
	OffScreenRenderer::getWidth( void ) const {
		return this->_width;
	}
	
	int 
	OffScreenRenderer::getHeight( void ) const {
		return this->_height;
	}
	
	void 
	OffScreenRenderer::swapBuffers( void ) {
		::glfwSwapBuffers( this->_window );
	}
	
	void 
	OffScreenRenderer::getImage ( std::vector<unsigned char>& image) {
		const int &w = this->getWidth();
		const int &h = this->getHeight();
		image.assign ( w * h * 3, 0x00);
		unsigned char *buf = new unsigned char [ w * h * 4 ];
		::glReadPixels ( 0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, buf );
		for ( int y = 0 ; y < h ; ++y ) {
			for ( int x = 0 ; x < w ; ++x ) {
				const int idxBuf = 4 * ( y * w + x );
				const int idxImg = 3 * ( y * w + x );
				for ( int i = 0 ; i < 3 ; ++i ) {
					image[idxImg+i] = buf[idxBuf+i];
				}
			}
		}
		delete[] buf;
		return;
	}
	
	void 
	OffScreenRenderer::getDepth ( std::vector<float>& depth ) {
		const int &w = this->getWidth();
		const int &h = this->getHeight();
		const int npixels = w * h;
		
		depth.assign( npixels , 0);
		float *buf = new float [ npixels ];
		::glReadPixels ( 0, 0, w, h, GL_DEPTH_COMPONENT, GL_FLOAT, buf );
		for ( int i = 0 ; i < npixels ; ++i ) {
			depth[i] = buf[i];
		}
		delete[] buf;
		return;
	}
}

