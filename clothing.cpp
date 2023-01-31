#include "clothing.h"
#include "util.h"
#include <sstream>

using namespace std;

Clothing::Clothing(const std::string category, 
                   const std::string name, 
                   double price, 
                   int qty, 
                   const std::string size, 
                   const std::string brand) 
                : 
                  Product(category, name, price, qty),
                  size_(size),
                  brand_(brand)

    {}

std::set<std::string> Clothing::keywords() const
{
    std::set<std::string> allKeywords = setUnion(
            parseStringToWords(name_),
            parseStringToWords(brand_)
    );
    
    return allKeywords;
}

std::string Clothing::displayString() const
{
    stringstream ss;

    ss << name_ << endl
       << "Size: " << size_ << " Brand: " << brand_ << endl
       << price_ << "  " << qty_ << " left.";

    return ss.str();
}

void Clothing::dump(std::ostream& os) const
{
    os << "clothing" << endl
       << name_ << endl
       << price_ << endl
       << qty_ << endl
       << size_ << endl
       << brand_ << endl;
}