#include <chessc.h>

using namespace ChessC;
using namespace Types;

Move Chessboard::findBestMove(const char* FEN)
{
    Chessboard board(FEN);
    return findBestMove(&board);
}
Move Chessboard::findBestMove(Chessboard* board)
{
    
}