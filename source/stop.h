#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "buttons.h"
#include "elevator.h"

void checkStopButton(int stopButton, int* hallDirectionUp, int* hallDirectionDown, int* floorButton, int currentFloor);

void obstruction();
