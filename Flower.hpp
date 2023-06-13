#ifndef FLOWER
#define FLOWER

#include <atomic>
#include <utility>

using namespace std;

class Flower
{
    public:
    float m_nectar;
    bool m_occupied = false;
    static atomic<int> m_containingFlowers;
    bool m_big;
    int m_beeCapacity;
    std::pair<int,int> m_location;


    Flower() = default;
    Flower(bool big);
};

#endif