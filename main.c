#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 1000


typedef struct bounding_box {
    double minLat;
    double minLon;
    double maxLat;
    double maxLon;
} Bounding_box;

typedef struct link {
    int id;
    int node;
    int way;
    double length;
    double veg;
    double arch;
    double land;
    int POI;
} Link;

typedef struct node {
    int id;
    double lat;
    double lon;
    struct edge* edges;
} Node;

typedef struct way {
    int id;
    int node;
    char** property_keys;
    char** property_values;
    struct geom* geom;
    struct way* next;
} Way;

typedef struct edge {
    Node* dest;
    char** property_keys;
    char** property_values;
    int num_properties;
    struct edge* next;
} Edge;

typedef struct geom {
    double lat;
    double lon;
    struct geom* next;
} Geom;

FILE* fp = fopen("leeds.map", "rb");

uint32_t type, size;
while (fread(&type, sizeof(uint32_t), 1, fp) == 1 &&
    fread(&size, sizeof(uint32_t), 1, fp) == 1) {


    switch (type) {
    case 0: {
        bounding_t bounding;
        fread(&bounding, size, 1, fp);

        break;
    }

    case 1: {
        link_t link;
        fread(&link, size, 1, fp);

        break;
    }

    case 2: {  
        node_t node;
        fread(&node, size, 1, fp);

        break;
    }

    case 3: {
        way_t way;
        fread(&way, sizeof(int64_t) + sizeof(int32_t), 1, fp);
        way.nodes = (int64_t*)malloc(way.node_count * sizeof(int64_t));
        fread(way.nodes, sizeof(int64_t), way.node_count, fp);

        break;
    }

    case 4: {
        geom_t geom;
        fread(&geom, size, 1, fp);

        break;
    }
    }
}