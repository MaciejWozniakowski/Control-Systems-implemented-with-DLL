// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"
#include "DllHeader.h"
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>

typedef UINT16 Uint16;
typedef UINT32 Uint32;
typedef UINT64 Uint64;
typedef INT64 int64;
typedef INT32 int32;
typedef INT16 int16;
 
#define Resonant_filter_calc_CLAasm Resonant_filter_calc 
#define Filter1_calc_CLAasm Filter1_calc 
#define PI_antiwindup_fast_ff_CLAasm PI_antiwindup_fast_ff 
#define PI_antiwindup_fast_CLAasm PI_antiwindup_fast 
#define PI_antiwindup_CLAasm PI_antiwindup 
#define Resonant_mult_calc_CLAasm Resonant_mult_calc 
#define CIC2_filter_CLAasm CIC2_filter 
#define CIC1_filter_CLAasm CIC1_filter 
#define Resonant_calc_CLAasm Resonant_calc 
#define CIC1_adaptive_filter_CLAasm CIC1_adaptive_filter 
#define CIC1_adaptive_global_CLAasm CIC1_adaptive_global_calc 

#define GPIO_SET(x) aState_global->outputs[x] = 1 
#define GPIO_CLEAR(x) aState_global->outputs[x] = 0 
#define GPIO_TOGGLE(x) aState_global->outputs[x] ^= 1 
#define GPIO_READ(x) 0 

#define SINCOS_HARMONICS 50
#define CIC_upsample1 10
#define CIC_upsample2 100

#include "Controllers.h"
#include "Converter.h"

struct Measurements
{
    float U_out;
    float I_conv;
	float U_in;
};

extern struct Measurements Meas;

extern struct trigonometric_struct sincos_table[SINCOS_HARMONICS];
extern struct trigonometric_struct sincos_table_comp[SINCOS_HARMONICS];
extern struct CIC1_adaptive_global_struct CIC1_adaptive_global;

extern struct SimulationState *aState_global;
// reference additional headers your program requires here
