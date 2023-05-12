set(WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
set(CoreFiles 
src/Core/EntryPoint.h 
src/Core/Macros.h
src/Core/Application.h 
src/Core/Application.cpp 
src/Core/Cursor.h 
src/Core/Cursor.cpp
src/Core/PerspectiveCamera.h
src/Core/PerspectiveCamera.cpp
src/Core/Renderer.h 
src/Core/Renderer.cpp 
src/Core/Timer.h 
src/Core/Timer.cpp 
src/Core/Window.h 
src/Core/Window.cpp) 

set(glCore
src/OpenGL/GLDebug.h
src/OpenGL/GLDebug.cpp
src/OpenGL/VertexBuffer.h
src/OpenGL/VertexBuffer.cpp
src/OpenGL/IndexBuffer.h
src/OpenGL/IndexBuffer.cpp
src/OpenGL/VertexArray.h
src/OpenGL/VertexArray.cpp
src/OpenGL/ShaderProgram.h
src/OpenGL/ShaderProgram.cpp)

set(glEntities
src/OpenGL/Entity/Mesh.h
src/OpenGL/Entity/Mesh.cpp
src/OpenGL/Entity/Material.h
src/OpenGL/Entity/Entity.h
src/OpenGL/Entity/Entity.cpp
src/OpenGL/Entity/Texture.h
src/OpenGL/Entity/Texture.cpp
src/OpenGL/Entity/Cube.h
src/OpenGL/Entity/Cube.cpp
src/OpenGL/Entity/Pyramid.h
src/OpenGL/Entity/Pyramid.cpp
src/OpenGL/Entity/Lights.h
src/OpenGL/Entity/Lights.cpp
src/OpenGL/Entity/DefaultTexture.png)

source_group(src/Core FILES ${CoreFiles})
source_group(src FILES src/Core.h)
source_group(src/OpenGL FILES ${glCore})
source_group(src/OpenGL/Entity FILES ${glEntities})

add_library(Core SHARED 
src/Core.h
${CoreFiles} 
${glCore} 
${glEntities} 
${Vendors}
)

set_target_properties(Core PROPERTIES
    CXX_STANDARD 20
    VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/LightingScene/Debug/
)

target_include_directories(Core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../Dependencies/GLEW/include/
    src/Vendor/
)

target_link_libraries(Core 
PRIVATE opengl32
PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../Dependencies/GLEW/lib/Release/x64/glew32s.lib)

target_compile_definitions(Core 
PRIVATE CORE_BUILD_DLL
PRIVATE GLEW_STATIC
PRIVATE GLEW_NO_GLU
PUBLIC UNICODE)

add_custom_command(TARGET Core POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/Debug/Core.dll ${CMAKE_BINARY_DIR}/LightingScene/Debug/)