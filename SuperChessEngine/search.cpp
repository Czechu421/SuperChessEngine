#include "search.hpp"

#include "chess.hpp"
#include <fstream>

#include "negaMax.cpp"

using namespace chess;

void search(const Board& board, Movelist& moves, std::int8_t depth, bool debug) {
	Board boardCopy(board);

    for (auto& move : moves) {
        if (debug) {
            std::ofstream log("log.txt", std::ios::app);
            for (int i = 0; i < depth; i++) {
                log << "\t";
            }
            log << "Trying move: " << uci::moveToUci(move) << std::endl;
            log.close();
        }
        boardCopy.makeMove(move);
        move.setScore(-negaMax(boardCopy, depth, debug));
        boardCopy.unmakeMove(move);
    }
}
