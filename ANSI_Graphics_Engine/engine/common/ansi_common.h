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

/* ���� ��ο� �� ��ȣ�� ���̵� ���ڿ��� �����ϴ� �Լ� */
std::wstring MakeLogString(const std::wstring & expression, const char * filePath, int lineNumber);
/* ���� ��ο� �� ��ȣ�� ���̵� ���ڿ��� �����ϴ� �Լ� */
std::wstring MakeLogString(const char * expression, const char * filePath, int lineNumber);
/* OpenGL ������ �˻��ϴ� �Լ� */
bool CheckGLError(const char * expression, const char * file, int line);

/* ǥ������ false�� ��ȯ�ϸ� false�� ��ȯ�ϴ� ��ũ�� �Լ� */
#define AN_CHECK(expression) if (!(expression)) { return false; }
/* ǥ������ false�� ��ȯ�ϸ� �ڵ����� �α� �޽����� ����ϰ� false�� ��ȯ�ϴ� ��ũ�� �Լ� */
#define AN_CHECK_LOG(expression) if (!(expression)) { AN::Core::GetLog()->WriteLine(MakeLogString(#expression, __FILE__, __LINE__)); return false; }
/* ǥ������ false�� ��ȯ�ϸ� �α� �޽����� ����ϰ� false�� ��ȯ�ϴ� ��ũ�� �Լ� */
#define AN_CHECK_LOG_M(expression, wstring) if (!(expression)) { AN::Core::GetLog()->WriteLine(MakeLogString(wstring, __FILE__, __LINE__)); return false; }
/* �α� �޽����� ����ϴ� ��ũ�� �Լ� */
#define AN_ERROR_LOG(wstring) AN::Core::GetLog()->WriteLine(MakeLogString(wstring, __FILE__, __LINE__));
/* OpenGL ��� ���� �� ������ Ȯ���ϴ� ��ũ�� �Լ� */
#define GL_CHECK(expression) expression; AN_CHECK(CheckGLError(#expression, __FILE__, __LINE__));

/* �޸� ���� �� nullptr ���� */
#define AN_DELETE(pointer) if (pointer) { delete pointer; pointer = nullptr; }
/* �迭 �޸� ���� �� nullptr ���� */
#define AN_DELETE_ARRAY(pointer) if (pointer) { delete[] pointer; pointer = nullptr; }
