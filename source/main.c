#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "order.h"
#include "elevator.h"
#include "floor.h"


int main(){
    elevio_init();

    
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    Order* p_headOrder = NULL;

    addNewOrder(&p_headOrder, 2, DIRN_UP);

    int startFloor = elevio_floorSensor();
    int lastFloor;
    //    printf("Start floor: %d\n", startFloor);

    while (startFloor == -1) {
        elevio_motorDirection(DIRN_UP);
        startFloor = elevio_floorSensor();
    }

    while(1){
        int volatile currentFloor = elevio_floorSensor();

        if (currentFloor != -1) {
            lastFloor = currentFloor;
        }

        //printf("Last floor: %d\n", lastFloor);
      //  printf("Current floor: %d\n", currentFloor);
       // printf("Head order: %p\n", p_headOrder);
        if (p_headOrder != NULL){
         elevio_motorDirection(p_headOrder->direction); 
         //   printf("Floor: %d\n", currentFloor);

            if (checkFloor(p_headOrder, currentFloor)){
                stopAtDestination(&p_headOrder, currentFloor);
            }
    }

        currentFloor = elevio_floorSensor();
// CHECK IF FLOORBUTTONS ARE PRESSED AND UPDATE ORDERS
        for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < 2; b++){
                if(elevio_callButton(f, b)){
                    floorButtonPressed(f,b, &p_headOrder, lastFloor);
                }
            }
        }

        /*for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);

                elevio_buttonLamp(f, b, btnPressed);
                printf("Button at floor %d, button type %d is %d\n", f, b, btnPressed);
            }
        }
        */

        if(elevio_obstruction()){
            elevio_stopLamp(1);
            elevio_doorOpenLamp(1);
            elevio_motorDirection(DIRN_STOP);
        } else {
            elevio_stopLamp(0);
        }
        
        if(elevio_stopButton()){
            elevio_motorDirection(DIRN_STOP);
            break;
        }
        
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

    return 0;
}
