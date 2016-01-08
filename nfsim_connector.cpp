#include <cstdlib>

#include "nfsim_connector.h"
#include <NFapi.hh>

#ifdef __cplusplus
extern "C" {
#endif

// Inside this "extern C" block, I can define C functions that are able to call C++ code


int setupNFSim_c(char* filename, int verbose) {
    return NFapi::setupNFSim(filename, verbose);
}


#ifdef __cplusplus
}
#endif