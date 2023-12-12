#include "PI.h"


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

void PI_CALC(struct PI* PI, float x,float ref)
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



    PI->y_1 = PI->y;
    PI->x_1 = PI->x;

    
}