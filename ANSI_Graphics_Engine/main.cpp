#include <ansi_graphics_engine.h>

/* 프로그램 진입점 */
int main()
{
	int result{ -1 };
	if (AN::Core::CreateInstance() && AN::Core::GetWindow()->Run()) { result = 0; }

	AN::Core::DeleteInstance();
	return result;
}
