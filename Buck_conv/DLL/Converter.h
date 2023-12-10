

#include "stdafx.h"

#pragma once
#ifndef Converter_H_
#define Converter_H_

struct Converter_struct
{
    float U_out_ref;
    float I_out_ref;
    struct PI_struct PI_I;
    struct PI_struct PI_U;
    struct Filter1_struct PI_U_filter;

    float U_ref;

    float Ts;
    float I_lim;
    float L_conv;
    float C;

    float duty;
    float RDY;
};

extern struct Converter_struct Conv;

void Converter_calc(float enable);

#endif /* Converter_H_ */
