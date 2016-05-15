/**
 * @file Projector.hpp
 * @author Takashi Michikawa <michikawa@acm.org>
 */

#ifndef MI_PROJECTOR_HPP
#define MI_PROJECTOR_HPP 1
#include <array>

#include <Eigen/Dense>
#include <mi/NonCopyable.hpp>

namespace mi
{
        class Projector : public NonCopyable 
        {
        public:
                explicit Projector ( double modelview[16], double projection[16], int viewport[4] );
		~Projector(void);
                Eigen::Vector3d project ( const Eigen::Vector3d& p, int *error = NULL );
                int project ( const double x, const double y, const double z, double &wx, double &wy, double &wz );
                Eigen::Vector3d unproject ( const Eigen::Vector3d& wp, int *error = NULL );
                int unproject ( const double wx, const double wy, const double wz, double &x, double &y, double &z );
        private:
		class Impl;
		std::unique_ptr<Impl> _impl;
        };
}
#endif// MI_PROJECTOR_HPP
