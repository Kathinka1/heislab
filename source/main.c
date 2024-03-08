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

    // Global variables
    int hallDirectionUp[4] = {0, 0, 0, 0};
    int hallDirectionDown[4] = {0, 0, 0, 0};
    int floorButton[4] = {0, 0, 0, 0};

    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    int startFloor = elevio_floorSensor();

    while (startFloor == -1) {
        elevio_motorDirection(DIRN_UP);
        startFloor = elevio_floorSensor();
    } 
    elevio_motorDirection(DIRN_STOP);

    int volatile currentFloor = elevio_floorSensor();
    MotorDirection direction = DIRN_STOP;
    
    elevio_doorOpenLamp(0);

    int stopButton = 0;

    resetButtons();


    while(1){
        currentFloor = elevio_floorSensor();
    

        printf("Current floor: %d\n", currentFloor);
     //   printf("Stop Button: %d\n", stopButton);

        if(currentFloor == 0 && direction != DIRN_STOP){
            elevio_motorDirection(DIRN_UP);
            direction = DIRN_UP;
        }

        if(currentFloor == N_FLOORS-1 && direction != DIRN_STOP){
            elevio_motorDirection(DIRN_DOWN);
            direction = DIRN_DOWN;
        }
        checkIfShouldStop(currentFloor, &direction, &hallDirectionUp, &hallDirectionDown, &floorButton);
        stopButton = elevio_stopButton();
        checkStopButton(stopButton, &hallDirectionUp, &hallDirectionDown, &floorButton, currentFloor);
        

        // Floor indicator light
        if(currentFloor != -1){
            elevio_floorIndicator(currentFloor);
        }

        checkButtons(&hallDirectionUp, &hallDirectionDown, &floorButton);

        checkIfAnyUnattendedOrders(&hallDirectionUp, &hallDirectionDown, &floorButton, &direction, currentFloor);

        
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

}