#include "Board.hpp"

#include <ostream>
#include <cassert>
#include <cmath>

Board::Board()
{
}
// new branche

void Board::setPiece(const Square& square, const Piece::Optional& piece) {
    boardArr[square.file()][square.rank()]=piece;
}

Piece::Optional Board::piece(const Square& square) const {
    return boardArr[square.file()][square.rank()];
}

void Board::setTurn(PieceColor turn) {
    turnAttr = turn;
}

PieceColor Board::turn() const {
    return turnAttr;
}

void Board::setCastlingRights(CastlingRights cr) {
    (void)cr;
}

CastlingRights Board::castlingRights() const {
    return CastlingRights::None;
}

void Board::setEnPassantSquare(const Square::Optional& square) {
    (void)square;
}

Square::Optional Board::enPassantSquare() const {
    return std::nullopt;
}

void Board::makeMove(const Move& move) {
    (void)move;
}

void Board::pseudoLegalMoves(MoveVec& moves) const {
    (void)moves;
}

void Board::pseudoLegalMovesFrom(const Square& from,
                                 Board::MoveVec& moves) const {
    if (piece(from)){
        Piece pieceFrom = piece(from).value();
        if (turn()==pieceFrom.color()){
            pseudoLegalKnightMoves(from,moves,pieceFrom.color());
        }
    }

}

void Board::pseudoLegalKnightMoves(const Square& from,
                                 Board::MoveVec& moves, PieceColor color) const {
    Square::Optional squareTo = Square::fromCoordinates(from.file()-1,from.rank()-2); //down down left
    checkSameColorCaptureAndSet(from,squareTo,moves,color);
    squareTo = Square::fromCoordinates(from.file()+1,from.rank()-2); //down down right
    checkSameColorCaptureAndSet(from,squareTo,moves,color);
    squareTo = Square::fromCoordinates(from.file()-2,from.rank()-1); //down left left
    checkSameColorCaptureAndSet(from,squareTo,moves,color);
    squareTo = Square::fromCoordinates(from.file()+2,from.rank()-1); //down right right
    checkSameColorCaptureAndSet(from,squareTo,moves,color);
    squareTo = Square::fromCoordinates(from.file()-1,from.rank()+2); //up up left
    checkSameColorCaptureAndSet(from,squareTo,moves,color);
    squareTo = Square::fromCoordinates(from.file()+1,from.rank()+2); //up up right
    checkSameColorCaptureAndSet(from,squareTo,moves,color);
    squareTo = Square::fromCoordinates(from.file()-2,from.rank()+1); //up left left
    checkSameColorCaptureAndSet(from,squareTo,moves,color);
    squareTo = Square::fromCoordinates(from.file()+2,from.rank()+1); //up right right
    checkSameColorCaptureAndSet(from,squareTo,moves,color);
}

void Board::checkSameColorCaptureAndSet(const Square& from, Square::Optional squareTo,
                                 Board::MoveVec& moves, PieceColor color) const {
    if (squareTo){
        if (piece(squareTo.value())){
            if (piece(squareTo.value()).value().color() == color){
                return;
            }
        }
        moves.push_back(* new Move(from,squareTo.value()));
    }

}

std::ostream& operator<<(std::ostream& os, const Board& board) {
    (void)board;
    return os;
}
