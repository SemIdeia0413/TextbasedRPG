#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "nlohmann/json.hpp"

using ordered_json = nlohmann::ordered_json;
using namespace std;
using json = nlohmann::json;

/*  =====================================================
    |                       STRUCTS                     |
    =====================================================
*/
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
    int defense;
    float evade;
};


/*  =====================================================
    |                DATA LOADING                       |
    =====================================================
*/
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

Player loadPlayer(json& saveData) {
    Player player;
    player.name         = saveData["name"];
    player.health       = saveData["health"];
    player.maxHealth    = saveData["maxHealth"];
    player.endurance    = saveData["endurance"];
    player.speed        = saveData["speed"];
    player.strength     = saveData["strength"];
    return player;
}

void savePlayer(Player& player, string filename){
    json saveData;
    
    saveData["name"]        = player.name;
    saveData["health"]      = player.health;
    saveData["maxHealth"]   = player.maxHealth;
    saveData["endurance"]   = player.endurance;
    saveData["speed"]       = player.speed;
    saveData["strength"]    = player.strength;
    
    ofstream file(filename);
    file << saveData.dump(4);
}

/*  =====================================================
    |               COMBAT CALCULATIONS                 |
    =====================================================
*/
int calculateDamage(int strength, int weaponDamage){
    return strength * weaponDamage;
}

int calculateDefense(int endurance, int armorDefense){
    return endurance * armorDefense;
}

int calculateFinalDamage(int rawDamage,  int defense){
    int finalDamage =  rawDamage - defense;
    return(finalDamage > 0) ? finalDamage : 0;
}


/*  =====================================================
    |                       MAIN                        |
    =====================================================
*/
int main() {
    ifstream Equipfile("Equipments.json");
    json equipmentData;
    Equipfile >> equipmentData;



    vector<Weapon> weaponList = loadWeapons(equipmentData);
    vector<Armor> armorList   = loadArmors(equipmentData);

    Player player;

    ifstream saveFile("savegame.json");
    if(saveFile.is_open() && saveFile.peek() != ifstream::traits_type::eof()){
        json saveData;
        saveFile >> saveData;
        player = loadPlayer(saveData);
    } else {
        player.name = "Hero";
        player.health = 10;
        player.maxHealth = 10;
        player.endurance = 1;
        player.speed = 1;
        player.strength = 1;

        ordered_json newSaveData;
        newSaveData["name"] = player.name;
        newSaveData["maxHealth"] = player.health;
        newSaveData["health"] = player.maxHealth;
        newSaveData["endurance"] = player.endurance;
        newSaveData["speed"] = player.speed;
        newSaveData["strength"] = player.strength;

        ofstream outFile("savegame.json");
        outFile << newSaveData.dump(4);

        cout << "savegame.json created" << endl;
    }

    for (auto& weapon : weaponList) {
        cout << weapon.name << " | Damage: " << weapon.damage << endl;
    }
    cout << endl;
    for(auto& armor : armorList){
        cout << armor.name << " | Defense: " << armor.defense << " | Evade: " << armor.evade << endl;
    }

    return 0;
}
