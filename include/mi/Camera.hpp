/**
 * @file Camera.hpp
 * @author Takashi Michikawa <michikawa@acm.org>
 */
#pragma once
#ifndef MI_CAMERA_HPP
#define MI_CAMERA_HPP 1
#include <Eigen/Dense>

namespace mi
{
        class Camera
        {
        private:
                Eigen::Quaterniond rotation_;	///< rotation
                Eigen::Vector3d center_;	///< center point
                double	 dist_;			///< distance between eye-center.
                double   radius_;		///< radius of bounding sphere.
                double   fov_;			///< field-of-view angle
        private:
                Camera ( const Camera& that );
                void operator = ( const Camera& that );
        public:
                explicit Camera ( const double fov = 40 ): rotation_ ( Eigen::Quaterniond( 1,0,0,0 ) ), center_( Eigen::Vector3d() ), dist_( 0 ), radius_( 100 ), fov_( fov ) {
                        Eigen::Vector3d b( 1,1,1 );
                        b.normalize();
                        b*= 100;
                        this->init( -b, b );
                        return;
                }

                // @todo initialization of rotation should be considered ?
                void init( const Eigen::Vector3d& bmin, const Eigen::Vector3d& bmax ) {
                        this->center_ = ( bmin + bmax ) * 0.5;
                        this->radius_ = ( bmin - bmax ).norm()* 0.5;
                        this->dist_ = this->radius_  / std::sin ( this->fov_ / 360.0 * 3.1415926 );
                }

                void init ( const Eigen::Vector3d& center, const double radius, const double dist ) {
                        this->center_ = center;
                        this->radius_ = radius;
                        this->dist_    = dist;
                        return;
                }

                void clone ( const Camera& that ) {
                        this->rotation_ = that.rotation_;
                        this->center_ = that.center_;
                        this->dist_   = that.dist_;
                        this->radius_ = that.radius_;
                        this->fov_    = that.fov_;
                        return;
                }

                void getLookAt( Eigen::Vector3d& eye, Eigen::Vector3d& center, Eigen::Vector3d& up ) {
                        Eigen::Matrix3d r; // rotation matrix
                        r.setIdentity();
                        r = this->rotation_.toRotationMatrix();
                        Eigen::Vector3d eye0( 0, 0, this->dist_ );
                        Eigen::Vector3d up0( 0, 1, 0 );
                        center = this->center_;
                        eye = r * eye0 + this->center_;
                        up  = r * up0;
                        return;
                }

                void getZNearFar( double &zNear, double &zFar ) {
                        zNear = this->dist_ - this->radius_;
                        zFar  = this->dist_ + this->radius_;
                        if( zNear < 0 ) zNear = 0.01;
                }

                double getFov( void ) const {
                        return this->fov_;
                }

                /**
                 * @brief Rotate by mouse behavior.
                 *
                 */
                void rotate( const double  oldx, const double oldy, const double newx, const double newy ) {
                        Eigen::Vector3d oldp( oldx, oldy, 0.0 );
                        Eigen::Vector3d newp( newx, newy, 0.0 );

                        if ( oldp.isApprox( newp, 1.0e-16 ) ) return;

                        double radius_virtual_sphere = 0.9;
                        this->project_to_sphere( radius_virtual_sphere, oldp );
                        this->project_to_sphere( radius_virtual_sphere, newp );
                        Eigen::Quaterniond dr;
                        dr.setFromTwoVectors( newp, oldp );
                        this->rotation_ *= dr;
                        return;
                }

                /**
                 * @brief Rotate by axis and angle.
                 * @param [in] axis Axis of rotation.
                 * @param [in] angle Rotation angle [rad].
                 */
                void rotate( const Eigen::Vector3d& axis,  const double angle ) {
                        Eigen::AngleAxisd aa( angle, axis );
                        Eigen::Quaterniond dr( aa );
                        this->rotation_ *= dr;
                        return;
                }

                /**
                 * @brief Get radius of virtual sphere.
                 */
                double getRadius ( void ) const {
                        return this->radius_;
                }
        private:
                void project_to_sphere( const double& radius, Eigen::Vector3d& p ) const {
                        p.z() = 0; // project onto xy-plane.
                        const double d = p.x()* p.x()+ p.y() * p.y();
                        const double r = radius * radius;
                        if ( d < r )	p.z() = std::sqrt( r - d ); // on sphere
                        else		p *= radius / p.norm();     // on silhouette
                        return;
                }
        };
}
#endif//CAMERA_HPP
