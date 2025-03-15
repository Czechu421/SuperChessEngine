#include "chess.hpp"

#define INT std::int16_t

using namespace chess;

static INT evaluate(const Board& board) {
const INT queenWeight = 1000;
const INT rookWeight = 525;
const INT bishopWeight = 350;
const INT knightWeight = 350;
const INT pawnWeight = 100;

INT materialScore = queenWeight		* (board.pieces(PieceType::QUEEN, Color::WHITE).count()		- board.pieces(PieceType::QUEEN, Color::BLACK).count())
				  + rookWeight		* (board.pieces(PieceType::ROOK, Color::WHITE).count()		- board.pieces(PieceType::ROOK, Color::BLACK).count())
				  + bishopWeight	* (board.pieces(PieceType::BISHOP, Color::WHITE).count()	- board.pieces(PieceType::BISHOP, Color::BLACK).count())
				  + knightWeight	* (board.pieces(PieceType::KNIGHT, Color::WHITE).count()	- board.pieces(PieceType::KNIGHT, Color::BLACK).count())
				  + pawnWeight		* (board.pieces(PieceType::PAWN, Color::WHITE).count()		- board.pieces(PieceType::PAWN, Color::BLACK).count());

INT score = materialScore;

if (board.sideToMove()) {
	score *= -1;
}

return score;
}
