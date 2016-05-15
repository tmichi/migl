/**
 * @file Camera.hpp
 * @author Takashi Michikawa <michikawa@acm.org>
 */
#pragma once
#ifndef MI_CAMERA_HPP
#define MI_CAMERA_HPP 1
#include <memory>

#include <Eigen/Dense>
#include <mi/NonCopyable.hpp>

namespace mi
{
        class Camera : public NonCopyable 
        {
        public:
		explicit Camera ( void ) ;
		~Camera(void);
                void init( const Eigen::Vector3d& bmin, const Eigen::Vector3d& bmax );
                void init ( const Eigen::Vector3d& center, const double radius, const double dist );
                void clone ( const Camera& that );
                void getLookAt( Eigen::Vector3d& eye, Eigen::Vector3d& center, Eigen::Vector3d& up ) ;

                void getZNearFar( double &zNear, double &zFar );

                double getFov( void ) const;
                /**
                 * @brief Rotate by mouse behavior.
                 *
                 */
                void rotate( const double  oldx, const double oldy, const double newx, const double newy );
                /**
                 * @brief Rotate by axis and angle.
                 * @param [in] axis Axis of rotation.
                 * @param [in] angle Rotation angle [rad].
                 */
                void rotate( const Eigen::Vector3d& axis,  const double angle );
                /**
                 * @brief Get radius of virtual sphere.
                 */
                double getRadius ( void ) const;
        private:
		class Impl;
		std::unique_ptr<Impl> _impl;
        };
}
#endif//CAMERA_HPP
