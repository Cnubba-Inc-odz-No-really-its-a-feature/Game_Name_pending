#ifndef _COMMAND_HPP
#define _COMMAND_HPP
#include "gameObject.hpp"


class command{
public:
    virtual ~command() {}
    virtual void execute(){}
    virtual void undo() = 0;


};

class jumpCommand : public command{
public:
    virtual void execute();
};




#endif