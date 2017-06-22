//
//  Model.h
//  cast advanced
//
//  Created by Joseph Delong on 6/14/17.
//  Copyright © 2017 txlabs. All rights reserved.
//

#ifndef Model_h
#define Model_h

#include "Polygon.h"
#include <string>
#include <vector>

class Model {
public:
    Model();
    
    std::string *name;
    uint32_t *polygonCount;
    Polygon *polygons;
    
    float *xMax;
    float *xMin;
    
    float *yMax;
    float *yMin;
    
    float *zMax;
    float *zMin;
};

Model::Model() {
}

#endif /* Model_h */
