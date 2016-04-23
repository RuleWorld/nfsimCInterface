#ifndef NFSIM_C_STRUCTS_H 
#define NFSIM_C_STRCTS_H 




#ifdef __cplusplus
extern "C" {
#endif

    //C wrapper classes for C++ std objects we use for nfsim api calls
    void* map_create(); 
    const char* map_get(void* map, const char* key);
    void* mapvector_create();
    int mapvector_size(void*);
    void* mapvector_get(void* vector, int position);
    void mapvector_delete(void*);
    void* mapmapvector_create();
    void mapmapvector_delete(void* container);
    void* mapmapvector_get(void* container, char* reactant);

#ifdef __cplusplus
}
#endif

#endif