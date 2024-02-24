#include "order.h"


void addNewOrder(Order** pp_head, int floor, MotorDirection direction) {
    Order* p_newOrder = (Order*)malloc(sizeof(Order));

    
    if (p_newOrder == NULL) {
        printf("Error: Could not allocate memory for new order\n");
        return;
    }
    p_newOrder->direction = direction;
    for (int i = 0; i < N_FLOORS; i++){
            p_newOrder->floorStops[i] = 0;
    }
    p_newOrder->floorStops[floor]= 1;


    p_newOrder->p_nextOrder = NULL;

    if (*pp_head == NULL) {
        *pp_head = p_newOrder;
        return;
    }
    else {
        Order* p_currentOrder = *pp_head;
        while (p_currentOrder->p_nextOrder != NULL) {
            p_currentOrder = p_currentOrder->p_nextOrder;
        }
        p_currentOrder->p_nextOrder = p_newOrder;
    }
    return;
}

void removeOrder(Order** pp_head){
    if (*pp_head == NULL) {
        printf("Error: No orders to remove\n");
        return;
    }
    Order* p_tempOrder = *pp_head;
    *pp_head = (*pp_head)->p_nextOrder;
    free(p_tempOrder);
    return;
}

int checkFloor(Order* p_head, int currentFloor){
    if (p_head == NULL) {
        return 0;
    }
    if (p_head->floorStops[currentFloor] == 1 && currentFloor != -1){
        printf("Elevator should stop at floor %d\n", currentFloor);
        return 1;
    }
    return 0;
}

void changeFloorStop(Order** p_order, int floor, int value){
    (*p_order)->floorStops[floor-1] = value;
    return;
}


void stopAtDestination(Order** p_headOrder, int currentFloor){
    elevio_motorDirection(DIRN_STOP);
    elevio_doorOpenLamp(1);
    //sleep(3);
    elevio_doorOpenLamp(0);
    changeFloorStop(p_headOrder, currentFloor, 0);
    if (checkIfOrderIsDone(*p_headOrder, currentFloor)){
        removeOrder(p_headOrder);
    }
}

int checkIfOrderIsDone(Order* p_head, int currentFloor){
    for (int i = 0; i < N_FLOORS; i++)
    {
        if (p_head->floorStops[i] == 1)
        {
            return 1;
        }
    }
    return 0;
}