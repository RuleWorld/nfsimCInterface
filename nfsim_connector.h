#ifndef NFSIM_CONNECTOR_H 
#define NFSIM_CONNECTOR_H 

#ifdef __cplusplus
extern "C" {
#endif

    struct queryResults{
        int numOfResults;
        char** results;
    };

    struct reactionResult{
        char* reactionName;
        char* rate;
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



    int setupNFSim_c(const char*,int);
    int resetSystem_c();
    int initSystemXML_c(const char*);
    int initSystemNauty_c(const char**, const int*, int);
    reactantQueryResults queryByNoReactant_c(const int);
    queryResults querySystemStatus_c(const char*);

#ifdef __cplusplus
}
#endif


#endif