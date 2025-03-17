#include "chess.hpp"
#include <fstream>

#include "evaluation.cpp"

#define INT std::int16_t
#define INF std::numeric_limits<std::int16_t>::max()

using namespace chess;

static INT negaMax(Board& board, INT depth, bool debug) {
	// Checking if game is ended by fifty move rule
	if (board.isHalfMoveDraw())
		return board.getHalfMoveDrawType().first == GameResultReason::CHECKMATE ?
		-INF : 0;

	// Checking if game is drawn by position repetition rule
	if (board.isRepetition(1))
		return 0;


	// From now on starting to calculate best move to play
	if (depth == 0) { // if reached max depth evaluate position
		if (debug) {
			std::ofstream log("log.txt", std::ios::app);
			for(int i = 0; i < depth; i++)
				log << "\t";
			log << "Evaluating position " << evaluate(board) << std::endl;
			log.close();
		}
		return evaluate(board);
	}

	Movelist moves;
	movegen::legalmoves(moves, board);
	INT max = -INF;

	for (const auto& move : moves) {
		if (debug) {
			std::ofstream log("log.txt", std::ios::app);
			for(int i = 0; i < depth; i++)
				log << "\t";
			log << "Trying move: " << uci::moveToUci(move) << std::endl;
			log.close();
		}
		board.makeMove(move);
		INT score = -negaMax(board, depth - 1, debug);
		board.unmakeMove(move);

		if (score > max)
			max = score;
	}


	// No moves means game over
	if (moves.empty()) 
		return board.inCheck() ? -INF : 0;

	return max;
}
