#ifndef BEE
#define BEE

#include <mutex>
#include <shared_mutex>
#include <vector>
#include "Hive.h"
#include "Flower.h"

class Bee
{   static int id;
    int myid=0;
    float m_nectar = 0;
    bool m_full = false;
    float m_nectarPerTick = 0.01;
    float m_capacity = 5.0;
    Hive m_hive;

    public:
    Bee() = default;
    Bee(const float nectarPerTick, const float capacity, Hive &hive);
    static mutex screen;

    void getNectar(Flower &flower);
    void returnNectar();
    void findFlower(std::vector<Flower> &flowers);
};

#endif