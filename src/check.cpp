#include <chessc.h>

using namespace ChessC;
using namespace Types;

bool Chessboard::isValid(chessposX_t initialX, chessposY_t initialY, chessposX_t finalX, chessposY_t finalY)
{
    if (initialX < 0 || initialX > 7 || initialY < 0 || initialX > 7 || finalX < 0 || finalX > 7 || finalY < 0 || finalX > 7) return false;
    Move tempMove;
    ChessSquare *initSq = getSquare(initialX, initialY);
    ChessSquare *finSq  = getSquare(finalX, finalY);
    tempMove.Piece = initSq->Piece;
    tempMove.PieceTarget = finSq->Piece;
    tempMove.Player = initSq->Player;
    tempMove.PlayerTarget = finSq->Player;
    tempMove.x = initSq->x;
    tempMove.y = initSq->y;
    tempMove.xTarget = finSq->x;
    tempMove.yTarget = finSq->y;
    return isValid(tempMove);
}
bool Chessboard::isValid(Move move)
{
    switch (move.Piece)
    {
        case KING:
            {
                if (move.x - move.xTarget <= 1 && move.x - move.xTarget >= -1 && move.y - move.yTarget <= 1 && move.y - move.yTarget >= -1 && move.PlayerTarget != move.Player && !isCheck(move.Player, move))
                {
                    return true;
                }
                else return false;
                break;
            }
        case QUEEN:
            {
                break;
            }
        case ROOK:
            {
                break;
            }
        case KNIGHT:
            {
                break;
            }
        case BISHOP:
            {
                break;
            }
        case PAWN:
            {
                break;
            }
        default:
            return false;
    }
}
bool isCheck(Types::PlayerType side)
{

}
bool Chessboard::isCheck(Types::PlayerType side, Move move)
{

}