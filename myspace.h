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

    container(const int count, const T &init)
    {
        for (int i = 0;i < count;++i)
            insert(init);
    }

    container(std::initializer_list<T> list)
    {
        for (const auto &item: list)
            insert(item);
    }

    ~container()
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
    static constexpr int PoolSize {Size};

    template<class U>
    allocator(const allocator<allocator::PoolSize, U>) noexcept
    {
        initMem();
    }

    template<class U>
    struct rebind
    {
        using other = allocator<allocator::PoolSize, U>;
    };

    constexpr allocator() noexcept
    {
        initMem();
    }

    // constexpr allocator(const allocator &) noexcept = default;

    T *allocate(std::size_t n)
    {
        if (n > allocator::PoolSize)
            throw std::bad_alloc();

//        std::cout << __FUNCTION__ << " allocate [n = " << n << "]" << std::endl;

//        return reinterpret_cast<T *>();


        // v1
        return std::allocator<T>::allocate(n);

        // v2
        // auto p = std::malloc(n * sizeof(T));
        // if (!p)
        //     throw std::bad_alloc();
        // return reinterpret_cast<T *>(p);
    }

    void deallocate(T* const ptr, const size_t count)
    {
//        std::cout << __FUNCTION__ << " deallocate [ptr = " << ptr << " count = " << count << "]" << std::endl;

        std::allocator<T>::deallocate(ptr, count);
    }

protected:
    void initMem()
    {
        constexpr auto PoolLength = sizeof(T) * allocator::PoolSize;
        m_pool = std::shared_ptr<uint8_t>(new uint8_t[PoolLength], [PoolLength](uint8_t *ptr)
        {
            delete[] ptr;
//            std::cout << __FUNCTION__ << "[pool lenght = " << PoolLength << "] deleted" << std::endl;
        });
    }

private:
    std::shared_ptr<uint8_t> m_pool;

};

}

