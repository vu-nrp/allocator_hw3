#pragma once

#include <memory>
#include <iostream>

namespace my {

// calc factorial
template<typename T>
T factorial(T n)
{
    return (n > 1) ? (n * factorial<T>(n - 1)) : 1;
}

template<typename T, typename Alloc = std::allocator<T>>
class container
{
public:
    container()
    {
    }

    container(std::initializer_list<T> list)
    {
        for (const auto &item: list)
            insert(item);
    }

    ~container()
    {
        m_allc.deallocate(m_ptr, m_size);
        m_ptr = nullptr;
    }

    void insert(const T &value)
    {
        if (m_size == m_cap) {
            m_cap = m_size + 1;

            auto ptr = m_allc.allocate(m_cap);
            std::copy(m_ptr, m_ptr + m_size, ptr);
            std::swap(m_ptr, ptr);
            m_allc.deallocate(ptr, m_size);
        }
        m_ptr[m_size++] = value;
    }

    const T *begin() const
    {
        return m_ptr;
    }

    const T *end() const
    {
        return m_ptr + m_size;
    }

    size_t size() const
    {
        return m_size;
    }

    bool empty() const
    {
        return (m_size == 0);
    }

private:
    size_t m_cap {0};
    Alloc m_allc;
    T *m_ptr {nullptr};
    size_t m_size {0};

};

template<const int size, typename T>
class allocator : public std::allocator<T>
{
public:

    // T *allocate(std::size_t n)
    // {
    //     std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
    //
    //     auto p = std::malloc(n * sizeof(T));
    //     if (!p)
    //         throw std::bad_alloc();
    //     return reinterpret_cast<T *>(p);
    // }

};

}

