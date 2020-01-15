#ifndef _SELECTEDCOMMAND_HPP
#define _SELECTEDCOMMAND_HPP

#include "command.hpp"
#include "memory"
#include "gameObject.hpp"
#include <iostream>

class selectedCommand : public command {
private:
    std::shared_ptr<gameObject> object;
public:
    selectedCommand( std::shared_ptr<gameObject> object ):
        object(object)
    {}

    void execute() override{
        object.get()->interact();
    }

    virtual void undo(){}
};


#endif