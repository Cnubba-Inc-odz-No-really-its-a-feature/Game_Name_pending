#ifndef _ENDTURNCOMMAND_HPP
#define _ENDTURNCOMMAND_HPP

#include "fightController.hpp"
#include "command.hpp"
#include <iostream>
#include <map>
#include "memory"
#include "E_turnPhase.hpp"

class endTurnCommand : public command{
private:
    fightController & fightControlPointer;

public:
    endTurnCommand(fightController &fightControlPointer):
        fightControlPointer(fightControlPointer)
    {}

    void execute() override{
        fightControlPointer.nextTurn(E_turnPhase::playerMoveAndChecks);
    }

    virtual void undo(){}
};

#endif

