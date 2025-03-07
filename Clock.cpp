//
// Clock.cpp
//

#include <chrono>
#include "Clock.h"
#include "LogManager.h"

Clock::Clock() {
    previous_time = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now().time_since_epoch()
    ).count();
    LM.writeLog("Clock started");
}

long int Clock::delta() {
    // Get the current time in milliseconds
    auto current_time = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now().time_since_epoch()
    ).count();

    // Calculate the elapsed time since the last call to delta()
    long int elapsed_time = current_time - previous_time;

    // Update previous_time to the current time
    previous_time = current_time;

    return elapsed_time;
}

long int Clock::split() const {
    // Get the current time in milliseconds
    auto current_time = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now().time_since_epoch()
    ).count();

    // Calculate the elapsed time since the last call to delta()
    long int elapsed_time = current_time - previous_time;

    return elapsed_time;
}