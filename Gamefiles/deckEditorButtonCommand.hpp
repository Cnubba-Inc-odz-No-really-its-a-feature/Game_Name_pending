#ifndef _DECK_EDITOR_BUTTON_COMMAND_HPP
#define _DECK_EDITOR_BUTTON_COMMAND_HPP

#include "command.hpp"
#include "objectStorage.hpp"


/// \brief
/// Command for adding or removing cards from the deck
class deckEditorButtonCommand : public command{
private:
    objectStorage & gameObjectStorage;
    int cardID;
    int editInt;
public:
    deckEditorButtonCommand(objectStorage &gameObjectStorage, int cardID, int editInt):
        gameObjectStorage{gameObjectStorage},
        cardID(cardID),
        editInt(editInt)
    {}

    void execute() override{
        gameObjectStorage.deckEditor.changeCardCountInDeck(cardID, editInt);
    }

    void undo() override{}

};

#endif