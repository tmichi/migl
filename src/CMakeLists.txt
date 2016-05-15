ADD_LIBRARY(migl STATIC OpenGlUtility.cpp OffScreenRenderer.cpp Camera.cpp Projector.cpp)
TARGET_LINK_LIBRARIES(migl glfw3 ${EXTRA_LIBS} ${GLFW_LIBRARIES})
INSTALL(TARGETS migl ARCHIVE DESTINATION lib)


