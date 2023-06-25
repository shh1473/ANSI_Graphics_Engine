#pragma once

/* Dependencies */

/* GLEW - OpenGL Extension Wrangler Library */
#include <GL/glew.h>
/* GLFW - Graphics Library Framework */
#include <GLFW/glfw3.h>
/* GLM - OpenGL Mathematics */
#include <GLM/glm.hpp>
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
#include <vector>

/* 파일 경로와 줄 번호를 와이드 문자열로 결합하는 함수 */
std::wstring MakeLogString(const std::wstring & expression, const char * filePath, int lineNumber);
/* 파일 경로와 줄 번호를 와이드 문자열로 결합하는 함수 */
std::wstring MakeLogString(const char * expression, const char * filePath, int lineNumber);
/* OpenGL 에러를 검사하는 함수 */
bool CheckGLError(const char * expression, const char * file, int line);

/* 표현식이 false를 반환하면 false를 반환하는 매크로 함수 */
#define AN_CHECK(expression) if (!(expression)) { return false; }
/* 표현식이 false를 반환하면 자동으로 로그 메시지를 출력하고 false를 반환하는 매크로 함수 */
#define AN_CHECK_LOG(expression) if (!(expression)) { AN::Core::GetLog()->WriteLine(MakeLogString(#expression, __FILE__, __LINE__)); return false; }
/* 표현식이 false를 반환하면 로그 메시지를 출력하고 false를 반환하는 매크로 함수 */
#define AN_CHECK_LOG_M(expression, wstring) if (!(expression)) { AN::Core::GetLog()->WriteLine(MakeLogString(wstring, __FILE__, __LINE__)); return false; }
/* 로그 메시지를 출력하는 매크로 함수 */
#define AN_ERROR_LOG(wstring) AN::Core::GetLog()->WriteLine(MakeLogString(wstring, __FILE__, __LINE__));
/* OpenGL 명령 실행 후 에러를 확인하는 매크로 함수 */
#define GL_CHECK(expression) expression; AN_CHECK(CheckGLError(#expression, __FILE__, __LINE__));

/* 메모리 해제 후 nullptr 대입 */
#define AN_DELETE(pointer) if (pointer) { delete pointer; pointer = nullptr; }
/* 배열 메모리 해제 후 nullptr 대입 */
#define AN_DELETE_ARRAY(pointer) if (pointer) { delete[] pointer; pointer = nullptr; }
