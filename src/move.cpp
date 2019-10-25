#include <chessc.h>

using namespace ChessC;
using namespace Types;

std::vector<Move> Chessboard::getValidMoves(chessposX_t x, chessposY_t y)
{
    return getValidMoves(getSquare(x, y));
}
std::vector<Move> Chessboard::getValidMoves(ChessSquare* square)
{
    std::vector<Move> movelist;
    if (square == nullptr) return movelist;
    Move movetemp;
    movetemp.Player  = square->Player;
    movetemp.Piece   = square->Piece;
    movetemp.x       = square->x;
    movetemp.y       = square->y;
    movetemp.isValid = true;
    Chessboard chessboardCopy = *this;

    #define CHECK_SET(ix, iy, tx, ty) if (isValid(ix, iy, tx, ty)) { ChessSquare *targetSquare = getSquare(tx, ty); movetemp.x = tx; movetemp.y = ty; movetemp.PlayerTarget = targetSquare->Player; movetemp.PieceTarget = targetSquare->Piece; movelist.push_back(movetemp); }

    switch (square->Piece)
    {
        case KING:
            {
                // Check left side
                CHECK_SET(square->x, square->y, square->x, square->y-1);
                // Check right side
                CHECK_SET(square->x, square->y, square->x, square->y+1);
                // Check up
                CHECK_SET(square->x, square->y, square->x+1, square->y);
                // Check down
                CHECK_SET(square->x, square->y, square->x-1, square->y);
                // Check diagonal up-left
                CHECK_SET(square->x, square->y, square->x+1, square->y-1);
                // Check diagonal up-right
                CHECK_SET(square->x, square->y, square->x+1, square->y+1);
                // Check diagonal down-left
                CHECK_SET(square->x, square->y, square->x-1, square->y-1);
                // Check diagonal down-right
                CHECK_SET(square->x, square->y, square->x-1, square->y+1);
                break;
            }
        case QUEEN:
            {
                for (int i = 0; i < 8; i++)
                {
                    // Down - Up
                    CHECK_SET(square->x, square->y, i, square->y);
                    // Left - Right
                    CHECK_SET(square->x, square->y, square->y, i);
                    // Diagonal bottom-left - upper-right
                    if (square->x+i+1 < 8 && square->y+i+1 < 8)   CHECK_SET(square->x, square->y, square->x+i+1, square->y+i+1);
                    if (square->x-i-1 >= 0 && square->y-i-1 >= 0) CHECK_SET(square->x, square->y, square->x-i-1, square->y-i-1);
                    // Diagonal bottom-right - upper-left
                    if (square->x+i+1 < 8 && square->y-i-1 >= 0)  CHECK_SET(square->x, square->y, square->x+i+1, square->y-i-1);
                    if (square->x-i-1 >= 0 && square->y+i+1 < 8)  CHECK_SET(square->x, square->y, square->x-i-1, square->y+i+1);
                }
                break;
            }
        case ROOK:
            {
                for (int i = 0; i < 8; i++)
                {
                    // Down - Up
                    CHECK_SET(square->x, square->y, i, square->y);
                    // Left - Right
                    CHECK_SET(square->x, square->y, square->y, i);
                }
                break;
            }
        case KNIGHT:
            {
                // Up-left
                CHECK_SET(square->x, square->y, square->x+2, square->y-1);
                // Up-right
                CHECK_SET(square->x, square->y, square->x+2, square->y+1);
                // Right-left
                CHECK_SET(square->x, square->y, square->x+1, square->y+2);
                // Right-right
                CHECK_SET(square->x, square->y, square->x-1, square->y+2);
                // Down-left
                CHECK_SET(square->x, square->y, square->x-2, square->y-1);
                // Down-right
                CHECK_SET(square->x, square->y, square->x-2, square->y+1);
                // Left-left
                CHECK_SET(square->x, square->y, square->x-1, square->y-2);
                // Left-right
                CHECK_SET(square->x, square->y, square->x+1, square->y-2);
                break;
            }
        case BISHOP:
            {
                for (int i = 0; i < 8; i++)
                {
                    // Diagonal bottom-left - upper-right
                    if (square->x+i+1 < 8 && square->y+i+1 < 8)   CHECK_SET(square->x, square->y, square->x+i+1, square->y+i+1);
                    if (square->x-i-1 >= 0 && square->y-i-1 >= 0) CHECK_SET(square->x, square->y, square->x-i-1, square->y-i-1);
                    // Diagonal bottom-right - upper-left
                    if (square->x+i+1 < 8 && square->y-i-1 >= 0)  CHECK_SET(square->x, square->y, square->x+i+1, square->y-i-1);
                    if (square->x-i-1 >= 0 && square->y+i+1 < 8)  CHECK_SET(square->x, square->y, square->x-i-1, square->y+i+1);
                }
                break;
            }
        case PAWN:
            {
                if (square->Player == WHITE)
                {
                    if (square->x == 1)
                    {
                        CHECK_SET(square->x, square->y, square->x+2, square->y);
                    }

                    CHECK_SET(square->x, square->y, square->x+1, square->y);

                    CHECK_SET(square->x, square->y, square->x+1, square->y-1);
                    CHECK_SET(square->x, square->y, square->x+1, square->y+1);
                }
                else
                {
                    if (square->x == 6)
                    {
                        CHECK_SET(square->x, square->y, square->x-2, square->y);
                    }

                    CHECK_SET(square->x, square->y, square->x-1, square->y);

                    CHECK_SET(square->x, square->y, square->x-1, square->y-1);
                    CHECK_SET(square->x, square->y, square->x-1, square->y+1);
                }

                break;
            }
        default:
            return movelist;
    }
    return movelist;
}