#ifndef HYDROTHERMAL_HH
#define HYDROTHERMAL_HH

#include <iostream>
#include <vector>

struct Point {
    int x, y;   
};

class SeaFloor {
    public:
        SeaFloor(int width, int height)
            : m_width{width}, m_height{height}, m_map(width*height, 0) {}

        void AddVent(Point x1, Point x2, bool diagonal) {
            // Horizontal line
            if(x1.x == x2.x) {
                if(x1.y > x2.y) std::swap(x1.y, x2.y);
                for(int i = x1.y; i <= x2.y; ++i) {
                    m_map[x1.x+m_width*i] += 1;
                }
            // Vertical line
            } else if(x1.y == x2.y) {
                if(x1.x > x2.x) std::swap(x1.x, x2.x);
                for(int i = x1.x; i <= x2.x; ++i) {
                    m_map[i+m_width*x1.y] += 1;
                }
            } else {
                // Diagonal line
                if(diagonal) {
                    if(x1.x > x2.x) std::swap(x1, x2); 
                    int direction = (x2.y - x1.y)/std::abs(x2.y - x1.y);
                    for(int i = 0; i <= x2.x - x1.x; ++i) {
                        m_map[(x1.x+i) + m_width*(x1.y+direction*i)] += 1;
                    }
                }
            }
        }

        void PrintMap() const {
            for(int i = 0; i < m_height; ++i) {
                for(int j = 0; j < m_width; ++j) {
                    if(m_map[Idx(i, j)] == 0)
                        std::cout << ".";
                    else
                        std::cout << m_map[Idx(i, j)];
                }
                std::cout << std::endl;
            }
        }

        int CalcDanger() const {
            int result = 0;
            for(const auto &elm : m_map) {
                if(elm >= 2) result++;
            }
            return result;
        }

    private:
        int Idx(int i, int j) const {
            return i*m_width + j;
        }
        int m_width, m_height;
        std::vector<int> m_map;
};

#endif
