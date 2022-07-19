cmake_minimum_required(VERSION 3.5)
option(GROUP_BY_EXPLORER ON)    # 文件分组是否和资源管理器对应


#vcpkg配置,改为自己的vcpkg位置
set(VCPKG_ROOT "D:/TL/Vscode/vcpkg-master/scripts/buildsystems/vcpkg.cmake")
set(CMAKE_TOOLCHAIN_FILE ${VCPKG_ROOT})

#设定工程名
set(Proj_Name Till_Engine)

PROJECT (${Proj_Name})

#转移文件夹
file(COPY ${PROJECT_SOURCE_DIR}/resource/ DESTINATION  resource FOLLOW_SYMLINK_CHAIN)
# file(COPY ${PROJECT_SOURCE_DIR}/shaders/ DESTINATION shaders FOLLOW_SYMLINK_CHAIN)
# file(COPY ${PROJECT_SOURCE_DIR}/data/ DESTINATION data FOLLOW_SYMLINK_CHAIN)
file(COPY src/imgui.ini DESTINATION src)

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
find_package(imguizmo CONFIG REQUIRED)

#包含头文件
INCLUDE_DIRECTORIES(src src/ECS src/Engine src/App)
INCLUDE_DIRECTORIES(src/ECS/Components  src/ECS/System )
INCLUDE_DIRECTORIES(src/Engine/Events src/Engine/Framework src/Engine/Render src/Engine/Layer)
INCLUDE_DIRECTORIES(src/Engine/Window src/Engine/Window/GuiWindow src/Engine/Render/Materials)
INCLUDE_DIRECTORIES(third_party third_party/imgui)

#指定库搜索目录
LINK_DIRECTORIES(third_party/libs)
LINK_LIBRARIES(assimp-vc143-mt)

#子文件夹src
ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(third_party)

