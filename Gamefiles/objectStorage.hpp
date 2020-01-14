#ifndef _OBJECTSTORAGE_HPP_
#define _OBJECTSTORAGE_HPP_

#include "vector"
#include "queue"
#include "gameObject.hpp"


class objectStorage {
public:
    std::vector<gameObject*> allObjects;
    std::vector<gameObject*> menu;
    std::vector<gameObject*> game;
};

#endif // _OBJECTSTORAGE_HPP_