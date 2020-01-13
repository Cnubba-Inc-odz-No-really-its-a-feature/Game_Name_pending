#ifndef _GAMESTORAGE_HPP
#define _GAMESTORAGE_HPP
#include "memory"
#include "gameObject.hpp"
#include <iostream>

class gameStorage{
private:
    std::vector<std::shared_ptr<gameObject>> storage;
    int count = 0;
public:
    void add(std::shared_ptr<gameObject> newObject){
        if(count != 10 ){
            std::cout<<"object Added to storage" << std::endl;
            storage.push_back(newObject);
            count++;
        }
    }


    std::vector<std::shared_ptr<gameObject>> &get(){return storage;}
    std::shared_ptr<gameObject> getObject(){std::cout<<storage.size() << std::endl;return storage[0];}


};


#endif