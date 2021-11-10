#include "Move.hpp"

#include <ostream>

#include <iostream>
using namespace std;

Move::Move(const Square& from, const Square& to,
           const std::optional<PieceType>& promotion)
{
    from_attr=from;
    to_attr=to;
    promotion_attr= promotion;
}

Move::Optional Move::fromUci(const std::string& uci) {
    std::optional<PieceType> extracted_promotion;
    if ((uci.length() == 5) || (uci.length() == 4)){
        if (uci.length() == 5) {
            char promotion_as_char = uci.at(4);
            std::optional<Piece> extracted_Piece_as_optional = Piece::fromSymbol(promotion_as_char);
            if (extracted_Piece_as_optional.has_value()){
                Piece extracted_Piece = *extracted_Piece_as_optional;
                extracted_promotion=extracted_Piece.type();
            } else{
                return std::nullopt;
            }
        }
        else{
            extracted_promotion=std::nullopt;
        }
        
        std::string from_as_string = uci.substr(0,2);
        std::optional extracted_from_as_optional=Square::fromName(from_as_string);
                
        std::string to_as_string = uci.substr(2,2);
        std::optional extracted_to_as_optional = Square::fromName(to_as_string);
        
        if (extracted_from_as_optional.has_value()&&extracted_to_as_optional.has_value()){
            Square extracted_from=*extracted_from_as_optional;
            Square extracted_to=*extracted_to_as_optional;
            return Move(extracted_from, extracted_to,extracted_promotion);
        }
    }

    else{
        return std::nullopt;
    }
    return std::nullopt;

}

Square Move::from() const {
    return from_attr;
}

Square Move::to() const {
    return to_attr;
}

std::optional<PieceType> Move::promotion() const {
    return promotion_attr;
}

std::ostream& operator<<(std::ostream& os, const Move& move) {
    std::optional<PieceType> promotion_as_optional = move.promotion();
        
    if (promotion_as_optional.has_value()){
        Piece temp_piece(PieceColor::Black,*promotion_as_optional); // make use of Piece streaming function
        os<<move.from()<<move.to()<<temp_piece;
    }
    else{
        os<<move.from()<<move.to();
    }
    return os;
}


bool operator<(const Move& lhs, const Move& rhs) {
    if (lhs.from().index()<rhs.from().index()){
        return true;
    }else if (lhs.from().index()>rhs.from().index()){
        return false;
    }
    else{
        if (lhs.to().index()<rhs.to().index()){
            return true;
        }else if (lhs.to().index()>rhs.to().index()){
            return false;
        }
        else{
            if (!(lhs.promotion().has_value()) && rhs.promotion().has_value()){
                return true;
            }
            else if (lhs.promotion().has_value() && !(rhs.promotion().has_value())){
                return false;
            }
            else{
                return (lhs.promotion()<rhs.promotion());
            }
        }
    }
    return false;
}

bool operator==(const Move& lhs, const Move& rhs) {
    if (lhs.from()==rhs.from() && lhs.to()==rhs.to() && lhs.promotion()==rhs.promotion()){
        return true;
    }
    return false;
}
