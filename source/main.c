#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "buttons.h"
#include "elevator.h"
#include "stop.h"


int main(){
    elevio_init();
    printf("=== Running Program ===\n");

    //Move to defined state
    int startFloor = elevio_floorSensor();
    while (startFloor == -1) {
        elevio_motorDirection(DIRN_UP);
        startFloor = elevio_floorSensor();
    } 
    elevio_motorDirection(DIRN_STOP);

    //Global variables
    int volatile g_currentFloor = elevio_floorSensor();
    MotorDirection g_direction = DIRN_STOP;
    int g_stopButtonPressed = 0;
    int g_hallDirectionUp[4] = {0, 0, 0, 0};
    int g_hallDirectionDown[4] = {0, 0, 0, 0};
    int g_floorButton[4] = {0, 0, 0, 0};

    //Reset lamp and buttons
    elevio_doorOpenLamp(0);
    resetButtons();

    //FSM
    while(1){
        g_currentFloor = elevio_floorSensor();
        printf("Current floor: %d\n", g_currentFloor);
     
        // Check if should change direction
        if(g_currentFloor == 0 && g_direction != DIRN_STOP){
            elevio_motorDirection(DIRN_UP);
            g_direction = DIRN_UP;
        }
        if(g_currentFloor == N_FLOORS-1 && g_direction != DIRN_STOP){
            elevio_motorDirection(DIRN_DOWN);
            g_direction = DIRN_DOWN;
        }

        checkIfShouldStop(g_currentFloor, &g_direction, &g_hallDirectionUp, &g_hallDirectionDown, &g_floorButton);
        g_stopButtonPressed = elevio_stopButton();
        checkStopButton(g_stopButtonPressed, &g_hallDirectionUp, &g_hallDirectionDown, &g_floorButton, g_currentFloor);
        

        // Floor indicator light
        if(g_currentFloor != -1){
            elevio_floorIndicator(g_currentFloor);
        }

        checkButtons(&g_hallDirectionUp, &g_hallDirectionDown, &g_floorButton);
        checkIfAnyUnattendedOrders(&g_hallDirectionUp, &g_hallDirectionDown, &g_floorButton, &g_direction, g_currentFloor);

        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

}