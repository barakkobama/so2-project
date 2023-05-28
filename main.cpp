#include <vector>
#include <random>
#include <iostream>
#include <thread>
#include <functional>
#include "Bee.h"
#include "Bumblebee.h"
#include "Flower.h"
#include "Hive.h"

using namespace std;

float getRandomFloat(float a, float b)
{
    static random_device rd;
    static mt19937 gen(rd());
    uniform_real_distribution<float> dis(a, b);

    return dis(gen);
}

int main()
{
    constexpr size_t c_flowerNumber = 2;
    constexpr size_t c_beeNumber = 4;
    //constexpr size_t c_bumblebeeNumber = 2;

    constexpr float c_minBeeIntake = 0.01f;
    constexpr float c_maxBeeIntake = 0.1f;
    constexpr float c_minBeeCapasity = 5.0f;
    constexpr float c_maxBeeCapasity = 10.0f;

    Hive hive;

    vector<Flower> flowers (c_flowerNumber);
    vector<Bee> bees;
    bees.resize(c_beeNumber);
    
    for(int i=0; i< c_beeNumber; ++i)
    {
        bees[i] = Bee(
            getRandomFloat(c_minBeeIntake, c_maxBeeIntake),
            getRandomFloat(c_minBeeCapasity, c_maxBeeCapasity),
            hive
        );
    }

    vector<Bumblebee> bumblebees ;

    vector<thread> beeThreads(c_beeNumber);

    for (int i=0; i < c_beeNumber; i++)
    {
        beeThreads[i] = thread(&Bee::findFlower, &bees[i], ref(flowers));
    }

    for (auto& bee : beeThreads)
    {
        bee.join();
    }


    /*mutex flowersMutex;
    while(Flower::m_fullFlowers > 0)
    {
        for(int i{0}; i < c_beeNumber; ++i)
        {
            lock_guard<mutex> lock(flowersMutex);
            beeThreads[i] = thread(&Bee::findFlower, &bees[i], ref(flowers));
        }
    }*/
   
    cout<<"All the flowers are empty, time to find a new meadow!\n";
    /*
    for( auto& bee : beeThreads)
    {
        bee.join();
    }*/
}