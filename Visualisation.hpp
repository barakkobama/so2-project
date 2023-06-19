#ifndef VISUALISATION
#define VISUALISATION
#include "Bee.hpp"
#include "Flower.hpp"
#include "Hive.hpp"
#include <vector>
#include <utility>
#include <memory>

class Bee;

class Visualisation
{

    static constexpr int rows {20};
    static constexpr int columns {50};
    public:

    char bigBeeSymbol {'B'};
    char smallBeeSymbol {'b'};
    char bigFlowerSymbol {'F'};
    char smallFlowerSymbol {'f'};
    char hiveSymbol {'H'};

    char display[rows][columns];

    Visualisation();
    void clearScreen();
    void prepereScreen(vector<Flower>& flowers, vector<Bee>& bees, std::shared_ptr<Hive> hive);
    void displayAnimation(Bee& bee);
    void updateScreen(Bee& bee);
    

};

#endif