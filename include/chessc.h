#ifndef CHESSC_H
#define CHESSC_H
#include <inttypes.h>
#include <vector>

#define POS_X_INT  int8_t
#define POS_Y_INT  int8_t
#define MV_VAL_INT uint16_t

#define NORMAL_START_POS "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

// Do not check if the move is valid, do not increase counters and do not call hooks
#define SILENT_MOVE 1

typedef POS_X_INT chessposX_t;
typedef POS_Y_INT chessposY_t;

typedef MV_VAL_INT moveval_t;

namespace ChessC
{
    class Chessboard;
    struct Move;
    namespace Utility
    {

    }
    namespace Types
    {
        enum PlayerType
        {
            BLACK,
            WHITE,
            NONE
        };
        enum PieceType
        {
            KING,
            QUEEN,
            ROOK,
            KNIGHT,
            BISHOP,
            PAWN,
            VACANT
        };
        enum BoardType
        {
            NORMAL,
            CHESS960
        };
    }

    struct Move
    {
        Types::PlayerType Player;
        Types::PieceType Piece;
        chessposX_t x;
        chessposY_t y;

        Types::PlayerType PlayerTarget;
        Types::PieceType PieceTarget;
        chessposX_t xTarget;
        chessposY_t yTarget;
        bool isValid;
    };
    struct ChessSquare
    {
        Types::PlayerType Player;
        Types::PieceType Piece;
        chessposX_t x;
        chessposY_t y;
        bool hasMoved;
    };

    class Chessboard
    {
        // Constructors
        public:
        Chessboard();
        Chessboard(Types::BoardType type);
        Chessboard(const char* FEN);

        // Public functions
        public:
            bool  move(chessposX_t initialX, chessposY_t initialY, chessposX_t finalX, chessposY_t finalY);
            bool  move(chessposX_t initialX, chessposY_t initialY, chessposX_t finalX, chessposY_t finalY, char isSilent);
            bool  move(Move);
            bool  move(char*);

            char* getFEN();
            ChessSquare *getSquare(chessposX_t x, chessposY_t y);
            std::vector<Move> getValidMoves(ChessSquare*, bool check = true);
            std::vector<Move> getValidMoves(chessposX_t, chessposY_t, bool check = true);
            bool  isValid(Move, bool check = true);
            bool  isValid(chessposX_t initialX, chessposY_t initialY, chessposX_t finalX, chessposY_t finalY, bool check = true);
            bool  isCheck(Types::PlayerType side);
            bool  isCheck(Types::PlayerType side, Move move);
            bool  isCheckMate(Types::PlayerType side);

            Move findBestMove(const char*);
            Move findBestMove(Chessboard*);
            
            bool loadBoard(const char*);

        // Private functions
        private:

        // Public variables
        public:
            uint32_t searchDepth = 5; // Changes the search depth for the minimax algoritm
            bool useABP = true; // Enable Alpha-Beta pruning

            Types::PlayerType turn; // Who's turn it currently is
            ChessSquare *EnPassent; // En passent target square. nullptr if none
            uint32_t Halfmoves; // Number of halfmoves since last capture
            uint32_t Movenum; // Number of moves since start
            
            bool WhiteCastKS; // If white can castle kingside
            bool WhiteCastQS; // If white can castle queenside
            bool BlackCastKS; // If black can castle kingside
            bool BlackCastQS; // If black can castle queenside
        // Private variables
        private:
            std::vector<Move> log;

            chessposX_t dimX;
            chessposY_t dimY;
            std::vector<std::vector<ChessSquare>> Board;

            // For chess solving
    };
}

#endif