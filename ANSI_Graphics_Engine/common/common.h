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

/* ���� �Լ�, ��ũ�� */
#ifdef _DEBUG

/* ��Ÿ�� ������ �˻��ϴ� �Լ� */
bool GL_CheckError(const char * expression, const char * file, int line);

/* ǥ������ false�� ��ȯ�ϸ� �ߴ� */
#define ASSERT(expression) if (!(expression)) { __debugbreak(); }

/* OpenGL ��� ���� �� ������ Ȯ���ϴ� ��ũ�� �Լ� */
#define GL_CHECK(x) x;\
	ASSERT(GL_CheckError(#x, __FILE__, __LINE__));

#else

/* ǥ���� ���� (Release) */
#define ASSERT(expression) expression;

/* OpenGL ��� ���� (Release) */
#define GL_CHECK(x) x;

#endif
