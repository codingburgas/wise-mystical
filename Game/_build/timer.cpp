#include "raylib.h"
#include "timer.h"

/**
 * Start or restart a timer with a specific lifetime.
 */
void StartTimer(Timer* timer, float lifetime)
{
	if (timer != NULL)
	{
		timer->Lifetime = lifetime;
	}
}

/**
 * Update a timer with the current frame time.
 */
void UpdateTimer(Timer* timer)
{
	// Subtract this frame from the timer if it's not already expired
	if (timer != NULL && timer->Lifetime > 0)
	{
		timer->Lifetime -= GetFrameTime();
	}
}

/**
 * Check if a timer is done.
 */
bool TimerDone(Timer* timer)
{
	if (timer != NULL)
	{
		return timer->Lifetime <= 0;
	}

	return false;
}