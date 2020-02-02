#ifndef _INTERACT_COMMAND_HPP
#define _INTERACT_COMMAND_HPP

#include "command.hpp"
#include <iostream>
#include <map>
#include "memory"

///\brief
/// an implementation of command that interacts with given objects upon execution
class interactCommand : public command{
private:
    std::shared_ptr<gameObject> toInteractObject;

public:
    ///\brief
    /// saves a obj to interact with
    interactCommand(std::shared_ptr<gameObject> toInteractObject):
        toInteractObject(toInteractObject)
    {}

    ///\brief
    /// interacts with the saved object
    void execute() override{

        toInteractObject.get()->interact();
    }

};
#endif