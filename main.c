#include <stdio.h>
#include "DllHeader.h"
struct PI {
    float x;
    float y;
    float y_1;
    float x_1;
    float kp;
    float ki;
    float Ts;
    float aw_min;
    float aw_max;
    float i;
    float p;
    float ref;
};



void PI_INIT(struct PI* pi, float kp, float ki, float ts, float aw_max, float aw_min)
{
    pi->kp = kp;
    pi->ki = ki;
    pi->Ts = ts;
    pi->aw_max = aw_max;
    pi->aw_min = aw_min;
    pi->y_1 = 0;
    pi->x_1 = 0;
    pi->x = 0;
    pi->x_1 = 0;
    pi->i = 0;
    pi->p = 0;
    pi->ref = 0;

}

double PI_CALC(struct PI* PI, float x,float ref)
{   
    PI->ref = ref;
    PI->x =PI->ref-x;

    //PI->i = i;

    //PI->i = PI->i + PI->Ts * PI->x;
    //PI->y = PI->x * PI->kp + PI->ki *PI-> i;
    //if (PI->y >= PI->aw_max || PI->y <= PI->aw_min)
    // {PI->y = PI->xPI->kp;
    // }
   // PI->y = (PI->kp * PI->x) - (PI->kp * PI->x_1) + (PI->ki * PI->Ts * PI->x) / 2 + (PI->ki * PI->Ts * PI->x_1) / 2 + (PI->y_1);
    PI->y = (PI->kp * PI->x) - (PI->kp * PI->x_1) + (PI->ki * PI->Ts * PI->x) / 2 + (PI->ki * PI->Ts * PI->x_1) / 2 + (PI->y_1);

    if (PI->y >= PI->aw_max || PI->y < PI->aw_min) {
        PI->y = PI->aw_max;
        //PI->y = (PI->kp * PI->x) - (PI->kp * PI->x_1) + PI->y_1;
    }


  return PI->y;
    PI->y_1 = PI->y;
    PI->x_1 = PI->x;


    
}
struct PI PI1;


DLLEXPORT void plecsSetSizes(struct SimulationSizes* aSizes)
{
aSizes->numInputs = 2;
aSizes->numOutputs = 1;
aSizes->numStates = 0;
aSizes->numParameters = 0; //number of user parameters passed in
}
DLLEXPORT void plecsStart(struct SimulationState* aState){
  float kp = 1, ki = 1, ts = 0.0001, aw_max = 0, aw_min = 2;

  PI_INIT(&PI1, kp, ki, ts, aw_max, aw_min);

}

DLLEXPORT void plecsOutput(struct SimulationState* aState)
{

aState->outputs[0] =2;// PI_CALC(&PI1, aState->inputs[0],5); // input 0 is feedback, input 1 is refference value  
//aState->outputs[1] = aState->inputs[0];
}


