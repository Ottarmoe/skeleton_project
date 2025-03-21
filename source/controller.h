#include "orderState.h"

//moves the elevator to the first floor below its position, while not taking input.
void CONTROL_HOME(floor f);

//reset the controll system to initial conditions
void CONTROL_RESET();

//handles the stop button
//moves elevator toward orders
//cycles doors
//clears old orders

//maintain direction type order selection
void CONTROL_UPDATE();
//prioritize by cab then age type order selection
void CONTROL_UPDATE_ARC();