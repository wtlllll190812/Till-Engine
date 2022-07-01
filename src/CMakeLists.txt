ADD_EXECUTABLE(${Proj_Name} ${SRC_DIR_LIST})

target_link_libraries(${Proj_Name} 
    PRIVATE 
    ${tinyxml_LIBRARIES}
    glfw
    imgui::imgui
    fmt::fmt
    ${SOIL2_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${spdlog_LIBRARIES})