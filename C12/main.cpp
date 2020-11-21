/****************************************************************
    Ievadot loģiski nepareizus datus, programmai jāizdod atbilstošs paziņojums. Jābūt iespējai programmu izpildīt atkārtoti.
    Atrādot programmu, jāatrāda
    a) programmas teksts,  b) testa piemēri,  c) programma darbībā.

    *************************************************************

    Vārds, Uzvārds: Pāvels Žuravļovs
    Apliec. num.: pz20014
    Uzdevuma veikšanas datums: 2020/11/22
    Valoda: C++

    Izveidot programmu valodā C++, obligāti izmantojot norādītās vai kādas citas funkcijas.
    Prasības tādas pašas kā iepriekšējā uzdevumā, precīzāk sk. Laboratorijas darbu noteikumos.

    C12. Doti naturāls skaitlis n un veseli skaitļi a(1), a(2), ... a(n).
    Neveicot visa masīva sakārtošanu, atrast trešo mazāko no šiem skaitļiem.

    *************************************************************

    TESTA PIEMĒRI:

    1. Masiva garuma noteikšana

    Ievads   |          Vēlamā reakcija         |    Rezultāts
    –––––––––+––––––––––––––––––––––––––––––––––+–––––––––––––––––––––––––––––––––––––
       -1    | Palaišana tālāk, lai pabeigtu    |
             | programmu                        | Programma beidz darbu
    –––––––––+––––––––––––––––––––––––––––––––––+–––––––––––––––––––––––––––––––––––––
        0    | Paziņojums par nepareizo masīva  | Array size should be at least 3!
             | garumu                           |
   –––––––––+––––––––––––––––––––––––––––––––––+–––––––––––––––––––––––––––––––––––––
        2    | Paziņojums par nepareizo masīva  | Array size should be at least 3!
             | garumu                           |
    –––––––––+––––––––––––––––––––––––––––––––––+–––––––––––––––––––––––––––––––––––––
        3    | Programma piereģistrē pareizo    | Programma klausās lietotāju ievadi
             | masīva garumu                    | skaitļus atbilstoši masīva
             |                                  | garumām
    –––––––––+––––––––––––––––––––––––––––––––––+–––––––––––––––––––––––––––––––––––––
        8    | Programma piereģistrē pareizo    | Programma klausās lietotāju ievadi
             | masīva garumu                    | skaitļus atbilstoši masīva
             |                                  | garumām

    1. masīva piemērs (3 elementi):
    0: 7
    1: 10
    2: 6
    Smallest: 6
    3rd smallest number is: 10

    2. masīva piemērs (8 elementi):
    0: 5
    1: 10
    2: 9
    3: 9
    4: 2
    5: 5
    6: 5
    7: 10
    Smallest: 2
    3rd smallest number is: 9
*/
#include <cstdio>
#include <stdlib.h>
#include <time.h>

int main()
{
    int n, smallest, biggest, tmp_small, tmp_big;
    bool was_assigned;
    do
    {
        do {
            printf("Input array size or -1 to exit: ");
            scanf("%d", &n);

            if (n != -1 && n < 3)
                printf("Array size should be at least 3!\n");
        } while(n != -1 && n < 3);

        if (n == -1)
            break;

        srand(time(NULL));
        int * arr = new int[n];
        for (int i = 0; i < n; ++i)
        {
            arr[i] = rand() % 10 + 1;
            printf("%d: %d\n", i, arr[i]);
        }

        smallest = arr[0];
        // determine smallest number
        for (int i = 1; i < n; ++i)
            if (arr[i] < smallest)
                smallest = arr[i];

        biggest = arr[0];
        // determine biggest number
        for (int i = 1; i < n; ++i)
            if (arr[i] > biggest)
                biggest = arr[i];

        printf("Smallest: %d\n", smallest);

        tmp_big = biggest;
        was_assigned = false;
        // determine 3rd smallest number by stacking 2nd ssmallest first
        //    and then 3rd
        for (int k = 0; k < 2; ++k)
        {
            for (int i = 0; i < n; ++i)
            {
                if (arr[i] > smallest && arr[i] < tmp_big)
                {
                    tmp_small = arr[i];
                    tmp_big = arr[i];
                    if (k == 1)
                        was_assigned = true;
                }
            }
            smallest = tmp_small;
            if (!was_assigned && k == 1)
                tmp_small = biggest;
            tmp_big = biggest;
        }

        printf("3rd smallest number is: %d\n", tmp_small);

        delete [] arr;
    } while (true);

    return 0;
}
