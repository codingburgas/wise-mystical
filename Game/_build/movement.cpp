#include "raylib.h"
#include "movement.h"

/**
 * Set the camera's intial positon based on the starter city's index.
 */
void setInitialCameraPos(float* cameraPosXPtr, float* cameraPosYPtr, int num)
{
	switch (num)
	{
	case 0:
		*cameraPosXPtr = 912;
		*cameraPosYPtr = 549;
		break;
	case 7:
	case 8:
	case 14: 
		*cameraPosXPtr = 912;
		*cameraPosYPtr = 1227;
		break;
	case 28:
	case 29:
	case 30:
	case 31:
	case 32:
	case 33:
	case 34:
		*cameraPosXPtr = 912;
		*cameraPosYPtr = 2199;
		break;
	case 22:
	case 23:
	case 24:
	case 25:
	case 26:
	case 27:
	case 35:
	case 37:
	case 38:
	case 39:
		*cameraPosXPtr = 1812;
		*cameraPosYPtr = 2250;
		break;
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 10:
	case 36:
		*cameraPosXPtr = 1566;
		*cameraPosYPtr = 1167;
		break;
	case 9:
	case 11:
	case 12:
	case 13:
	case 15: 
	case 16:
	case 17:
	case 18:
	case 19:
	case 20:
	case 21:
		*cameraPosXPtr = 1287;
		*cameraPosYPtr = 1677;
		break;
	default:
		break;
	}
}

/**
 * Update camera position.
 */
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