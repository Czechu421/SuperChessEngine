#include "chess.hpp"

#include "usefullFunctions.cpp"
#include "negaMax.cpp"

#define INF std::numeric_limits<std::int16_t>::max()

using namespace chess;

int main() {
    std::string line;

    Board board;

    while (std::getline(std::cin, line)) {
        if (line.empty())
            continue;
        auto words = explode(line);

        if (words[0] == "uci") {
            std::cout << "id name SuperChessEngine" << std::endl;
            std::cout << "id author Czechu" << std::endl;
            std::cout << "uciok" << std::endl;
        }
        else if (words[0] == "quit") {
            std::cout << "Quiting!" << std::endl;
            break;
        }
        else if (words[0] == "isready") {
            std::cout << "readyok" << std::endl;
        }
        else if (words[0] == "position") {
            if (words[1] == "fen") {
                std::string fen = words[2];
                board.setFen(fen);
            }
            else if (words[1] == "startpos") {
                board.setFen(chess::constants::STARTPOS);
                    for (int i = 3; i < words.size(); i++) {
                        board.makeMove(uci::uciToMove(board, words[i]));
                    }
            }
        }
        else if (words[0] == "go") {
            std::int8_t depth = 5;

            Movelist moves;
            movegen::legalmoves(moves, board);

            Move bestMove;
            std::int16_t bestScore = -INF;

            for (auto& move : moves) {
                board.makeMove(move);
                move.setScore(negaMax(board, depth));
                if (bestScore < move.score()) {
                    bestMove = move;
                    bestScore = move.score();
                }
                board.unmakeMove(move);
            }

            std::cout << "bestmove " << uci::moveToUci(bestMove) << std::endl;
        }
    }

    return 0;
}
