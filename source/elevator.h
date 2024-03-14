#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "buttons.h"
#include "stop.h"

void checkIfShouldStop(int currentFloor, int* direction, int* hallDirectionUp, int* hallDirectionDown, int* floorButton);
void checkIfAnyUnattendedOrders(int* hallDirectionUp, int* hallDirectionDown, int* floorButton, int* direction, int currentFloor);
void stopAndOpenDoors(int* hallDirectionDown, int* hallDirectionUp, int* floorButton, int currentFloor);