#include "chess.hpp"

#define INT std::int16_t

using namespace chess;

static INT evaluate(const Board& board) {
INT score = 0;

const INT kingWeight = 20000;
const INT queenWeight = 1000;
const INT rookWeight = 525;
const INT bishopWeight = 350;
const INT knightWeight = 340;
const INT pawnWeight = 100;

const INT kingSquareBonusMIDDLE[64] = {
	-30,-40,-40,-50,-50,-40,-40,-30,
	-30,-40,-40,-50,-50,-40,-40,-30,
	-30,-40,-40,-50,-50,-40,-40,-30,
	-30,-40,-40,-50,-50,-40,-40,-30,
	-20,-30,-30,-40,-40,-30,-30,-20,
	-10,-20,-20,-20,-20,-20,-20,-10,
	 20, 20,  0,  0,  0,  0, 20, 20,
	 20, 30, 10,  0,  0, 10, 30, 20
};

const INT kingSquareBonusEND[64] = {
	-50,-40,-30,-20,-20,-30,-40,-50,
	-30,-20,-10,  0,  0,-10,-20,-30,
	-30,-10, 20, 30, 30, 20,-10,-30,
	-30,-10, 30, 40, 40, 30,-10,-30,
	-30,-10, 30, 40, 40, 30,-10,-30,
	-30,-10, 20, 30, 30, 20,-10,-30,
	-30,-30,  0,  0,  0,  0,-30,-30,
	-50,-30,-30,-30,-30,-30,-30,-50
};

const INT queenSquareBonus[64] = {
	-20,-10,-10, -5, -5,-10,-10,-20,
	-10,  0,  0,  0,  0,  0,  0,-10,
	-10,  0,  5,  5,  5,  5,  0,-10,
	 -5,  0,  5,  5,  5,  5,  0, -5,
	  0,  0,  5,  5,  5,  5,  0, -5,
	-10,  5,  5,  5,  5,  5,  0,-10,
	-10,  0,  5,  0,  0,  0,  0,-10,
	-20,-10,-10, -5, -5,-10,-10,-20
};

const INT rookSquareBonus[64] = {
  	 0,  0,  0,  0,  0,  0,  0,  0,
	 5, 10, 10, 10, 10, 10, 10,  5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
 	 0,  0,  0,  5,  5,  0,  0,  0
};

const INT bishopSquareBonus[64] = {
	-20,-10,-10,-10,-10,-10,-10,-20,
	-10,  0,  0,  0,  0,  0,  0,-10,
	-10,  0,  5, 10, 10,  5,  0,-10,
	-10,  5,  5, 10, 10,  5,  5,-10,
	-10,  0, 10, 10, 10, 10,  0,-10,
	-10, 10, 10, 10, 10, 10, 10,-10,
	-10,  5,  0,  0,  0,  0,  5,-10,
	-20,-10,-10,-10,-10,-10,-10,-20
};

const INT knightSquareBonus[64] = {
	-50,-40,-30,-30,-30,-30,-40,-50,
	-40,-20,  0,  0,  0,  0,-20,-40,
	-30,  0, 10, 15, 15, 10,  0,-30,
	-30,  5, 15, 20, 20, 15,  5,-30,
	-30,  0, 15, 20, 20, 15,  0,-30,
	-30,  5, 10, 15, 15, 10,  5,-30,
	-40,-20,  0,  5,  5,  0,-20,-40,
	-50,-40,-30,-30,-30,-30,-40,-50
};

const INT pawnSquareBonus[64] {
	 0,  0,  0,  0,  0,  0,  0,  0,
	50, 50, 50, 50, 50, 50, 50, 50,
	10, 10, 20, 30, 30, 20, 10, 10,
	 5,  5, 10, 25, 25, 10,  5,  5,
	 0,  0,  0, 20, 20,  0,  0,  0,
	 5, -5,-10,  0,  0,-10, -5,  5,
	 5, 10, 10,-20,-20, 10, 10,  5,
	 0,  0,  0,  0,  0,  0,  0,  0
};

Bitboard whiteKing = board.pieces(PieceType::KING, Color::WHITE);
Bitboard blackKing = board.pieces(PieceType::KING, Color::BLACK);
Bitboard whiteQueens = board.pieces(PieceType::QUEEN, Color::WHITE);
Bitboard blackQueens = board.pieces(PieceType::QUEEN, Color::BLACK);
Bitboard whiteRooks = board.pieces(PieceType::ROOK, Color::WHITE);
Bitboard blackRooks = board.pieces(PieceType::ROOK, Color::BLACK);
Bitboard whiteBishops = board.pieces(PieceType::BISHOP, Color::WHITE);
Bitboard blackBishops = board.pieces(PieceType::BISHOP, Color::BLACK);
Bitboard whiteKnights = board.pieces(PieceType::KNIGHT, Color::WHITE);
Bitboard blackKnights = board.pieces(PieceType::KNIGHT, Color::BLACK);
Bitboard whitePawns = board.pieces(PieceType::PAWN, Color::WHITE);
Bitboard blackPawns = board.pieces(PieceType::PAWN, Color::BLACK);

Bitboard whiteMinorPieces = whiteBishops | whiteKnights;
Bitboard blackMinorPieces = blackBishops | blackKnights;
Bitboard whiteMajorPieces = whiteQueens | whiteRooks;
Bitboard blackMajorPieces = blackQueens | blackRooks;

bool isEndgame = whiteMinorPieces.count() <= 1 && blackMinorPieces.count() <= 1 && whiteMajorPieces.count() <= 1 && blackMajorPieces.count() <= 1;

if (isEndgame) {
	if (whiteKing.empty() == false) {
		Square kingSquare(whiteKing.pop());
		score += kingWeight + kingSquareBonusEND[kingSquare.flip().index()];
	}

	if (blackKing.empty() == false) {
		Square kingSquare(blackKing.pop());
		score -= kingWeight + kingSquareBonusEND[kingSquare.flip().index()];
	}
}
else {
	if (whiteKing.empty() == false) {
		Square kingSquare(whiteKing.pop());
		score += kingWeight + kingSquareBonusMIDDLE[kingSquare.flip().index()];
	}

	if (blackKing.empty() == false) {
		Square kingSquare(blackKing.pop());
		score -= kingWeight + kingSquareBonusMIDDLE[kingSquare.flip().index()];
	}
}


while (whiteQueens.empty() == false) {
	Square queenSquare(whiteQueens.pop());
	score += queenWeight + queenSquareBonus[queenSquare.flip().index()];
}
while (blackQueens.empty() == false) {
	Square queenSquare(blackQueens.pop());
	score -= queenWeight + queenSquareBonus[queenSquare.flip().index()];
}

while (whiteRooks.empty() == false) {
	Square rookSquare(whiteRooks.pop());
	score += rookWeight + rookSquareBonus[rookSquare.flip().index()];
}
while (blackRooks.empty() == false) {
	Square rookSquare(blackRooks.pop());
	score -= rookWeight + rookSquareBonus[rookSquare.flip().index()];
}

while (whiteBishops.empty() == false) {
	Square bishopSquare(whiteBishops.pop());
	score += bishopWeight + bishopSquareBonus[bishopSquare.flip().index()];
}
while (blackBishops.empty() == false) {
	Square bishopSquare(blackBishops.pop());
	score -= bishopWeight + bishopSquareBonus[bishopSquare.flip().index()];
}

while (whiteKnights.empty() == false) {
	Square knightSquare(whiteKnights.pop());
	score += knightWeight + knightSquareBonus[knightSquare.flip().index()];
}
while (blackKnights.empty() == false) {
	Square knightSquare(blackKnights.pop());
	score -= knightWeight + knightSquareBonus[knightSquare.flip().index()];
}

while (whitePawns.empty() == false) {
	Square pawnSquare(whitePawns.pop());
	score += pawnWeight + pawnSquareBonus[pawnSquare.flip().index()];
}
while (blackPawns.empty() == false) {
	Square pawnSquare(blackPawns.pop());
	score -= pawnWeight + pawnSquareBonus[pawnSquare.flip().index()];
}


if (board.sideToMove()) {
	score *= -1;
}

return score;
}
