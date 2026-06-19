#include <iostream>
#include <fstream>
#include <string>
#include "nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

struct Player {
    string name;
    int health;
    int maxHealth;
    int endurance;
    int speed;
    int strength;
};

struct Weapon {
    string name;
    int damage;
    float accuracy;
    float critrate;

};

struct Armor {
    string name;
    float defense;
    float evade;
};


vector<Weapon> loadWeapons(json& equipmentData){
    vector<Weapon> weaponList;

    for(auto& entry: equipmentData["weapons"]){
        Weapon newWeapon;
        newWeapon.name      = entry["name"];
        newWeapon.damage    = entry["damage"];
        newWeapon.accuracy  = entry["accuracy"];
        newWeapon.critrate  = entry["critrate"];
        weaponList.push_back(newWeapon);
    }
    return weaponList;
}

vector<Armor> loadArmors(json& equipmentData){
    vector<Armor> armorList;
    
    for(auto& entry: equipmentData["armors"]){
        Armor newArmor;
        newArmor.name      = entry["name"];
        newArmor.defense   = entry["defense"];
        newArmor.evade     = entry["evade"];

        armorList.push_back(newArmor);
    }
    return armorList;
}

int main() {
    ifstream file("Equipments.json");
    json equipmentData;
    file >> equipmentData;

    vector<Weapon> weaponList = loadWeapons(equipmentData);
    vector<Armor> armorList   = loadArmors(equipmentData);

    for (auto& weapon : weaponList) {
        cout << weapon.name << " | Damage: " << weapon.damage << endl;
    }
    cout << endl;
    for(auto& armor : armorList){
        cout << armor.name << " | Defense: " << armor.defense << " | Evade: " << armor.evade << endl;
    }

    return 0;
}
