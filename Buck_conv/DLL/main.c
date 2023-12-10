

// main.c : Defines the exported functions for the DLL application.

//#include "stdafx.h"
#include "Controllers.h"
#include "Converter.h"
#include "stddef.h"

//! Debug :
//. Change the view to expert view using Tools > Settings > Expert settings.
//2. Attach the DLL to the PLECS process using Debug > Attach to process > PLECS.exe.
//3. In main.c, create a breakpoint at the line y = kp * e + ki * i.

DLLEXPORT void plecsSetSizes(struct SimulationSizes* aSizes)
{
	aSizes->numInputs = 10;
	aSizes->numOutputs = 13;
	aSizes->numStates = 0;
	aSizes->numParameters = 5; //number of user parameters passed in
}

void CIC1_filter_init(struct CIC1_struct *CIC, float max_value, float OSR, float decimation_ratio)
{
    CIC->decimation_ratio = decimation_ratio;
    CIC->OSR = OSR;
    CIC->div_OSR = 1.0f / OSR;
    CIC->range_modifier = (float)(1UL << 31) / OSR / max_value;
    CIC->div_range_modifier = 1.0f / CIC->range_modifier;
}

void CIC1_adaptive_filter_init(struct CIC1_adaptive_struct *CIC, float max_value, float OSR)
{
    CIC->range_modifier = (float)(1UL << 31) / OSR / max_value;
    CIC->div_range_modifier = 1.0f / CIC->range_modifier;
}

//This function is automatically called at the beginning of the simulation
DLLEXPORT void plecsStart(struct SimulationState* aState)
{
    memset(&Conv, 0, sizeof(Conv));

	Conv.Ts = aState->parameters[0] * 0.5f;
	Conv.L_conv = aState->parameters[1];
	Conv.C = aState->parameters[2];
    Conv.U_ref = aState->parameters[3];
    Conv.I_lim = INFINITY;

    ///////////////////////////////////////////////////////////////////

    register float alfa2 = 2.0f;
    register float STC1 = 1.6f * Conv.Ts;
    float kp_L1 = Conv.L_conv / (alfa2 * STC1);
    float ti_L1 = alfa2 * alfa2 * STC1;

    Conv.PI_I.Ts_Ti = Conv.Ts / ti_L1;
    Conv.PI_I.Kp = kp_L1;
    Conv.PI_I.lim_H = 0.0f;
    Conv.PI_I.lim_L = 0.0f;
    
    ///////////////////////////////////////////////////////////////////

    register float STC2 = 10.0f * Conv.Ts;
    float kp_C = Conv.C / (alfa2 * STC2);
    float ti_C = alfa2 * alfa2 * STC2;

    Conv.PI_U.Ts_Ti = Conv.Ts / ti_C;
    Conv.PI_U.Kp = kp_C;
    Conv.PI_U.lim_H = Conv.I_lim;
    Conv.PI_U.lim_L = -Conv.I_lim;

    Conv.PI_U_filter.Ts_Ti = Conv.Ts / STC2;

    ///////////////////////////////////////////////////////////////////

	aState_global = aState;
}

#define TRIG_0 aState_global->inputs[0]
#define TRIG_180 aState_global->inputs[1]

//This function is automatically called every sample time
//output is written to DLL output port after the output delay
DLLEXPORT void plecsOutput(struct SimulationState* aState)
{
	if (TRIG_0 || TRIG_180)
	{
		Meas.U_out = aState_global->inputs[2];
        Meas.I_conv = aState_global->inputs[3];
        Meas.U_in = aState_global->inputs[4];

        Conv.I_out_ref = aState_global->inputs[7];
        Conv.U_out_ref = aState_global->inputs[8];

        if (!Conv.RDY)
        {
            aState_global->outputs[0] = 
            aState_global->outputs[1] =
            aState_global->outputs[2] =
            aState_global->outputs[3] = 0;
        }
        else
        {
            aState_global->outputs[0] = Conv.duty;
            aState_global->outputs[1] = 1.0 - Conv.duty;
            aState_global->outputs[2] = 0.0;
            aState_global->outputs[3] = 1.0;
        }

        static float first = 0;
		Converter_calc(++first >= 2000);

        aState_global->outputs[4] = Conv.PI_I.out;
        aState_global->outputs[5] = Meas.U_out;
        aState_global->outputs[6] = 0;

        aState_global->outputs[7] = Conv.PI_U.out;
        aState_global->outputs[8] = Meas.I_conv;
        aState_global->outputs[9] = 0;

        aState_global->outputs[10] = 0;
        aState_global->outputs[11] = 0;
        aState_global->outputs[12] = 0;
	}

	if (TRIG_180)
	{

	}
}
