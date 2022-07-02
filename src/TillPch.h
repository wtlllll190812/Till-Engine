#pragma once
#include <string>
#include <functional>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include<iostream>
#include<vector>
#include <memory>
#include <queue>
#include <map>
#include <utility>
#include "Singleton .h"
#include "Debug.h"


#define BIND_EVENT_FN(x) std::bind(&x,this,std::placeholders::_1)
#define BIT(x) (1 << x)