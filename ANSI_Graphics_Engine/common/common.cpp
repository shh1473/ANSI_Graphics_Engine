#include "common.h"

#ifdef _DEBUG

bool GL_CheckError(const char * expression, const char * filePath, int lineNumber)
{
	GLenum error = glGetError();
	if (error == GL_NO_ERROR) { return true; }
	std::cout << "[OpenGL Error] (" << error << "): " << expression << " " << filePath << ":" << lineNumber << std::endl;
	return false;
}

#endif
