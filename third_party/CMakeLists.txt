#编译imgui
file(GLOB_RECURSE IMGUI_LIST imgui/*.cpp imgui/*.h)
ADD_LIBRARY(imgui STATIC ${IMGUI_LIST})
target_include_directories(imgui PUBLIC ${CMAKE_BINARY_DIR}/vcpkg_installed/x64-windows/include)

# file(GLOB_RECURSE IMGUIZMO_LIST imGuizmo/*.cpp imGuizmo/*.h)
# ADD_LIBRARY(imGuizmo STATIC ${IMGUIZMO_LIST})
# target_include_directories(imGuizmo PUBLIC ${CMAKE_BINARY_DIR}/vcpkg_installed/x64-windows/include)