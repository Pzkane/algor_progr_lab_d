/****************************************************************
    Ievadot loģiski nepareizus datus, programmai jāizdod atbilstošs paziņojums. Jābūt iespējai programmu izpildīt atkārtoti.
    Atrādot programmu, jāatrāda
    a) programmas teksts,  b) testa piemēri,  c) programma darbībā.

    *************************************************************

    Vārds, Uzvārds: Pāvels Žuravļovs
    Apliec. num.: pz20014
    Uzdevuma veikšanas datums: 2020/10/02
    Valoda: C++11

    A8. Dots naturāls skaitlis n. Izdrukāt tos skaitļa n reizinātājus, kuri ir kāda naturāla skaitļa kvadrāti.

    *************************************************************

    TESTA PIEMĒRI:

    Ievads   |          Vēlamā reakcija         |    Rezultāts
    –––––––––+––––––––––––––––––––––––––––––––––+–––––––––––––––––––––––––––––––––––––
    abcdg    | Paziņojums par nepareizo ievadi  | Programma izvada "Incorrect input!"
    –––––––––+––––––––––––––––––––––––––––––––––+–––––––––––––––––––––––––––––––––––––
        0    |              0^2 = 0             |    0^2 = 0
    –––––––––+––––––––––––––––––––––––––––––––––+–––––––––––––––––––––––––––––––––––––
        -8   | Paziņojums par nepareizo         | Programma izvada "Number cannot be
             | kvadrātsakni no negatīva skaitļa | less than 0! <skaitlis> is not a
             |                                  | natural number!"
    –––––––––+––––––––––––––––––––––––––––––––––+–––––––––––––––––––––––––––––––––––––
        4    |  0^2 = 0                         |   0^2 = 0
             |  1^2 = 1                         |   1^2 = 1
             |  2^2 = 4                         |   2^2 = 4
    –––––––––+––––––––––––––––––––––––––––––––––+–––––––––––––––––––––––––––––––––––––
        5    |  0^2 = 0                         |   0^2 = 0
             |  1^2 = 1                         |   1^2 = 1
             |  2^2 = 4                         |   2^2 = 4
    –––––––––+––––––––––––––––––––––––––––––––––+–––––––––––––––––––––––––––––––––––––
        -1   | Iziešana no programmas           | Programma iziet no galvenā cikla un
             |                                  | beidz darbu
*/

#include <iostream>
#include <cmath>
#include <limits>

void clear_input();
bool b_check_square(int);

int main()
{
    bool b_quit = false;
    do {
        int n;
        bool b_validate;
        do {
            b_validate = true;
            std::cout << "Input number to get squares from or type '-1' to exit: ";
            std::cin >> n;

            if (n == -1)
            {
                b_quit = true;
                break;
            }

            if (n < 0)
            {
                std::cout << "Number cannot be less than 0! " << n << " is not a natural number!" << std::endl;
                b_validate = false;
            }

            if (std::cin.fail())
            {
                b_validate = false;
                std::cout << "Incorrect input!" << std::endl;
                clear_input();
            }
        } while(!b_validate);

        clear_input();

        if (b_quit)
        {
            break;
        }

        for (int i = 0; i <= (int)n; i++)
        {
            if (b_check_square(i))
            {
                std::cout << i << " = " << sqrt(i) << "^2" << std::endl;
            }
        }
        std::cout << '\n';
    } while(true);

    return 0;
}

/**
 * Clear std::cin().
 *
 */
void clear_input()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/**
 * Check if number can be squared.
 *
 * @param val - Numbers which will be checked
 * @return bool - Result of the check
 */
bool b_check_square(int val)
{
    int i = 0;
    int i_sqr;
    do {
        i_sqr = i * i;
        if (i_sqr == val)
        {
            return true;
        }
        i++;
    } while (i_sqr < val);

    return false;
}
