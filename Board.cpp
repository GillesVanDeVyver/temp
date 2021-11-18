#include "Board.hpp"

#include <ostream>
#include <cassert>
#include <cmath>
#include <iostream>


Board::Board()
{
    WhiteKing=0;
    WhiteQueens=0;
    WhiteRooks=0;
    WhiteBishops=0;
    WhiteKnights=0;
    WhitePawns=0;
    WhitePieces=0;
    
    BlackKing=0;
    BlackQueens=0;
    BlackRooks=0;
    BlackBishops=0;
    BlackKnights=0;
    BlackPawns=0;
    BlackPieces=0;
}

void Board::setPiece(const Square& square, const Piece::Optional& piece) { // todo overwrite occupied
    
    int index_to_set=square.index();
    
    // remove old piece
    if ((WhitePieces >> index_to_set) & 1){ // there is a white piece at location to set
        if (piece.value().color() == PieceColor::Black){ // piece to set is black
            WhitePieces &= ~(1UL << index_to_set);
        }
        if ((WhitePawns >> index_to_set) & 1){
            WhitePawns &= ~(1UL << index_to_set);
        } else if ((WhiteKnights >> index_to_set) & 1){
            WhiteKnights &= ~(1UL << index_to_set);
        } else if ((WhiteBishops >> index_to_set) & 1){
            WhiteBishops &= ~(1UL << index_to_set);
        } else if ((WhiteRooks >> index_to_set) & 1){
            WhiteRooks &= ~(1UL << index_to_set);
        } else if ((WhiteQueens >> index_to_set) & 1){
            WhiteQueens &= ~(1UL << index_to_set);
        } else if ((WhiteKing>> index_to_set) & 1){
            WhiteKing &= ~(1UL << index_to_set);
        }
    } else if ((BlackPieces >> index_to_set) & 1) { // there is a Black piece at location to set
        if (piece.value().color() == PieceColor::White){ // piece to set is white
            BlackPieces &= ~(1UL << index_to_set);
        }
        if ((BlackPawns >> index_to_set) & 1){
            BlackPawns &= ~(1UL << index_to_set);
        } else if ((BlackKnights >> index_to_set) & 1){
            BlackKnights &= ~(1UL << index_to_set);
        } else if ((BlackBishops >> index_to_set) & 1){
            BlackBishops &= ~(1UL << index_to_set);
        } else if ((BlackRooks >> index_to_set) & 1){
            BlackRooks &= ~(1UL << index_to_set);
        } else if ((BlackQueens >> index_to_set) & 1){
            BlackQueens &= ~(1UL << index_to_set);
        } else if ((BlackKing>> index_to_set) & 1){
            BlackKing &= ~(1UL << index_to_set);
        }
    }

    // set new piece    
    if (piece.value().color() == PieceColor::White){
        switch(piece.value().type()){
            case PieceType::Pawn:
                WhitePawns |= 1UL << index_to_set;
                break;
            case PieceType::King:
                WhiteKing |= 1UL << index_to_set;
                break;
            case PieceType::Queen:
                WhiteQueens |= 1UL << index_to_set;
                break;
            case PieceType::Knight:
                WhiteKnights|= 1UL << index_to_set;
                break;
            case PieceType::Bishop:
                WhiteBishops |= 1UL << index_to_set;
                break;
            case PieceType::Rook:
                WhiteRooks |= 1UL << index_to_set;
        }
        WhitePieces |= 1UL << index_to_set;
    }else{
        switch(piece.value().type()){
            case PieceType::Pawn:
                BlackPawns |= 1UL << index_to_set;
                break;
            case PieceType::King:
                BlackKing |= 1UL << index_to_set;
                break;
            case PieceType::Queen:
                BlackQueens |= 1UL << index_to_set;
                break;
            case PieceType::Knight:
                BlackKnights|= 1UL << index_to_set;
                break;
            case PieceType::Bishop:
                BlackBishops |= 1UL << index_to_set;
                break;
            case PieceType::Rook:
                BlackRooks |= 1UL << index_to_set;
        }
        BlackPieces |= 1UL << index_to_set;
    }
}



Piece::Optional Board::piece(const Square& square) const {
    int index_to_get=square.index();
    if ((WhitePieces >> index_to_get) & 1){
        if ((WhitePawns >> index_to_get) & 1){
            return Piece(PieceColor::White, PieceType::Pawn);
        } else if ((WhiteKnights >> index_to_get) & 1){
            return Piece(PieceColor::White, PieceType::Knight);
        } else if ((WhiteBishops >> index_to_get) & 1){
            return Piece(PieceColor::White, PieceType::Bishop);
        } else if ((WhiteRooks >> index_to_get) & 1){
            return Piece(PieceColor::White, PieceType::Rook);
        } else if ((WhiteQueens >> index_to_get) & 1){
            return Piece(PieceColor::White, PieceType::Queen);
        } else if ((WhiteKing>> index_to_get) & 1){
            return Piece(PieceColor::White, PieceType::King);
        }
    }
    else if ((BlackPieces >> index_to_get) & 1) {
        if ((BlackPawns >> index_to_get) & 1){
            return Piece(PieceColor::Black, PieceType::Pawn);
        } else if ((BlackKnights >> index_to_get) & 1){
            return Piece(PieceColor::Black, PieceType::Knight);
        } else if ((BlackBishops >> index_to_get) & 1){
            return Piece(PieceColor::Black, PieceType::Bishop);
        } else if ((BlackRooks >> index_to_get) & 1){
            return Piece(PieceColor::Black, PieceType::Rook);
        } else if ((BlackQueens >> index_to_get) & 1){
            return Piece(PieceColor::Black, PieceType::Queen);
        } else if ((BlackKing>> index_to_get) & 1){
            return Piece(PieceColor::Black, PieceType::King);
        }
    }
    return std::nullopt;
}

void Board::setTurn(PieceColor turn) {
    turn_attr=turn;
}

PieceColor Board::turn() const {
    return turn_attr;
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
    (void)from;
    (void)moves;
}

std::ostream& operator<<(std::ostream& os, const Board& board) {
    (void)board;
    return os;
}
