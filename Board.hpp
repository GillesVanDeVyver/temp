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



private:
    PieceColor turn_attr;
    long WhiteKing;
    long WhiteQueens;
    long WhiteRooks;
    long WhiteBishops;
    long WhiteKnights;
    long WhitePawns;
    long WhitePieces;
    
    long BlackKing;
    long BlackQueens;
    long BlackRooks;
    long BlackBishops;
    long BlackKnights;
    long BlackPawns;
    long BlackPieces;
    
    CastlingRights cstlingRights;
    
    int enpassantsqr;
    
};

std::ostream& operator<<(std::ostream& os, const Board& board);

#endif
