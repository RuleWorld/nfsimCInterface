#include "src/nfsim_c.h"
#include "src/nfsim_c_structs.h"
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

int main() {
    //const char *species[1] = {"c:a~NO_STATE!4!2,c:l~NO_STATE!3,c:l~NO_STATE!3!0,m:Lig!2!1,m:Rec!0"};
    //char* iSpecies = "c:l~NO_STATE!3!1,c:r~NO_STATE!2!0,m:L@EC!1,m:R@CP!0";
    char* iSpecies = "c:SH2~NO_STATE!5,c:U~NO_STATE!5!3,c:a~NO_STATE!6,c:b~Y!6!1,c:g~Y!6,m:Lyn@PM!0!1,m:Rec@PM!3!4!2,";
    const char** species = malloc(1 * sizeof(char*));
    species[0] = iSpecies;
    static const int seeds[1]= {1};
    int result = setupNFSim_c("fceri3.mdlr_total.xml", 0);
    //int result = setupNFSim_c("cbngl_test_empty.xml", 0);
    if(result != 0){
        return -1;
    }


    printf("result %d\n",result);
    //getCompartmentInformation_c("PM");
    resetSystem_c();
    //initSystemNauty_c(species, seeds, 1);
    constructNauty_c(iSpecies, 1);
    initFromConstruct_c();
    void* resultVector = mapvector_create();
    //void* reactionResultVector = reactionQuery_createContainer();

    querySystemStatus_c("complex", resultVector);
    for (int i=0; i < mapvector_size(resultVector); i++){
        //printf("\n----%s\n",query.results[i].label);
        void* individualResult = mapvector_get(resultVector, i);
        printf("\n----%s\n",map_get(individualResult,"label"));
        printf("\n----%s\n",map_get(individualResult,"diffusion_function"));
    }
    //logObservables_c(0);

    printf("<<<<\n");
    //reactantQueryResults query2 = queryByNumReactant_c(1);
 
    static const char* optionKeys[2]  = {"numReactants", "onlyActive"};
    static const char* optionValues[2] = {"2", "false"};
    //initialize speciesArray with the string we are going to query

    //copy these settings to the options object
    queryOptions options;
    options.initKeys = species;
    options.initValues = seeds;
    options.numOfInitElements = 1;

    //experiment design: query for reactions with 1 reactant
    options.optionKeys = optionKeys;
    options.optionValues = optionValues;
    options.numOfOptions =2;
    //reset, init, query the nfsim system
    printf("hello\n");
    void* reactionResultVector2 = mapmapvector_create();
    initAndQueryByNumReactant_c(options, reactionResultVector2);

    //printf("hello %d\n",query3.numOfResults);
    void* reactionsByReactant = mapmapvector_get(reactionResultVector2, "c:SH2~NO_STATE!5,c:U~NO_STATE!5!3,c:a~NO_STATE!6,c:b~Y!6!1,c:g~Y!6,m:Lyn@PM!0!1,m:Rec@PM!3!4!2,");

    int vectorsize = mapvector_size(reactionsByReactant);

    for (int i=0; i<vectorsize; i++){
        void* localMap = mapvector_get(reactionsByReactant, i);
        printf("-- %s\n",map_get(localMap,"name"));
        printf("---- %s\n",map_get(localMap,"rate"));
        printf("----- %s\n",map_get(localMap,"reactionDimensionality"));
    }
    mapmapvector_delete(reactionResultVector2);

    compartmentStruct tmp = getCompartmentInformation_c("PM");
    printf("bye %s %s\n",tmp.name,tmp.outside);
    //queryObservables_c();

    logNFSimObservables_c(1);
    outputNFSimObservables_c();

    void* resultVector2 = mapvector_create();

    initAndQuerySystemStatus_c(options, resultVector2);


    for (int i=0; i < mapvector_size(resultVector2); i++){
        //printf("\n----%s\n",query.results[i].label);
        void* individualResult = mapvector_create(resultVector, i);
        printf("\n+++++%s\n",map_get(individualResult,"label"));
    }

    mapvector_delete(resultVector2);

    /*stepSimulationRxn_c(query2.associatedReactions[0].reactionNames[0]);
    query = querySystemStatus_c("complex");
    for (int i=0; i < query.numOfResults; i++){
        printf("%s\n",query.results[i]);
    }*/


    /*queryOptions options;
    options.initKeys = species;
    options.initValues = seeds;
    options.numOfInitElements = 1;
    options.numOfOptions = 2;
    const char* optionKeys[2]  = {"reaction", "numReactants"};

    char* optionValues[2];
    optionValues[0] = malloc(sizeof(char) * strlen(query2.associatedReactions[0].reactionNames[0]));
    strcpy(optionValues[0],query2.associatedReactions[0].reactionNames[0]);
    optionValues[1] = "2";
    options.optionKeys = optionKeys;
    options.optionValues = optionValues;

    reactantQueryResults query3 = initAndQueryByNumReactant_c(options);
    for (int i=0; i<query3.numOfResults; i++){
        printf("%s\n", query3.keys[i]);
        for(int j=0;j<query3.numOfAssociatedReactions[i]; j++){
            printf("----- %d\n",query3.numOfAssociatedReactions[i]);
            printf("\t%s: %f\n",query3.associatedReactions[i].reactionNames[j],query3.associatedReactions[i].rates[j]);
        }
    }

    const char* optionKeys2[2] = {"systemQuery", "reaction"};
    char* optionValues2[2];
    optionValues2[0] = "complex";
    optionValues2[1] = malloc(sizeof(char) * strlen(query2.associatedReactions[0].reactionNames[0]));

    strcpy(optionValues2[1],query2.associatedReactions[0].reactionNames[0]);

    options.optionKeys = optionKeys2;
    options.optionValues = optionValues2;

    options.numOfOptions = 2;
    queryResults query4 = initAndQuerySystemStatus_c(options);

    for (int i=0; i < query4.numOfResults; i++){
        printf("''''''' %s\n",query4.results[i]);
    }
    */
    /*
    queryResults query = querySystemStatus_c("complex");
    printf("%d\n",query.numOfResults);
    for (int i=0; i < query.numOfResults; i++){
        printf("%s\n",query.results[i]);
    }
    */
    //initAndQueryByNumReactant_c(species, seeds, 1, 1);


    //initAndQueryByNumReactant_c(species, seeds, 1, 1);

}