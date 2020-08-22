#ifndef INVENTORY_DATABASE_H
#define INVENTORY_DATABASE_H

#include "House.h"

#include <string>

class Inventory {
private:
    int invArrSize;
    House* inventory;
    int invSize; // House objects in the array that are initialized
    std::string HouseData;
    
public:
    void updateHouseData();
    Inventory();
//    Inventory(std::string HouseData);
    Inventory(int invArrSize, House inventory[], int invSize, std::string HouseData);
    Inventory(const Inventory& i);

    ~Inventory();

    House* getInventory() const {
        return inventory;
    }
    
    void setHouseData(std::string houseData);

    int getInvSize() const;

    House searchHouse(std::string address) const;

    // Add House functions must also add to the txt file and also increment invSize
    void addHouse(House house, bool update = true);
    void addHouse(std::string address, long price, int beds, int baths, std::string type, int area, bool update = true);

    // Also remember to delete from txt file and decrement invSize
    bool deleteHouse(House House);
    bool deleteHouse(std::string address);
    
    void operator=(const Inventory &right);
};

#endif
