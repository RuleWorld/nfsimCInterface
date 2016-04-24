#include "nfsim_c_structs.h"

#include <cstdlib>
#include <map>
#include <vector>
#include <string.h>

typedef std::map<std::string, std::string> Map;
typedef std::vector<Map*> MapVector;
typedef std::map<std::string, MapVector*> MapVectorMap;

#ifdef __cplusplus
extern "C" {
#endif

const char* map_get(void* map, const char* key) {
        Map* m = reinterpret_cast<Map*> (map);
        std::string keyStr(key);
        if(m->find(keyStr) == m->end())
            return NULL;
        return m->find(keyStr)->second.c_str();
        //std::cout << "Key: " << k << " Value: " << m->find(k)->second <<'\n';
}


void* map_create() {
    return reinterpret_cast<void*> (new Map);
}

void* mapvector_create(){
    return reinterpret_cast<void*>(new MapVector);
}

void* mapvectormap_create(){
    return reinterpret_cast<void*>(new MapVectorMap);
}

void mapvectormap_delete(void* container){
    MapVectorMap* tmp = reinterpret_cast<MapVectorMap*> (container);
    for(auto it: *tmp){
        for(auto it2: *(it.second)){
            it2->clear();
            delete it2;
        }
        it.second->clear();
        delete it.second;
    }

    tmp->clear();
    delete tmp;
}

void* mapvectormap_get(void* container, char* reactant){
    MapVectorMap* tmp = reinterpret_cast<MapVectorMap*>(container);
    std::string reactantStr(reactant);
    if(tmp->find(reactantStr) == tmp->end())
        return NULL;
    return reinterpret_cast<void*>(tmp->find(reactantStr)->second);

}

char** mapvectormap_getKeys(void* container){
    char** results;
    MapVectorMap* tmp = reinterpret_cast<MapVectorMap*>(container);
    std::vector<std::string> keys;
    for(auto& it: *tmp){
        keys.emplace_back(it.first);
    }

    results = (char**) malloc(tmp->size() * sizeof(char*));
    int counter = 0;
    for(auto& it: keys){
        results[counter] = strdup(it.c_str());
        counter++;
    }

    keys.clear();

    return results;
}

void mapvector_delete(void* container){
    MapVector* tmp = reinterpret_cast<MapVector*> (container);
    for(auto it: *tmp){
        it->clear();
        delete it;
    }
    tmp->clear();

    delete tmp;
}


int mapvector_size(void* container){
    MapVector* tmp = reinterpret_cast<MapVector*> (container);
    return tmp->size();
}

int mapvectormap_size(void* container){
    MapVectorMap* tmp = reinterpret_cast<MapVectorMap*>(container);
    return tmp->size();
}

void* mapvector_get(void* container, int position){
    MapVector* tmp = reinterpret_cast<MapVector*> (container);
    return reinterpret_cast<void*> (tmp->at(position));
}

#ifdef __cplusplus
}
#endif