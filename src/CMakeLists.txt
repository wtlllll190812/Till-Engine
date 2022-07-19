ADD_EXECUTABLE(${Proj_Name} ${SRC_DIR_LIST})

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SRC_DIR_LIST})
#链接
TARGET_LINK_LIBRARIES(${Proj_Name} 
    PRIVATE 
    imgui
    glfw
    imguizmo::imguizmo
    ${tinyxml_LIBRARIES}
    fmt::fmt
    ${SOIL2_LIBRARIES}
    ${GLEW_LIBRARIES}
    glm::glm
    assimp-vc143-mt
    ${spdlog_LIBRARIES})
#TARGET_LINK_LIBRARIES(${Proj_Name} PUBLIC imgui)