#include "../include/hashmap.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size;
    long capacity;
    long current;
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

//Cambiamos la función para que ignore mayúsculas o minúsculas.
int is_equal(char *key1, char *key2) {
    if (key1 == NULL || key2 == NULL) return 0;

    while (*key1 && *key2) {
        if (tolower(*key1) != tolower(*key2))
            return 0;
        key1++;
        key2++;
    }
    return *key1 == *key2;
}


void insertMap(HashMap * map, char * key, void * value) {
    if ((float)map->size / map->capacity > 0.7) enlarge(map);
    
    unsigned long index = hash(key, map->capacity);
    unsigned long originalIndex = index;
    
    do{
        Pair *bucket = map->buckets[index];
        
        if(bucket == NULL || bucket->key == NULL){
            
            char *key_copy = strdup(key);
            Pair *newPair = createPair(key_copy, value);

            map->buckets[index] = newPair;
            map->current = index;
            map->size++;
            return;
        }

        if(is_equal(bucket->key,key)) return;

        index = (index + 1) % map->capacity;
    }while(originalIndex != index);
}

void enlarge(HashMap * map) {
    enlarge_called = 1;

    Pair **old_bucket = map->buckets;
    map->capacity *= 2;

    map->buckets = (Pair **) calloc(map->capacity, sizeof(Pair*));

    map->size = 0;
    map->current = -1;

    for(long i = 0; i < (map->capacity/2); i++){
        if(old_bucket[i] != NULL && old_bucket[i]->key != NULL) insertMap(map, old_bucket[i]->key, old_bucket[i]->value);     
    }
    free(old_bucket);
}

HashMap * createMap(long capacity) {
    HashMap *map = (HashMap *) malloc(sizeof(HashMap));
    map->buckets = (Pair **) calloc(capacity, sizeof(Pair *));
    map->capacity = capacity;
    map->current = -1;
    map->size = 0;
    return map;
}

void eraseMap(HashMap * map,  char * key) {    
    
    Pair *par = searchMap(map, key);

    if(par != NULL ){
        par->key = NULL;
        map->size--;
    }
}

Pair *searchMap(HashMap * map,  char * key) {   
    unsigned long index = hash(key, map->capacity);
    unsigned long originalIndex = index;

    while(1){
        Pair *bucket = map->buckets[index];
        if(bucket == NULL) return NULL;

        if(bucket != NULL && is_equal(bucket->key,key)){
            map->current = index;
            return bucket;
        }

        index = (index+1) % map->capacity;

        if(index == originalIndex) break;
    }
    
    return NULL;
}

Pair *firstMap(HashMap * map) {
    if (map == NULL || map->buckets == NULL) return NULL;

    for(unsigned long i = 0; i < map->capacity;i++){
        Pair *bucket = map->buckets[i];
        if(bucket != NULL && bucket->key != NULL){
            map->current = i;
            return bucket;
        }    
    }
    return NULL;
}

Pair *nextMap(HashMap * map) {
    if (map == NULL || map->buckets == NULL) return NULL;

    for(unsigned long i = (map->current + 1); i < map->capacity;i++){ // recorremos desde el current en vez desde la pos 0
        Pair *bucket = map->buckets[i];
        if(bucket != NULL && bucket->key != NULL){
            map->current = i;
            return bucket;
        }    
    }

    return NULL;
}

int sizeMap(HashMap *map) {
    return map->size;
}