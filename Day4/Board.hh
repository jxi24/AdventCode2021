#ifndef BOARD_HH
#define BOARD_HH

#include <array>
#include <iostream>

class Board {
    public:
        Board(std::array<int, 25> board) : m_board{std::move(board)} {};
        void Mark(int val) {
            for(std::size_t i = 0; i < m_rows; ++i) {
                for(std::size_t j = 0; j < m_cols; ++j) {
                    std::size_t pos = GetPos(i, j);
                    if(m_board[pos] == val)
                        m_marked[pos] = true;
                }
            }
        }
        bool Winner() const {
            PrintBoard();
            std::cout << RowWin() << " " << ColWin() << std::endl;
            return RowWin() || ColWin();
        }
        int Score(int val) const {
            int sum = 0;
            for(std::size_t i = 0; i < m_rows; ++i) {
                for(std::size_t j = 0; j < m_cols; ++j) {
                    std::size_t pos = GetPos(i, j);
                    if(!m_marked[pos])
                        sum += m_board[pos];
                }
            }

            return sum * val;
        }
        void PrintBoard() const {
            for(std::size_t i = 0; i < m_rows; ++i) {
                for(std::size_t j = 0; j < m_cols; ++j) {
                    std::size_t pos = GetPos(i, j);
                    std::cout << m_board[pos];
                    if(m_marked[GetPos(i, j)]) {
                        std::cout << "*";
                    } else {
                        std::cout << " ";
                    }
                    std::cout << " ";
                }
                std::cout << std::endl;
            }
        }

    private:
        std::size_t GetPos(std::size_t row, std::size_t col) const {
            return m_cols*row + col;
        }
        bool RowWin() const {
            for(std::size_t i = 0; i < m_rows; ++i) {
                bool winner = true;
                for(std::size_t j = 0; j < m_cols; ++j) {
                    if(!m_marked[GetPos(i, j)]) {
                        winner = false;
                        break;
                    }
                }
                if(winner) return true;
            }
            return false;
        }
        bool ColWin() const {
            for(std::size_t j = 0; j < m_cols; ++j) {
                bool winner = true;
                for(std::size_t i = 0; i < m_rows; ++i) {
                    if(!m_marked[GetPos(i, j)]) {
                        winner = false;
                        break;
                    }
                }
                if(winner) return true;
            }
            return false;
        }
        static constexpr int m_rows{5}, m_cols{5};
        std::array<int, m_rows*m_cols> m_board;
        std::array<bool, m_rows*m_cols> m_marked{false};
};

#endif
