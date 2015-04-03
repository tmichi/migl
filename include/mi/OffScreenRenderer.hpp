#ifndef MI_RENDER_OFFSCREEN_RENDERER_HPP
#define MI_RENDER_OFFSCREEN_RENDERER_HPP 1
#include <vector>

typedef struct GLFWwindow GLFWwindow;
namespace mi
{
        class OffScreenRenderer
        {
        protected:
                bool _isOK;
                int _width;
                int _height;
                GLFWwindow* _window;
        public:
                OffScreenRenderer ( const int width = 128, const int height = 128 );
		~OffScreenRenderer ( void );
                bool init ( const int width, const int height );

                int  getWidth( void ) const;
                int  getHeight( void ) const;
                void swapBuffers( void );

                void getImage ( std::vector<unsigned char>& image );
                void getDepth ( std::vector<float>& depth );
        };
}
#endif// MI_RENDER_OFFSCREEN_RENDERER_HPP
