//
//  ToggleTrafficExample.h
//  ExampleApp
//
//  Created by eeGeo on 14/05/2013.
//  Copyright (c) 2013 eeGeo. All rights reserved.
//

#ifndef __ExampleApp__ToggleTrafficExample__
#define __ExampleApp__ToggleTrafficExample__

#include "IExample.h"
#include "Traffic.h"

namespace Examples
{
    class ToggleTrafficExample : public IExample
    {
    private:
        long long lastToggle;
        Eegeo::Traffic::TrafficSimulationController& trafficSimulation;
        
    public:
        ToggleTrafficExample(Eegeo::Traffic::TrafficSimulationController& trafficSimulation);
        
        void Start() {}
        void Update(float dt);
        void Draw() {}
        void Suspend() {}
    };
}

#endif /* defined(__ExampleApp__ToggleTrafficExample__) */
