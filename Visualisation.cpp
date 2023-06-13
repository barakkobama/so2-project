#include <iostream>
#include <thread>
#include <chrono>
#include "Visualisation.hpp"


Visualisation::Visualisation()
{
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            this->display[i][j] = ' ';
        }
    }
}

void Visualisation::clearScreen() {
    // Clear the console screen
    std::cout << "\033[2J\033[1;1H";
}


void Visualisation::prepereScreen(vector<Flower>& flowers, vector<Bee>& bees, std::shared_ptr<Hive> hive){

    hive->m_location.first = this->rows/2;
    hive->m_location.second = 1;

    this->display[hive->m_location.first][hive->m_location.second] = this->hiveSymbol;

    int flowerRow = 1;
    for(auto& flower : flowers)
    {
        flower.m_location.first = flowerRow;
        flower.m_location.second = 15;
        this->display[flower.m_location.first][flower.m_location.second] = flower.m_big ? this->bigFlowerSymbol : this->smallFlowerSymbol;
        flowerRow+= this->rows/flowers.size();
    }
}

void Visualisation::updateScreen(vector<Bee>& bees)
{
    for (auto& bee : bees)
    {
        this->display[bee.m_location.first][bee.m_location.second] = bee.m_big ? this->bigBeeSymbol : this->smallBeeSymbol;
    }
}

void Visualisation::displayAnimation(vector<Bee>& bees) {
 
    while(true){
        this->clearScreen();
        updateScreen(bees);
        for(int i = 0; i < this->rows; ++i)
        {
                for(int j = 0; j < this->columns; ++j)
                {
                    std::cout<<this->display[i][j]<<" ";
                }
                std::cout<<endl;
        }
    }
    
}
