/****************************************************************
    Ievadot loģiski nepareizus datus, programmai jāizdod atbilstošs paziņojums. Jābūt iespējai programmu izpildīt atkārtoti.
    Atrādot programmu, jāatrāda
    a) programmas teksts,  b) testa piemēri,  c) programma darbībā.

    *************************************************************

    Vārds, Uzvārds: Pāvels Žuravļovs
    Apliec. num.: pz20014
    Uzdevuma veikšanas datums: 2020/10/01
    Valoda: C++11

    B25. Sastādīt programmu, kura saskaita un atņem racionālus skaitļus, racionālos skaitļus uzdodot kā divu veselu  skaitļu pāri
    (1/3 tiek uzdota kā divi skaitļi 1 un 3). Rezultātam jābūt kā nesaīsināmam daļskaitlim. Uzrakstīt funkciju,
    kas  saskaita 2 racionālus skaitļus un funkciju, kas pārveido racionālu skaitli par nesaīsināmu daļskaitli.

    *************************************************************


*/
#include <iostream>
#include <conio.h>
#include <string>
#include <limits>

std::string to_indivisible_fraction (int, int);
int number_input (bool);
int greatest_common_factor (int, int);
char operator_input ();
bool is_char_number (int);

int main ()
{
    bool quit = false;
    do
    {
        // Input validation and exit flag
        int n;
        do
        {
            std::cout << "Input fractional number count (at least 2) or type -1 to exit: ";
            std::cin >> n;

            if (std::cin.fail())
            {
                std::cout << "Incorrect input!" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            } else if (n == -1) {
                quit = true;
                break;
            } else if (n < 2)
                std::cout << "At least 2 numbers are required!" << std::endl;
        } while(std::cin.fail() || n < 2);

        if (quit)
            break;

        std::cout << "\n";
        std::cout << "Number count = " << n << std::endl;
        std::cout << "Start typing numbers and ; press Space to iterate between numbers/operations\n> ";

        // Fill numerators, denominators and operations arrays between them
        int numerators[n];
        int denominators[n];
        char operators[n-1];
        for(int i = 0; i < n; i++)
        {
            int i_a = number_input(true);
            numerators[i] = i_a;
            std::cout << "/";
            int i_b = number_input(false);
            denominators[i] = i_b;

            if (i != n-1)
            {
                char c_op = operator_input();
                operators[i] = c_op;
            }
        }
        std::cout << " = ";

        // Get common denominator
        int denominator_multipl = 1;
        for (int i = 0; i < n; i++)
            denominator_multipl *= denominators[i];

        // Calculate new numerators based on common denominator value
        int new_numerators[n];
        for (int i = 0; i < n; i++)
            new_numerators[i] = denominator_multipl / denominators[i] * numerators[i];

        // Output and prettify new fraction
        for (int i = 0; i < n; i++){
            (new_numerators[i] < 0) ? void(std::cout << "(" << new_numerators[i] << ")") : void(std::cout << new_numerators[i]);
            if (i < n-1)
                std::cout << operators[i];
        }

        std::cout << "/" << denominator_multipl;

        // Calculate numerators' sum based on operators
        int numerators_sum = new_numerators[0];
        for (int i = 0; i < n; i++){
            if (i < n-1)
            {
                switch (operators[i]) {
                case '+':
                    numerators_sum += new_numerators[i+1];
                    break;
                case '-':
                    numerators_sum -= new_numerators[i+1];
                    break;
                }
            }
        }

        std::cout << " = " << numerators_sum << "/" << denominator_multipl;

        std::string indiv_fract = to_indivisible_fraction(numerators_sum, denominator_multipl);
        std::cout << indiv_fract << "\n\n";
    } while (!quit);
}

std::string  to_indivisible_fraction (int numerator, int denominator)
{
    int gcf = greatest_common_factor(abs(numerator), abs(denominator));
    std::string indiv_fract = " = " + std::to_string(numerator/gcf) + "/" + std::to_string(denominator/gcf);
    return indiv_fract;
}

/**
 * To use with fractions. Allows user to input digits only and returns its number.
 *
 * @param numerator - Provide a bool type value to determine whenever allow input to include '-'
 * @return char - Operation type
 */
int number_input (bool numerator)
{
    char c_n;
    std::string s_n = "";
    bool break_input = false;
    while(!break_input)
    {
        do
        {
            c_n = getch();

            if (numerator && s_n.empty() && c_n == 45)
            {
                break;
            }

            if (c_n == 32 && !s_n.empty())
            {
                break_input = true;
                break;
            }
        } while (!is_char_number(c_n) || (c_n == 48 && !numerator));

        if (!break_input)
        {
            std::cout << c_n;
            s_n += c_n;
        }
    }
    return std::stoi(s_n);
}

/**
 * Get GCF of 2 numbers.
 * Function uses Euclid's Algorithm.
 *
 * @param a, b - Numbers from which GCF is calculated
 * @return int - Greatest common factor of a and b
 */
int greatest_common_factor (int a, int b)
{
    if (a == 0 || b == 0)
        return 0;
    else if (a == b)
        return a;
    else if (a > b)
        return greatest_common_factor(a-b, b);
    else
        return greatest_common_factor(a, b-a);
}

/**
 * Outputs operations for user to choose from.
 * Supports addition (+) and subtraction (-).
 *
 * @return char - Operation type
 */
char operator_input ()
{
    std::cout << " (+/-)";
    char c_op;
    do
    {
        c_op = getch();
    } while (c_op != 43 && c_op != 45);

    for (int i = 0; i < 4; i++)
    {
        std::cout << '\b' << " " << '\b';
    }
    std::cout << '\b' << c_op << " ";
    return c_op;
}

/**
 * Get confirmation if char ASCII code represents a number.
 *
 * @param val - ASCII code
 * @return bool
 */
bool is_char_number (int val)
{
    if (val >= 48 && val <= 57)
    {
        return true;
    }
    return false;
}
