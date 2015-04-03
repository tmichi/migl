#include <mi/OpenGlUtility.hpp>
#include <mi/glconf.hpp>
namespace mi
{
	void 
	OpenGlUtility::lookAt( const  Eigen::Vector3d& eye, const Eigen::Vector3d& center, Eigen::Vector3d& up ) {
		const Eigen::Vector3d forward = ( center - eye ).normalized();
		const Eigen::Vector3d side = forward.cross( up ).normalized();
		const Eigen::Vector3d upv  = side.cross( forward ).normalized();
		double m[16];
		OpenGlUtility::setZero( m );
		for( int i = 0  ; i < 3 ; ++i ) {
			m[i * 4 + 0] = side[i];
			m[i * 4 + 1] = upv[i];
			m[i * 4 + 2] = -forward[i];
		}
		m[3 * 4 + 3] = 1.0;
		::glMultMatrixd( m );
		::glTranslated( -eye.x(), -eye.y(), -eye.z() );
	}
	
	void 	
	OpenGlUtility::perspective ( const double fov, const double aspect,const double znear, const double zfar ) {
		double m[16];
		OpenGlUtility::setZero( m );
		double f = 1.0 / std::tan ( 0.5 * fov * M_PI / 180.0 );
		m[0] = f * 1.0 /aspect;
		m[1 * 4 + 1] = f;
		
		m[2 * 4 + 2] = ( zfar + znear ) * 1.0 / ( znear - zfar ) ;
		m[2 * 4 + 3] = -1.0;
		m[3 * 4 + 2] =  2.0 * zfar * znear / ( znear - zfar ) ;
		::glMultMatrixd( m );
	}
	void 
	OpenGlUtility::ortho ( const double left, const double  right, const double  bottom, const double  top, const double znear, const double zfar ) {
		::glOrtho( left, right, bottom, top, znear, zfar );
		return;
	}
	
	void 
	OpenGlUtility::ortho2d ( const double  left, const double  right, const double  bottom, const double  top ) {
		OpenGlUtility::ortho( left, right, bottom, top, -1, 1 );
		return;
	}
	
	
	void 
	OpenGlUtility::setZero ( double* m ) {
		for( int i = 0 ; i < 16 ; ++i ) m[i] = 0;
	}
}

