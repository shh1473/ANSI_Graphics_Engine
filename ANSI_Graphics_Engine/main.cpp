#include <ansi_graphics_engine.h>

/* ���α׷� ������ */
int main()
{
	int result{ -1 };
	if (AN::Core::CreateInstance() && AN::Core::GetWindow()->Run()) { result = 0; }

	AN::Core::DeleteInstance();
	return result;
}
