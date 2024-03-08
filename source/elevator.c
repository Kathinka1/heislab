#include "elevator.h"


void checkIfShouldStop(int currentFloor, int* direction, int* hallDirectionUp, int* hallDirectionDown, int* floorButton) {
    // Check if the elevator should stop at first floor
    if (currentFloor == 0  && (hallDirectionUp[currentFloor] || floorButton[currentFloor])) {
        stopAndOpenDoors(hallDirectionDown, hallDirectionUp, floorButton, currentFloor);
        elevio_motorDirection(DIRN_UP);
        direction = DIRN_UP;
    }
    // Check if the elevator should stop at top floor
    
    else if (currentFloor == 3  && (hallDirectionDown[currentFloor] || floorButton[currentFloor])) {
        stopAndOpenDoors(hallDirectionDown, hallDirectionUp, floorButton, currentFloor);
        elevio_motorDirection(DIRN_DOWN);
        direction = DIRN_DOWN;
    }
    else if (currentFloor != -1 && *direction == DIRN_UP && (hallDirectionUp[currentFloor] || floorButton[currentFloor])) {
        stopAndOpenDoors(hallDirectionDown, hallDirectionUp, floorButton, currentFloor);
        elevio_motorDirection(*direction);
    } 

    else if (currentFloor != -1 && *direction == DIRN_DOWN && (hallDirectionDown[currentFloor] || floorButton[currentFloor])) {
        stopAndOpenDoors(hallDirectionDown, hallDirectionUp, floorButton, currentFloor);
        elevio_motorDirection(*direction);
    }    
}

void checkIfAnyUnattendedOrders(int* hallDirectionUp, int* hallDirectionDown, int* floorButton, int* direction, int currentFloor) {
    for (int i = 0; i < N_FLOORS; i++) {
        if (hallDirectionUp[i] || hallDirectionDown[i] || floorButton[i]) {
            if (*direction == DIRN_STOP) {
                if (currentFloor == 3) {
                    *direction = DIRN_DOWN;
                    elevio_motorDirection(DIRN_DOWN);  
                    return;
                } 
              
                *direction = DIRN_UP;
                elevio_motorDirection(DIRN_UP);
                return;
            }
        return;
        }
    }
    elevio_motorDirection(DIRN_STOP);
    *direction = DIRN_STOP;
}

void stopAndOpenDoors(int* hallDirectionDown, int* hallDirectionUp, int* floorButton, int currentFloor) {
    elevio_motorDirection(DIRN_STOP);
    elevio_doorOpenLamp(1);
    sleep(1);
    checkButtons(hallDirectionUp, hallDirectionDown, floorButton);
    sleep(1);
    checkButtons(hallDirectionUp, hallDirectionDown, floorButton);
    sleep(1);
    checkButtons(hallDirectionUp, hallDirectionDown, floorButton);

    obstruction();

    elevio_doorOpenLamp(0);

    hallDirectionDown[currentFloor] = 0;
    hallDirectionUp[currentFloor] = 0;
    floorButton[currentFloor] = 0; 

    elevio_buttonLamp(currentFloor, BUTTON_CAB, 0);
    elevio_buttonLamp(currentFloor, BUTTON_HALL_DOWN, 0);
    elevio_buttonLamp(currentFloor, BUTTON_HALL_UP, 0);
}