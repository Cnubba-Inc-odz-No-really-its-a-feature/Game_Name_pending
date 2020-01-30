#ifndef _E_TURNPHASE
#define _E_TURNPHASE

enum class E_turnPhase{
    playerMoveAndChecks,
    enemySummoning,
    enemyMove,
    fight,
    drawHand,
    wait
};

#endif