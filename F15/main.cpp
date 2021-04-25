/*******************************************

Pāvels Žuravļovs, pz20014

F15. Dots teksta fails, kurā atrodas sintaktiski pareizs C++ programmas teksts.
Uzrakstīt programmu, kura saskaita, cik dažādu bibliotēku (#include) iekļauts dotajā programmā. Drīkst uzskatīt,
ka programmas tekstā nav komentāru un ka attiecīgie simboli neparādīsies teksta literāļos.

Programma izveidota: 2021/02/19, pielabota: 2021/03/04

*******************************************/
#include <iostream>
#include <fstream>
#include <string>

/**
  Funkcija var atrast velāmo stringu vairākas reizes vienā padotā rindā,
  bet strādā tikai ar const char * tipa virknēm
**/
int compare(const char * needle, const char * haystack)
{
    if (*haystack == NULL) return 0;

    int needle_len, correct, positive;
    needle_len = correct = positive = 0;

    // count number of characters of the needle
    //   and after get back to the start of the needle string
    while (*needle != '\0')
    {
        ++needle_len;
        ++needle;
    }
    for (int i = needle_len; i > 0; --i)
        --needle;

    for (; *haystack; ++haystack)
    {
        if (correct == needle_len)
        {
            ++positive;
            correct = 0;
            for (int i = needle_len; i > 0; --i)
                --needle;
        }

        if (*needle == *haystack)
        {
            ++needle;
            ++correct;
        }
        else
            // loop back needle string if at least 1 haystack char
            //   was not equal to the needle char
            while(correct > 0)
            {
                --needle;
                --correct;
            }
    }
    // final check if needle was located at the end of the haystack
    if (correct == needle_len) ++positive;
    return positive;
}

int main()
{
    const char * C_NEEDLE = "#include <";
    int hash_include_count = 0;
    std::string line;
    std::ifstream f("./sfml_main.txt", std::ifstream::in);
    while(std::getline(f, line))
    {
        hash_include_count += compare(C_NEEDLE, line.c_str());
    }
    std::cout<<"Included libraries: "<<hash_include_count<<std::endl;
    f.close();

    return 0;
}
