#include "core/window/ansi_window.h"

/* ���α׷� ������ */
int main()
{
	int result{ -1 };
	if (AN::Core::CreateInstance() && AN::Core::GetWindow()->Run()) { result = 0; }

	AN::Core::DeleteInstance();
	return result;
}
