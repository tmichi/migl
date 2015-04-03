/**
 * @file Projector.hpp
 * @author Takashi Michikawa <michikawa@acm.org>
 */

#ifndef MI_PROJECTOR_HPP
#define MI_PROJECTOR_HPP 1
#include <Eigen/Dense>
namespace mi
{
        class Projector
        {
        private:
                Eigen::Matrix4d _matrix;
                Eigen::Matrix4d _inv_matrix;
		int             _viewport[4];        
        public:
                explicit Projector ( double modelview[16], double projection[16], int viewport[4] ) {
                        this->_matrix =  Eigen::Map<Eigen::Matrix4d>( projection ) * Eigen::Map<Eigen::Matrix4d>( modelview );
                        this->_inv_matrix = this->_matrix.inverse();
                        for ( int i = 0 ; i < 4 ; ++i ) {
                                this->_viewport[i] = viewport[i];
                        }
                }

                Eigen::Vector3d project ( const Eigen::Vector3d& p, int *error = NULL ) {
                        Eigen::Vector3d w;
                        *error = this->project( p.x(), p.y(), p.z(), w.x(), w.y(), w.z() );
                        return w;
                }

                int project ( const double x, const double y, const double z, double &wx, double &wy, double &wz ) {
                        Eigen::Vector4d p = this->_matrix * Eigen::Vector4d( x, y, z, 1 );
                        if ( p.w() == 0 ) return 0;
                        p *= 1.0 / p.w();

                        wx = this->_viewport[0] + ( 1 + p.x() ) * this->_viewport[2] * 0.5;
                        wy = this->_viewport[1] + ( 1 + p.y() ) * this->_viewport[3] * 0.5;
                        wz = ( 1.0 + p.z() ) * 0.5;

                        return 1;
                }

                Eigen::Vector3d unproject ( const Eigen::Vector3d& wp, int *error = NULL ) {
                        Eigen::Vector3d p;
                        *error = this->unproject( wp.x(), wp.y(), wp.z(), p.x(), p.y(), p.z() );
                        return p;
                }

                int unproject ( const double wx, const double wy, const double wz, double &x, double &y, double &z ) {
                        Eigen::Vector4d p;
                        p.x() = ( wx - this->_viewport[0] ) * 2 / this->_viewport[2] - 1.0;
                        p.y() = ( wy - this->_viewport[1] ) * 2 / this->_viewport[3] - 1.0;
                        p.z() = 2.0 * wz  - 1.0;
                        p.w() = 1.0;

                        const Eigen::Vector4d p1 = this->_inv_matrix * p;
                        if ( p1.w() == 0.0 ) return 0;
                        x = p1.x() / p1.w();
                        y = p1.y() / p1.w();
                        z = p1.z() / p1.w();
                        return 1;
                }
        };
}
#endif// MI_PROJECTOR_HPP
