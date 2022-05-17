%module cameralib

%{
#include "cameralib.h"
using namespace std;
%}

/*适应 uint8_t这样的数值*/
%include "stdint.i"
%include "std_vector.i"
%include "std_string.i"

// Instantiate templates used by example
namespace std{
%template(Uint8Vector) vector<uint8_t>;
}

/* Let's just grab the original header file here */
%include "cameralib.h"