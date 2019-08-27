#include "chart.hpp"
#include <string>

std::string Chart::getType() {
    return type;
}

void Chart::addType(std::string newType) {
    type = newType;
}