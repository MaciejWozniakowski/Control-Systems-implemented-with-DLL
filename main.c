#include <stdio.h>
#include "DllHeader.h"
#include <math.h>
#define TS 0.0001
#define invTS 10000
//#define M_PI 3.14159265358979323846

int signum(double x) {
    if (x > 0) {
        return 1;
    } else if (x < 0) {
        return -1;
    } else {
        return 0;
    }
}
int power_function(double phase_shift, double Udc1, double Udc2, double fp, double L)
{
    double power = signum(phase_shift) * (Udc1 * Udc2 * fabs(phase_shift) * (M_PI - fabs(phase_shift))) / (2 * pow(M_PI, 2) * fp * L);
    return power;
}
int phase_shift(double Ich2, double Udc1, double L, double fp)
{
    double delta = signum(Ich2) * (M_PI / 2) * (sqrt(pow(Udc1, 2) - 8 * Udc1 * L * fp * fabs(Ich2))) / (Udc1);
    return delta;
}

struct PI{
	float x;
	float y;
	float y_1;
	float x_1;
	float Ts;
	float Kr;
	float Ti;
	float integ;
	float final_output;
	float integ_1;
	float final_output_before;
	float max;
	float min;
};

void PIInit(struct PI *pi, float Kr, float Ti,  float Ts,float max, float min){
	pi->y=0;
	pi->x=0;
	pi->y_1=0;
	pi->x_1 = 0;
	pi->Kr=Kr;
	pi->Ts=Ts;
	pi->Ti=Ti;
	pi->integ = 0;
	pi->final_output = 0;
	pi->integ_1 = 0;
	pi->final_output_before = 0;
	pi->max = max;
	pi->min = min;
	
}

double PICalc(struct PI *pi, float x, float feedback){
	pi->x=x - feedback;
	
	if (pi->final_output_before < pi->max && pi->final_output_before > pi->min)
	{
		pi->integ=(((pi->Ts/pi->Ti * pi->x * pi->Kr) / 2.0) + ((pi->Ts/pi->Ti * pi->x_1 * pi->Kr) / 2.0) +  pi->integ_1);

	}
	else
	{
		pi->integ = pi->integ_1;
	}
	
	pi->final_output = pi->Kr*pi->x + pi->integ;
	if(pi->final_output >= pi->max)
	{
		pi->final_output = pi->max;
	}
	else if(pi->final_output <= pi->min)
	{
		pi->final_output = pi->min;
	}

  return pi->final_output;
	pi->x_1 = pi->x;

	pi->integ_1 = pi->integ;
	pi->y_1=pi->final_output;

	pi->final_output_before = pi->final_output;
}
struct PI PI1;
// implementing improved modulator

int * modulator(float power){
  static int outputs[4];
  float x1 = 0, x2 = 0;
  if(x1>2.0){ // counter reset, so that sin function takes memory efficient args
    x1 = 0;
  }
  if(sin(invTS*x1)>=0){ // transistor 1 and 2 signals are inverted
    x1+= 0.000001;
    outputs[0] = 1;
    outputs[1] = 0;
  }
    
  if(sin(invTS*x1)<0){

    x1+= 0.000001;
    outputs[0] = 0;
    outputs[1] = 1;
  }
 // transistor 3 and 4 signals dictate the power of the converter
 // signal 4 is signal 3 inverted  
  if(x2 > 2.0){
    x2 = 0;
  }
  if(sin(invTS*x2 +(invTS * power))>= 0){
    x2 += 0.000001;
    outputs[2] = 1;
    outputs[3] = 0;
  }
  if(sin(invTS*x2 +(invTS * power))< 0){
    x2 += 0.000001;
    outputs[2] = 0;
    outputs[3] = 1;
  }
  
  return outputs;
}


DLLEXPORT void plecsSetSizes(struct SimulationSizes* aSizes)
{
aSizes->numInputs = 4;
aSizes->numOutputs = 4;
aSizes->numStates = 0;
aSizes->numParameters = 0; //number of user parameters passed in
}
DLLEXPORT void plecsStart(struct SimulationState* aState){
  float kr = 0.0, ti = 100000.0, aw_max = 2.0, aw_min = 0.0;

  PIInit(&PI1, kr, ti, TS, aw_max, aw_min);

}

DLLEXPORT void plecsOutput(struct SimulationState* aState)
{
  int *phaseshiftOutputs;
  phaseshiftOutputs = modulator(aState->inputs[0]);
  aState->outputs[0] =  phaseshiftOutputs[0];
  aState->outputs[1] =  phaseshiftOutputs[1];
  aState->outputs[2] =  phaseshiftOutputs[2];
  aState->outputs[3] =  phaseshiftOutputs[3];
//aState->outputs[0] = PICalc(&PI1, aState->inputs[0], aState->inputs[1]); // input 0 is refference, input 1 is feedback
//aState->outputs[1] = aState->inputs[0];
}


