#include <mi/glconf.hpp>
#include <vector>
#include <iostream>
#include <mi/Camera.hpp>
#include <mi/OpenGlUtility.hpp>
#include "Window.hpp"
int main( int argc, char** argv )
{
	std::vector<Eigen::Vector3d> cloud;
        for( int i = 0  ; i  < 1000 ; ++i ) {
                cloud.push_back( Eigen::Vector3d::Random().normalized() );
        }
	 
        Eigen::Vector3d bmin, bmax;
        mi::Camera camera;
        camera.init( Eigen::Vector3d(-1, -1, -1), Eigen::Vector3d(1, 1, 1));

        if ( ::glfwInit() == GL_FALSE ) return -1;
        Window win( 640, 480, "hello world" );
        if ( !win ) return -1;
        GLFWwindow* window = win.getWindow();

        ::glEnable( GL_DEPTH_TEST );
        ::glClearColor( 0,0,1,1 );
        ::glPointSize( 2.0 );

        while ( !::glfwWindowShouldClose( window ) ) {
                double zNear, zFar;
                Eigen::Vector3d eye, center, up;
                camera.getZNearFar( zNear, zFar );
                double fov = camera.getFov();
                camera.getLookAt( eye, center, up );

                //カメラ、投影情報の設定
                ::glMatrixMode( GL_PROJECTION );
                ::glLoadIdentity();
                mi::OpenGlUtility::perspective ( fov, win.getAspectRatio(),  zNear, zFar );

                ::glMatrixMode( GL_MODELVIEW );
                ::glLoadIdentity();
                mi::OpenGlUtility::lookAt( eye, center, up );

                //オブジェクトの描画
                ::glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
                ::glBegin( GL_POINTS );
                for( int i = 0 ; i < cloud.size(); ++i ) {
                        ::glColor3f( 1, 1, 1 );
                        const Eigen::Vector3d& p = cloud[i];
                        ::glVertex3d( p.x(), p.y(), p.z() );
                }
                ::glEnd();
                ::glfwSwapBuffers( window );

                //マウスイベントの取得
                ::glfwWaitEvents();
                double oldx, oldy, newx, newy;
                win.getMousePosition( oldx, oldy, newx, newy );
                //右ドラッグで回転
                if ( ::glfwGetMouseButton( window, GLFW_MOUSE_BUTTON_1 ) != GLFW_RELEASE ) {
                        camera.rotate( oldx, oldy, newx, newy );
                }
        }
        return 0;
}


