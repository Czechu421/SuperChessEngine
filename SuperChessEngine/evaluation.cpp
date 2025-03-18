#include "chess.hpp"

#define INT std::int16_t

using namespace chess;

static INT evaluate(const Board& board) {
INT score = 0;

const INT queenWeight = 1000;
const INT rookWeight = 525;
const INT bishopWeight = 350;
const INT knightWeight = 350;
const INT pawnWeight = 100;

// NEW EVALUATION HERE

if (board.sideToMove()) {
	score *= -1;
}

return score;
}
