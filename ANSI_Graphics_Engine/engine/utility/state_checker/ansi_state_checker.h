#pragma once

namespace AN
{

	template<typename T>
	class StateChecker
	{
	public:
		explicit StateChecker() : m_curValue(), m_oldValue() {}

		bool Check() const { return (m_curValue != m_oldValue); }
		void Reset() { m_oldValue = m_curValue; }

		void Set(const T & value) { m_curValue = value; }

		const T & Get() const { return m_curValue; }
		const T * GetAddress() const { return &m_curValue; }

	protected:
		T m_curValue;
		T m_oldValue;

	};

	template <typename T, unsigned SIZE>
	class StateArrayChecker
	{
	public:
		explicit StateArrayChecker() : m_start(SIZE), m_end(-1) {}

		bool Check() const
		{
			for (int i{ 0 }; i < m_end + 1; ++i)
			{
				if (m_curValues[i] != m_oldValues[i]) { return true; }
			}
			return false;
		}
		void Reset()
		{
			m_start = SIZE;
			m_end = -1;
			for (unsigned i{ 0 }; i < SIZE; ++i) { m_oldValues[i] = m_curValues[i]; }
		}

		void Set(int index, const T & value)
		{
			m_curValues[index] = value;

			if (index < m_start) { m_start = index; }
			else if (index == m_start)
			{
				if (m_curValues[index] == m_oldValues[index])
				{
					for (; m_start < m_end; ++m_start)
					{
						if (m_curValues[m_start] != m_oldValues[m_start]) { break; }
					}
				}
			}

			if (index > m_end) { m_end = index; }
			else if (index == m_end)
			{
				if (m_curValues[index] == m_oldValues[index])
				{
					for (; m_end > m_start; --m_end)
					{
						if (m_curValues[m_end] != m_oldValues[m_end]) { break; }
					}
				}
			}
		}
		void SetAll(const T & value)
		{
			m_start = 0;
			m_end = SIZE - 1;
			for (unsigned i{ 0 }; i < SIZE; ++i) { m_curValues[i] = value; }
		}

		unsigned GetStart() const { return m_start; }
		unsigned GetEnd() const { return m_end; }
		unsigned GetRange() const { return m_end - m_start + 1; }
		const T & Get(unsigned index) const { return m_curValues[index]; }
		const T * GetAddress(unsigned index) const { return &m_curValues[index]; }
		const T * GetArray() const { return m_curValues; }

	protected:
		int m_start;
		int m_end;
		T m_curValues[SIZE];
		T m_oldValues[SIZE];

	};

}
