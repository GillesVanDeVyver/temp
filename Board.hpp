#ifndef CHESS_ENGINE_BOARD_HPP
#define CHESS_ENGINE_BOARD_HPP

#include "Piece.hpp"
#include "Square.hpp"
#include "Move.hpp"
#include "CastlingRights.hpp"

#include <optional>
#include <iosfwd>
#include <vector>

class Board {
public:

    using Optional = std::optional<Board>;
    using MoveVec = std::vector<Move>;

    Board();

    void setPiece(const Square& square, const Piece::Optional& piece);
    Piece::Optional piece(const Square& square) const;
    void setTurn(PieceColor turn);
    PieceColor turn() const;
    void setCastlingRights(CastlingRights cr);
    CastlingRights castlingRights() const;
    void setEnPassantSquare(const Square::Optional& square);
    Square::Optional enPassantSquare() const;

    void makeMove(const Move& move);

    void pseudoLegalMoves(MoveVec& moves) const;
    void pseudoLegalMovesFrom(const Square& from, MoveVec& moves) const;
    
    void pseudoLegalMovesKnight(const Square& from, MoveVec& moves, long ownpieces) const;
    void pseudoLegalMovesKing(const Square& from, MoveVec& moves, long ownpieces) const;
    void pseudoLegalMovesBishop(const Square& from, MoveVec& moves, long ownpieces, long otherpieces) const;
    void pseudoLegalMovesRook(const Square& from, MoveVec& moves, long ownpieces, long otherpieces) const;
    void pseudoLegalMovesPawn(const Square& from, MoveVec& moves, long ownpieces, long otherpieces, PieceColor color) const;




private:
    PieceColor turn_attr;
    unsigned long long WhiteKing;
    unsigned long long WhiteQueens;
    unsigned long long WhiteRooks;
    unsigned long long WhiteBishops;
    unsigned long long WhiteKnights;
    unsigned long long WhitePawns;
    unsigned long long WhitePieces;
    
    unsigned long long BlackKing;
    unsigned long long BlackQueens;
    unsigned long long BlackRooks;
    unsigned long long BlackBishops;
    unsigned long long BlackKnights;
    unsigned long long BlackPawns;
    unsigned long long BlackPieces;
    
    CastlingRights cstlingRights;
    
    int enpassantsqr;
    
};

std::ostream& operator<<(std::ostream& os, const Board& board);

#endif
