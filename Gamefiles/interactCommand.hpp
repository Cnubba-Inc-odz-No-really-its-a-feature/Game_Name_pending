#ifndef _INTERACT_COMMAND_HPP
#define _INTERACT_COMMAND_HPP

#include "command.hpp"
#include <iostream>
#include <map>
#include "memory"

class interactCommand : public command{
private:
    std::shared_ptr<gameObject> toInteractObject;

public:
    interactCommand(std::shared_ptr<gameObject> toInteractObject):
        toInteractObject(toInteractObject)
    {}

    void execute() override{

        toInteractObject.get()->interact();
    }

    void undo() override {}
};
#endif