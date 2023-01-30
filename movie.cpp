#include "movie.h"
#include "util.h"
#include <sstream>

using namespace std;

Movie::Movie(const std::string category, 
            const std::string name, 
            double price, 
            int qty, 
            const std::string genre, 
            const std::string rating) 
                : 
            Product(category, name, price, qty),
            genre_(genre),
            rating_(rating)

    {}

std::set<std::string> Movie::keywords() const
{
    std::set<std::string> allKeywords = parseStringToWords(name_);
    allKeywords.insert(convToLower(genre_));

    return allKeywords;
}

std::string Movie::displayString() const
{
    stringstream ss;

    ss << name_ << endl
       << "Genre: " << genre_ << " Rating: " << rating_ << endl
       << price_ << "   " << qty_ << " left.";

    return ss.str();
}

void Movie::dump(std::ostream& os) const
{
    os << "book" << endl
       << name_ << endl
       << price_ << endl
       << qty_ << endl
       << genre_ << endl
       << rating_ << endl;
}