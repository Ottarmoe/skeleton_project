#include <stdbool.h>
#include <limits.h>
#include "driver/elevio.h"

//no functions have security checks

//inputs not done by default
void ORDSTAT_DOINPUTS(bool set);
void ORDSTAT_UPDATE();

void ORDSTAT_CLEAR();
void ORDSTAT_CLOSE(int f);
void ORDSTAT_OPEN(int f, ButtonType i);

bool ORDGET(int f, ButtonType i);
int ORDINDEX(int f, ButtonType i);


#define NO_FLOOR INT_MIN

//returns NO_FLOOR if no applicable orders
int ORDSTAT_OLDEST_CAB();
int ORDSTAT_OLDEST_HALL();