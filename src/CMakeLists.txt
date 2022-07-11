ADD_EXECUTABLE(${Proj_Name} ${SRC_DIR_LIST})


source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SRC_DIR_LIST})
link_directories(lib)
target_link_libraries(${Proj_Name} 
    PRIVATE 
    glfw
    ${tinyxml_LIBRARIES}
    fmt::fmt
    ${SOIL2_LIBRARIES}
    ${GLEW_LIBRARIES}
    glm::glm
    ${spdlog_LIBRARIES})

target_link_libraries(${Proj_Name} lib/assimp-vc143-mt)