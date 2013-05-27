//
//  MarkovChainState.h
//  MarkovChains
//
//  Created by Almer Lucke on 5/7/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#ifndef __MarkovChains__MarkovChainState__
#define __MarkovChains__MarkovChainState__

#include <iostream>

/*
 *  Markov Chain State Transition
 *
 *  - Marks a chance percentage to go to a certain state from an virtual current state
 *  - States are identified by an integer
 */

struct MarkovChainStateTransition {
    int stateID;
    double stateChangeFactor;
};


/*
 * Markov chain State
 *
 * - Specifies a specific state in the Markov Chain
 * - States are identified by an integer
 * - The transitions are the states this state can jump to
 * - The total stateChangeFactor is calculated by accumulating the stateChangeFactor from all transitions for this state
 * - The chance to jump to a certain state from this state is defined by the relative strength
 *   of a stateTransition's stateChangeFactor compared to the total stateChangeFactor for all stateTransitions
 */

class MarkovChainState {
private:
    double _stateChangeFactorTotal;
    int _numTransitions;
    int _stateID;
    MarkovChainStateTransition *_transitions;
    
public:
    MarkovChainState(int stateID, int numTransitions, ...);
    
    ~MarkovChainState();

    int stateID();
    int nextStateID();
};

#endif /* defined(__MarkovChains__MarkovChainState__) */
