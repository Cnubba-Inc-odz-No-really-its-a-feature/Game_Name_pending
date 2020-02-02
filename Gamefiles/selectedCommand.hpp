#ifndef _SELECTEDCOMMAND_HPP
#define _SELECTEDCOMMAND_HPP

#include "command.hpp"
#include "memory"
#include "gameObject.hpp"
#include <iostream>

///\brief
/// Command used for selecting specific objects to interact with
class selectedCommand : public command {
private:
    std::shared_ptr<gameObject> object;
public:
    ///\brief
    /// Command used for selecting specific objects to interact with
    selectedCommand( std::shared_ptr<gameObject> object ):
        object(object)
    {}

    ///\brief
    /// Interacts with given object
    void execute() override{
        object->interact();
    }

    virtual void undo(){}
};


#endif