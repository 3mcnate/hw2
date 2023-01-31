#ifndef MY_DATASTORE_H
#define MY_DATASTORE_H
#include "datastore.h"
#include <queue>
#include <map>

class MyDataStore : public DataStore
{
    public:
        ~MyDataStore();

        void addProduct(Product* p);
        void addUser(User* u);

        void addToCart(std::string user, Product* item);
        void viewCart(std::string user);
        void buyCart(std::string user);

        std::vector<Product*> search(std::vector<std::string>& terms, int type);
        
        void dump(std::ostream& ofile);

    private:
        std::vector<Product*> products_;
        std::vector<User*> users_;
        std::map<std::string, std::deque<Product*>> carts_;
        std::map<std::string, std::set<Product*>> keywordsMap_;
        std::map<std::string, User*> usernameMap_;
};

#endif