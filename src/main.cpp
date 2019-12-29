//
//  main.cpp
//  SimulatorSFML
//
//  Created by Samuel Arbibe on 18/11/2019.
//  Copyright © 2019 Samuel Arbibe. All rights reserved.
//

#include <iostream>
#include "Simulator/Engine.hpp"

int main(int argc, const char * argv[]) {
    
    Engine * engine;
    
    engine = new Engine(1500, 1500, "Simulator");
    
    engine->Start();
    
    return EXIT_SUCCESS;
}
