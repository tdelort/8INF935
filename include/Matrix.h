#pragma once

#include <initializer_list>
#include <iostream>
#include <cassert>

template<typename T, size_t N, size_t M>
class Matrix
{
protected:
    double m_data[N * M];
    size_t m_n;
    size_t m_m;
public:
    Matrix();
    Matrix(std::initializer_list<std::initializer_list<T>> row_list);
};

template<typename T, size_t N, size_t M>
Matrix<T,N,M>::Matrix()
    : m_n(N), m_m(M)
{
    memset(m_data, 0, sizeof(double) * m_n * m_m);
}

template<typename T, size_t N, size_t M>
Matrix<T,N,M>::Matrix(std::initializer_list<std::initializer_list<T>> row_list)
    : m_n(N), m_m(M)
{
    if(row_list.size() != m_n)
    {
        std::cerr << "Matrix<T,N,M>::Martix(std::initializer_list<std::initializer_list<T>>) : ";
        std::cerr << row_list.size() << " rows were given but was expecting " << m_n << std::endl;
        assert(false);
    }

    int i = 0;
    for (auto const& row : row_list)
    {
        if(row.size() != m_m)
        {
            std::cerr << "Matrix<T,N,M>::Martix(std::initializer_list<std::initializer_list<T>>) : ";
            std::cerr << "row with length " << row_list.size() << " was given but was expecting " << m_m << std::endl;
            assert(false);
        }

        for (auto const& val : row) 
        {
            m_data[i] = val;
            i++;
        }
    }
}