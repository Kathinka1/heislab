#include "buttons.h"

void checkButtons(int *hallDirectionUp, int *hallDirectionDown, int *floorButton) {
    for(int f = 0; f < N_FLOORS; f++){
        for(int b = 0; b < N_BUTTONS; b++){
            
            int btnPressed = elevio_callButton(f, b);
            if (btnPressed) {
                if (b == BUTTON_HALL_UP) {
                    hallDirectionUp[f] = 1;
                    elevio_buttonLamp(f, b, hallDirectionUp[f]);
                } else if (b == BUTTON_HALL_DOWN) {
                    hallDirectionDown[f] = 1;
                    elevio_buttonLamp(f, b, hallDirectionDown[f]);
                } else if (b == BUTTON_CAB) {
                    floorButton[f] = 1;
                    elevio_buttonLamp(f, b, floorButton[f]);
                }
            }
         }
    }
}

void resetButtons() {
    for(int f = 0; f < N_FLOORS; f++){
        for(int b = 0; b < N_BUTTONS; b++){
            elevio_buttonLamp(f, b, 0);
        }
    }
}
