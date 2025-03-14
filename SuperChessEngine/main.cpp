#include "chess.hpp"

#include "usefullFunctions.cpp"

using namespace chess;

int main() {
    std::string line;

    Board board;

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
                board.setFen(fen);
            }
            else if (words[1] == "startpos") {
                board.setFen(STARTPOS);
                for (int i = 2; i < words.size(); i++) {
                    // todo: implement moving pieces after STARTPOS
                }
            }
        }
    }

    return 0;
}