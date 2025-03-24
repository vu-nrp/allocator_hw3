#include <map>
#include <iostream>
#include "myspace.h"

//
int main()
{
    std::cout << "Home work #3" << std::endl;

    // simple type
    using Element1 = int;
    // hard type
    using Element2 = std::pair<Element1, Element1>;

    static constexpr int MaxMemoryItemsCount {10};

    {
        // std map, std allocator
        std::map<Element1, Element1> std_map_std_allc;
        PRINT(std::cout << std::endl);
        for (auto i = 0;i < MaxMemoryItemsCount;++i)
            std_map_std_allc.insert({i, my::factorial<Element1>(i)});
        std::cout << "std map, std allocator [size: " << std_map_std_allc.size() << "]> ";
        for (const auto &item: std_map_std_allc)
            std::cout << "{" << item.first << ": " << item.second << "} ";
        std::cout << std::endl;
    }

    {
        // std map, custom allocator
        PRINT(std::cout << std::endl);
        std::map<Element1, Element1, std::less<Element1>, my::allocator<MaxMemoryItemsCount, std::pair<const Element1, Element1>>> std_map_cstm_allc;
        for (auto i = 0;i < MaxMemoryItemsCount;++i)
            std_map_cstm_allc.insert({i, my::factorial<Element1>(i)});
        std::cout << "std map, custom allocator [size: " << std_map_cstm_allc.size() << "]> ";
        for (const auto &item: std_map_cstm_allc)
            std::cout << "{" << item.first << ": " << item.second << "} ";
        std::cout << std::endl;
    }

    {
        // custom container, std allocator
        PRINT(std::cout << std::endl);
        my::array_based_container<Element1> cstm_cntr_std_allc;
        for (auto i = 0;i < MaxMemoryItemsCount;++i)
            cstm_cntr_std_allc.insert(i);
        std::cout << "custom container, std allocator [size: " << cstm_cntr_std_allc.size() << "]> ";
        for (const auto &item: cstm_cntr_std_allc)
            std::cout << "{" << item << "} ";
        std::cout << std::endl;
    }

    {
        // because [n - alocation] + [(n - 1) - previous alocated]
        decltype(MaxMemoryItemsCount) MaxArrayBasedMemoryItemsCount = MaxMemoryItemsCount * 2;
        // custom container, custom allocator
        PRINT(std::cout << std::endl);
        my::array_based_container<Element1, my::allocator<MaxArrayBasedMemoryItemsCount, Element1>> cstm_cntr_cstm_allc;
        for (auto i = 0;i < MaxMemoryItemsCount;++i)
            cstm_cntr_cstm_allc.insert(i);
        std::cout << "custom container, custom allocator [size: " << cstm_cntr_cstm_allc.size() << "]> ";
        for (const auto &item: cstm_cntr_cstm_allc)
            std::cout << "{" << item << "} ";
        std::cout << std::endl;
    }

    PRINT({
        // because [n - alocation] + [(n - 1) - previous alocated]
        decltype(MaxMemoryItemsCount) MaxArrayBasedMemoryItemsCount = MaxMemoryItemsCount * 2;
        // custom container list init, custom allocator
        PRINT(std::cout << std::endl);
        my::array_based_container<Element1, my::allocator<MaxArrayBasedMemoryItemsCount, Element1>> cstm_cntr_cstm_allc_list {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        std::cout << "custom container list init, custom allocator [size: " << cstm_cntr_cstm_allc_list.size() << "]> ";
        for (const auto &item: cstm_cntr_cstm_allc_list)
            std::cout << "{" << item << "} ";
        std::cout << std::endl;
    })

    PRINT({
        // hard type custom container, std allocator
        PRINT(std::cout << std::endl);
        my::array_based_container<Element2> hrd_cstm_cntr_std_allc;
        for (auto i = 0;i < MaxMemoryItemsCount;++i)
            hrd_cstm_cntr_std_allc.insert({i, my::factorial<Element1>(i)});
        std::cout << "hard type custom container, std allocator [size: " << hrd_cstm_cntr_std_allc.size() << "]> ";
        for (const auto &item: hrd_cstm_cntr_std_allc)
            std::cout << "{" << item.first << ": " << item.second << "} ";
        std::cout << std::endl;
    })

    PRINT({
        // because [n - alocation] + [(n - 1) - previous alocated]
        decltype(MaxMemoryItemsCount) MaxArrayBasedMemoryItemsCount = MaxMemoryItemsCount * 2;
        // hard type custom container, custom allocator
        PRINT(std::cout << std::endl);
        my::array_based_container<Element2, my::allocator<MaxArrayBasedMemoryItemsCount, Element2>> hrd_cstm_cntr_cstm_allc;
        for (auto i = 0;i < MaxMemoryItemsCount;++i)
            hrd_cstm_cntr_cstm_allc.insert({i, my::factorial<Element1>(i)});
        std::cout << "hard type custom container, custom allocator [size: " << hrd_cstm_cntr_cstm_allc.size() << "]> ";
        for (const auto &item: hrd_cstm_cntr_cstm_allc)
            std::cout << "{" << item.first << ": " << item.second << "} ";
        std::cout << std::endl;
    })

    PRINT(try {
        // memory exception case
        PRINT(std::cout << std::endl);
        my::array_based_container<Element1, my::allocator<MaxMemoryItemsCount, Element1>> cstm_cntr_cstm_allc_list(MaxMemoryItemsCount, -1);
    } catch (...) {
        std::cout << "exception fire!!!" << std::endl;
    })

    return 0;
}
