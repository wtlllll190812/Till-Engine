## Till Engine 
A simple game engine


## 使用方法:
mkdir build

cd build

cmake ../ -G "Visual Studio 17 2022" -DCMAKE_TOOLCHAIN_FILE="D:/TL/Vscode/vcpkg-master/scripts/buildsystems/vcpkg.cmake"

将DCMAKE_TOOLCHAIN_FILE后的路径替换为你的vcpkg安装路径
## What the engine looks like now:
![image](https://user-images.githubusercontent.com/80517003/178116747-012a1120-b276-4d58-a6fc-df3edc8079e7.png)

## Dependencies
1. imgui-Docing
2. glm
3. spdlog
4. glfw
5. glew
6. SOIL2
7. tinyxml

## Features
- ECS FrameWork
  - Components
    - Transfoem
    - DirectionLight
    - PointLight
    - Renderer
    - Camera
    - Behaviour
  - System
    - RenderSystem
- Base components of game engine
  - Reflection for c++
  - A debug tool made with spdlog
  - A editor windows made with imgui  
  - (Only opengl now)Render framework supporting the multiple graphics API
