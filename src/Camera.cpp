/**
 * @file Camera.cpp
 * @author Takashi Michikawa <michikawa@acm.org>
 */
#include "../include/mi/Camera.hpp"
namespace mi {
	class Camera::Impl : public NonCopyable {
	public:
		Impl ( void ) : NonCopyable(), rotation_ ( Eigen::Quaterniond( 1,0,0,0 ) ), center_( Eigen::Vector3d() ), dist_( 0 ), radius_( 100 ), fov_( 40 ) {
			return;
		}
		
		~Impl ( void ) {
			return;
		}
		
		Eigen::Quaterniond& rotation( void ) {
			return this->rotation_;
		}
		
		Eigen::Vector3d& center ( void ) {
			return this->center_;
		}
		
		double& dist ( void ) {
			return this->dist_;
		}
		
		double& radius ( void ) {
			return this->radius_;
		}
		
		double fov ( void ) {
			return this->fov_;
		}
		
		void
		project_to_sphere( const double& radius, Eigen::Vector3d& p ) {
			p.z() = 0; // project onto xy-plane.
			const double d = p.x()* p.x()+ p.y() * p.y();
			const double r = radius * radius;
			if ( d < r )	p.z() = std::sqrt( r - d ); // on sphere
			else		p *= radius / p.norm();     // on silhouette
			return;
		}		
	private:
		Eigen::Quaterniond rotation_;	///< rotation
		Eigen::Vector3d center_;	///< center point
		double	 dist_;			///< distance between eye-center.
		double   radius_;		///< radius of bounding sphere.
		double   fov_;			///< field-of-view angle			
	};

	Camera::Camera ( void ) : NonCopyable() , _impl ( new Impl () )  {
		Eigen::Vector3d b( 1,1,1 );
		b.normalize();
		b*= 100;
		this->init( -b, b );
		return;
	}

	Camera::~Camera( void ) {
		return;
	}
	// @todo initialization of rotation should be considered ?
	void
	Camera::init( const Eigen::Vector3d& bmin, const Eigen::Vector3d& bmax ) {
		Eigen::Vector3d & center = this->_impl->center();
		double& radius = this->_impl->radius();
		double& dist   = this->_impl->dist();
		const double& fov    = this->_impl->fov();
		
		center = ( bmin + bmax ) * 0.5;
		radius = ( bmin - bmax ).norm() * 0.5;
		dist   = radius * 1.0 / std::sin ( fov / 360.0 * 3.1415926 ) ;
		return;
	}

	void 
	Camera::init ( const Eigen::Vector3d& center, const double radius, const double dist ) {
		this->_impl->center() = center;
		this->_impl->radius() = radius;
		this->_impl->dist()   = dist;
		
		return;
	}
	
	void
	Camera::clone ( const Camera& that ) {
		const std::unique_ptr<Impl>& copied = that._impl;
		this->init( copied->center(), copied->radius(), copied->dist());
		// this->_impl->fov() = copied->fov();
		this->_impl->rotation() = copied->rotation();
		
		return;
	}
	
	void 
	Camera::getLookAt( Eigen::Vector3d& eye, Eigen::Vector3d& center, Eigen::Vector3d& up ) {	
		const Eigen::Quaterniond& rotation = this->_impl->rotation();	
		center = this->_impl->center();
		const double& dist   = this->_impl->dist();
		
		Eigen::Matrix3d r; // rotation matrix
		r.setIdentity();
		r = rotation.toRotationMatrix();
		const Eigen::Vector3d eye0( 0, 0, dist );
		const Eigen::Vector3d up0( 0, 1, 0 );
		
		eye = r * eye0 + center;
		up  = r * up0;
		return;
	}
	
	void
	Camera::getZNearFar( double &zNear, double &zFar ) {
		double& radius = this->_impl->radius();
		double& dist   = this->_impl->dist();
		
		zNear = dist - radius;
		zFar  = dist + radius;
		
		if( zNear < 0 ) zNear = 0.01;
	}
	
	double
	Camera::getFov( void ) const {
		return this->_impl->fov();
	}
	
	/**
	 * @brief Rotate by mouse behavior.
	 *
	 */
	void 
	Camera::rotate( const double  oldx, const double oldy, const double newx, const double newy ) {
		Eigen::Quaterniond& rotation = this->_impl->rotation();	
		Eigen::Vector3d oldp( oldx, oldy, 0.0 );
		Eigen::Vector3d newp( newx, newy, 0.0 );
		
		if ( oldp.isApprox( newp, 1.0e-16 ) ) return;
		
		double radius_virtual_sphere = 0.9;
		this->_impl->project_to_sphere( radius_virtual_sphere, oldp );
		this->_impl->project_to_sphere( radius_virtual_sphere, newp );
		Eigen::Quaterniond dr;
		dr.setFromTwoVectors( newp, oldp );
		rotation *= dr;
		return;
	}
	
	/**
	 * @brief Rotate by axis and angle.
	 * @param [in] axis Axis of rotation.
	 * @param [in] angle Rotation angle [rad].
	 */
	void
	Camera::rotate( const Eigen::Vector3d& axis,  const double angle ) {
		Eigen::Quaterniond& rotation = this->_impl->rotation();	
		Eigen::AngleAxisd aa( angle, axis );
		Eigen::Quaterniond dr( aa );
		rotation *= dr;
		return;
	}
	
	/**
	 * @brief Get radius of virtual sphere.
	 */
	double 
	Camera::getRadius ( void ) const {
		return this->_impl->radius();
	}


}

