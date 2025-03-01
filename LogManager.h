#ifndef __LOG_MANAGER_H__
#define __LOG_MANAGER_H__

#include <stdio.h>
#include <string.h>

#include "Manager.h"

namespace df {
	const std::string LOGFILE_DEFAULT = "dragonfly.log";

#define LM df::LogManager::getInstance() // Two-letter acronym 

	class LogManager : public Manager {
	private:
		// Private(a singleton).
		LogManager(); // No constructing.
		LogManager(LogManager const&); // No copying.
		void operator=(LogManager const&); // No assignment.

		int log_level; // Logging level.
		bool m_do_flush; // True if flush to disk after write.		
		FILE* m_p_f; // Pointer to logfile structure.

	public:
		// If logfile is open, close it.
		~LogManager();

		// Get/Return the one and only instance of the LogManager.
		static LogManager& getInstance();

		// Start up LogManager (open logfile "dragonfly log").
		int startUp();

		// Shut down LogManager (close logfile).
		void shutDown();

		// Set flush of logfile after each write.
		void setFlush(bool do_flush = true);

		// Write to logfile. Supports printf() formatting of strings.
		// Return number of bytes written, -1 if error.
		int writeLog(const char* fmt, ...);

		// Write to logfile.
		// Only write if indicated log level >= LogManager log level.
		// Supports printf() formatting of strings.
		// Return number of bytes written (excluding prepends), -1 if error.
		//int writeLog(int log_level, const char* fmt, ...) const;
		void writeLog(int log_level, const char* fmt, ...) const;
	};
} // end of namespace df
#endif // __LOG_MANAGER_H__
