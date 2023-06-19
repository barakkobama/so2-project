#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
//#include <windows.h>  //FOR WINDOWS
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
    system("clear");        //FOR LINUX
    //system("cls");        //FOR WINDOWS
    //std::cout << "\033[2J\033[1;1H";
}

//Funckja przygotowuje ekran obliczajc pozycje kwiatkow i ula
void Visualisation::prepereScreen(vector<Flower>& flowers, vector<Bee>& bees, std::shared_ptr<Hive> hive){
    this->clearScreen();
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

//Funckja ustawiajaca pozycje pszczol
void Visualisation::updateScreen(Bee& bee)
{
    
    this->display[bee.m_last_location.first][bee.m_last_location.second] = ' ';     //Usuwanie starego znacznika pszczoly
    this->display[bee.m_last_location.first][bee.m_last_location.second + 1] = ' ';
    this->display[bee.m_location.first][bee.m_location.second] = bee.m_big ? this->bigBeeSymbol : this->smallBeeSymbol;
    this->display[bee.m_location.first][bee.m_location.second + 1] = bee.myid;
}

void Visualisation::displayAnimation(Bee& bee) {
 
    this->clearScreen();
    this->updateScreen(bee);
    for(int i = 0; i < this->rows; ++i)
    {
        for(int j = 0; j < this->columns; ++j)
        {
            std::cout<<this->display[i][j]<<" ";
        }
        std::cout<<endl;
    }    
}
