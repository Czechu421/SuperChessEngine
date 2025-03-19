#ifndef SEARCH_HPP
#define SEARCH_HPP

#include "chess.hpp"

void search(const chess::Board& board, chess::Movelist& moves, std::int8_t depth, bool debug);

#endif // SEARCH_HPP