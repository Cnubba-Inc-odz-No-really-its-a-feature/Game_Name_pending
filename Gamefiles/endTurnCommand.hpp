#ifndef _ENDTURNCOMMAND_HPP
#define _ENDTURNCOMMAND_HPP

#include "fightController.hpp"
#include "command.hpp"
#include <iostream>
#include <map>
#include "memory"

class endTurnCommand : public command{
private:
    fightController & fightControlPointer;

public:
    endTurnCommand(fightController &fightControlPointer):
        fightControlPointer(fightControlPointer)
    {}

    void execute() override{
        fightControlPointer.nextTurn();
    }

    virtual void undo(){}
};

#endif

