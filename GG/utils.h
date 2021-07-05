#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <iostream>
#include <list>
#include <string>
#include <limits>
#include <cstdlib>
#include "./linked_list.h"

namespace PZ
{
    void clear_io();

    template <typename T_list>
    void fill_numeric_list(T_list &linked_list, void (*on_insert) (T_list &, double), bool (*on_empty) (T_list &), bool generate_nums = false);

    template <typename T>
    void print_numeric_list(std::list<T> &std_list);

    template <typename T>
    void next_numeric_is_smaller(std::list<T> &std_l);

    void std_l_d_push_back(std::list<double> &std_l, double val);

    bool std_l_d_empty(std::list<double> &std_l);

    template <typename T>
    void print_numeric_list(PZ::Linked_List<T> &lnk_list);

    template <typename T>
    void next_numeric_is_smaller(PZ::Linked_List<T> &lnk_list);

    void linked_l_d_push_back(PZ::Linked_List<double> &lnk_list, double val);

    bool linked_l_d_empty(PZ::Linked_List<double> &lnk_list);

    int demo();
}

#endif // UTILS_H_INCLUDED
