#ifndef _CARD_SELECT_COMMAND_HPP
#define _CARD_SELECT_COMMAND_HPP

#include "command.hpp"
#include "fightController.hpp"

class cardSelectCommand : public command{
private:
    std::shared_ptr<fightController> controlPointer;
    std::shared_ptr<unit> unitPointer;
public:
    cardSelectCommand(std::shared_ptr<fightController> controlPointer, std::shared_ptr<unit> unitPointer):
        controlPointer{controlPointer},
        unitPointer{unitPointer}
    {
        std::cout<<"CardSelectcommand created for damage: " << unitPointer->getDamage()<< std::endl;
    }

    void execute() override{
        std::cout<<"poep" << unitPointer->getDamage()<<std::endl;

        controlPointer->placeUnitOnBoard(unitPointer);
    }

    void undo() override{}

};

#endif