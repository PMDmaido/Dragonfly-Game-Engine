#include "Clock.h"
#include <windows.h>

namespace df {

	Clock::Clock() {
		SYSTEMTIME st;
		GetSystemTime(&st);
		m_previous_time = (st.wDay * 24 * 60 * 60 * 1000000)
			+ (st.wHour * 60 * 60 * 1000000)
			+ (st.wMinute * 60 * 1000000)
			+ (st.wSecond * 1000000)
			+ (st.wMilliseconds * 1000);
	}

	long int Clock::delta() { 
		SYSTEMTIME st;
		GetSystemTime(&st);

		long int m_current_time = (st.wDay * 24 * 60 * 60 * 1000000)
			+ (st.wHour * 60 * 60 * 1000000)
			+ (st.wMinute * 60 * 1000000)
			+ (st.wSecond * 1000000)
			+ (st.wMilliseconds * 1000);


		/// Return time elapsed since delta() was called, -1 if error.
		long int delta = m_current_time - m_previous_time;

		/// Resets clock time.
		m_previous_time = m_current_time;

		/// Units are microseconds.
		return delta;
	}

	long int Clock::split() const { 
		SYSTEMTIME st;
		GetSystemTime(&st);

		long int m_current_time = (st.wDay * 24 * 60 * 60 * 1000000)
			+ (st.wHour * 60 * 60 * 1000000)
			+ (st.wMinute * 60 * 1000000)
			+ (st.wSecond * 1000000)
			+ (st.wMilliseconds * 1000);

		/// Return time elapsed since delta() was called, -1 if error.
		long int split = m_current_time - m_previous_time;

		/// Units are microseconds.
		return split;
	}

} // end of namespace df