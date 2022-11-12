#pragma once

// Define Timer struct
typedef struct
{
    float Lifetime;

}Timer;

// Start or restart a timer with a specific lifetime
void StartTimer(Timer* timer, float lifetime);

// Update a timer with the current frame time
void UpdateTimer(Timer* timer);

// Check if a timer is done
bool TimerDone(Timer* timer);