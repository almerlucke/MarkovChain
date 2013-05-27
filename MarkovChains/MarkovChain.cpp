//
//  MarkovChain.cpp
//  MarkovChains
//
//  Created by Almer Lucke on 5/7/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include "MarkovChain.h"



#pragma mark - Init/Dealloc

MarkovChain::MarkovChain()
{
    _states = NULL;
    _numStates = 0;
    _startState = NULL;
    _currentState = NULL;
    _resetWhenFinished = false;
}

MarkovChain::~MarkovChain()
{
    for (int i = 0; i < _numStates; i++) {
        delete _states[i];
    }
    
    if (NULL != _states) {
        delete[] _states;
    }
}

void MarkovChain::setStates(int startStateID, int numStates, ...)
{
    va_list stateList;
    va_start(stateList, numStates);

    _states = new MarkovChainState *[numStates];
    _numStates = numStates;

    for (int i = 0; i < numStates; i++) {
        _states[i] = va_arg(stateList, MarkovChainState *);
    }

    _startState = this->findStateByID(startStateID);
    _currentState = _startState;

    va_end(stateList);
}



#pragma mark - Utils
MarkovChainState *MarkovChain::findStateByID(int stateID)
{
    for (int i = 0; i < _numStates; i++) {
        if (_states[i]->stateID() == stateID) {
            return _states[i];
        }
    }
    
    return NULL;
}



#pragma mark - Reset

void MarkovChain::reset()
{
    _currentState = _startState;
}

void MarkovChain::setResetWhenFinished(bool resetWhenFinished)
{
    _resetWhenFinished = resetWhenFinished;
}

bool MarkovChain::resetWhenFinished()
{
    return _resetWhenFinished;
}



#pragma mark - Get Next Value

double MarkovChain::nextValue()
{
    double value = 0.0;
    
    if (NULL != _currentState) {
        value = this->generateValue();
        
        int stateTransitionID = _currentState->nextStateID();
        MarkovChainState *newState = this->findStateByID(stateTransitionID);
        
        if (NULL != newState) {
            _currentState = newState;
        } else if (_resetWhenFinished) {
            this->reset();
        }
    }
    
    return value;
}