#include "chess.hpp"
#include <fstream>
#include <thread>
#include <vector>

#include "usefullFunctions.cpp"
#include "search.cpp"

#define INF std::numeric_limits<std::int16_t>::max()

using namespace chess;

int main() {
    bool debug = false;
	std::uint8_t threads = 2;
	std::int8_t depth = 6;

    std::string line;

    Board board;

    while (std::getline(std::cin, line)) {
        if (line.empty())
            continue;
        auto words = explode(line);

        if (words[0] == "uci") {
            std::cout << "id name SuperChessEngine" << std::endl;
            std::cout << "id author Czechu" << std::endl;
			std::cout << "option name Threads type spin default " << (int) threads << " min 1 max 255" << std::endl;
            std::cout << "option name Depth type spin default " << (int) depth << " min 1 max 255" << std::endl;
			std::cout << "option name Debug type check default false" << std::endl;
            std::cout << "uciok" << std::endl;
            continue;
        }
        else if (words[0] == "setoption") {
			if (words[1] == "name" && words[2] == "Threads") {
				threads = std::stoi(words[4]);
				std::cout << "info string Threads set to " << (int)threads << std::endl;
			}
			else if (words[1] == "name" && words[2] == "Depth") {
				depth = std::stoi(words[4]);
				std::cout << "info string Depth set to " << (int)depth << std::endl;
			}
			else if (words[1] == "name" && words[2] == "Debug") {
				debug = words[4] == "true";
				std::cout << "info string Debug set to " << (debug ? "true" : "false") << std::endl;
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
            if (words[1] == "fen") {
                std::string fen = words[2];
                for (int i = 3; i <= 7; i++) {
                    fen += " " + words[i];
                }
                if (debug) {
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
			std::int8_t depthCopy = depth;

            if (words.size() > 1)
                if (words[1] == "movetime" && words[2] == "10000") {
                    depthCopy = 4;
                    std::cout << "info string Depth set to " << (int)depthCopy << std::endl;
                }
            Movelist moves;
            movegen::legalmoves(moves, board);

            Move bestMove;
            std::int16_t bestScore = -INF;

            if (debug) {
                std::ofstream log("log.txt", std::ios::app);
                log << "Legal moves: " << moves.size() << std::endl;
                for (auto& move : moves) {
                    log << uci::moveToUci(move) << " ";
                }
                log << std::endl;
                log.close();
            }

            
			// MULTITHREADING

            std::vector<std::thread> threadPool;
            std::vector<Movelist> moveChunks(threads);

            for (size_t i = 0; i < moves.size(); ++i) {
                moveChunks[i % threads].add(moves[i]);
            }

            for (std::uint8_t i = 0; i < threads; ++i) {
                threadPool.emplace_back(search, std::cref(board), std::ref(moveChunks[i]), depthCopy, debug);
            }

            for (auto& thread : threadPool) {
                thread.join();
            }

			for (auto& moveChunk : moveChunks) {
				for (auto& move : moveChunk) {
					if (move.score() > bestScore) {
						bestScore = move.score();
						bestMove = move;
					}
				}
			}

            std::cout << "bestmove " << uci::moveToUci(bestMove) << std::endl;

            if (debug) {
                std::ofstream log("log.txt", std::ios::app);
                for (auto& moveChunk : moveChunks) {
                    for (auto& move : moveChunk) {
                        log << std::endl << uci::moveToUci(move) << " " << move.score();
                    }
                    log << std::endl;
                    log.close();
                }
            }
            continue;
        }
    }

    return 0;
}
