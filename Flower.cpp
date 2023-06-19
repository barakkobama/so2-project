#include "Flower.hpp"


atomic<int> Flower::m_containingFlowers = 0;

Flower::Flower(bool big): m_big{big}
{
    ++m_containingFlowers;
    m_nectar = big ? 30.0 : 15.0;
    m_beeCapacity = big ? 3 : 1; 
}
