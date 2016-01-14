#include <cstdlib>

#include "nfsim_c.h"
#include <NFapi.hh>

#ifdef __cplusplus
extern "C" {
#endif

// Inside this "extern C" block, I can define C functions that are able to call C++ code


int setupNFSim_c(const char* filename, int verbose) {
    //nfapi returns bool
    if(NFapi::setupNFSim(filename, verbose))
        return 0;
    return -1;
}

int resetSystem_c(){
    if(NFapi::resetSystem())
        return 0;
    return -1;
}

int initSystemXML_c(const char * initXML){
    if(NFapi::initSystemXML(std::string(initXML)))
        return 0;
    return -1;
}


int initSystemNauty_c(const char** nautyString, const int* seedNumber, int numberOfElements){
    map<std::string, int> initMap;
    for(int i=0; i< numberOfElements; i++){
        initMap[std::string(nautyString[i])] = seedNumber[i];
    }
    if(NFapi::initSystemNauty(initMap))
        return 0;
    return -1;
}

queryResults querySystemStatus_c(const char* option){
    std::vector<string> tmpResults;
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

    tmpResults.clear();

    return query;
}



reactantQueryResults map2ReactantQueryResults(const std::map<std::string, vector<map<string,string>>> &queryResults){

    reactantQueryResults finalResults;
    finalResults.numOfResults = queryResults.size();
    finalResults.keys = (char**) malloc(queryResults.size() * sizeof(char *));
    finalResults.numOfAssociatedReactions = (int*) malloc(queryResults.size() * sizeof(int));
    finalResults.associatedReactions = (reactionResult*) malloc(queryResults.size() * sizeof(reactionResult));

    int idx = 0;
    int idx2 = 0;
    for(auto it: queryResults){
        finalResults.keys[idx] = (char *) malloc(it.first.size() + 1);
        memcpy(finalResults.keys[idx], it.first.c_str(), it.first.size() + 1);
        finalResults.numOfAssociatedReactions[idx] = it.second.size();
        finalResults.associatedReactions[idx].reactionNames = (char**) malloc(it.second.size() * sizeof(char*));
        finalResults.associatedReactions[idx].rates = (double*) malloc(it.second.size() * sizeof(double));
        idx2 = 0;


        for(auto rxn: it.second){
            finalResults.associatedReactions[idx].reactionNames[idx2] = (char*) malloc(rxn["name"].size() + 1);
            memcpy(finalResults.associatedReactions[idx].reactionNames[idx2], rxn["name"].c_str(), rxn["name"].size() + 1);

            finalResults.associatedReactions[idx].rates[idx2] = std::stod(rxn["rate"]);
            ++idx2;
        }
        ++idx;
    }
    return finalResults;    
}


reactantQueryResults queryByNumReactant_c(const int numReactants){
    std::map<std::string, vector<map<string,string>>> queryResults;
    NFapi::queryByNumReactant(queryResults, numReactants);

    reactantQueryResults finalResults = map2ReactantQueryResults(queryResults);

    //cleanup
    for(auto it: queryResults){
        it.second.clear();
    }
    queryResults.clear();

    return finalResults;
}


reactantQueryResults initAndQueryByNumReactant_c(const char** nautyString, const int* seedNumber, const int numberOfElements, 
                                                 const int numberOfReactants){
    map<std::string, int> initMap;
    for(int i=0; i< numberOfElements; i++){
        initMap[std::string(nautyString[i])] = seedNumber[i];
    }
    std::map<std::string, vector<map<string,string>>> queryResults;
    NFapi::initAndQueryByNumReactant(initMap, queryResults, numberOfReactants);

    reactantQueryResults finalResults = map2ReactantQueryResults(queryResults);
    //cleanup
    for(auto it: queryResults){
        it.second.clear();
    }

    queryResults.clear();
    initMap.clear();

    return finalResults;

}

int stepSimulation_c(){
    if(NFapi::stepSimulation())
        return 0;
    return 1;

}

int stepSimulationRxn_c(const char* rxn){
    if(NFapi::stepSimulation(string(rxn))){
        return 0;
    }
    return 1;
}

#ifdef __cplusplus
}
#endif