// System includes
#include <stdio.h>  // For FILE, fopen, fclose, fprintf, vfprintf, fflush
#include <stdarg.h> // For variable argument lists
#include <time.h>   // For time, localtime, strftime

// Engine includes
#include "LogManager.h"	

namespace df {

	LogManager::LogManager() {
		setType("LogManager");
		m_p_f = nullptr; // Null pointer to logfile structure
		m_do_flush = false;
		log_level = 0; // Default log level (0 = no logging)
	}

	LogManager::~LogManager() {
		if (m_p_f != nullptr) {
			fclose(m_p_f);
		}
	}

	// Return the one and only one instance of the LogManager
	LogManager& LogManager::getInstance() {
		static LogManager instance;
		return instance;
	}

	int LogManager::startUp() {
		if (Manager::startUp() != 0) {
			return -1; // Unable to start up base Manager
		}

		errno_t err = fopen_s(&m_p_f, LOGFILE_DEFAULT.c_str(), "w");
		if (err != 0 || m_p_f == nullptr) {
			return -1; // Unable to open logfile
		}

		writeLog("LogManager started\n");
		return 0;
	}

	void LogManager::shutDown() {
		if (m_p_f) {
			writeLog("LogManager shutting down\n");
			fclose(m_p_f);
			m_p_f = nullptr;
		}
	}

	void LogManager::setFlush(bool do_flush) {
		m_do_flush = do_flush;
	}

	int LogManager::writeLog(const char* fmt, ...) {
		if (!m_p_f) {
			return -1; // Unable to open logfile
		}

		// Print message
		va_list args;
		va_start(args, fmt);
		int bytes_written = vfprintf(m_p_f, fmt, args);
		va_end(args);
		//printf("\n");

		// Flush buffer if requested
		if (m_do_flush) {
			fflush(m_p_f);
		}
		return bytes_written;
	}

	void LogManager::writeLog(int log_level, const char* fmt, ...) const {

		if (log_level > this->log_level) {
			return; // Do not write if log level is too low
		}

		if (!m_p_f) {
			return; // Logfile not open
		}

		va_list args;
		va_start(args, fmt);
		vfprintf(m_p_f, fmt, args);
		va_end(args);

		if (m_do_flush) {
			fflush(m_p_f);
		}
	}

}
