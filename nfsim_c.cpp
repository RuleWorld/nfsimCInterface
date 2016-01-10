#include <cstdlib>

#include "nfsim_c.h"
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

    tmpResults.clear();

    return query;
}

reactantQueryResults queryByNoReactant_c(const int numReactants){
    std::map<std::string, vector<map<string,string>>> queryResults;
    NFapi::queryByNoReactant(queryResults, numReactants);
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
        finalResults.associatedReactions[idx].rates = (char**) malloc(it.second.size() * sizeof(char*));


        idx2 = 0;


        for(auto rxn: it.second){
            finalResults.associatedReactions[idx].reactionNames[idx2] = (char*) malloc(rxn["name"].size() + 1);
            memcpy(finalResults.associatedReactions[idx].reactionNames[idx2], rxn["name"].c_str(), rxn["name"].size() + 1);

            finalResults.associatedReactions[idx].rates[idx2] = (char*) malloc(rxn["rate"].size() + 1);
            memcpy(finalResults.associatedReactions[idx].rates[idx2], rxn["rate"].c_str(), rxn["rate"].size() + 1);
            ++idx2;
        }
        ++idx;
    }

    //cleanup
    for(auto it: queryResults){
        it.second.clear();
    }
    queryResults.clear();

    return finalResults;
}


#ifdef __cplusplus
}
#endif