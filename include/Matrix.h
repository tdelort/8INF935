#pragma once

#include <initializer_list>
#include <iostream>
#include <cassert>

template<typename T, size_t N, size_t M>
class Matrix
{
protected:
    T m_data[N * M];
    size_t m_n;
    size_t m_m;
public:
    Matrix();
    Matrix(std::initializer_list<std::initializer_list<T>> row_list);
    
    // getters and setters for the matrix elements
    T operator()(size_t i, size_t j) const 
    { 
        return m_data[i * m_m + j]; 
    };

    T& operator()(size_t i, size_t j) 
    { 
        return m_data[i * m_m + j]; 
    };
    size_t n() const { return m_n; };
    size_t m() const { return m_m; };

    // stream operator for printing the matrix
    friend std::ostream& operator<<(std::ostream& os, const Matrix<T, N, M>& m)
    {
        for (size_t i = 0; i < m.m_n; i++)
        {
            for (size_t j = 0; j < m.m_m; j++)
            {
                os << m(i, j) << " ";
            }
            os << std::endl;
        }
        return os;
    }

};

template<typename T, size_t N, size_t M>
Matrix<T,N,M>::Matrix()
    : m_n(N), m_m(M)
{
    memset(m_data, 0, sizeof(T) * m_n * m_m);
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