ADD_EXECUTABLE(offscreen offscreen.cpp Bmp.hpp BmpImage.hpp)
ADD_EXECUTABLE(projection projection.cpp)
ADD_EXECUTABLE(viewer viewer.cpp)
if(APPLE)
	ADD_DEFINITIONS(-g -O3 -Wall)
	TARGET_LINK_LIBRARIES(offscreen glfw3 ${EXTRA_LIBS} ${GLFW_LIBRARIES} migl)
	TARGET_LINK_LIBRARIES(projection glfw3 ${EXTRA_LIBS} ${GLFW_LIBRARIES} migl)
	TARGET_LINK_LIBRARIES(viewer glfw3 ${EXTRA_LIBS} ${GLFW_LIBRARIES} migl)
#elseif(WIN32)
#	INCLUDE_DIRECTORIES(.. ${PROJECT_SOURCE_DIR}/include)
	
endif()


