#ifndef _CARD_SELECT_COMMAND_HPP
#define _CARD_SELECT_COMMAND_HPP

#include "command.hpp"
#include "fightController.hpp"

/// \brief
/// implemetation of command that handles when a card should be played
class cardSelectCommand : public command{
private:
    fightController& controlPointer;
    std::shared_ptr<unit> unitPointer;
public:
    ///\brief
    /// Saves the controller and the unit to be executed.
    cardSelectCommand(fightController& controlPointer, std::shared_ptr<unit> unitPointer):
        controlPointer{controlPointer},
        unitPointer{unitPointer}
    {
    }

    ///\brief
    /// places the unit on the board when exectuted.
    void execute() override{
        
        controlPointer.placeUnitOnBoard(unitPointer);
    }

    void undo() override{}

};

#endif