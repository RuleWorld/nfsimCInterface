#include <cstdlib>

#include "nfsim_connector.h"
#include <NFapi.hh>

#ifdef __cplusplus
extern "C" {
#endif

// Inside this "extern C" block, I can define C functions that are able to call C++ code


int setupNFSim_c(const char* filename, int verbose) {
    return NFapi::setupNFSim(filename, verbose);
}

int resetSystem_c(){
    return NFapi::resetSystem();
}

int initSystemXML_c(const char * initXML){
    return NFapi::initSystemXML(std::string(initXML));
}


int initSystemNauty_c(const char** nautyString, const int* seedNumber, int numberOfElements){
    map<std::string, int> initMap;
    for(int i=0; i< numberOfElements; i++){
        initMap[std::string(nautyString[i])] = seedNumber[i];
    }

    NFapi::initSystemNauty(initMap);

}

queryResults querySystemStatus_c(const char* option){
    std::set<string> tmpResults;
    NFapi::querySystemStatus(std::string(option), tmpResults);
    queryResults query;
    query.results = (char**) malloc(tmpResults.size() * sizeof(char *));
    query.numOfResults = tmpResults.size();
    int index = 0;
    for(string it: tmpResults){
        query.results[index] = (char *)malloc(it.size()+1);
        memcpy(query.results[index], it.c_str(), it.size() + 1);
        index++;
    }

    return query;
}

#ifdef __cplusplus
}
#endif