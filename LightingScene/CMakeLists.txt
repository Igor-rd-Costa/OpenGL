set(Textures
    src/Textures/container2.png
    src/Textures/container2_specular.png
    src/Textures/DefaultTexture.png
    src/Textures/DefaultSpecular.png
)

set(Shaders
    src/Shaders/LightSourceVertex.glsl
    src/Shaders/LightSourceFragment.glsl
    src/Shaders/MultipleLightsVertex.glsl
    src/Shaders/MultipleLightsFragment.glsl
)

set(Main
    src/LightingScene.h
    src/LightingScene.cpp
)

source_group(src/Textures FILES ${Textures})
source_group(src/Shaders FILES ${Shaders})
source_group(src FILES ${Main})

add_executable(LightingScene
    ${Textures}
    ${Shaders}
    ${Main}
)
set_target_properties(LightingScene PROPERTIES
    WIN32_EXECUTABLE TRUE
    CXX_STANDARD 20
    VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/LightingScene/Debug/
)

target_link_Libraries(LightingScene Core)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Debug/src/Textures)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Debug/src/Shaders)

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/src/Textures/" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/Debug/src/Textures")
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/src/Shaders/" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/Debug/src/Shaders")

message (${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(LightingScene
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../Core/src/
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../Core/src/Vendor/
)