#include "DllHeader.h"
#include "PI.h"

//Global variables
double kp, ki, ts, y,aw_max,aw_min,kp_i,ki_i,v_ref,aw_max_U;
//Map input and output parameters to meaningful names
#define v_out aState->inputs[0]
#define i_out aState->inputs[1]
//#define i aState->states[0]
//#define y aState->outputs[0]
struct PI PI1;
struct PI PI2;


DLLEXPORT void plecsSetSizes(struct SimulationSizes* aSizes)
{
   aSizes->numInputs = 2;
   aSizes->numOutputs = 1;
   aSizes->numStates = 1;
   aSizes->numParameters = 9; //number of user parameters passed in
}


//This function is automatically called at the beginning of the simulation
DLLEXPORT void plecsStart(struct SimulationState* aState)
{
	//Example error message box
	if (aState->parameters[0] < 0 )
		aState->errorMessage = "kp cannot be less than 0";
	kp = aState->parameters[0];
	ki = aState->parameters[1];
	ts = aState->parameters[2];
	aw_max = aState->parameters[3];
	aw_min = aState->parameters[4];
	kp_i = aState->parameters[5];
	ki_i = aState->parameters[6];
	v_ref = aState->parameters[7];
	aw_max_U = aState->parameters[8];

	

	PI_INIT(&PI1, kp, ki, ts, aw_max_U, aw_min);
	PI_INIT(&PI2, kp_i, ki_i, ts, aw_max, aw_min);
	//aState_global = aState;
}

//#define TRIG_0 aState_global->inputs[0]
//#define TRIG_180 aState_global->inputs[1]


//This function is automatically called every sample time
//output is written to DLL output port after the output delay
DLLEXPORT void plecsOutput(struct SimulationState* aState)
{	
	//i = i + ts * e;
	//y = kp * e + ki * i;
	// PI.i -> przechowany poprzedni stan i
	PI_CALC(&PI1, v_out,v_ref);

	PI_CALC(&PI2,i_out, PI1.y);


	//aState->states[0] = PI1.i;
	//aState->outputs[0]= y;
	aState->outputs[0] = PI2.y;

}
