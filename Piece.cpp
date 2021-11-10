#include "Piece.hpp"

#include <ostream>

Piece::Piece(PieceColor color, PieceType type)
{
    color_attr = color;;
    type_attr = type;
}

Piece::Optional Piece::fromSymbol(char symbol) {
    PieceColor color;
    PieceType type;
    if (isupper(symbol)){
        color=PieceColor::White;
    }else{
        color=PieceColor::Black;
    }
    char symbolLower = tolower(symbol);
    switch(symbolLower) {
        case 'p':
            type=PieceType::Pawn;
            break;
        case 'n':
            type=PieceType::Knight;
            break;
        case 'b':
            type=PieceType::Bishop;
            break;
        case 'r':
            type=PieceType::Rook;
            break;
        case 'q':
            type=PieceType::Queen;
            break;
        case 'k':
            type=PieceType::King;
            break;
        default:
            return std::nullopt;
        }
    Piece newPiece(color,type);
    return newPiece;
}

PieceColor Piece::color() const {
    return color_attr;
}

PieceType Piece::type() const {
    return type_attr;
}

bool operator==(const Piece& lhs, const Piece& rhs) {
    if ((lhs.color()==rhs.color()) && (lhs.type()==rhs.type())){
           return true;     
    }
    return false;
}

std::ostream& operator<<(std::ostream& os, const Piece& piece) {
    char piecePresenation;
    switch(piece.type()) {
        case PieceType::Pawn:
            piecePresenation='P';
            break;
        case PieceType::Knight:
            piecePresenation='N';
            break;
        case PieceType::Bishop:
            piecePresenation='B';
            break;
        case PieceType::Rook:
            piecePresenation='R';
            break;
        case PieceType::King:
            piecePresenation='K';
            break;
        case PieceType::Queen:
            piecePresenation='Q';
            break;
        }
    if (piece.color()==PieceColor::Black){
        piecePresenation=tolower(piecePresenation);
    }
    os<<piecePresenation;
    return os;
}

PieceColor operator!(PieceColor color) {
    if (color==PieceColor::White){
        return PieceColor::Black;
    }else{
        return PieceColor::White;
    }
}
