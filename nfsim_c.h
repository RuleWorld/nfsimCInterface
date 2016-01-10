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
        char** rates;
    };

    typedef struct queryResults queryResults;
    typedef struct reactionResult reactionResult;

    struct reactantQueryResults{
        int numOfResults;
        char** keys;
        int* numOfAssociatedReactions;
        reactionResult* associatedReactions;
    };

    typedef struct reactantQueryResults reactantQueryResults;


    //loads up an xml file and keeps it in memory
    int setupNFSim_c(const char*,int);

    //restores the nfsim system before molecule seeding
    int resetSystem_c();
    //seeds the nfsim system with an xml string
    int initSystemXML_c(const char*);
    //seeds the nfsim system with an array of hnauty labels- int pairs
    int initSystemNauty_c(const char**, const int*, int);
    //returns those molecules in the system that are participants in a reaction with <param> reactants that can be fired
    reactantQueryResults queryByNoReactant_c(const int);

    //returns all possible complexes in the current system
    queryResults querySystemStatus_c(const char* option);


#ifdef __cplusplus
}
#endif


#endif