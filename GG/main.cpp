#include <iomanip>
#include "./utils.h"

using std::cout;
using std::endl;

void testResult(const char* test_label, bool result)
{
    const char* lbl_result = result ? "OK" : "FAILED";
    std::cout<<test_label<<"..."<<lbl_result<<endl;
}

void test_linked_list__constructor()
{
    bool _case = false;
    PZ::Linked_List<double> lnk_list;
    if (lnk_list.begin()) _case = true;
    testResult("test_linked_list__constructor", _case);
}

void test_linked_list__push_back()
{
    bool _case = false;
    const int number = 232323;
    PZ::Linked_List<double> lnk_list;
    lnk_list.push_back(number);
    if (lnk_list.begin()->data == number)
        _case = true;
    testResult("test_linked_list__push_back", _case);
}

void test_linked_list__push_front()
{
    bool _case = false;
    const int number1 = 10, number2 = 20;
    PZ::Linked_List<double> lnk_list;
    lnk_list.push_back(number1);
    lnk_list.push_front(number2);
    if (lnk_list.begin()->data == number2 && lnk_list.begin()->next->data == number1)
        _case = true;
    testResult("test_linked_list__push_front", _case);
}

void test_linked_list__erase()
{
    bool _case_lt_0, _case_gt_size, _case;
    _case_lt_0=_case_gt_size=_case=false;
    const int number1 = 10, number2 = 20;
    PZ::Linked_List<double> lnk_list;
    lnk_list.push_back(number1);
    lnk_list.push_front(number2);
    try
    {
        lnk_list.erase(-1);
    } catch (std::runtime_error err)
    {
        _case_lt_0 = true;
    }

    try
    {
        lnk_list.erase(2);
    } catch (std::runtime_error err)
    {
        _case_gt_size = true;
    }

    try
    {
        lnk_list.erase(0);
        if (lnk_list.begin()->next == nullptr) _case = true;
    } catch (std::runtime_error err)
    {
        cout<<err.what()<<endl;
    }

    if (_case_lt_0 && _case_gt_size && _case)
        _case = true;
    else
    {
        cout<<std::setfill('.')<<std::setw(20)<<"_case_lt_0: "<<_case_lt_0<<endl;
        cout<<std::setfill('.')<<std::setw(20)<<"_case_gt_size: "<<_case_gt_size<<endl;
        cout<<std::setfill('.')<<std::setw(20)<<"_case: "<<_case<<endl;
    }
    testResult("test_linked_list__erase", _case);
}

void test_linked_list__destructor()
{
    bool _case, _case_val;
    _case=_case_val=false;
    const int number1 = 10, number2 = 20;
    PZ::Linked_List<double> *lnk_list = new PZ::Linked_List<double>;
    lnk_list->push_back(number1);
    lnk_list->push_back(number2);
    auto list_node = lnk_list->begin();
    delete (lnk_list);
    lnk_list = nullptr;

    if (list_node->data != number1) _case_val = true;

    if (_case_val)
        _case = true;
    else
    {
        cout<<std::setfill('.')<<std::setw(20)<<"_case_val: "<<_case_val<<endl;
        cout<<std::setfill('.')<<std::setw(20)<<"_case: "<<_case<<endl;
    }

    testResult("test_linked_list__destructor", _case);
}

void test_utils__next_numeric_is_smaller_LL()
{
    bool _case = false;
    PZ::Linked_List<double> lnk_list;
    lnk_list.push_back(2);
    lnk_list.push_back(3);
    lnk_list.push_back(1);
    PZ::next_numeric_is_smaller<double>(lnk_list);
    if (lnk_list.size() == 1 && lnk_list.begin()->data == 1)
        _case = true;
    testResult("test_utils__next_numeric_is_smaller_LL", _case);
}

void test_utils__next_numeric_is_smaller_STL()
{
    bool _case = false;
    std::list<double> std_l;
    std_l.push_back(2);
    std_l.push_back(3);
    std_l.push_back(1);
    PZ::next_numeric_is_smaller<double>(std_l);
    if (std_l.size() == 1 && std_l.front() == 1)
        _case = true;
    testResult("test_utils__next_numeric_is_smaller_STL", _case);
}

void testSuite()
{
    test_linked_list__constructor();
    test_linked_list__push_back();
    test_linked_list__push_front();
    test_linked_list__erase();
    test_linked_list__destructor();
    test_utils__next_numeric_is_smaller_LL();
    test_utils__next_numeric_is_smaller_STL();
}

int main()
{
    short int in;
    do {
        cout<<"Izvele:"<<endl;
        cout<<" 1: G23 uzdevuma demo"<<endl;
        cout<<" 2: vienibtestesana"<<endl;
        cout<<" 3: exit"<<endl;
        std::cin>>in;

        switch (in){
            case 1:
                PZ::demo();
                break;
            case 2:
                testSuite();
                break;
            default:
                break;
        }
    } while(in != 3);

    return 0;
}
