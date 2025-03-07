//
// LogManager.cpp
//

#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include "LogManager.h"
#include <cstdarg>


namespace df {

	LogManager::LogManager() {
		m_do_flush = true;
		m_p_f = nullptr;

	}

	LogManager::~LogManager() {
		if (m_p_f) {
			fclose(m_p_f);
			m_p_f = nullptr;
		}
	}

	LogManager& LogManager::getInstance() {
		static LogManager instance;
		return instance;
	}

	int LogManager::startUp() {
	
		// Check if the logfile is already open
		if (m_p_f) 
			return 0;

		const char* logfile_name = LOGFILE_DEFAULT.c_str();
		
		// Open the logfile
		m_p_f = fopen(logfile_name, "w");
		if (!m_p_f) 
			return -1; // Failed to open file

		return 0;
	}

	void LogManager::shutDown() {
		if (m_p_f) {
			fclose(m_p_f);
			m_p_f = nullptr;
		}
	}

	int LogManager::writeLog(const char* fmt, ...) {

		va_list args;
		va_start(args, fmt);

		// Allocate a buffer for formatted message
		char buffer[1024];
		vsnprintf(buffer, sizeof(buffer), fmt, args);
		va_end(args);

		// Check if the message already ends with a newline
		if (buffer[strlen(buffer) - 1] != '\n') {
			strcat(buffer, "\n");  
		}

		// Print the final message
		int bytes_written = fprintf(m_p_f, "%s", buffer);

		if (m_do_flush) {
			fflush(m_p_f);
		}

		return bytes_written;
	}


	void LogManager::setFlush(bool do_flush) {
		m_do_flush = do_flush;
	}

} 