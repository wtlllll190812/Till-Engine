cmake_minimum_required(VERSION 3.5)
option(GROUP_BY_EXPLORER ON)    # 文件分组是否和资源管理器对应


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
file(GLOB_RECURSE SRC_DIR_LIST "src/*.cpp" "src/*.h")
file(GLOB_RECURSE source_list RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "*.cpp" "*.hpp")

#寻找依赖库
find_package(tinyxml CONFIG REQUIRED)
find_package(glfw3 REQUIRED)
find_package(SOIL2 CONFIG REQUIRED)
find_package(GLEW CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

#包含头文件
INCLUDE_DIRECTORIES(src src/ECS src/Engine src/App)
INCLUDE_DIRECTORIES( src/ECS/Components  src/ECS/System )
INCLUDE_DIRECTORIES(src/Engine/Events src/Engine/Framework src/Engine/Render src/Engine/Layer)
INCLUDE_DIRECTORIES(src/Engine/Window src/Engine/Window/GuiWindow)

INCLUDE_DIRECTORIES(vendor/imgui)

#子文件夹src
ADD_SUBDIRECTORY(src)