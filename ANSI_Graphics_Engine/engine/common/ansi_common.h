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

/* ���� ��ο� �� ��ȣ�� ���̵� ���ڿ��� �����ϴ� �Լ� */
std::wstring MakeLogString(const std::wstring & expression, const char * filePath, int lineNumber);

/* ���� ��ο� �� ��ȣ�� ���̵� ���ڿ��� �����ϴ� �Լ� */
std::wstring MakeLogString(const char * expression, const char * filePath, int lineNumber);

/* OpenGL ������ �˻��ϴ� �Լ� */
bool CheckGLError(const char * expression, const char * filePath, int lineNumber);

/* GLFW ������ �˻��ϴ� �Լ� */
bool CheckGLFWError(const char * expression, const char * filePath, int lineNumber);

/* ǥ������ false�� ��ȯ�ϸ� false�� ��ȯ�ϴ� ��ũ�� �Լ� */
#define AN_CHECK(expression) if (!(expression)) { return false; }

/* ǥ������ false�� ��ȯ�ϸ� nullptr�� ��ȯ�ϴ� ��ũ�� �Լ� */
#define AN_CHECK_NULL(expression) if (!(expression)) { return nullptr; }

/* �α� �޽����� ����ϴ� ��ũ�� �Լ� */
#define AN_ERROR_LOG(wstring) AN::Core::GetLog()->WriteLine(MakeLogString(wstring, __FILE__, __LINE__));

/* ǥ������ false�� ��ȯ�ϸ� �ڵ����� �α� �޽����� ����ϴ� ��ũ�� �Լ� */
#define AN_ERROR_LOG_IF(expression) if (!(expression)) { AN_ERROR_LOG(#expression); }

/* ǥ������ false�� ��ȯ�ϸ� �������� �α� �޽����� ����ϴ� ��ũ�� �Լ� */
#define AN_ERROR_LOG_IF_M(expression, wstring) if (!(expression)) { AN_ERROR_LOG(wstring); }

/* ǥ������ false�� ��ȯ�ϸ� �ڵ����� �α� �޽����� ����ϰ� false�� ��ȯ�ϴ� ��ũ�� �Լ� */
#define AN_CHECK_LOG(expression) if (!(expression)) { AN_ERROR_LOG(#expression); return false; }

/* ǥ������ false�� ��ȯ�ϸ� �������� �α� �޽����� ����ϰ� false�� ��ȯ�ϴ� ��ũ�� �Լ� */
#define AN_CHECK_LOG_M(expression, wstring) if (!(expression)) { AN_ERROR_LOG(wstring); return false; }

/* OpenGL ��� ���� �� ������ �߻��ϸ� �ڵ����� �α� �޽����� ����ϰ� false�� ��ȯ�ϴ� ��ũ�� �Լ� */
#define GL_CHECK(expression) expression; AN_CHECK(CheckGLError(#expression, __FILE__, __LINE__));

/* OpenGL ��� ���� �� ������ �߻��ϸ� �ڵ����� �α� �޽����� ����ϰ� nullptr�� ��ȯ�ϴ� ��ũ�� �Լ� */
#define GL_CHECK_NULL(expression) expression; AN_CHECK_NULL(CheckGLError(#expression, __FILE__, __LINE__));

/* OpenGL ��� ���� �� ������ �߻��ϸ� �ڵ����� �α� �޽����� ����ϴ� ��ũ�� �Լ� */
#define GL_ERROR_LOG(expression) expression; CheckGLError(#expression, __FILE__, __LINE__);

/* GLFW ��� ���� �� ������ �߻��ϸ� �ڵ����� �α� �޽����� ����ϰ� false�� ��ȯ�ϴ� ��ũ�� �Լ� */
#define GLFW_CHECK(expression) expression; AN_CHECK(CheckGLFWError(#expression, __FILE__, __LINE__));

/* �޸� ���� �� nullptr ���� */
#define AN_DELETE(pointer) if (pointer) { delete pointer; pointer = nullptr; }

/* �迭 �޸� ���� �� nullptr ���� */
#define AN_DELETE_ARRAY(pointer) if (pointer) { delete[] pointer; pointer = nullptr; }
