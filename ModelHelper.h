//
//  ModelHelper.h
//  cast advanced
//
//  Created by Joseph Delong on 6/14/17.
//  Copyright © 2017 txlabs. All rights reserved.
//

#ifndef ModelHelper_h
#define ModelHelper_h

#include "Model.h"
#include "Polygon.h"
#include "Vertex.h"
#include <vector>
#include <string>

class ModelHelper {
public:
    static Model* readBinarySTL(std::string &path);
    static Model* readBinarySTLThreaded(std::string &path, int &threadCount);
    static Polygon* readPolygon(int &begin, int &end, std::string &path);
};
Model* ModelHelper::readBinarySTL(std::string &path) {
    
    Model *model = new Model();
    
    char *buffer;
    buffer = (char *)malloc(sizeof(char)*41);
    
    uint32_t *polygonCount;
    polygonCount = (uint32_t *)malloc(sizeof(uint32_t));
    
    uint16_t *byteCount;
    byteCount = (uint16_t *)malloc(sizeof(uint16_t));
    
    FILE *ptr;
    
    ptr = fopen(path.c_str(),"rb");
    
    if(!ptr){
        throw std::invalid_argument( "File failed to open" );
    }
    else{
        fread(buffer,sizeof(uint8_t),80,ptr);
        buffer[40] = (char)NULL;
        
        model->name = new std::string(buffer);
        
        fread(polygonCount,sizeof(uint32_t),1,ptr);
        
        model->polygonCount = polygonCount;
        
        model->polygons = new Polygon[(int)*polygonCount];
        
        for(int i=0; i<*polygonCount; i++){
            
            Vertex *vertices = new Vertex[3];
            for(int j=0; j<4; j++){
                
                float *vertex = (float *)malloc(sizeof(float)*3);
                fread(vertex,sizeof(float),3,ptr);
                
                if(j!=0){
                    vertices[j-1].coordinates = vertex;
                }
                else{
                    free(vertex);
                }
                
            }
            model->polygons[i].vertices = vertices;
            
            fread(byteCount,sizeof(uint16_t),1,ptr);
            std::cout << std::endl;
        }
    }
    
    return model;
}

//Threaded Version
Model* ModelHelper::readBinarySTLThreaded(std::string &path, int &threadCount) {
    
    Model *model = new Model();
    
    char *buffer;
    buffer = (char *)malloc(sizeof(char)*41);
    
    uint32_t *polygonCount;
    polygonCount = (uint32_t *)malloc(sizeof(uint32_t));
    
    FILE *ptr = fopen(path.c_str(),"rb");
    
    if(!ptr){
        throw std::invalid_argument( "File failed to open" );
    }
    else{
        fread(buffer,sizeof(uint8_t),80,ptr);
        buffer[40] = NULL;
        
        model->name = new std::string(buffer);
        
        fread(polygonCount,sizeof(uint32_t),1,ptr);
        
        model->polygonCount = polygonCount;
        
        model->polygons = new Polygon[(int)*polygonCount];
        //std::array<Polygon, (int)*polygonCount> polygons;

        int polygonsPerThread = (int)(*polygonCount/threadCount);
        
        std::cout<< polygonsPerThread << std::endl;

        std::vector<Polygon> polygonList;


        for(int i=0; i<threadCount; i++){
            
            if(i+1==threadCount){
                
            }
            else{
                int begin = i*polygonsPerThread;
                int end = begin+polygonsPerThread-1;

                Polygon *polygon = ModelHelper::readPolygon(begin, end, path);
                //polygonList.insert(polygonList.end(), &polygon[0], &polygon[polygonsPerThread-1]);
            }
        }
        
    }
    fclose(ptr);
    return model;
}

Polygon* ModelHelper::readPolygon(int &begin, int &end, std::string &path){

    int polygonCount = (end-begin)+1;
    Polygon *polygons = new Polygon[polygonCount];

    int sizeOfHeader = sizeof(uint8_t)*80;
    int sizeOfPolygonCount = sizeof(uint32_t);

    int sizeOfPolygon = (sizeof(float)*12)+sizeof(uint16_t);

    int seekSize = begin*sizeOfPolygon;

    FILE *ptr;

    ptr = fopen(path.c_str(),"rb");

    if(!ptr){
        throw std::invalid_argument( "File failed to open" );
    }
    else{
        fseek(ptr, seekSize, sizeOfHeader+sizeOfPolygonCount);
        for(int i=0; i<polygonCount; i++){

            Vertex *vertices = new Vertex[3];

            for(int j=0; j<4; j++){

                float *vertex = (float*)malloc(sizeof(float)*3);

                fread(vertex,sizeof(float),3,ptr);

                if(j!=0){
                    vertices[j-1].coordinates = vertex;
                }
                else{

                    free(vertex);
                }
            }
            polygons[i].vertices = vertices;

            uint16_t buffer;
            fread(&buffer,sizeof(uint16_t),1,ptr);
        }
    }
    fclose (ptr);

    return polygons;
}


#endif /* ModelHelper_h */
