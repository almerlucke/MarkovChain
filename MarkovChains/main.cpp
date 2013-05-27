//
//  main.cpp
//  MarkovChains
//
//  Created by Almer Lucke on 5/7/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include <iostream>
#include "MarkovChain.h"

/*
 * Concrete MarkovChain subclass
 * 
 * Use stateID as index into a value array to generate a value for the current state
 */

class LinearMarkovChain :public MarkovChain {
    double *_values;
    
public:
    LinearMarkovChain(int numValues, double *values) : MarkovChain()
    {
        _values = new double[numValues];
        
        for (int i = 0; i < numValues; i++) {
            _values[i] = values[i];
        }
    }
    
    ~LinearMarkovChain()
    {
        delete[] _values;
    }
    
    double generateValue()
    {
        return _values[_currentState->stateID()];
    }
};


int main(int argc, const char * argv[])
{
    double values[] = {10, 20, 30};
    LinearMarkovChain *chain = new LinearMarkovChain(3, values);
    MarkovChainState *state0 = new MarkovChainState(0, 2, 1, 0.9, 2, 0.1);
    MarkovChainState *state1 = new MarkovChainState(1, 2, 1, 0.5, 2, 0.5);
    MarkovChainState *state2 = new MarkovChainState(2, 2, 2, 0.5, 0, 0.5);
    
    chain->setStates(0, 3, state0, state1, state2);
    
    for (int i = 0; i < 100; i++) {
        printf("next value %lf\n", chain->nextValue());
    }
    
    delete chain;
    
    return 0;
}