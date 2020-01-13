#ifndef _OBJECTSTORAGE_HPP_
#define _OBJECTSTORAGE_HPP_

#include "vector"
#include "gameObject.hpp"
#include "memory"


class objectStorage {
public:
    std::vector<std::shared_ptr<gameObject>> allObjects;
    std::vector<std::shared_ptr<gameObject>> menu;
    std::vector<std::shared_ptr<gameObject>> game;
};

#endif // _OBJECTSTORAGE_HPP_