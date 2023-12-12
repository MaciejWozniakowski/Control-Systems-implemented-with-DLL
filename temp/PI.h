
#ifndef PI_H_
#define PI_H_

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

void PI_INIT(struct PI* pi, float kp, float ki, float Ts, float aw_min, float aw_max);
void PI_CALC(struct PI* pi, float x,float ref);


#endif /* PI_H_ */