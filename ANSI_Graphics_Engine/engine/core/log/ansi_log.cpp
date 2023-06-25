#include "ansi_log.h"

#ifdef _DEBUG
#include "utility/converter/ansi_converter.h"
#endif

namespace AN
{

	Log::Log() :
		m_isGood(false),
		m_fileName(),
		m_file()
	{

	}

	Log::~Log()
	{
		if (m_isGood) { m_file.close(); }
	}

	bool Log::Initialize()
	{
		m_file.open(L"logs/ansi_graphics_engine.log");
		m_isGood = m_file.good();

		return m_isGood;
	}

	void Log::WriteSpace(const std::wstring & string)
	{
		m_file << string << L" ";
		m_file.flush();

#ifdef _DEBUG
		std::cout << Converter::ToAscii(string) << " ";
#endif
	}

	void Log::WriteLine(const std::wstring & string)
	{
		m_file << string << L"\n";
		m_file.flush();

#ifdef _DEBUG
		std::cout << Converter::ToAscii(string) << std::endl;
#endif
	}

	void Log::NextLine()
	{
		m_file << L"\n";
		m_file.flush();

#ifdef _DEBUG
		std::cout << std::endl;
#endif
	}

	void Log::LineOpen()
	{
		WriteLine(L"-----------------------------------------------------------------\n");

#ifdef _DEBUG
		std::cout << "-----------------------------------------------------------------\n" << std::endl;
#endif
	}

	void Log::LineClose()
	{
		WriteLine(L"\n-----------------------------------------------------------------");

#ifdef _DEBUG
		std::cout << "\n-----------------------------------------------------------------" << std::endl;
#endif
	}

}
