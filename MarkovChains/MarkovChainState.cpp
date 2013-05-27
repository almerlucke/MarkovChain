//
//  MarkovChainState.cpp
//  MarkovChains
//
//  Created by Almer Lucke on 5/7/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include "MarkovChainState.h"


MarkovChainState::MarkovChainState(int stateID, int numTransitions, ...)
{
    va_list stateTransitionList;
    va_start(stateTransitionList, numTransitions);
    
    _stateID = stateID;
    _numTransitions = numTransitions;
    _transitions = new MarkovChainStateTransition[_numTransitions];
    _stateChangeFactorTotal = 0.0;
    
    for (int i = 0; i < numTransitions; i++) {
        _transitions[i].stateID = va_arg(stateTransitionList, int);
        _transitions[i].stateChangeFactor = va_arg(stateTransitionList, double);
        _stateChangeFactorTotal += _transitions[i].stateChangeFactor;
    }
    
    va_end(stateTransitionList);
}

MarkovChainState::~MarkovChainState()
{
    delete [] _transitions;
}

int MarkovChainState::stateID()
{
    return _stateID;
}

int MarkovChainState::nextStateID()
{
    double randomValue = ((double)arc4random() / 0x100000000) * _stateChangeFactorTotal;
    double stateChangeFactorAdder = 0.0;
    int stateTransitionID = -1;
    
    for (int i = 0; i < _numTransitions; i++) {
        stateChangeFactorAdder += _transitions[i].stateChangeFactor;
        if (randomValue < stateChangeFactorAdder) {
            stateTransitionID = _transitions[i].stateID;
            break;
        }
    }
    
    return stateTransitionID;
}