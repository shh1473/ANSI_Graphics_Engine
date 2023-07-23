#pragma once

/* Dependencies */

/* GLEW - OpenGL Extension Wrangler Library */
#include <GL/glew.h>
/* GLFW - Graphics Library Framework */
#include <GLFW/glfw3.h>
/* GLM - OpenGL Mathematics */
#include <GLM/glm.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include <GLM/gtc/quaternion.hpp>
#include <GLM/gtc/matrix_transform.hpp>

#ifdef _DEBUG
/* VLD - Visual Leak Detector */
#include <vld.h>
#endif

/* C++ */
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <codecvt>
#include <chrono>
#include <typeindex>
#include <algorithm>
#include <functional>
#include <random>
#include <array>
#include <vector>
#include <unordered_map>

#define PI 3.1415927f
#define PI2 6.2831853f

/* 파일 경로와 줄 번호를 와이드 문자열로 결합하는 함수 */
std::wstring MakeLogString(const std::wstring & expression, const char * filePath, int lineNumber);

/* 파일 경로와 줄 번호를 와이드 문자열로 결합하는 함수 */
std::wstring MakeLogString(const char * expression, const char * filePath, int lineNumber);

/* OpenGL 에러를 검사하는 함수 */
bool CheckGLError(const char * expression, const char * filePath, int lineNumber);

/* GLFW 에러를 검사하는 함수 */
bool CheckGLFWError(const char * expression, const char * filePath, int lineNumber);

/* 표현식이 false를 반환하면 false를 반환하는 매크로 함수 */
#define AN_CHECK(expression) if (!(expression)) { return false; }

/* 표현식이 false를 반환하면 nullptr을 반환하는 매크로 함수 */
#define AN_CHECK_NULL(expression) if (!(expression)) { return nullptr; }

/* 로그 메시지를 출력하는 매크로 함수 */
#define AN_ERROR_LOG(wstring) AN::Core::GetLog()->WriteLine(MakeLogString(wstring, __FILE__, __LINE__));

/* 표현식이 false를 반환하면 자동으로 로그 메시지를 출력하는 매크로 함수 */
#define AN_ERROR_LOG_IF(expression) if (!(expression)) { AN_ERROR_LOG(#expression); }

/* 표현식이 false를 반환하면 수동으로 로그 메시지를 출력하는 매크로 함수 */
#define AN_ERROR_LOG_IF_M(expression, wstring) if (!(expression)) { AN_ERROR_LOG(wstring); }

/* 표현식이 false를 반환하면 자동으로 로그 메시지를 출력하고 false를 반환하는 매크로 함수 */
#define AN_CHECK_LOG(expression) if (!(expression)) { AN_ERROR_LOG(#expression); return false; }

/* 표현식이 false를 반환하면 수동으로 로그 메시지를 출력하고 false를 반환하는 매크로 함수 */
#define AN_CHECK_LOG_M(expression, wstring) if (!(expression)) { AN_ERROR_LOG(wstring); return false; }

/* OpenGL 명령 실행 후 에러가 발생하면 자동으로 로그 메시지를 출력하고 false를 반환하는 매크로 함수 */
#define GL_CHECK(expression) expression; AN_CHECK(CheckGLError(#expression, __FILE__, __LINE__));

/* OpenGL 명령 실행 후 에러가 발생하면 자동으로 로그 메시지를 출력하고 nullptr을 반환하는 매크로 함수 */
#define GL_CHECK_NULL(expression) expression; AN_CHECK_NULL(CheckGLError(#expression, __FILE__, __LINE__));

/* OpenGL 명령 실행 후 에러가 발생하면 자동으로 로그 메시지를 출력하는 매크로 함수 */
#define GL_ERROR_LOG(expression) expression; CheckGLError(#expression, __FILE__, __LINE__);

/* GLFW 명령 실행 후 에러가 발생하면 자동으로 로그 메시지를 출력하고 false를 반환하는 매크로 함수 */
#define GLFW_CHECK(expression) expression; AN_CHECK(CheckGLFWError(#expression, __FILE__, __LINE__));

/* 메모리 해제 후 nullptr 대입 */
#define AN_DELETE(pointer) if (pointer) { delete pointer; pointer = nullptr; }

/* 배열 메모리 해제 후 nullptr 대입 */
#define AN_DELETE_ARRAY(pointer) if (pointer) { delete[] pointer; pointer = nullptr; }
