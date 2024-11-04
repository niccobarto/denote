//
// Created by nicco on 04/11/2024.
//

#ifndef DENOTE_OBSERVABLE_H
#define DENOTE_OBSERVABLE_H
#include "Observer.h"
#include <list>
using namespace std;
#endif //DENOTE_OBSERVABLE_H
class Observable{
public:
    virtual void addObserver(Observer* o)=0;
    virtual void removeObserver(Observer* o)=0;
    virtual void notify(){
        for(auto o:observers){
            o->update();
        }
    }
protected:
    list<Observer*> observers;
};