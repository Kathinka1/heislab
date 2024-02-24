#include "floor.h"


void floorButtonPressed(int floor, int button, Order** pp_headOrder, int lastFloor) {
    if (*pp_headOrder != NULL){
    
        Order* tempOrderPointer = *pp_headOrder;
        while(tempOrderPointer != NULL) {
            if (button == BUTTON_HALL_UP && tempOrderPointer->direction == DIRN_UP && lastFloor <= floor) {
                changeFloorStop(&tempOrderPointer, floor, 1);
                printf("floor: %d\n, button = %d\n", floor, button);
                return;
            }
            else if (button == BUTTON_HALL_DOWN && tempOrderPointer->direction == DIRN_DOWN && lastFloor >= floor) {
                changeFloorStop(&tempOrderPointer, floor, 1);
                return;
            }
            tempOrderPointer = tempOrderPointer->p_nextOrder;
        }
    } 

    if (button == BUTTON_HALL_UP) {
            addNewOrder(pp_headOrder, floor, DIRN_UP);
        } 
    else if (button == BUTTON_HALL_DOWN){
            addNewOrder(pp_headOrder, floor, DIRN_DOWN);
        }

}