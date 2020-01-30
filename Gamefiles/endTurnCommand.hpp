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
    std::shared_ptr<bool> allowedEndTurn;

public:
    endTurnCommand(fightController &fightControlPointer, std::shared_ptr<bool> allowedEndTurn):
        fightControlPointer(fightControlPointer),
        allowedEndTurn{allowedEndTurn}
    {}

    void execute() override{
        fightControlPointer.setAllowedToEnd(allowedEndTurn);
        fightControlPointer.nextTurn(1);
    }

    virtual void undo(){}
};

#endif

