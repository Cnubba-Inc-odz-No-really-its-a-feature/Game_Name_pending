#ifndef _INVENTORY_HPP
#define _INVENTORY_HPP

#include "memory"
#include "gameObject.hpp"

///\brief
/// is this used?
struct inventory{
    std::shared_ptr<std::vector<std::shared_ptr<gameObject>>> itemList;
};

#endif