#include "raylib.h"
#include "movement.h"

void updateCameraPos(float* xCoordinate, float* yCoordinate)
{
	// Uptade camera position, based on W, A, S, D keys
	if (IsKeyDown(KEY_A))
	{
		// Check left camera boundary 
		if (*xCoordinate > 910)
		{
			*xCoordinate -= 3.0f;
		}
		else
		{
			*xCoordinate += 3.0f;
		}

		// Check top or bottom key down
		if (IsKeyDown(KEY_W))
		{
			// Check top boundary
			if (*yCoordinate > 550)
			{
				*yCoordinate -= 3.0f;
			}
			else
			{
				*yCoordinate += 3.0f;
			}
		}
		else if (IsKeyDown(KEY_S))
		{
			// Check bottom boundary
			if (*yCoordinate < 2250)
			{
				*yCoordinate += 3.0f;
			}
			else
			{
				*yCoordinate -= 3.0f;
			}
		}
	}
	else if (IsKeyDown(KEY_D))
	{
		// Check right camera boundary 
		if (*xCoordinate < 1815)
		{
			*xCoordinate += 3.0f;
		}
		else
		{
			*xCoordinate -= 3.0f;
		}

		// Check top or bottom key down
		if (IsKeyDown(KEY_W))
		{
			// Check top boundary
			if (*yCoordinate > 550)
			{
				*yCoordinate -= 3.0f;
			}
			else
			{
				*yCoordinate += 3.0f;
			}
		}
		else if (IsKeyDown(KEY_S))
		{
			// Check bottom boundary
			if (*yCoordinate < 2250)
			{
				*yCoordinate += 3.0f;
			}
			else
			{
				*yCoordinate -= 3.0f;
			}
		}
	}

	// Update camera, based on seperate key input - W, A, S, D 
	if (IsKeyDown(KEY_W))
	{
		if (*yCoordinate > 550)
		{
			*yCoordinate -= 3.0f;
		}
		else
		{
			*yCoordinate += 3.0f;
		}
	}
	else if (IsKeyDown(KEY_S))
	{
		if (*yCoordinate < 2250)
		{
			*yCoordinate += 3.0f;
		}
		else
		{
			*yCoordinate -= 3.0f;
		}
	}
	else if (IsKeyDown(KEY_A))
	{
		if (*xCoordinate > 910)
		{
			*xCoordinate -= 3.0f;
		}
		else
		{
			*xCoordinate += 3.0f;
		}
	}
	else if (IsKeyDown(KEY_D))
	{
		if (*xCoordinate < 1815)
		{
			*xCoordinate += 3.0f;
		}
		else
		{
			*xCoordinate -= 3.0f;
		}
	}
}