#include <mi/OffScreenRenderer.hpp>
#include <mi/glconf.hpp>
#include <GLFW/glfw3.h>

namespace mi
{
	class OffScreenRenderer::Impl {
	public:
		Impl ( void ) : _isOk (true), _width (128), _height(128), _window (NULL) {
			return;
		}

		~Impl ( void ) {
			return;
		}

		void setNg( void ) {
			this->_isOk = false;
			return;
		}
		
		bool isOk ( void ) {
			return this->_isOk;
		}

		void setSize ( const int width, const int height ) {
			this->_width  = width;
			this->_height = height;
			return;
		}

		int getWidth ( void ) const {
			return this->_width;
		}

		int getHeight ( void ) const {
			return this->_height;
		}

		void getWindow ( GLFWwindow* window ) {
			window = this->_window;
		}
		
	private:
                bool _isOk;
                int _width;
                int _height;
                GLFWwindow* _window;
	};

        OffScreenRenderer::OffScreenRenderer ( const int width, const int height ) : _impl ( new Impl())
        {
                if ( this->init ( width,height ) ) this->_impl->setNg();
                return;
        }

        OffScreenRenderer::~OffScreenRenderer ( void )
        {
		if ( this->_impl != NULL ) {
			delete this->_impl;
			this->_impl = NULL;
		}
                return;
        }

        bool
        OffScreenRenderer::init ( const int width, const int height )
        {
		GLFWwindow* window = NULL;
		this->_impl->getWindow(window);
		this->_impl->setSize( width, height); 
                if ( ::glfwInit() == GL_FALSE )  return false;
                ::glfwWindowHint( GLFW_VISIBLE, 0 );
		window = ::glfwCreateWindow( width, height, "tmp", NULL, NULL );
                ::glfwMakeContextCurrent( window );
                if ( !window ) return false;
                return true;
        }

        int
        OffScreenRenderer::getWidth( void ) const
        {
                return this->_impl->getWidth();
        }

        int
        OffScreenRenderer::getHeight( void ) const
        {
                return this->_impl->getHeight();
        }

        void
        OffScreenRenderer::swapBuffers( void )
        {
		GLFWwindow* window = NULL;
		this->_impl->getWindow(window);
                ::glfwSwapBuffers( window );
        }

        void
        OffScreenRenderer::getImage ( std::vector<unsigned char>& image )
        {
                const int &width = this->getWidth();
                const int &height = this->getHeight();
                const int npixels = width * height;
		
                image.assign ( npixels * 3 , 0x00 );
                unsigned char *buf = new unsigned char [ npixels * 4 ];

                ::glReadPixels ( 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, buf );

                for ( int y = 0 ; y < height ; ++y ) {
                        for ( int x = 0 ; x < width ; ++x ) {
				const int idx = y * width + x ;
                                const int idxBuf = 4 * idx; 
                                const int idxImg = 3 * idx;
                                for ( int i = 0 ; i < 3 ; ++i ) {
                                        image[idxImg+i] = buf[idxBuf+i];
                                }
                        }
                }
                delete[] buf;
                return;
        }

        void
        OffScreenRenderer::getDepth ( std::vector<float>& depth )
        {
                const int &width = this->getWidth();
                const int &height = this->getHeight();
                const int npixels = width * height;

                depth.assign( npixels , 0 );
                float *buf = new float [ npixels ];
                ::glReadPixels ( 0, 0, width, height, GL_DEPTH_COMPONENT, GL_FLOAT, buf );
                for ( int i = 0 ; i < npixels ; ++i ) {
                        depth[i] = buf[i];
                }
                delete[] buf;
                return;
        }
}

