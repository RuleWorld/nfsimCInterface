#ifndef NFSIM_CONNECTOR_H 
#define NFSIM_CONNECTOR_H 



#ifdef __cplusplus
extern "C" {
#endif


    //helper structures for the querying methods
    struct queryResults{
        int numOfResults;
        char** results;
    };

    struct reactionResult{
        char** reactionNames;
        double* rates;
    };

    struct observableResults{
        char** observableNames;
        double* observableValues;
        int numResults;
    };

    typedef struct queryResults queryResults;
    typedef struct reactionResult reactionResult;
    typedef struct observableResults observableResults;

    struct reactantQueryResults{
        int numOfResults;
        char** keys;
        int* numOfAssociatedReactions;
        reactionResult* associatedReactions;
    };

    struct queryOptions{
        const char** initKeys;
        const int* initValues;

        const char** optionKeys;
        char** optionValues;

        int numOfInitElements;
        int numOfOptions;
    };

    typedef struct queryOptions queryOptions;
    typedef struct reactantQueryResults reactantQueryResults;


    //loads up an xml file and keeps it in memory
    int setupNFSim_c(const char*,int);

    //restores the nfsim system before molecule seeding
    int resetSystem_c();
    //seeds the nfsim system with an xml string
    int initSystemXML_c(const char*);
    //seeds the nfsim system with an array of hnauty labels- int pairs
    int initSystemNauty_c(const char**, const int*, int);


    //update a seeding table that keeps track of molecules we will use to initialize the system
    int constructNauty_c(const char*, const int);

    //init a system from the incremental list
    int initFromConstruct_c();

    //returns those molecules in the system that are participants in a reaction with <param> reactants that can be fired
    reactantQueryResults queryByNumReactant_c(const int);

    //convenience function that calls reset, initNauty and queryByNumReactant
    reactantQueryResults initAndQueryByNumReactant_c(const queryOptions);

    //convenience function that calls reset, init, step and query
    queryResults initAndQuerySystemStatus_c(const queryOptions);


    //returns all possible complexes in the current system
    queryResults querySystemStatus_c(const char* option);

    observableResults queryObservables_c();

    //perform one simulation step
    int stepSimulation_c();
    //performs exactly one simulation step by firying reaction rxn
    int stepSimulationRxn_c(const char* rxn);

#ifdef __cplusplus
}
#endif


#endif