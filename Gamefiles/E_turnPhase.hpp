#ifndef _E_TURNPHASE
#define _E_TURNPHASE

/// \brief
/// Defines an enum to track the current turnphase progression. nessesary for pasing the turn to be understandable
enum E_turnPhase{
    playerMoveAndChecks = 1,
    enemySummoning = 2,
    enemyMove = 3,
    fight = 4,
    drawHand = 5,
    wait = 6
};

#endif