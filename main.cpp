//
//  main.cpp
//  cast advanced
//
//  Created by Joseph Delong on 6/12/17.
//  Copyright © 2017 txlabs. All rights reserved.
//

#include <iostream>
#include <fstream>

#include <ctime>
#include "Model.h"
#include "ModelHelper.h"

using namespace std;



int main(int argc, const char * argv[]) {
    int threadCount = 6;
    clock_t begin = clock();
    
    string path = "/Users/jdelong/Google Drive/Dev/C++/Cast-Advanced/cast advanced/cast advanced/3DBenchy.stl";
    //Model *model = readFile(filePath);
    
    Model *model;
    
    try{
        model = ModelHelper::readBinarySTLThreaded(path, threadCount);
        //model = ModelHelper::readBinarySTL(path);
    }
    catch( const std::invalid_argument &e ){
        cerr << e.what() << endl;
    }
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    
    cout << "Time to open file: " << elapsed_secs << endl;
    /*
    cout << *model->name << endl;
    cout << *model->polygonCount << endl;
    
    /*for(int i=0; i<(int)*model->polygonCount; i++){
        for(int j=0; j<3; j++){
            cout << model->polygons[i].vertices[j].coordinates[0] << " " << model->polygons[i].vertices[j].coordinates[1] << " " << model->polygons[i].vertices[j].coordinates[2] << endl;
        }
    }*/
    return 0;
}
