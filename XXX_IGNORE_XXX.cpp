#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

// Define the MapInfo struct
struct MapInfo {
    std::string name;
    int difficulty;
    std::string background;
};

// Function to read the file and populate the MapInfo struct
MapInfo readMapInfo(const std::string& fileName) {
    MapInfo mapInfo;
    std::ifstream file(fileName);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + fileName);
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string key;
        if (std::getline(iss, key, ':')) {
            std::string value;
            if (std::getline(iss >> std::ws, value)) {
                if (key == "name") {
                    mapInfo.name = value;
                } else if (key == "difficulty") {
                    mapInfo.difficulty = std::stoi(value);
                } else if (key == "background") {
                    mapInfo.background = value;
                }
            }
        }
    }

    file.close();
    return mapInfo;
}

int main() {
    try {
        MapInfo mapInfo = readMapInfo("map_info.txt");

        std::cout << "Name: " << mapInfo.name << std::endl;
        std::cout << "Difficulty: " << mapInfo.difficulty << std::endl;
        std::cout << "Background: " << mapInfo.background << std::endl;
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }

    return 0;
}