
#include <vector>
#include <iostream>

#include <Eigen/Dense>
#include <GLFW/glfw3.h>

#include <mi/OffScreenRenderer.hpp>
#include <mi/OpenGlUtility.hpp>
#include <mi/glconf.hpp>

#include <mi/Camera.hpp>
#include <mi/Projector.hpp>
int main( int argc, char** argv )
{
	std::vector<Eigen::Vector3d> cloud;

        for( int i = 0  ; i  < 1000 ; ++i ) {
                cloud.push_back( Eigen::Vector3d::Random().normalized() );
        }
	
        mi::Camera camera;
        camera.init( Eigen::Vector3d(-3, -3, -3), Eigen::Vector3d(3, 3, 3));
	
	const int w = 640;
	const int h = 480;
	mi::OffScreenRenderer renderer( w, h );
	renderer.swapBuffers();
	
        ::glEnable( GL_DEPTH_TEST );
        ::glClearColor( 1, 0,0,1 );
        ::glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
        double zNear, zFar;
        Eigen::Vector3d eye, center, up;
        camera.getZNearFar( zNear, zFar );
        double fov = camera.getFov();
        camera.getLookAt( eye, center, up );

        //カメラ、投影情報の設定
        ::glMatrixMode( GL_PROJECTION );
        ::glLoadIdentity();
        mi::OpenGlUtility::perspective( fov, w * 1.0 / h ,  zNear, zFar );
	
        ::glMatrixMode( GL_MODELVIEW );
        ::glLoadIdentity();
        mi::OpenGlUtility::lookAt( eye, center, up );

        int viewport[4];
        double projection[16];
        double modelview[16];
        ::glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
        ::glGetDoublev( GL_PROJECTION_MATRIX, projection );
        ::glGetIntegerv( GL_VIEWPORT, viewport );

        
	::glPointSize( 2.0 );		
        ::glBegin( GL_POINTS );
        for( int i = 0 ; i < cloud.size(); ++i ) {
                ::glColor3f( 1, 1, 1 );
                const Eigen::Vector3d& p = cloud[i];
                ::glVertex3d( p.x(), p.y(), p.z() );
        }
        ::glEnd();
        renderer.swapBuffers();

	std::vector<float> depth;
        renderer.getDepth( depth );
        mi::Projector projector( modelview, projection, viewport );
	
        for( int y = 0 ; y < h ; ++y ) {
                for ( int x = 0 ; x < w ; ++x ) {
                        double px, py, pz;
                        const double wx = x;
                        const double wy = y;
                        const double wz = depth[ x + w * y ];
			if ( wz > 1.0 -  1.0e-10) continue;
                        projector.unproject( wx,wy,wz, px,py,pz );
                        std::cout<<px<<" "<<py<<" "<<pz<<std::endl;
                }
        }
        return 0;
}


