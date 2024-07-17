# Source files
set(SHADER_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/shaders")
set(SHADER_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/shaders")

#models
set(MODELS_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Models")
set(MODELS_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/Models")
file(MAKE_DIRECTORY "${MODELS_OUTPUT_DIR}")

#textures
set(TEXTURES_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Textures")
set(TEXTURES_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/Textures")
file(MAKE_DIRECTORY "${TEXTURES_OUTPUT_DIR}")



file(GLOB_RECURSE GLSL_SOURCE_FILES
    "${SHADER_SOURCE_DIR}/*.frag"
    "${SHADER_SOURCE_DIR}/*.vert"
)

foreach(GLSL ${GLSL_SOURCE_FILES})
    get_filename_component(FILE_NAME ${GLSL} NAME)
    set(SPIRV "${SHADER_BINARY_DIR}/${FILE_NAME}.spv")
    add_custom_command(
        OUTPUT ${SPIRV}
        COMMAND ${Vulkan_GLSLC_EXECUTABLE} ${GLSL} -o ${SPIRV}
        DEPENDS ${GLSL}
    )
    list(APPEND SPIRV_BINARY_FILES ${SPIRV})
endforeach(GLSL)

add_custom_target(
    Shaders 
    DEPENDS ${SPIRV_BINARY_FILES}
)


set(SOURCES
    "main.cpp"
    "vulkanbase/VulkanBase.h" 
    "vulkanbase/VulkanUtil.h"
    # Add other source files here
    "labwork/Week01.cpp"
    "labwork/Week02.cpp" 
    "labwork/Week04.cpp" 
    "labwork/Week05.cpp"
    "labwork/Week06.cpp"
 "Shader.h" "Shader.cpp" "Shader3D.h" "Shader3D.cpp" "Command.h" "Command.cpp" "Pipeline.h" "Pipeline.cpp" "Pipeline3D.h" "Pipeline3D.cpp" "MeshFactory.h" "MeshFactory.cpp" "Scene.h" "Scene.cpp" "Globals.h" "Buffer.h" "Buffer.cpp" "Mesh3D.h" "Mesh3D.cpp" "Vertex.h"   "Texture.h" "Texture.cpp")

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES} ${GLSL_SOURCE_FILES}  "vulkanbase/VulkanUtil.cpp")
add_dependencies(${PROJECT_NAME} Shaders)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${MODELS_SOURCE_DIR}" "${MODELS_OUTPUT_DIR}"
    COMMENT "Copying models to output directory"
)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${TEXTURES_SOURCE_DIR}" "${TEXTURES_OUTPUT_DIR}"
    COMMENT "Copying textures to output directory pls"
)

# Link libraries
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE ${Vulkan_LIBRARIES} glfw)