//
//  House.hpp
//  FinalProject
//
//  Created by Kevin Jin on 6/8/20.
//  Copyright © 2020 Kevin Jin. All rights reserved.
//

#ifndef HOUSE_H
#define HOUSE_H

#include <string>
#include <iostream>
#include <iomanip>

class House {
private:
    std::string address;
    long price;
    int beds, baths;
    std::string type;
    int area;
    
public:
    House();
    House(std::string, long, int, int, std::string, int);
    
    void setAddress(std::string a) {
        address = a;
    }
    std::string getAddress() const {
        return address;
    }
    void setPrice(long p) {
        price = p;
    }
    long getPrice() const {
        return price;
    }
    void setBeds(int b) {
        beds = b;
    }
    int getBeds() const {
        return beds;
    }
    void setBaths(int b) {
        baths = b;
    }
    int getBaths() const {
        return baths;
    }
    void setType(std::string t) {
        type = t;
    }
    std::string getType() const {
        return type;
    }
    void setArea(int a) {
        area = a;
    }
    int getArea() const {
        return area;
    }
    
    bool operator == (const House&) const;
    bool operator < (const House&) const;
    bool operator > (const House&) const;
    bool operator >= (const House&) const;
    bool operator <= (const House&) const;
    
    friend std::ostream& operator << (std::ostream&, const House&);
};

#endif /* HOUSE_H */
