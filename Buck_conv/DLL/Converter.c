

#include "stdafx.h"

void Converter_calc(float enable)
{
    ////////////////////////////////////////////////////////////////////////////////////////////

    if (!enable)
    {
        Conv.RDY = 0.0f;

        Conv.PI_U.integrator = 0.0f;
        Conv.PI_I.integrator = Meas.U_out;
    }
    else
    {
        Conv.RDY = 1;

        register float error_U_C = Conv.U_out_ref - Meas.U_out;
        PI_antiwindup_fast_CLAasm(&Conv.PI_U, error_U_C);
        Filter1_calc_CLAasm(&Conv.PI_U_filter, Conv.PI_U.out);

        register float error_I_L = Conv.PI_U_filter.out - Meas.I_conv;
        //error_I_L = Conv.set_current_gain - Meas.I_conv;
        Conv.PI_I.lim_H = Meas.U_in;
        PI_antiwindup_fast_CLAasm(&Conv.PI_I, error_I_L);

        Conv.U_ref = Conv.PI_I.out;

        //////////////////////////////////////////////////////////////////////////////////
        
        register float div_U_C = 1.0f / Meas.U_in;
        Conv.duty = (Conv.U_ref) * div_U_C;
    }
}
