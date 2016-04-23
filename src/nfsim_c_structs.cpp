#include "nfsim_c_structs.h"

#include <cstdlib>
#include <map>
#include <vector>


typedef std::map<std::string, std::string> Map;
typedef std::vector<Map*> MapVector;
typedef std::map<std::string, MapVector*> MapMapVector;

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

void* mapmapvector_create(){
    return reinterpret_cast<void*>(new MapMapVector);
}

void mapmapvector_delete(void* container){
    MapMapVector* tmp = reinterpret_cast<MapMapVector*> (container);
    for(auto it: *tmp){
        for(auto it2: *(it.second)){
            it2->clear();
        }
        it.second->clear();
    }

    tmp->clear();
    delete tmp;
}

void* mapmapvector_get(void* container, char* reactant){
    MapMapVector* tmp = reinterpret_cast<MapMapVector*>(container);
    std::string reactantStr(reactant);
    if(tmp->find(reactantStr) == tmp->end())
        return NULL;
    return reinterpret_cast<void*>(tmp->find(reactantStr)->second);

}

void mapvector_delete(void* container){
    MapVector* tmp = reinterpret_cast<MapVector*> (container);
    for(auto it: *tmp){
        it->clear();
    }
    tmp->clear();

    delete tmp;
}


int mapvector_size(void* container){
    MapVector* tmp = reinterpret_cast<MapVector*> (container);
    return tmp->size();
}

void* mapvector_get(void* container, int position){
    MapVector* tmp = reinterpret_cast<MapVector*> (container);
    return reinterpret_cast<void*> (tmp->at(position));
}

#ifdef __cplusplus
}
#endif