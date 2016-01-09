#include "nfsim_connector.h"
#include <stdio.h>

int main() {
    const char *species[1] = {"c:a~NO_STATE!4!2,c:l~NO_STATE!3,c:l~NO_STATE!3!0,m:Lig!2!1,m:Rec!0"};
    const int seeds[1]= {1};
    int result = setupNFSim_c("example.mdlr.xml_total.xml", 0);
    resetSystem_c();
    initSystemNauty_c(species, seeds, 1);
    queryResults query = querySystemStatus_c("complex");
    for (int i=0; i < query.numOfResults; i++){
        printf("%s\n",query.results[i]);
    }
    printf("<<<<\n");
    reactantQueryResults query2 = queryByNoReactant_c(1);
    for (int i=0; i<query2.numOfResults; i++){
        printf("%s\n", query2.keys[i]);
        for(int j=0;j<query2.numOfAssociatedReactions[i]; j++){
            printf("-----\n");
            printf("\t%s: %s\n",query2.associatedReactions[i].reactionNames[j],query2.associatedReactions[i].rates[j]);
        }
    }

}