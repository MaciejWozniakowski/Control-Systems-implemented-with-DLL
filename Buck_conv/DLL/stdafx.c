

#include "stdafx.h"

struct Converter_struct Conv;

struct Measurements Meas;

struct trigonometric_struct sincos_table[SINCOS_HARMONICS];
struct trigonometric_struct sincos_table_comp[SINCOS_HARMONICS];
struct CIC1_adaptive_global_struct CIC1_adaptive_global;

struct SimulationState *aState_global;