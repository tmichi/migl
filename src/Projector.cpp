/**
 * @file Projector.cpp
 * @author Takashi Michikawa <michikawa@acm.org>
 */
#include "../include/mi/Projector.hpp"

namespace mi
{
	class Projector::Impl : public NonCopyable {
	public:
		Impl (void ) : NonCopyable () {
			return;
		}
		
		~Impl ( void ) {
			return;
		}
		
		Eigen::Matrix4d& matrix ( void ) { 
			return this->_matrix;
		}
		
		Eigen::Matrix4d& inv_matrix( void ) {
			return this->_inv_matrix;
		}
		
		std::array<int, 4>& viewport( void ) {
			return  this->_viewport;
		}
	private:
		Eigen::Matrix4d _matrix;
		Eigen::Matrix4d _inv_matrix;
		std::array<int, 4>  _viewport;        
	};

	Projector::Projector ( double modelview[16], double projection[16], int viewport[4] ) : NonCopyable (), _impl ( new Impl() ) {
		Eigen::Matrix4d&  matrix = this->_impl->matrix();
		Eigen::Matrix4d&  inv_matrix = this->_impl->inv_matrix();
		
		
		matrix =  Eigen::Map<Eigen::Matrix4d>( projection ) * Eigen::Map<Eigen::Matrix4d>( modelview );
		inv_matrix = matrix.inverse();
		for ( int i = 0 ; i < 4 ; ++i ) {
			this->_impl->viewport()[i] = viewport[i];
		}
	}
	
	Projector::~Projector() {
		return;
	}
         
	Eigen::Vector3d 
	Projector::project ( const Eigen::Vector3d& p, int *error ) {
		Eigen::Vector3d w;
		*error = this->project( p.x(), p.y(), p.z(), w.x(), w.y(), w.z() );
		return w;
	}
	
	int
	Projector::project ( const double x, const double y, const double z, double &wx, double &wy, double &wz ) {
		Eigen::Matrix4d&  matrix = this->_impl->matrix();
		std::array<int, 4>& viewport = this->_impl->viewport();
		
		Eigen::Vector4d p = matrix * Eigen::Vector4d( x, y, z, 1 );
		if ( p.w() == 0 ) return 0;
		p *= 1.0 / p.w();
		
		wx = viewport[0] + ( 1 + p.x() ) * viewport[2] * 0.5;
		wy = viewport[1] + ( 1 + p.y() ) * viewport[3] * 0.5;
		wz = ( 1.0 + p.z() ) * 0.5;
		
		return 1;
	}
	
	Eigen::Vector3d 
	Projector::unproject ( const Eigen::Vector3d& wp, int *error) {
		Eigen::Vector3d p;
		*error = this->unproject( wp.x(), wp.y(), wp.z(), p.x(), p.y(), p.z() );
		return p;
	}
	
	int
	Projector::unproject ( const double wx, const double wy, const double wz, double &x, double &y, double &z ) {
		Eigen::Matrix4d&  inv_matrix = this->_impl->inv_matrix();
		std::array<int, 4>& viewport = this->_impl->viewport();
		Eigen::Vector4d p;
		p.x() = ( wx - viewport[0] ) * 2 / viewport[2] - 1.0;
		p.y() = ( wy - viewport[1] ) * 2 / viewport[3] - 1.0;
		p.z() = 2.0 * wz  - 1.0;
		p.w() = 1.0;
		
		const Eigen::Vector4d p1 = inv_matrix * p;
		if ( p1.w() == 0.0 ) return 0;
		x = p1.x() / p1.w();
		y = p1.y() / p1.w();
		z = p1.z() / p1.w();
		return 1;
	}
}

