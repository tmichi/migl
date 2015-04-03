SET (INCLUDE_FILES OpenGlUtility.hpp OffScreenBuffer.hpp Camera.hpp Projector.hpp glconf.hpp)
INSTALL(FILES ${INCLUDE_FILES}
        DESTINATION include/mi
        PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)
