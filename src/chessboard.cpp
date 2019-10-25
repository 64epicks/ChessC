#include <chessc.h>

using namespace ChessC;
using namespace Types;

// NOTE: when refering to 'left', 'right', 'up' or 'down'; the perspective is defined by the array:
/* 
            UP 
            Y --
        ---------------
       |r n b q k b n r|
       |p p p p p p p p|
       |               |        
  LEFT |               | RIGHT  |
       |               |        X
       |               |
       |P P P P P P P P|
       |R N B Q K B N R|
        ---------------
            DOWN
*/

Chessboard::Chessboard()
{
    Chessboard(NORMAL_START_POS); // Initialize chessboard with default staring position
}
Chessboard::Chessboard(BoardType type)
{
    switch (type)
    {
        case NORMAL:
            Chessboard(NORMAL_START_POS);
            return;
        case CHESS960:
            return;
    }
}
Chessboard::Chessboard(const char* FEN)
{
    std::vector<ChessSquare> row;
    for (int i = 0; i < 8; i++) 
    {
        Board.push_back(row);
        ChessSquare square;
        square.x = i;
        square.Piece = VACANT;
        square.Player = NONE;
        for (int t = 0; t < 8; t++)
        {
            square.y = t;
            Board[i].push_back(square);
        }
    }
    loadBoard(FEN);
}
ChessSquare *Chessboard::getSquare(chessposX_t x, chessposY_t y)
{
    if (x >= Board.size() || x < 0 || y >= Board[x].size() || y < 0) return nullptr;

    return &Board[x][y];
}