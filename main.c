#include "DllHeader.h"
#include <stdio.h>

DLLEXPORT void plecsSetSizes(struct SimulationSizes* aSizes)
{
aSizes->numInputs = 1;
aSizes->numOutputs = 2;
aSizes->numStates = 0;
aSizes->numParameters = 0; //number of user parameters passed in
}

DLLEXPORT void plecsOutput(struct SimulationState* aState)
{
aState->outputs[0] = aState->inputs[0] * 3;
aState->outputs[1] = aState->inputs[0] + 5;
}
