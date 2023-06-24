#pragma once

/* Dependencies */

/* GLEW - OpenGL Extension Wrangler Library */
#include <GL/glew.h>
/* GLFW - Graphics Library Framework */
#include <GLFW/glfw3.h>
/* GLM - OpenGL Mathematics */
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
/* VLD - Visual Leak Detector */
#include <vld.h>

/* C++ */
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
/* C */
#include <cassert>

/* 전역 함수, 매크로 */
#ifdef _DEBUG

/* 런타임 에러를 검사하는 함수 */
bool GL_CheckError(const char * expression, const char * file, int line);

/* 표현식이 false를 반환하면 중단 */
#define ASSERT(expression) if (!(expression)) { __debugbreak(); }

/* OpenGL 명령 실행 후 에러를 확인하는 매크로 함수 */
#define GL_CHECK(x) x;\
	ASSERT(GL_CheckError(#x, __FILE__, __LINE__));

#else

/* 표현식 실행 (Release) */
#define ASSERT(expression) expression;

/* OpenGL 명령 실행 (Release) */
#define GL_CHECK(x) x;

#endif
