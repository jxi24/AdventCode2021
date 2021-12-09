#ifndef HEIGHT_MAP_HH
#define HEIGHT_MAP_HH

#include <array>
#include <iostream>
#include <vector>
#include <algorithm>

class HeightMap {
    public:
        HeightMap(int rows, int cols) : m_rows{rows}, m_cols{cols}, m_heights(rows*cols) {}
        void AddRow(int row, std::vector<int> heights) {
            for(std::size_t i = 0; i < m_cols; ++i) {
                m_heights[row*m_cols + i] = heights[i];
            }
        }
        void PrintMap() const {
            // Loop over all points
            for(std::size_t iRow = 0; iRow < m_rows; ++iRow) {
                for(std::size_t iCol = 0; iCol < m_cols; ++iCol) {
                    std::cout << m_heights[iCol + iRow*m_cols];
                }
                std::cout << std::endl;
            }
        }
        std::vector<int> FindLowPoints() {
            std::vector<int> lowPoints;
            // Loop over all points
            for(std::size_t iRow = 0; iRow < m_rows; ++iRow) {
                for(std::size_t iCol = 0; iCol < m_cols; ++iCol) {
                    std::vector<int> allowedMoves;
                    // Up allowed
                    if(iRow != 0) allowedMoves.push_back(-m_cols);
                    // Down allowed
                    if(iRow != m_rows-1) allowedMoves.push_back(m_cols);
                    // Left allowed
                    if(iCol != 0) allowedMoves.push_back(-1);
                    // Right allowed
                    if(iCol != m_cols-1) allowedMoves.push_back(1);

                    // Check if all points are higher
                    int idx = m_cols*iRow + iCol;
                    int current = m_heights[idx];
                    bool lowPoint = true;
                    for(const auto &move : allowedMoves) {
                        if(m_heights[idx+move] <= current) {
                            lowPoint = false;
                            break;
                        }
                    }
                    if(lowPoint) {
                        lowPoints.push_back(current+1);
                        m_basin_seeds.push_back({iRow, iCol});
                    }
                }
            }
            return lowPoints;
        }
        std::vector<int> FindBasins() const {
            std::vector<int> basins;
            for(const auto &seed : m_basin_seeds) {
                basins.push_back(BuildBasin(seed.first, seed.second)); 
            }
            return basins;
        }

    private:
        int BuildBasin(int row, int col) const {
            static std::vector<std::pair<int, int>> visted;
            if(std::find(visted.begin(), visted.end(), std::pair<int, int>{row, col}) != visted.end()) return 0;
            visted.push_back({row, col});
            if(m_heights[m_cols*row+col] == 9) return 0;
            int size = 1;
            // Move up
            if(row != 0) size += BuildBasin(row-1, col);
            // Move down
            if(row != m_rows-1) size += BuildBasin(row+1, col);
            // Move left
            if(col != 0) size += BuildBasin(row, col-1);
            // Move right
            if(col != m_cols-1) size += BuildBasin(row, col+1);
            return size;
        }
        int m_rows, m_cols;
        std::vector<int> m_heights;
        std::vector<std::pair<int, int>> m_basin_seeds;
    
};

#endif
