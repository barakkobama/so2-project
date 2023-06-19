#ifndef BEE
#define BEE

#include <mutex>
#include <memory>
#include <shared_mutex>
#include <vector>
#include "Hive.hpp"
#include "Flower.hpp"
#include "Visualisation.hpp"

class Visualisation;

class Bee
{   
    static char id;
    float m_nectar = 0;
    bool m_full = false;
    float m_nectarPerTick = 0.01;
    float m_capacity = 5.0;
    std::shared_ptr<Hive> m_hive;


    public:
    char myid;
    Bee() = default;
    Bee(const float nectarPerTick, const float capacity, std::shared_ptr<Hive> hive, bool big);
    static mutex screen;
    static mutex hiveMutex;
    bool m_big;
    std::pair<int,int> m_last_location;
    std::pair<int,int> m_location;

    void getNectar(Flower &flower,Visualisation& vis);
    void returnNectar(Visualisation& vis);
    void findFlower(std::vector<Flower> &flowers, Visualisation& vis);
};


#endif