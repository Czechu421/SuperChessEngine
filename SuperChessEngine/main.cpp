#include "chess.hpp"
#include <fstream>

#include "usefullFunctions.cpp"
#include "negaMax.cpp"

#define INF std::numeric_limits<std::int16_t>::max()

using namespace chess;

int main() {
    bool debug = false;

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
            continue;
        }
        if (words[0] == "debug") {
            if (debug) {
                debug = false;
                std::cout << "Debugging off !!!" << std::endl;
                std::ofstream log("log.txt", std::ios::app);
                log << std::endl << "<--- END DEBUG LOG --->" << std::endl;
                log.close();
            }
            else {
                debug = true;
                std::cout << "Debugging on !!!" << std::endl;
                std::ofstream log("log.txt", std::ios::app);
                log << std::endl << "<--- NEW DEBUG LOG --->" << std::endl;
                log.close();
            }
            continue;
        }
        else if (words[0] == "quit") {
            std::cout << "Quiting!" << std::endl;
            break;
        }
        else if (words[0] == "isready") {
            std::cout << "readyok" << std::endl;
            continue;
        }
        else if (words[0] == "position") {
            std::string fen = words[2];
            if (words[1] == "fen") {
                for (int i = 3; i <= 7; i++) {
                    fen += " " + words[i];
                }
                if (debug) {
                    std::cout << "Fen: " << fen << std::endl;
                    std::ofstream log("log.txt", std::ios::app);
                    log << "Fen: " << fen << std::endl;
                    log.close();
                }
                board.setFen(fen);
            }
            else if (words[1] == "startpos") {
                board.setFen(chess::constants::STARTPOS);
                    for (int i = 3; i < words.size(); i++) {
                        board.makeMove(uci::uciToMove(board, words[i]));
                    }
            }
            continue;
        }
        else if (words[0] == "go") {
            std::int8_t depth = 4;

            Movelist moves;
            movegen::legalmoves(moves, board);

            Move bestMove;
            std::int16_t bestScore = -INF;

            if (debug) {
                std::ofstream log("log.txt", std::ios::app);
                std::cout << "Legal moves: " << moves.size() << std::endl;
                log << "Legal moves: " << moves.size() << std::endl;
                for (auto& move : moves) {
                    std::cout << uci::moveToUci(move) << " ";
                    log << uci::moveToUci(move) << " ";
                }
                std::cout << std::endl;
                log << std::endl;
                log.close();
            }

            for (auto& move : moves) {
                if (debug) {
                    std::ofstream log("log.txt", std::ios::app);
                    for(int i = 0; i < depth; i++) {
                        std::cout << "\t";
                        log << "\t";
                    }
                    std::cout << "Trying move: " << uci::moveToUci(move) << std::endl;
                    log << "Trying move: " << uci::moveToUci(move) << std::endl;
                    log.close();
                }
                board.makeMove(move);
                move.setScore(-negaMax(board, depth, debug));
                if (bestScore < move.score()) {
                    bestMove = move;
                    bestScore = move.score();
                }
                board.unmakeMove(move);
            }

            std::cout << "bestmove " << uci::moveToUci(bestMove) << std::endl;

            if (debug) {
                std::ofstream log("log.txt", std::ios::app);
                for (auto& move : moves) {
                    std::cout << std::endl << uci::moveToUci(move) << " " << move.score();
                    log << std::endl << uci::moveToUci(move) << " " << move.score();
                }
                std::cout << std::endl;
                log << std::endl;
                log.close();
            }
            continue;
        }
    }

    return 0;
}
