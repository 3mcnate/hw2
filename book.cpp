#include "book.h"
#include "util.h"
#include <sstream>

using namespace std;

Book::Book(const std::string category, 
           const std::string name, 
           double price, 
           int qty, 
           const std::string ISBN, 
           const std::string author) 
            : 
            Product(category, name, price, qty),
            ISBN_(ISBN),
            author_(author)

    {}

std::set<std::string> Book::keywords() const
{
    std::set<std::string> allKeywords = setUnion(
        parseStringToWords(name_),
        parseStringToWords(author_)
    );

    allKeywords.insert(ISBN_);

    return allKeywords;
}

std::string Book::displayString() const
{
    stringstream ss;

    ss << name_ << '\n'
       << "Author: " << author_ << " ISBN: " << ISBN_ << '\n'
       << price_ << "  " << qty_ << " left.";

    return ss.str();
}

void Book::dump(std::ostream& os) const
{
    os << "book" << endl
       << name_ << endl
       << price_ << endl
       << qty_ << endl
       << ISBN_ << endl
       << author_ << endl;
}