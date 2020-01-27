#ifndef _END_TURN_COMMAND_HPP
#define _END_TURN_COMMAND_HPP

#include "command.hpp"
#include "fightController.hpp"

class endTurnCommand : public command{
private:
    std::shared_ptr<fightController> fightControlPointer;
public:
    endTurnCommand(std::shared_ptr<fightController> fightControlPointer):
        fightControlPointer{fightControlPointer}
    {}

    void execute() override{
        fightControlPointer->nextTurn();
        std::cout << "ENDTURN++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
    }

    void undo() override{}
};

#endif

