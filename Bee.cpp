#include "Bee.hpp"
#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <memory>
#include <utility>


char Bee::id = '1';
mutex Bee::screen;
mutex Bee::hiveMutex;

//Pszczoly moga miec rozna predkosc pobierania nektaru oraz rozne pojemnosci
Bee::Bee(const float nectarPerTick, const float capacity, std::shared_ptr<Hive> hive, bool big) :
         m_nectarPerTick(nectarPerTick), m_capacity(capacity), m_hive{hive}, m_big{!big}
{
    myid = id++;
};

//Rekurencyjnie spradza czy dane miejsce w kolejce do ula jest zajete
//jak jest to przesuwa Y o jeden w dol
int checkAndIncreaseQueue(Visualisation& vis, int row, int column, int queue)
{
    if (vis.display[row + queue][column] != ' ') {
        return checkAndIncreaseQueue(vis, row, column, queue + 1); 
    } else {
        return queue; 
    }
}

//Zwraca nektar do ula
void Bee::returnNectar(Visualisation& vis)
{
    int queue = checkAndIncreaseQueue(vis,m_hive->m_location.first+1,m_hive->m_location.second,0);
    
    this->m_last_location = this->m_location;
    this->m_location.first = m_hive->m_location.first + 1 + queue;
    this->m_location.second = m_hive->m_location.second;
    vis.displayAnimation(*this);

    hiveMutex.lock();
    this_thread::sleep_for(chrono::milliseconds(1000));
    this->m_hive->m_nectarLevel += this->m_nectar;
    this->m_nectar = 0;
    hiveMutex.unlock();
}

//Funckja wykonujaca sie w kazdym przebiegu glownej petli, decyduje o powrocie do ula i o ilosci zebranego nektaru
void Bee::getNectar(Flower &flower, Visualisation& vis)
{
    this->m_last_location = this->m_location;
    this->m_location.first = flower.m_location.first;
    this->m_location.second = flower.m_location.second - 2;
    vis.displayAnimation(*this);
    this_thread::sleep_for(chrono::milliseconds(10000));

    while(this->m_nectar + this->m_nectarPerTick <= this->m_capacity && flower.m_nectar > 0)
    {
        flower.m_nectar -= this->m_nectarPerTick;
        this->m_nectar += this->m_nectarPerTick;
    }


    if(flower.m_nectar <= 0)
    {
        --flower.m_containingFlowers;
    }

    flower.m_occupied = false;

    this->returnNectar(vis);

}

//Ta funckja bedzie w watku
void Bee::findFlower(vector<Flower> &flowers, Visualisation& vis)
{

    while (Flower::m_containingFlowers)
    {

        for (auto& flower : flowers)
        {
            if((!flower.m_big && !this->m_big) || flower.m_big)
             {
                if (!flower.m_occupied && flower.m_nectar > 0)
                {
                    flower.m_occupied = true;
                    this_thread::sleep_for(chrono::milliseconds(1000));
                    this->getNectar(flower,vis);
                    break;
                }
            }
            else
            {
                this_thread::sleep_for(chrono::milliseconds(1000));
            }
        }
    }
}