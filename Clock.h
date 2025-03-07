#pragma once
// 
// Clock.h
//


class Clock {
private:
	long int previous_time; // Prev time delta() called (milli sec)

public:
	//set previous_time to current time
	Clock();

	// Return time elapsed since delta was last called, -1 if error.
	//Units are milliseconds.
	long int delta(void);

	// Return time elapsed since delta() was last called
	// Units are milliseconds.
	long int split(void) const;

};