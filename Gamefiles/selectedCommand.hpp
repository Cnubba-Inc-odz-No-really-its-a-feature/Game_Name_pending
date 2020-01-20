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
    {
        // std::cout << "Click made" << std::endl;
    }

    void execute() override{
        // std::cout << "who is this?" << std::endl;
        object->interact();
    }

    virtual void undo(){}
};


#endif