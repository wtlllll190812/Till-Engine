#pragma once
#include <functional>

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)
#define BIT(x) (1 << x)
#define DATA_PATH "../data/"
#define SHADER_PATH "../shaders/"
#define IMAGE_PATH "../resource/images/"
#define MODEL_PATH "../resource/models/"