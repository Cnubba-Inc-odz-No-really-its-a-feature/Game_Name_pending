#include "renderer.hpp"

bool objSort(const std::shared_ptr<gameObject> & lhs, const std::shared_ptr<gameObject> & rhs)
{
    return lhs->objectPriority < rhs->objectPriority;
}