#pragma once

#include <initializer_list>

template<typename T, size_t N, size_t M>
class Matrix
{
private:
    T m_data[N * M];
    size_t m_n = N;
    size_t m_m = M;
public:
    Matrix();
    Matrix(std::initializer_list<std::initializer_list<T>> row_list);
};