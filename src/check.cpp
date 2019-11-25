#include <chessc.h>
#include <stdlib.h>

using namespace ChessC;
using namespace Types;

bool Chessboard::isValid(chessposX_t initialX, chessposY_t initialY, chessposX_t finalX, chessposY_t finalY, bool check)
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
    return isValid(tempMove, check);
}
bool Chessboard::isValid(Move move, bool check)
{
    if (check && isCheck(move.Player, move)) return false;
    if (move.x == move.xTarget && move.y == move.yTarget) return false;
    if (move.PlayerTarget == move.Player) return false;
    switch (move.Piece)
    {
        case KING:
            {
                if (move.x - move.xTarget <= 1 && move.x - move.xTarget >= -1 && move.y - move.yTarget <= 1 && move.y - move.yTarget >= -1)
                {
                    return true;
                }
                else return false;
                break;
            }
        case QUEEN:
            {
                if (move.x == move.xTarget || move.y == move.yTarget)
                {
                    // Rook
                    if (move.x == move.xTarget)
                    {
                        chessposX_t i;
                        if (move.x - move.xTarget < 0) i = move.x + 1;
                        else i = move.x - 1;

                        while (i != move.xTarget)
                        {
                            if (getSquare(i, move.x)->Piece != VACANT) return false;
                            if (move.x - move.xTarget < 0) i++;
                            else i--;
                        } 
                        return true;
                    }
                    else
                    {
                        chessposY_t i;
                        if (move.y - move.yTarget < 0) i = move.y + 1;
                        else i = move.y - 1;

                        while (i != move.yTarget)
                        {
                            if (getSquare(move.x, i)->Piece != VACANT) return false;
                            if (move.y - move.yTarget < 0) i++;
                            else i--;
                        }
                        return true;
                    }
                }
                else
                {
                    // Bishop
                    if (abs(move.x - move.xTarget) != abs(move.y - move.yTarget)) return false;

                    chessposX_t x;
                    chessposY_t y;

                    if (move.x - move.xTarget < 0) x = move.x + 1;
                    else x = move.x - 1;
                    if (move.y - move.yTarget < 0) y = move.y + 1;
                    else y = move.y - 1;

                    while (x != move.xTarget)
                    {
                        if (getSquare(x, y)->Piece != VACANT) return false;
                        if (move.x - move.xTarget < 0) x++;
                        else x--;
                        if (move.y - move.yTarget < 0) y++;
                        else y--;
                    }
                    return true;
                }
            }
        case ROOK:
            {
                if (move.x == move.xTarget)
                {
                    chessposX_t i;
                    if (move.x - move.xTarget < 0) i = move.x + 1;
                    else i = move.x - 1;

                    while (i != move.xTarget)
                    {
                        if (getSquare(i, move.x)->Piece != VACANT) return false;
                        if (move.x - move.xTarget < 0) i++;
                        else i--;
                    } 
                    return true;
                }
                else
                {
                    chessposY_t i;
                    if (move.y - move.yTarget < 0) i = move.y + 1;
                    else i = move.y - 1;

                    while (i != move.yTarget)
                    {
                        if (getSquare(move.x, i)->Piece != VACANT) return false;
                        if (move.y - move.yTarget < 0) i++;
                        else i--;
                    }
                    return true;
                }
            }
        case KNIGHT:
            {
                if ((abs(move.x - move.xTarget) == 2 && abs(move.y - move.yTarget) == 1) || (abs(move.x - move.xTarget) == 1 && abs(move.y - move.yTarget) == 2))
                    return true;
                else return false;
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
    return false;
}
bool isCheck(Types::PlayerType side)
{

}
bool Chessboard::isCheck(Types::PlayerType side, Move move)
{

}