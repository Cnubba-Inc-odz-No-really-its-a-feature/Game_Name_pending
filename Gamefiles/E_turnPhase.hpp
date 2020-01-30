#ifndef _E_TURNPHASE
#define _E_TURNPHASE

enum E_turnPhase{
    playerMoveAndChecks = 1,
    enemySummoning = 2,
    enemyMove = 3,
    fight = 4,
    drawHand = 5,
    wait = 6
};

#endif