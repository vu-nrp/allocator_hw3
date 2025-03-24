#pragma once

#include <memory>
#include <iostream>

#if PRINT_ON
    #define PRINT(...) __VA_ARGS__
#else
    #define PRINT(...)
#endif

namespace my {

// calc factorial
template<typename N>
N factorial(N n)
{
    return (n > 1) ? (n * factorial<N>(n - 1)) : 1;
}

template<typename T, typename Alloc = std::allocator<T>>
class array_based_container
{
public:
    array_based_container()
    {
    }

    array_based_container(const int count, const T &init)
    {
        for (int i = 0;i < count;++i)
            insert(init);
    }

    array_based_container(std::initializer_list<T> list)
    {
        for (const auto &item: list)
            insert(item);
    }

    ~array_based_container()
    {
        m_allc.deallocate(m_ptr, m_cap);
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

template<const int Size, typename T>
class allocator : public std::allocator<T>
{
public:
    static constexpr int PoolElementsCount {Size};

    // template<class U>
    // allocator(const allocator<allocator::PoolElementsCount, U>) noexcept
    // {
    //     initMem();
    // }

    template<class U>
    struct rebind
    {
        rebind()
        {
            PRINT(std::cout << "rebind: sizeof(U) = " << sizeof(U) << " allocator::PoolElementsCount = " << allocator::PoolElementsCount << std::endl);
        }

        using other = allocator<Size, U>;
    };

    constexpr allocator() noexcept
    {
        initMem();
    }

    T *allocate(size_t n)
    {
        if ((m_allocCounter + n) > allocator::PoolElementsCount)
            throw std::bad_alloc();

        m_allocCounter += n;
        PRINT(std::cout << __FUNCTION__ << ": allocate [n = " << n << "], exist memory for " << (allocator::PoolElementsCount - m_allocCounter) << " items" << std::endl);
        return std::allocator<T>::allocate(n);
    }

    void deallocate(T* const ptr, const size_t &count)
    {
        m_allocCounter -= count;
        std::allocator<T>::deallocate(ptr, count);
        PRINT(std::cout << __FUNCTION__ << ": deallocate [ptr = " << ptr << " count = " << count << "], exist memory for " << (allocator::PoolElementsCount - m_allocCounter) << " items" << std::endl);
    }

protected:
    void initMem()
    {
        constexpr auto poolLength = sizeof(T) * allocator::PoolElementsCount;
        PRINT(std::cout << "init memory: sizeof(T) = " << sizeof(T) << ", allocator::PoolElementsCount = " << allocator::PoolElementsCount << ", allocate bytes = " << poolLength << std::endl);
        m_poolBuffer = std::shared_ptr<uint8_t>(new uint8_t[poolLength], [poolLength](uint8_t *ptr)
        {
            delete[] ptr;
            PRINT(std::cout << __FUNCTION__ << "delete memory: [pool lenght = " << poolLength << " bytes] deleted" << std::endl);
        });
    }

private:
    std::shared_ptr<uint8_t> m_poolBuffer;
    size_t m_allocCounter {0};

};

}

