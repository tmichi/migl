#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#include <windows.h>
#include <GL/gl.h>
#pragma comment(lib, "glfw3dll.lib")
#pragma comment(lib, "opengl32.lib")
#elif defined(__APPLE__)
#include <OpenGL/gl.h>
// -framework OpenGL -I/usr/local/include -L/usr/locallib -lglfw3
#endif
