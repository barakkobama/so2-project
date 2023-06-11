#ifndef FLOWER
#define FLOWER

#include <atomic>

using namespace std;

class Flower
{
    public:
    float m_nectar = 20.0;
    bool m_occupied = false;
    static atomic<int> m_containingFlowers;

    Flower();
};

#endif