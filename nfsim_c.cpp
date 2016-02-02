#include <cstdlib>

#include "nfsim_c.h"
#include <NFapi.hh>

map<string,int> preInitMap;

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

int initFromConstruct_c(){
    if(NFapi::initSystemNauty(preInitMap))
        return 0;
    return -1;
        
}


int constructNauty_c(const char* nautyString, const int seedNumber){
    if(preInitMap.find(nautyString) == preInitMap.end()){
        preInitMap[nautyString] = 0;
    }

    preInitMap[nautyString] = preInitMap[nautyString] + seedNumber;
    preInitMap[nautyString] = max(preInitMap[nautyString], 0);

    return 0;
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

            //finalResults.associatedReactions[idx].numReactants[idx2] = std::stoul(rxn["numReactants"],0,10);
            //finalResults.associatedReactions[idx].numProducts[idx2] = std::stoul(rxn["numProducts"],0,10);
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

observableResults queryObservables_c(){
    std::map<std::string, double> observables;
    observableResults results;
    results.observableNames = (char**) malloc(observables.size() * sizeof(char *));
    results.observableValues = (double*) malloc(observables.size() * sizeof(double));

    NFapi::queryObservables(observables);
    int idx = 0;
    for (auto it: observables){
        results.observableNames[idx] = (char *) malloc(it.first.size() + 1);
        memcpy(results.observableNames[idx], it.first.c_str(), it.first.size() + 1);
        results.observableValues[idx] = it.second;
        ++idx;
    }

    results.numResults = observables.size();
    return results;
}


queryResults initAndQuerySystemStatus_c(const queryOptions options_c){
    std::vector<string> tmpResults;
    NFapi::numReactantQueryIndex options;

    for(int i=0;i < options_c.numOfInitElements; i++)
    {
        options.initMap[options_c.initKeys[i]] = options_c.initValues[i];
    }

    for(int i=0; i< options_c.numOfOptions; i++)
    {
        options.options[options_c.optionKeys[i]] = std::string(options_c.optionValues[i]);

    }

    NFapi::initAndQuerySystemStatus(options, tmpResults);

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
    options.initMap.clear();
    options.options.clear();
    return query;

}


reactantQueryResults initAndQueryByNumReactant_c(const queryOptions options_c){
    NFapi::numReactantQueryIndex options;
    for(int i=0;i < options_c.numOfInitElements; i++)
    {
        options.initMap[options_c.initKeys[i]] = options_c.initValues[i];
    }

    for(int i=0; i< options_c.numOfOptions; i++)
    {
        options.options[options_c.optionKeys[i]] = options_c.optionValues[i];
    }

    std::map<std::string, vector<map<string,string>>> queryResults;
    NFapi::initAndQueryByNumReactant(options, queryResults);

    //translate results to a C friendly form
    reactantQueryResults finalResults = map2ReactantQueryResults(queryResults);
    //cleanup
    for(auto it: queryResults){
        it.second.clear();
    }

    queryResults.clear();
    options.initMap.clear();
    options.options.clear();

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