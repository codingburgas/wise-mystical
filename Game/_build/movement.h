#pragma once

// Set the camera's intial positon based on the starter city's index
void setInitialCameraPos(float* cameraPosXPtr, float* cameraPosYPtr, int num);

// Update the camera's position based on keyboard input
void updateCameraPos(float* xCoordinate, float* yCoordinate);