#include <ctime>
#include "./utils.h"

namespace PZ
{
    void clear_io()
    {
        std::cin.clear();
        std::cin.ignore(10000,'\n');
    }

    template <typename T_list>
    void fill_numeric_list(T_list &linked_list, void (*on_insert) (T_list &, double), bool (*on_empty) (T_list &), bool generate_nums)
    {
        std::string input;
        std::string s_num = "";
        do
        {
            if (generate_nums)
            {
                std::srand(std::time(nullptr));
                for (int i = 0; i < 10; ++i)
                {
                    input += std::to_string(1 + std::rand() % 20);
                    input += " ";
                }
                std::cout<<input<<std::endl;
            } else {
                clear_io();
                std::cout<<"Turpiniet ievadit skaitlus, atdalot ar atstarpi un uzspiediet Enter:"<<std::endl;
                std::getline(std::cin, input);
            }

            if (input == "\0")
            {
                std::cout<<"STL List ir tukss!"<<std::endl;
            }
            for (char c: input)
            {
                if (c == '.' && s_num != "" && s_num.find(".") == std::string::npos)
                    s_num += c;

                if (c == '-' && s_num == "")
                    s_num += c;

                if (c == '0' && s_num != "")
                    s_num += c;

                if (c >= '1' && c <= '9')
                    s_num += c;

                if (c == 32 && s_num != "")
                {
                    on_insert(linked_list, std::stod(s_num.c_str()));
                    s_num = "";
                }
            }
        } while(on_empty(linked_list) && s_num == "");
        if (s_num != "")
            on_insert(linked_list, std::stod(s_num.c_str()));
    }

    // std::list izmantojamas funkcijas

    template <typename T>
    void print_numeric_list(std::list<T> &std_list)
    {
        typename std::list<T>::iterator it;
        for (it = std_list.begin(); it != std_list.end();)
        {
            std::cout<<*it;
            if (++it != std_list.end())
            {
                std::cout<<", ";
            }
        }
        std::cout<<std::endl;
    }

    template <typename T>
    void next_numeric_is_smaller(std::list<T> &std_l)
    {
        bool all_nnis;
        do {
            all_nnis = true;
            if (std_l.size() < 2) return;
            typename std::list<T>::iterator it_curr, it_prev = std_l.begin();
            for(it_curr = ++std_l.begin(); it_curr != std_l.end(); ++it_prev)
            {
                if (*it_curr < *it_prev)
                {
                    it_prev = std_l.erase(it_prev);
                    ++it_curr;
                    all_nnis = false;
                }
                if (it_curr != std_l.end())
                    ++it_curr;
            }
        } while(!all_nnis);
    }

    void std_l_d_push_back(std::list<double> &std_l, double val)
    {
        std_l.push_back(val);
    }

    bool std_l_d_empty(std::list<double> &std_l)
    {
        return std_l.empty();
    }

    // PZ::Linked_List izmantojamas funkcijas

    template <typename T>
    void print_numeric_list(PZ::Linked_List<T> &lnk_list)
    {
        PZ::Node<T> *node;
        for (node = lnk_list.begin(); node != lnk_list.end();)
        {
            std::cout<<node->data;
            node = node->next;
            if (node != lnk_list.end())
            {
                std::cout<<", ";
            }
        }
        std::cout<<std::endl;
    }

    template <typename T>
    void next_numeric_is_smaller(PZ::Linked_List<T> &lnk_list)
    {
        bool all_nnis;
        do {
            all_nnis = true;
            if (lnk_list.size() < 2) return;
            PZ::Node<T> *node_curr, *node_prev = lnk_list.begin();
            unsigned int n_pos = 0;
            for(node_curr = lnk_list.begin()->next; node_curr != lnk_list.end(); node_curr = node_curr->next, node_prev = node_prev->next)
            {
                if (node_curr->data < node_prev->data)
                {
                    node_prev = lnk_list.erase(n_pos);
                    if (node_curr->next != lnk_list.end())
                        node_curr = node_curr->next;
                    all_nnis = false;
                }
                ++n_pos;
            }
        } while(!all_nnis);
    }

    void linked_l_d_push_back(PZ::Linked_List<double> &lnk_list, double val)
    {
        lnk_list.push_back(val);
    }

    bool linked_l_d_empty(PZ::Linked_List<double> &lnk_list)
    {
        return lnk_list.empty();
    }

    int demo()
    {
        bool in_method = false;
        std::list<double> std_l;
        std::cout<<"Aizpildit STL sarakstu automatiski? (1/0): ";
        std::cin>>in_method;
        if (in_method)
        {
            clear_io();
            fill_numeric_list<std::list<double>>(std_l, std_l_d_push_back, std_l_d_empty, true);
        }
        else
            fill_numeric_list<std::list<double>>(std_l, std_l_d_push_back, std_l_d_empty);
        std::cout<<"STL List PRIMS izmainam:"<<std::endl;
        print_numeric_list<double>(std_l);
        next_numeric_is_smaller<double>(std_l);
        std::cout<<"STL List PEC izmainam:"<<std::endl;
        print_numeric_list<double>(std_l);

        PZ::Linked_List<double> lnk_list;
        std::cout<<"Aizpildit STL sarakstu automatiski? (1/0): ";
        std::cin>>in_method;
        if (in_method)
        {
            clear_io();
            fill_numeric_list<PZ::Linked_List<double>>(lnk_list, linked_l_d_push_back, linked_l_d_empty, true);
        }
        else
            fill_numeric_list<PZ::Linked_List<double>>(lnk_list, linked_l_d_push_back, linked_l_d_empty);
        std::cout<<"Linked_List PRIMS izmainam:"<<std::endl;
        print_numeric_list<double>(lnk_list);
        std::cout<<lnk_list<<std::endl;
        try
        {
            lnk_list.erase(10);
        }
        catch (std::runtime_error err)
        {
            std::cout<<"Planned error on out-of-bounds error if size <= 10: ";
            std::cout<<err.what()<<std::endl;
        }
        next_numeric_is_smaller<double>(lnk_list);
        std::cout<<"Linked_List PEC izmainam:"<<std::endl;
        print_numeric_list<double>(lnk_list);

        std::cout<<std::endl;

        lnk_list.pop_back();
        print_numeric_list<double>(lnk_list);
        lnk_list.push_front(4.8);
        print_numeric_list<double>(lnk_list);
        lnk_list.pop_front();
        print_numeric_list<double>(lnk_list);

        return 0;
    }
}
