#include "ansi_common.h"

#include "core/ansi_core.h"
#include "core/log/ansi_log.h"
#include "utility/converter/ansi_converter.h"

std::wstring MakeLogString(const std::wstring & expression, const char * filePath, int lineNumber)
{
	return expression + L" | " + AN::Converter::ToUnicode(std::string(filePath)) + L":" + std::to_wstring(lineNumber);
}

std::wstring MakeLogString(const char * expression, const char * filePath, int lineNumber)
{
	return MakeLogString(AN::Converter::ToUnicode(std::string(expression)), filePath, lineNumber);
}

bool CheckGLError(const char * expression, const char * filePath, int lineNumber)
{
	GLenum error = glGetError();
	if (error == GL_NO_ERROR) { return true; }

	std::string errorString{ std::string("[OpenGL Error] (") + std::to_string(error) + std::string("): ") };
	AN::Core::GetLog()->WriteLine(MakeLogString(errorString.c_str(), filePath, lineNumber));
	return false;
}
