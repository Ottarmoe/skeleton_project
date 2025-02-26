#include "orderState.h"

//moves the elevator to the first floor below its position, while not taking input.
void CONTROL_HOME(floor f);

void CONTROL_RESET();

//handles the stop button
//moves elevator toward orders
//cycles doors
//clears old orders
void CONTROL_UPDATE();
void CONTROL_UPDATE_ARC();