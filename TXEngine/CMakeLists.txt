project(TXEngine)

add_definitions(-DTXENGINE_BUILD)
add_definitions(-DSTB_IMAGE_STATIC)
add_definitions(-DSTB_IMAGE_IMPLEMENTATION)
add_definitions(-w)

set(GLFW_DIR ./lib/glfw-3.3.7/lib/cmake/glfw3)
set(FREETYPE_DIR ./lib/freetype/lib/cmake/freetype)
set(AL_DIR ./lib/openal-soft-1.22.2/lib/cmake/OpenAL)

set(FREEALUT_INCLUDE ./lib/freealut/include)
set(FREEALUT_LIB ./lib/freealut/lib)
set(GLAD_INCLUDE ./lib/glad/include)
set(GLAD_SRC ./lib/glad/src/glad.c)
set(GLM_INCLUDE ./lib/glm/include)
set(STB_INCLUDE ./lib/stb)

find_package(glfw3 REQUIRED HINTS ${GLFW_DIR})
find_package(OpenAL REQUIRED HINTS ${AL_DIR})
find_package(freetype REQUIRED HINTS ${FREETYPE_DIR})

include_directories(${GLAD_INCLUDE})
include_directories(${GLM_INCLUDE})
include_directories(${STB_INCLUDE})
include_directories(${FREEALUT_INCLUDE})

link_directories(${FREEALUT_LIB})

set(INC_ROOT ./include)
include_directories(${INC_ROOT})

set(SRC_ROOT ./src)
set(SRC
    # Audio
    ${SRC_ROOT}/${PROJECT_NAME}/Audio/Sound.cpp
    ${SRC_ROOT}/${PROJECT_NAME}/Audio/AlUtil.cpp
    # Graphics
    ${SRC_ROOT}/${PROJECT_NAME}/Graphics/Window.cpp
    ${SRC_ROOT}/${PROJECT_NAME}/Graphics/Color.cpp
    ${SRC_ROOT}/${PROJECT_NAME}/Graphics/Shape.cpp
    ${SRC_ROOT}/${PROJECT_NAME}/Graphics/RectangleShape.cpp
    ${SRC_ROOT}/${PROJECT_NAME}/Graphics/CircleShape.cpp
    ${SRC_ROOT}/${PROJECT_NAME}/Graphics/Texture.cpp
    ${SRC_ROOT}/${PROJECT_NAME}/Graphics/TextureTarget.cpp
    ${SRC_ROOT}/${PROJECT_NAME}/Graphics/Font.cpp
    ${SRC_ROOT}/${PROJECT_NAME}/Graphics/Text.cpp
    # Event
    ${SRC_ROOT}/${PROJECT_NAME}/Event/EventBase.cpp
    ${SRC_ROOT}/${PROJECT_NAME}/Event/KeyPressEvent.cpp
    ${SRC_ROOT}/${PROJECT_NAME}/Event/CloseEvent.cpp
    ${SRC_ROOT}/${PROJECT_NAME}/Event/ResizeEvent.cpp
    # Util
    ${SRC_ROOT}/${PROJECT_NAME}/Util/Clock.cpp
    # OpenGL
    ${SRC_ROOT}/${PROJECT_NAME}/OpenGL/VertexBuffer.cpp
    ${SRC_ROOT}/${PROJECT_NAME}/OpenGL/Vertex.cpp
    ${SRC_ROOT}/${PROJECT_NAME}/OpenGL/VertexArrayBuffer.cpp
    ${SRC_ROOT}/${PROJECT_NAME}/OpenGL/Shader.cpp
    ${SRC_ROOT}/${PROJECT_NAME}/OpenGL/IndexBuffer.cpp
    ${SRC_ROOT}/${PROJECT_NAME}/OpenGL/GLUtil.cpp
)

add_library(${PROJECT_NAME} SHARED ${SRC} ${GLAD_SRC})

target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE alut.lib)
target_link_libraries(${PROJECT_NAME} PRIVATE freetype) 
target_link_libraries(${PROJECT_NAME} PRIVATE OpenAL::OpenAL)