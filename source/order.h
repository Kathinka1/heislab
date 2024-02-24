/**
 * @file   
 * @brief  This file contains the Order struct and the functions that are used to handle the orders.   
*/

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"

/**
 * @brief  The Order struct contains the direction of the elevator, an array of the floors that the elevator should stop at and a pointer to the next order.   
*/
typedef struct {
    MotorDirection direction;
    int floorStops[N_FLOORS];
    struct Order* p_nextOrder;
} Order;

/**
 * @brief  This function adds a new order to the linked list of orders.   
 * @param[in]  pp_head  A pointer to the head of the linked list of orders.
 * @param[in]  floor  The floor that the elevator should stop at.
 * @param[in]  direction  The direction the elevator should move.
*/
void addNewOrder(Order** pp_head, int floor, MotorDirection direction) ;

/**
 * @brief  This function removes the first order in the linked list of orders.   
 * @param[in]  pp_head  A pointer to the head of the linked list of orders.
*/
void removeOrder(Order** pp_head);

/**
 * @brief  This function checks if the elevator should stop at the current floor.   
 * @param[in]  p_head  A pointer to the head of the linked list of orders.
 * @param[in]  currentFloor  The current floor of the elevator.
 * @return  1 if the elevator should stop, 0 if not.   

*/
int checkFloor(Order* p_head, int currentFloor);

/**
 * @brief  This function changes the value of the floorStops array in the order struct.
 * @param[in]  p_head  A pointer to the head of the linked list of orders.
 * @param[in]  floor  The floor in the floorStops array to be changed.
 * @param[in]  value  The value that the floorStops array should be changed to.
*/
void changeFloorStop(Order** p_head, int floor, int value);

void stopAtDestination(Order** p_head, int currentFloor);

int checkIfOrderIsDone(Order* p_head, int currentFloor);