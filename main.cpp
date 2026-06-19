#include <iostream>
#include <fstream>
#include <string>
#include <C:\Users\SemIdeia\Documents\Visual Studio Code\Projetos\TextbasedRPG\json.hpp>

using json = nlohmann::json;

int main() {
    std::ifstream file("Equipaments.json");

    json data;
    file >> data;

    std::cout << "TextbasedRPG starting..." << std::endl;
    std::cout << data["name"]["dagger"]["damage"] << std::endl;


    return 0;
}
