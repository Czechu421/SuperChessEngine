#include "chess.hpp"

#include "usefullFunctions.cpp"

using namespace chess;

int main() {
    std::string line;

    while (std::getline(std::cin, line)) {
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
                std::cout << "FEN: " << fen << std::endl;
            }
            else if (words[1] == "startpos") {
                std::cout << "moves: " << std::endl;
                for (int i = 2; i < words.size(); i++) {
                    std::cout << words[i] << " ";
                }
                std::cout << std::endl;
            }
        }
    }

    return 0;
}