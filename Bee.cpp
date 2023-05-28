#include "Bee.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>

using namespace std;

int Bee::id = 0;
mutex Bee::screen;

//Pszczoly moga miec rozna predkosc pobierania nektaru oraz rozne pojemnosci
Bee::Bee(const float nectarPerTick, const float capacity, Hive &hive) : m_nectarPerTick(nectarPerTick), m_capacity(capacity), m_hive{hive}
{
    myid = id;
    this->id++;
};

//Zwraca nektar do ula
void Bee::returnNectar()
{
    screen.lock();
    cout << "bee " << myid << " zwraca nektar do ula " << endl;
    screen.unlock();

    this->m_hive.m_nectarLevel += this->m_nectar;
    this->m_nectar = 0;
    this_thread::sleep_for(chrono::seconds(1));
}

//Funckja wykonujaca sie w kazdym przebiegu glownej petli, decyduje o powrocie do ula i o ilosci zebranego nektaru
void Bee::getNectar(Flower &flower)
{
    screen.lock();
    cout << "getnectar... by bee " << myid <<" with " <<this->m_nectar<< endl;
    screen.unlock();

    int licznik = 0;
    while(this->m_nectar + this->m_nectarPerTick <= this->m_capacity && flower.m_nectar > 0)
    {
        screen.lock();
        cout << "pobieranie by bee " << myid << " po raz " << licznik << endl;
        licznik = licznik + 1;
        screen.unlock();

        flower.m_nectar -= this->m_nectarPerTick;
        this_thread::sleep_for(chrono::milliseconds(1000));
        this->m_nectar += this->m_nectarPerTick;
    }

    if(flower.m_nectar <= 0)
    {
        //--Flower::m_fullFlowers;
        --flower.m_containingFlowers;
    }

    flower.m_occupied = false;
    this->returnNectar();
}

//Ta funckja bedzie w watku
void Bee::findFlower(vector<Flower> &flowers)
{
    while (Flower::m_containingFlowers)
    {
        screen.lock();
        cout << "Finding a flower... by bee " << myid << endl;
        screen.unlock();

        for (auto& flower : flowers)
        {
            screen.lock();
            cout << "Flower with "<< flower.m_nectar <<" is found by bee " << myid << endl;
            screen.unlock();

            if (!flower.m_occupied && flower.m_nectar > 0)
            {
                flower.m_occupied = true;
                screen.lock();
                cout << "Flower found statring acquiering nectar... by bee" << myid << endl;
                screen.unlock();
                this_thread::sleep_for(chrono::milliseconds(10000));
                this->getNectar(flower);
                //flower.m_occupied = false;  //usunac jak bedzie funkcja opuszczania kwiata
                break;
            }
            else
                {
                    this_thread::sleep_for(chrono::milliseconds(1000));
                }
        }
    }
}