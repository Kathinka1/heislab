#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "elevator.h"
#include "stop.h"


void checkButtons(int *hallDirectionUp, int *hallDirectionDown, int *floorButton);
void resetButtons() ;