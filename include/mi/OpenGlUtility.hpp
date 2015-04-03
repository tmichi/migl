#ifndef MI_OPEN_GL_UTILITY_HPP
#define MI_OPEN_GL_UTILITY_HPP 1
#include <Eigen/Dense>
namespace mi
{
        class OpenGlUtility
        {
        public:
                static void lookAt( const  Eigen::Vector3d& eye, const Eigen::Vector3d& center, Eigen::Vector3d& up );
                static void perspective ( const double fov, const double aspect,const double znear, const double zfar );
                static void ortho ( const double left, const double  right, const double  bottom, const double  top, const double znear, const double zfar );
                static void ortho2d ( const double  left, const double  right, const double  bottom, const double  top );
        private:
                static void setZero ( double* m );
        };
}
#endif//MI_OPEN_GL_UTILITY_HPP
