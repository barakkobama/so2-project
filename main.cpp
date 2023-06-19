#include <vector>
#include <random>
#include <iostream>
#include <thread>
#include <functional>
#include "Bee.hpp"
#include "Flower.hpp"
#include "Hive.hpp"
#include "Visualisation.hpp"
#include <memory>


static std::random_device rd;
static std::mt19937 gen(rd());

bool getRandomBool()
{
    std::uniform_int_distribution<int> dis(0, 1);
    return static_cast<bool>(dis(gen));
}
float getRandomFloat(float a, float b)
{
    std::uniform_real_distribution<float> dis(a, b);
    return dis(gen);
}

int main()
{
    constexpr size_t c_flowerNumber = 6;
    constexpr size_t c_beeNumber = 4;

    constexpr float c_minBeeIntake = 0.01f;
    constexpr float c_maxBeeIntake = 0.1f;
    constexpr float c_minBeeCapasity = 2.0f;
    constexpr float c_maxBeeCapasity = 5.0f;

    auto hive = std::make_shared<Hive>();

    vector<Flower> flowers;
    flowers.resize(c_flowerNumber);
    vector<Bee> bees;
    bees.resize(c_beeNumber);

    for (int i=0; i<c_flowerNumber; ++i)
    {
        flowers[i] = Flower(getRandomBool());
    }
    
    for(int i=0; i< c_beeNumber; ++i)
    {
        bees[i] = Bee(
            getRandomFloat(c_minBeeIntake, c_maxBeeIntake),
            getRandomFloat(c_minBeeCapasity, c_maxBeeCapasity),
            hive,
            getRandomBool() || getRandomBool()
        );
    }


    vector<thread> beeThreads(c_beeNumber);

    Visualisation vis;

    vis.prepereScreen(flowers, bees, hive);
    for (int i=0; i < c_beeNumber; i++)
    {
        beeThreads[i] = thread(&Bee::findFlower, &bees[i], ref(flowers), ref(vis));
    }

    for (auto& bee : beeThreads)
    {
        bee.join();
    }
   
    //cout<<"All the flowers are empty, time to find a new meadow!\n";
}