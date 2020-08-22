//
//  House.cpp
//  FinalProject
//
//  Created by Kevin Jin on 6/13/20.
//  Copyright © 2020 Kevin Jin. All rights reserved.
//

#include "House.h"

bool House::operator == (const House& right) const {
    if (address == right.getAddress())
        return true;
    else
        return false;
}

bool House::operator < (const House& right) const {
    if (!(price < right.getPrice()))
        return false;
    return true;
}

bool House::operator > (const House& right) const {
    if (!(price > right.getPrice()))
        return false;
    return true;
}

bool House::operator >= (const House& right) const {
    if (!(price >= right.getPrice()))
        return false;
    return true;
}

bool House::operator <= (const House& right) const {
    if (!(price <= right.getPrice()))
        return false;
    return true;
}

House::House() {
    address = "";
    price = 0;
    beds = 0;
    baths = 0;
    type = "";
    area = 0;
}

House::House(std::string adrs, long p, int bds, int bths, std::string t, int a) {
    address = adrs;
    price = p;
    beds = bds;
    baths = bths;
    type = t;
    area = a;
}

std::ostream& operator << (std::ostream& out, const House& right) {
    out << std::right << "$" << std::setw(8) << right.price << ": "
        << right.address << ", "
        << right.beds << ", "
        << right.baths << ", "
        << right.type << ", "
        << right.area;
    return out;
}
