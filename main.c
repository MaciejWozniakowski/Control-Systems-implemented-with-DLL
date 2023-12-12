#include "DllHeader.h"
#include <stdio.h>
#include "PI.h"

struct PI PI1;

DLLEXPORT void plecsSetSizes(struct SimulationSizes* aSizes)
{
aSizes->numInputs = 2;
aSizes->numOutputs = 1;
aSizes->numStates = 0;
aSizes->numParameters = 0; //number of user parameters passed in
}

DLLEXPORT void plecsStart(struct SimulationState* aState){

  PI_INIT(&PI1, 1, 1, 0.0001, -2, 2);

}

DLLEXPORT void plecsOutput(struct SimulationState* aState)
{

aState->outputs[0] = PI_CALC(&PI1, aState->inputs[0],aState->inputs[1]);
//aState->outputs[1] = aState->inputs[0];
}



