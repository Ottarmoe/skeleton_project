#include <stdbool.h>
#include <limits.h>
#include "driver/elevio.h"

typedef int floor;

//no functions have security checks

//inputs not done by default
void ORDSTAT_DOINPUTS(bool set);
void ORDSTAT_UPDATE();

void ORDSTAT_CLEAR();
void ORDSTAT_CLOSE(floor f);
void ORDSTAT_OPEN(floor f, ButtonType i);

bool ORDGET(floor f, ButtonType i);
int ORDINDEX(floor f, ButtonType i);


#define NO_FLOOR INT_MIN

//returns NO_FLOOR if no applicable orders
int ORDSTAT_OLDEST_CAB();
int ORDSTAT_OLDEST_HALL();