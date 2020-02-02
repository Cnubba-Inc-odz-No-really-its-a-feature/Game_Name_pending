#ifndef _COMMAND_HPP
#define _COMMAND_HPP
#include "gameObject.hpp"


///\brief
///virtual class that can be inhereted from in order to send diffrent types of commands to objects
class command{
public:
    /// \brief
    /// call to execute the command
    virtual void execute(){};
    ///\brief
    /// we dont track previous commands so this is unused
    virtual void undo(){};


};

///\brief
/// Not used anymore, since we cant jump
class jumpCommand : public command{
public:
    ///\brief
    /// Not used anymore, since we cant jump
    virtual void execute();
};




#endif