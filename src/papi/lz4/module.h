#ifndef __CINT_LZ4_MODULE__
#define __CINT_LZ4_MODULE__
#pragma once

#include <pybind11/pybind11.h>

#include "api.h"    

namespace lz4 {

    class context {
        context();
        ~context();
    };

};
#endif // __CINT_LZ4_MODULE__