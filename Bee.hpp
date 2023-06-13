#ifndef BEE
#define BEE

#include <mutex>
#include <memory>
#include <shared_mutex>
#include <vector>
#include "Hive.hpp"
#include "Flower.hpp"

class Bee
{   static int id;
    int myid=0;
    float m_nectar = 0;
    bool m_full = false;
    float m_nectarPerTick = 0.01;
    float m_capacity = 5.0;
    std::shared_ptr<Hive> m_hive;


    public:
    Bee() = default;
    Bee(const float nectarPerTick, const float capacity, std::shared_ptr<Hive> hive, bool big);
    static mutex screen;
    static mutex hiveMutex;
    bool m_big;
    std::pair<int,int> m_location;

    void getNectar(Flower &flower);
    void returnNectar();
    void findFlower(std::vector<Flower> &flowers);
};

#endif