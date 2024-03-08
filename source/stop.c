#include "stop.h"

void checkStopButton(int stopButton, int* hallDirectionUp, int* hallDirectionDown, int* floorButton, int currentFloor) {
    if (stopButton) {
        elevio_stopLamp(1);
        elevio_motorDirection(DIRN_STOP);

        if (currentFloor != -1) {
            elevio_doorOpenLamp(1);
        }

        while (stopButton) {
            stopButton = elevio_stopButton();
        }

        for (int i = 0; i < 4; i++) {
            hallDirectionUp[i] = 0;
            hallDirectionDown[i] = 0;
            floorButton[i] = 0;
        }

        elevio_stopLamp(0);

        if (currentFloor != -1) {
            sleep(3);
            elevio_doorOpenLamp(0);

        }
    }
}

void obstruction() {
    int obstructionTrue = elevio_obstruction();
    if (!obstructionTrue) {
        elevio_stopLamp(1);
        while (!obstructionTrue){
            obstructionTrue = elevio_obstruction();
        } 
        sleep(3);
        elevio_stopLamp(0);  
    }     
}

