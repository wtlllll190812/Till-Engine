#CMakeLists.txt
cmake_minimum_required(VERSION 3.5)
set_property(GLOBAL PROPERTY USE_FOLDERS On)

#vcpkg配置,改为自己的vcpkg位置
set(VCPKG_ROOT "D:/TL/Vscode/vcpkg-master/scripts/buildsystems/vcpkg.cmake")
set(CMAKE_TOOLCHAIN_FILE ${VCPKG_ROOT})

#设定文件名
set(Proj_Name Till_Engine)

PROJECT (${Proj_Name})

#转移文件夹
file(COPY ${PROJECT_SOURCE_DIR}/resource/ DESTINATION  resource FOLLOW_SYMLINK_CHAIN)
file(COPY ${PROJECT_SOURCE_DIR}/shaders/ DESTINATION shaders FOLLOW_SYMLINK_CHAIN)
file(COPY ${PROJECT_SOURCE_DIR}/data/ DESTINATION data FOLLOW_SYMLINK_CHAIN)

#源文件和头文件
file(GLOB_RECURSE SRC_DIR_LIST "src/*.cpp" "include/*.h")

#寻找依赖库
find_package(tinyxml REQUIRED)
find_package(imgui REQUIRED)
find_package(glfw3 REQUIRED)
find_package(SOIL2 REQUIRED)
find_package(GLEW REQUIRED)
find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)

#包含头文件
INCLUDE_DIRECTORIES(include)

#子文件夹src
ADD_SUBDIRECTORY(src)