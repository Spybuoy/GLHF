#pragma once
#include<glew\glew.h>

#define _ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    _ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();


bool GLLogCall(const char* function, const char* file, int line);
