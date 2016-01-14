#include "nfsim_c.h"
#include <stdio.h>
#include <stdlib.h> 
int main() {
    //const char *species[1] = {"c:a~NO_STATE!4!2,c:l~NO_STATE!3,c:l~NO_STATE!3!0,m:Lig!2!1,m:Rec!0"};
    char* iSpecies = "c:a~NO_STATE!4!2,c:l~NO_STATE!3,c:l~NO_STATE!3!0,m:Lig!2!1,m:Rec!0";

    const char** species = malloc(1 * sizeof(char*));
    species[0] = iSpecies;
    const int seeds[1]= {1};
    int result = setupNFSim_c("example.mdlr.xml_total.xml", 0);
    if(result != 0){
        return -1;
    }
    
    printf("result %d\n",result);
    resetSystem_c();
    initSystemNauty_c(species, seeds, 1);
    queryResults query = querySystemStatus_c("complex");
    for (int i=0; i < query.numOfResults; i++){
        printf("%s\n",query.results[i]);
    }
    printf("<<<<\n");
    reactantQueryResults query2 = queryByNumReactant_c(1);
    stepSimulationRxn_c(query2.associatedReactions[0].reactionNames[0]);
    query = querySystemStatus_c("complex");
    for (int i=0; i < query.numOfResults; i++){
        printf("%s\n",query.results[i]);
    }


        
    /*
    reactantQueryResults query2 = initAndQueryByNumReactant_c(species, seeds, 1, 1);
    for (int i=0; i<query2.numOfResults; i++){
        printf("%s\n", query2.keys[i]);
        for(int j=0;j<query2.numOfAssociatedReactions[i]; j++){
            printf("-----\n");
            printf("\t%s: %f\n",query2.associatedReactions[i].reactionNames[j],query2.associatedReactions[i].rates[j]);
        }
    }

    queryResults query = querySystemStatus_c("complex");
    printf("%d\n",query.numOfResults);
    for (int i=0; i < query.numOfResults; i++){
        printf("%s\n",query.results[i]);
    }
    */
    //initAndQueryByNumReactant_c(species, seeds, 1, 1);


    //initAndQueryByNumReactant_c(species, seeds, 1, 1);

}