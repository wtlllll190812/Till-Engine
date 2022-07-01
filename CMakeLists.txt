#CMakeLists.txt
cmake_minimum_required(VERSION 3.5)

#换成你的vcpkg路径
set(VCPKG_ROOT "D:/TL/Vscode/vcpkg-master/scripts/buildsystems/vcpkg.cmake")
set(CMAKE_TOOLCHAIN_FILE ${VCPKG_ROOT})


PROJECT (Till_Engine)
INCLUDE_DIRECTORIES(include)
ADD_SUBDIRECTORY(src)
