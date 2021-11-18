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
    
    void pseudoLegalKnightMoves(const Square& from,Board::MoveVec& moves, PieceColor color) const;
    void checkSameColorCaptureAndSet(const Square& from, Square::Optional squareTo,
                                 Board::MoveVec& moves, PieceColor color) const;
    void pseudoLegalKingMoves(const Square& from,
                                 Board::MoveVec& moves, PieceColor color) const;
    void pseudoLegalBishopMoves(const Square& from,
                                 Board::MoveVec& moves, PieceColor color) const;
    bool checkCaptureAndSet(const Square& from, Square::Optional squareTo,
                                 Board::MoveVec& moves, PieceColor color) const;
    void pseudoLegalRookMoves(const Square& from,
                                 Board::MoveVec& moves, PieceColor color) const;
    void pseudoLegalPawnMoves(const Square& from,
                                 Board::MoveVec& moves, PieceColor color) const;
    void checkBlockedAndSet(const Square& from, Square::Optional squareTo,
                                 Board::MoveVec& moves) const;
    void checkOtherColorCaptureAndSet(const Square& from, Square::Optional squareTo,
                                 Board::MoveVec& moves, PieceColor color) const;
    void checkFreeBaseAndSet(const Square& from, const Square& squareToIntermediate,
                                 const Square& squareTo,Board::MoveVec& moves) const;
    
private:
    Piece::Optional boardArr[8][8];
    PieceColor turnAttr;
};

std::ostream& operator<<(std::ostream& os, const Board& board);

#endif
