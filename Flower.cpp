#include "Flower.h"

using namespace std;

atomic<int> Flower::m_containingFlowers = 0;

Flower::Flower()
{
    ++m_containingFlowers;
}
