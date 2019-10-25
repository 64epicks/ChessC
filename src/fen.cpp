#include <chessc.h>
#include <string>
#include <iostream>
#include <iterator>
#include <sstream>
#include <cstring>

using namespace ChessC;
using namespace Types;

bool Chessboard::loadBoard(const char* FEN)
{
    // Split FEN string up to a vector separated by ' '
    std::string FEN_string = FEN;
    std::istringstream iss(FEN_string);
    std::vector<std::string> FEN_data(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>());

    // Start with laying out the pieces
    int index = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int t = 0; t < 8; t++)
        {
            char piece = FEN_data[0][index];
            if (isalpha(piece))
            {
                switch (tolower(piece))
                {
                    case 'k':
                        Board[7-i][t].Piece = KING;
                        if (isupper(piece)) { Board[7-i][t].Player = WHITE; }
                        else                { Board[7-i][t].Player = BLACK; }
                        break;
                    case 'q':
                        Board[7-i][t].Piece = QUEEN;
                        if (isupper(piece)) { Board[7-i][t].Player = WHITE; }
                        else                { Board[7-i][t].Player = BLACK; }
                        break;
                    case 'r':
                        Board[7-i][t].Piece = ROOK;
                        if (isupper(piece)) { Board[7-i][t].Player = WHITE; }
                        else                { Board[7-i][t].Player = BLACK; }
                        break;
                    case 'n':
                        Board[7-i][t].Piece = KNIGHT;
                        if (isupper(piece)) { Board[7-i][t].Player = WHITE; }
                        else                { Board[7-i][t].Player = BLACK; }
                        break;
                    case 'b':
                        Board[7-i][t].Piece = BISHOP;
                        if (isupper(piece)) { Board[7-i][t].Player = WHITE; }
                        else                { Board[7-i][t].Player = BLACK; }
                        break;
                    case 'p':
                        Board[7-i][t].Piece = PAWN;
                        if (isupper(piece)) { Board[7-i][t].Player = WHITE; }
                        else                { Board[7-i][t].Player = BLACK; }
                        break;
                    case '/': // Just in case
                        t = 8;
                        break;
                    default:
                        return false;
                }
            }
            else if (isdigit(piece))
            {
                uint8_t skipVal = piece - 0x30;
                if (skipVal < 1 || skipVal > 8) return false;
                t += skipVal - 1;
            }
            else return false;
            index++;
        }
        index++;
    }

    // Check turn
    if (FEN_data[1][0] == 'b') turn = BLACK;
    else turn = WHITE;

    // Check castling
    if (FEN_data[2][0] == '-')
    {
        WhiteCastKS = false;
        WhiteCastQS = false;
        BlackCastKS = false;
        BlackCastQS = false;
    }
    else
    {
        for (int i = 0; i < FEN_data[2].length(); i++)
        {
            switch (FEN_data[2][i])
            {
                case 'K':
                    WhiteCastKS = true;
                    break;
                case 'Q':
                    WhiteCastQS = true;
                    break;
                case 'k':
                    BlackCastKS = true;
                    break;
                case 'q':
                    BlackCastQS = true;
                    break;
                default:
                    return false;
            }
        }
    }

    // Check en passent
    if (FEN_data[3][0] == '-') EnPassent = nullptr;
    else
    {
        if(!isalpha(FEN_data[3][0]) || !isdigit(FEN_data[3][1])) return false;
        EnPassent = &Board[toupper(FEN_data[3][0]) - 0x41][FEN_data[3][1] - 0x30];
    }
    
    // Set halfmoves clock
    Halfmoves = atoi(FEN_data[4].c_str());
    // Set total moves variable
    Movenum = atoi(FEN_data[5].c_str());

    return true;
}
char* Chessboard::getFEN()
{
    std::string fen = "";

    for (int i = 0; i < 8; i++)
    {
        for (int t = 0; t < 8; t++)
        {
            switch (Board[7-i][t].Piece)
            {
                case KING:
                    if (Board[7-i][t].Player == WHITE) fen += "K";
                    else fen += "k";
                    break;
                case QUEEN:
                    if (Board[7-i][t].Player == WHITE) fen += "Q";
                    else fen += "q";
                    break;
                case ROOK:
                    if (Board[7-i][t].Player == WHITE) fen += "R";
                    else fen += "r";
                    break;
                case KNIGHT:
                    if (Board[7-i][t].Player == WHITE) fen += "N";
                    else fen += "n";
                    break;
                case BISHOP:
                    if (Board[7-i][t].Player == WHITE) fen += "B";
                    else fen += "b";
                    break;
                case PAWN:
                    if (Board[7-i][t].Player == WHITE) fen += "P";
                    else fen += "p";
                    break;
                case VACANT:
                    int vacount = 1;
                    t++;
                    while (Board[7-i][t].Piece == VACANT)
                    {
                        if (t > 8) return nullptr;
                        if (vacount >= 8) break;
                        vacount++;
                        t++;
                    }
                    t--;
                    fen += std::to_string(vacount);
                    break;
            }
        }
        if (i < 7) fen += "/";
    }
    fen += " ";

    if (turn == WHITE) fen += "w ";
    else fen += "b ";

    if (WhiteCastKS) fen += "K";
    if (WhiteCastQS) fen += "Q";
    if (BlackCastKS) fen += "k";
    if (BlackCastQS) fen += "q";
    if (!WhiteCastKS && !WhiteCastQS && !BlackCastKS && !BlackCastQS) fen += "-";
    fen += " ";

    if (EnPassent == nullptr) fen += "- ";
    else
    {
        fen += EnPassent->x + 0x61;
        fen += EnPassent->y + 0x30;
        fen += " ";
    }

    fen += std::to_string(Halfmoves) + " ";
    fen += std::to_string(Movenum);
    
    char* FEN_char = (char*)malloc(fen.length()+1);
    memcpy ( FEN_char, fen.c_str(), fen.length()+1 );

    return FEN_char;
}