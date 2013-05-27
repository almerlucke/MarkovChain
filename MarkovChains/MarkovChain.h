//
//  MarkovChain.h
//  MarkovChains
//
//  Created by Almer Lucke on 5/7/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#ifndef __MarkovChains__MarkovChain__
#define __MarkovChains__MarkovChain__

#include <iostream>
#include "MarkovChainState.h"

/*
 * Abstract MarkovChain class
 * 
 * - Use subclasses to create a concrete generateValue method
 * - Subclasses can use the _currentState ivar to decide which value to generate for the generateValue method
 * - The state transitions of a concrete subclass of MarkovChain must always be initialized with
 *   setStates besides the class's normal initialization, otherwise the MarkovChain will return 0.0 on all nextValue calls 
 */

class MarkovChain {
protected:
    int _numStates;
    bool _resetWhenFinished;
    MarkovChainState **_states;
    MarkovChainState *_currentState;
    MarkovChainState *_startState;
    
    // find a state by id
    MarkovChainState *findStateByID(int stateID);
    
public:
    MarkovChain();
    virtual ~MarkovChain();
    
    void setStates(int startStateID, int numStates, ...);
    
    void setResetWhenFinished(bool resetWhenFinished);
    bool resetWhenFinished();
    
    void reset();
    double nextValue();
    
    // override this by subclasses to generate a value based on the current state
    virtual double generateValue() = 0;
};

#endif /* defined(__MarkovChains__MarkovChain__) */
