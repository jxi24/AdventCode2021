#ifndef LANTERNFISH_HH
#define LANTERNFISH_HH

#include <cstddef>

class LanternFish {
    public:
        LanternFish(size_t timer, size_t weight=1) : m_timer{timer}, m_weight{weight} {}
        void Tick() { m_timer -= 1; }
        LanternFish Reset() {
            m_timer = 6;
            return LanternFish(8, m_weight);
        }
        size_t& Age() { return m_timer; }
        size_t Age() const { return m_timer; }
        size_t& Weight() { return m_weight; }
        size_t Weight() const { return m_weight; }

    private:
        size_t m_timer, m_weight;
};

#endif
