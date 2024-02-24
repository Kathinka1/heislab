#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "order.h"
#include "elevator.h"

void floorButtonPressed(int floor, int button, Order** pp_headOrder, int lastFloor);