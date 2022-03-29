%module matrixCommon

%{
#include "matrixCommon.h"
%}

/*适应 uint8_t这样的数值*/
%include "stdint.i"
/* Let's just grab the original header file here */
%include "matrixCommon.h"
