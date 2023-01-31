#include "mydatastore.h"
#include "util.h"
#include <cassert>

using namespace std;

MyDataStore::~MyDataStore()
{
    for (size_t i = 0; i < products_.size(); i++) {
        delete products_[i];
    }

    for (size_t i = 0; i < users_.size(); i++) {
        delete users_[i];
    }
}

void MyDataStore::addProduct(Product* p)
{
    products_.push_back(p);
    
    // add to keyword mapping
    set<string> productKeywords = p->keywords();
    for (set<string>::iterator it = productKeywords.begin(); it != productKeywords.end(); ++it) {
        keywordsMap_[*it].insert(p);
    }
}

void MyDataStore::addUser(User* u)
{
    users_.push_back(u);
    usernameMap_[convToLower(u->getName())] = u;
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
    if (terms.size() == 0) {
        return std::vector<Product*>(0);
    }

    std::set<Product*> matchingProducts = keywordsMap_[terms[0]];
    
    // AND search
    if (type == 0) {
        for (size_t i = 1; i < terms.size(); i++) {
            matchingProducts = setIntersection(keywordsMap_[terms[i]], matchingProducts);
        }
    }

    // OR search
    else if (type == 1){
        for (size_t i = 1; i < terms.size(); i++) {
            matchingProducts = setUnion(keywordsMap_[terms[i]], matchingProducts);
        }
    }

    std::vector<Product*> searchHits(matchingProducts.begin(), matchingProducts.end());
    
#ifdef DEBUG
    for (size_t i = 0; i < searchHits.size(); i++) {
        assert(searchHits[i] != NULL);
    }
#endif 

    return searchHits;
}

void MyDataStore::addToCart(string user, Product* item)
{
    if (usernameMap_.find(user) == usernameMap_.end()) {
        cout << "Invalid request" << endl;
        return;
    }
    carts_[user].push_back(item);
}

void MyDataStore::viewCart(std::string user)
{
    if (carts_.find(user) == carts_.end()) {
        cout << "Invalid username" << endl;
        return;
    }

    deque<Product*> & cart = carts_[user];
    int itemNo = 1;
    for (deque<Product*>::iterator it = cart.begin(); it != cart.end(); ++it) {
        cout << endl << "Item " << itemNo++ << ":" << endl;
        cout << (*it)->displayString() << endl;
    }
}

void MyDataStore::buyCart(std::string username)
{
    if (carts_.find(username) == carts_.end()) {
        cout << "Invalid username" << endl;
        return;
    }
    
    deque<Product*> & cart = carts_[username];
    User* user = usernameMap_[username];

    deque<Product*>::iterator it = cart.begin();
    while (it != cart.end()) {
        if ((*it)->getPrice() <= user->getBalance() &&
            (*it)->getQty() > 0)
        {
            user->deductAmount((*it)->getPrice());
            (*it)->subtractQty(1);

            it = cart.erase(it);
        }
        else {
            ++it;
        }
    }
}

void MyDataStore::dump(std::ostream& ofile)
{
    ofile << "<products>" << endl;
    for (size_t i = 0; i < products_.size(); i++) {
        products_[i]->dump(ofile);
    }
    ofile << "</products>" << endl;
    
    ofile << "<users>" << endl;
    for (size_t i = 0; i < users_.size(); i++) {
        users_[i]->dump(ofile);
    }
    ofile << "</users>" << endl;
}