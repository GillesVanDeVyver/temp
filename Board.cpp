#include "Board.hpp"

#include <ostream>
#include <cassert>
#include <cmath>
#include <iostream>
using namespace std;

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
    enPassantSquareAttr = square;
}

Square::Optional Board::enPassantSquare() const {
    return enPassantSquareAttr;
}

void Board::makeMove(const Move& move) {
    (void)move;
}

void Board::pseudoLegalMoves(MoveVec& moves) const {
    for (int i =0; i<=63;i++){
        Square fromSqr = Square::fromIndex(i).value();
        pseudoLegalMovesFrom(fromSqr,moves);
    }
}

void Board::pseudoLegalMovesFrom(const Square& from,
                                 Board::MoveVec& moves) const {
    if (piece(from)){
        Piece pieceFrom = piece(from).value();
        if (turn()==pieceFrom.color()){
            if (pieceFrom.type()==PieceType::Knight){
                pseudoLegalKnightMoves(from,moves,pieceFrom.color());
            }
            if (pieceFrom.type()==PieceType::King){
                pseudoLegalKingMoves(from,moves,pieceFrom.color());
            }
            if (pieceFrom.type()==PieceType::Bishop){
                pseudoLegalBishopMoves(from,moves,pieceFrom.color());
            }
            if (pieceFrom.type()==PieceType::Rook){
                pseudoLegalRookMoves(from,moves,pieceFrom.color());
            }
            if (pieceFrom.type()==PieceType::Queen){
                pseudoLegalRookMoves(from,moves,pieceFrom.color());
                pseudoLegalBishopMoves(from,moves,pieceFrom.color());
            }
            if (pieceFrom.type()==PieceType::Pawn){
                pseudoLegalPawnMoves(from,moves,pieceFrom.color());
            }
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

void Board::pseudoLegalKingMoves(const Square& from,
                                 Board::MoveVec& moves, PieceColor color) const {
    Square::Optional squareTo = Square::fromCoordinates(from.file()-1,from.rank()-1); //down left
    checkSameColorCaptureAndSet(from,squareTo,moves,color);
    squareTo = Square::fromCoordinates(from.file(),from.rank()-1); //down
    checkSameColorCaptureAndSet(from,squareTo,moves,color);
    squareTo = Square::fromCoordinates(from.file()+1,from.rank()-1); //down right
    checkSameColorCaptureAndSet(from,squareTo,moves,color);
    squareTo = Square::fromCoordinates(from.file()-1,from.rank()); //left
    checkSameColorCaptureAndSet(from,squareTo,moves,color);
    squareTo = Square::fromCoordinates(from.file()+1,from.rank()); //right
    checkSameColorCaptureAndSet(from,squareTo,moves,color);
    squareTo = Square::fromCoordinates(from.file()-1,from.rank()+1); //up left
    checkSameColorCaptureAndSet(from,squareTo,moves,color);
    squareTo = Square::fromCoordinates(from.file(),from.rank()+1); //up
    checkSameColorCaptureAndSet(from,squareTo,moves,color);
    squareTo = Square::fromCoordinates(from.file()+1,from.rank()+1); //up right
    checkSameColorCaptureAndSet(from,squareTo,moves,color);
}

void Board::pseudoLegalBishopMoves(const Square& from,
                                 Board::MoveVec& moves, PieceColor color) const {
    Square::Optional squareTo;
    int i = 1;
    bool noCapture=true;
    while(i<8 && noCapture){
        squareTo = Square::fromCoordinates(from.file()-i,from.rank()-i); //down left
        noCapture = checkCaptureAndSet(from,squareTo,moves,color);
        i++;
    }
    i=1;
    noCapture=true;
    while(i<8 && noCapture){
        squareTo = Square::fromCoordinates(from.file()+i,from.rank()-i); //down right
        noCapture = checkCaptureAndSet(from,squareTo,moves,color);
        i++;
    }
    i=1;
    noCapture=true;
    while(i<8 && noCapture){
        squareTo = Square::fromCoordinates(from.file()-i,from.rank()+i); //up left
        noCapture = checkCaptureAndSet(from,squareTo,moves,color);
        i++;
    }
    i=1;
    noCapture=true;
    while(i<8 && noCapture){
        squareTo = Square::fromCoordinates(from.file()+i,from.rank()+i); //up right
        noCapture = checkCaptureAndSet(from,squareTo,moves,color);
        i++;
    }
}

void Board::pseudoLegalRookMoves(const Square& from,
                                 Board::MoveVec& moves, PieceColor color) const {
    Square::Optional squareTo;
    int i = 1;
    bool noCapture=true;
    while(i<8 && noCapture){
        squareTo = Square::fromCoordinates(from.file(),from.rank()-i); //down
        noCapture = checkCaptureAndSet(from,squareTo,moves,color);
        i++;
    }
    i=1;
    noCapture=true;
    while(i<8 && noCapture){
        squareTo = Square::fromCoordinates(from.file(),from.rank()+i); //up
        noCapture = checkCaptureAndSet(from,squareTo,moves,color);
        i++;
    }
    i=1;
    noCapture=true;
    while(i<8 && noCapture){
        squareTo = Square::fromCoordinates(from.file()-i,from.rank()); //left
        noCapture = checkCaptureAndSet(from,squareTo,moves,color);
        i++;
    }
    i=1;
    noCapture=true;
    while(i<8 && noCapture){
        squareTo = Square::fromCoordinates(from.file()+i,from.rank()); //right
        noCapture = checkCaptureAndSet(from,squareTo,moves,color);
        i++;
    }
}

void Board::pseudoLegalPawnMoves(const Square& from,
                                 Board::MoveVec& moves, PieceColor color) const {
    
    Square::Optional squareTo;
    if (color==PieceColor::White){
        //normal step
        squareTo = Square::fromCoordinates(from.file(),from.rank()+1); //up
        checkBlockedAndSet(from,squareTo,moves);
        //captures
        squareTo = Square::fromCoordinates(from.file()-1,from.rank()+1); //up left
        checkOtherColorCaptureAndSet(from,squareTo,moves, color);
        squareTo = Square::fromCoordinates(from.file()+1,from.rank()+1); //up right
        checkOtherColorCaptureAndSet(from,squareTo,moves, color);
        //base step
        if (from.rank()==1){
            squareTo = Square::fromCoordinates(from.file(),from.rank()+2); //up up
            Square squareToIntermediate=Square::fromCoordinates(from.file(),from.rank()+1).value(); //up
            checkFreeBaseAndSet(from,squareToIntermediate,squareTo.value(),moves);
        }
        // en Passant
        Square::Optional enPssntSqOpt = enPassantSquare();
        if (enPssntSqOpt){
            Square enPssntSq=enPssntSqOpt.value();
            if (enPssntSq.rank()==from.rank()+1){
                if (enPssntSq.file() == from.file() -1){
                    squareTo = Square::fromCoordinates(from.file()-1,from.rank()+1);
                    checkBlockedAndSet(from,squareTo,moves);
                }
                if (enPssntSq.file() == from.file() +1){
                    squareTo = Square::fromCoordinates(from.file()+1,from.rank()+1);
                    checkBlockedAndSet(from,squareTo,moves);
                }
            }
        }
    } else{
        // normal step
        squareTo = Square::fromCoordinates(from.file(),from.rank()-1); //down
        checkBlockedAndSet(from,squareTo,moves);
        // captures
        squareTo = Square::fromCoordinates(from.file()-1,from.rank()-1); //down left
        checkOtherColorCaptureAndSet(from,squareTo,moves, color);
        squareTo = Square::fromCoordinates(from.file()+1,from.rank()-1); //down right
        checkOtherColorCaptureAndSet(from,squareTo,moves, color);
        //base step
        if (from.rank()==6){
            squareTo = Square::fromCoordinates(from.file(),from.rank()-2); //down down
            Square squareToIntermediate=Square::fromCoordinates(from.file(),from.rank()-1).value(); //down
            checkFreeBaseAndSet(from,squareToIntermediate,squareTo.value(),moves);
        }
        // en Passant
        Square::Optional enPssntSqOpt = enPassantSquare();
        if (enPssntSqOpt){
            Square enPssntSq=enPssntSqOpt.value();
            if (enPssntSq.rank()==from.rank()-1){
                if (enPssntSq.file() == from.file() -1){
                    squareTo = Square::fromCoordinates(from.file()-1,from.rank()-1);
                    checkBlockedAndSet(from,squareTo,moves);
                }
                if (enPssntSq.file() == from.file() +1){
                    squareTo = Square::fromCoordinates(from.file()+1,from.rank()-1);
                    checkBlockedAndSet(from,squareTo,moves);
                }
            }
        }
    }
}

void Board::checkOtherColorCaptureAndSet(const Square& from, Square::Optional squareTo, // used in pawn captures
                                 Board::MoveVec& moves, PieceColor color) const {
    if (squareTo){
        if (piece(squareTo.value())){
            if (piece(squareTo.value()).value().color() != color){ //opposite color
                moves.push_back(* new Move(from,squareTo.value()));
            }
        }
    }
}

void Board::checkFreeBaseAndSet(const Square& from, const Square& squareToIntermediate, // used in pawn base moves
                                 const Square& squareTo,Board::MoveVec& moves) const {
                                     
    if (!(piece(squareToIntermediate)) && !(piece(squareTo))){
        moves.push_back(* new Move(from,squareTo));
    }
}

void Board::checkBlockedAndSet(const Square& from, Square::Optional squareTo, // used in pawn moves
                                 Board::MoveVec& moves) const {
    if (squareTo){
        if (!(piece(squareTo.value()))){
            moves.push_back(* new Move(from,squareTo.value()));
        }
    }
}

void Board::checkSameColorCaptureAndSet(const Square& from, Square::Optional squareTo, // used for king/knight
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

bool Board::checkCaptureAndSet(const Square& from, Square::Optional squareTo, // used for rook/bishop/queen
                                 Board::MoveVec& moves, PieceColor color) const {
    if (squareTo){
        if (piece(squareTo.value())){
            if (piece(squareTo.value()).value().color() == color){
                return false;
            } else{
                moves.push_back(* new Move(from,squareTo.value()));
                return false;
            }
        }
        moves.push_back(* new Move(from,squareTo.value()));
        return true;
    }
    return false;
}


std::ostream& operator<<(std::ostream& os, const Board& board) {
    (void)board;
    return os;
}
