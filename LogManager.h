//
// LogManager.h
// 

#ifndef __LOG_MANAGER_H__
#define __LOG_MANAGER_H__

#include <stdio.h>
#include <map>

#include "Manager.h"

// Two-letter acronym for easier access to manager.
#define LM df::LogManager::getInstance()

namespace df {

	/// Default Dragonfly logfile.
	/// Override with DRAGONFLY_LOG environment variable.
	const std::string LOGFILE_DEFAULT = "dragonfly.log";

	class LogManager : public Manager {

	private:
		LogManager();                     
		LogManager(LogManager const&);    
		void operator=(LogManager const&);	// No assignment. 
		bool m_do_flush;					// True if fflush after each               
		FILE* m_p_f;						//Pointer to logfile
		

	public:
		/// If logfile is open, close it.
		~LogManager();

		/// Get the one and only instance of the LogManager.
		static LogManager& getInstance();

		/// Start up LogManager (open main logfile, usually "dragonfly.log").
		/// Return 0 if ok, else -1.
		int startUp() override;

		/// Shut down LogManager (close logfile).
		void shutDown() override;

		/// Write to logfile.  Supports printf() formatting.
		/// Return number of bytes written (excluding prepends), -1 if error.
		int writeLog(const char* fmt, ...);

		/// Set flush of logfile after each write.
		void setFlush(bool do_flush = true);
	};

} // end of namespace df
#endif // __LOG_MANAGER_H__
