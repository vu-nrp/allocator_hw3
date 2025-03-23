#include <map>
#include <iostream>
#include "myspace.h"

//
int main()
{
    std::cout << "Home work #3" << std::endl;

    using Element = int;
    static const int ItemsCount {10};

    {
        std::map<Element, Element> std_map_std_allc;
        // std map std allocator
        for (auto i = 0;i < ItemsCount;++i)
            std_map_std_allc.insert({i, my::factorial<Element>(i)});
        std::cout << "std map std allocator [size: " << std_map_std_allc.size() << "]> ";
        for (const auto &item: std_map_std_allc)
            std::cout << "{" << item.first << ": " << item.second << "} ";
        std::cout << std::endl;
    }

    {
        // std map custom allocator
        std::map<Element, Element, std::less<Element>, my::allocator<ItemsCount, std::pair<const Element, Element>>> std_map_cstm_allc;
        for (auto i = 0;i < ItemsCount;++i)
            std_map_cstm_allc.insert({i, my::factorial<Element>(i)});
        std::cout << "std map custom allocator [size: " << std_map_cstm_allc.size() << "]> ";
        for (const auto &item: std_map_cstm_allc)
            std::cout << "{" << item.first << ": " << item.second << "} ";
        std::cout << std::endl;
    }

    {
        // custom container
        my::container<Element> cstm_cntr_std_allc;
        for (auto i = 0;i < ItemsCount;++i)
            cstm_cntr_std_allc.insert(i);
        std::cout << "custom container std allocator [size: " << cstm_cntr_std_allc.size() << "]> ";
        for (const auto &item: cstm_cntr_std_allc)
            std::cout << "{" << item << "} ";
        std::cout << std::endl;
    }

    {
        // custom container custom allocator
        my::container<Element, my::allocator<ItemsCount, Element>> cstm_cntr_cstm_allc;
        for (auto i = 0;i < ItemsCount;++i)
            cstm_cntr_cstm_allc.insert(i);
        std::cout << "custom container custom allocator [size: " << cstm_cntr_cstm_allc.size() << "]> ";
        for (const auto &item: cstm_cntr_cstm_allc)
            std::cout << "{" << item << "} ";
        std::cout << std::endl;
    }

    {
        // custom container list init custom allocator
        my::container<Element, my::allocator<ItemsCount, Element>> cstm_cntr_cstm_allc_list {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        std::cout << "custom container list init custom allocator [size: " << cstm_cntr_cstm_allc_list.size() << "]> ";
        for (const auto &item: cstm_cntr_cstm_allc_list)
            std::cout << "{" << item << "} ";
        std::cout << std::endl;
    }

    using Element2 = std::pair<Element, Element>;

    {
        // x
        my::container<Element2> x;
        for (auto i = 0;i < ItemsCount;++i)
            x.insert({i, my::factorial<Element>(i)});
        std::cout << "x [size: " << x.size() << "]> ";
        for (const auto &item: x)
            std::cout << "{" << item.first << ": " << item.second << "} ";
        std::cout << std::endl;
    }
    {
        // y
        my::container<Element2, my::allocator<ItemsCount, Element2>> y;
        for (auto i = 0;i < ItemsCount;++i)
            y.insert({i, my::factorial<Element>(i)});
        std::cout << "y [size: " << y.size() << "]> ";
        for (const auto &item: y)
            std::cout << "{" << item.first << ": " << item.second << "} ";
        std::cout << std::endl;
    }

    return 0;
}
