#ifndef _EXITCOMMAND_HPP
#define _EXITCOMMAND_HPP

#include "command.hpp"
#include <iostream>
#include <map>
#include "memory"

class exitCommand : public command{
private:
    
public:
    exitCommand()
    {}

    void execute() override{
        std::cout << "exit command" << std::endl;
        exit(0);
    }

    virtual void undo(){}
};
#endif