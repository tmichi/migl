/**
 * @file OffScreenRenderer.hpp
 * @brief Class declaration of mi::OffScreenRenderer
 * @author Takashi Michikawa <michikawa@acm.org>
 */
#ifndef MI_RENDER_OFFSCREEN_RENDERER_HPP
#define MI_RENDER_OFFSCREEN_RENDERER_HPP 1
#include <vector>
#include <memory>
namespace mi
{
        class OffScreenRenderer
        {
        public:
		/**
		 * @brief Constructor
		 * @param [in] width Width of the buffer.
		 * @param [in] height Height of the buffer.
		 */
                OffScreenRenderer ( const int width = 128, const int height = 128 );

		/**
		 * @brief Destructor
		 */
		~OffScreenRenderer ( void );

		/**
		 * @brief Initilaize the buffer. 
		 * @param [in] width Width of the buffer.
		 * @param [in] height Height of the buffer.
		 * @retval true Success
		 * @retval false Failure. The buffer could not be created. 
		 */
                bool init ( const int width, const int height );

		/**
		 * @brief Get width of the buffer
		 * @return Width of the buffer
		 */
                int  getWidth( void ) const;

		/**
		 * @brief Get height of the buffer
		 * @return Height of the buffer
		 */
                int  getHeight( void ) const;

		/**
		 * @brief Swap buffers. 
		 */
                void swapBuffers( void );

		/**
		 * @brief Get the color buffer 
		 * @param [out] image Pixel array
		 */
                void getImage ( std::vector<unsigned char>& image );
		/**
		 * @brief Get the depth buffer 
		 * @param [out] image Depth array
		 */
                void getDepth ( std::vector<float>& depth );

        private:
		class Impl;
		std::unique_ptr<Impl> _impl;
        };
}
#endif// MI_RENDER_OFFSCREEN_RENDERER_HPP
