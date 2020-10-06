
#    Ievadot loģiski nepareizus datus, programmai jāizdod atbilstošs paziņojums. Jābūt iespējai programmu izpildīt atkārtoti.
#    Atrādot programmu, jāatrāda
#    a) programmas teksts,  b) testa piemēri,  c) programma darbībā.

#    *************************************************************

#    Vārds, Uzvārds: Pāvels Žuravļovs
#    Apliec. num.: pz20014
#    Uzdevuma veikšanas datums: 2020/10/06
#    Valoda: Python 3.8

#    A8. Dots naturāls skaitlis n. Izdrukāt tos skaitļa n reizinātājus, kuri ir kāda naturāla skaitļa kvadrāti.

#    *************************************************************

#    TESTA PIEMĒRI:

#    Ievads   |          Vēlamā reakcija         |    Rezultāts
#    –––––––––+––––––––––––––––––––––––––––––––––+–––––––––––––––––––––––––––––––––––––
#    abcdg    | Paziņojums par nepareizo ievadi  | Programma izvada "Incorrect input!"
#    –––––––––+––––––––––––––––––––––––––––––––––+–––––––––––––––––––––––––––––––––––––
#        0    |              0^2 = 0             |    0^2 = 0
#    –––––––––+––––––––––––––––––––––––––––––––––+–––––––––––––––––––––––––––––––––––––
#        -8   | Paziņojums par nepareizo         | Programma izvada "Number cannot be
#             | kvadrātsakni no negatīva skaitļa | less than 0! -8 is not a natural 
#             |                                  | number!"
#    –––––––––+––––––––––––––––––––––––––––––––––+–––––––––––––––––––––––––––––––––––––
#        4    |  0^2 = 0                         |   0^2 = 0
#             |  1^2 = 1                         |   1^2 = 1
#             |  2^2 = 4                         |   2^2 = 4
#    –––––––––+––––––––––––––––––––––––––––––––––+–––––––––––––––––––––––––––––––––––––
#        5    |  0^2 = 0                         |   0^2 = 0
#             |  1^2 = 1                         |   1^2 = 1
#             |  2^2 = 4                         |   2^2 = 4
#    –––––––––+––––––––––––––––––––––––––––––––––+–––––––––––––––––––––––––––––––––––––
#        -1   | Iziešana no programmas           | Programma iziet no galvenā cikla un
#             |                                  | beidz darbu
#

from math import sqrt

def main():
    b_quit = False
    while(True):
        b_validate = False
        n = 0

        while(not b_validate):
            b_validate = True
            try:
                n = input("Input number to get squares from or type '-1' to exit: ")
                n = int(n)
                if (n == -1):
                    b_quit = True
                    break

                if (n < 0):
                    print(f"Number cannot be less than 0! {n} is not a natural number!")
                    b_validate = False
            except ValueError:
                print("Incorrect input!")
                b_validate = False
            
        if (b_quit):
            break

        n += 1
        for i in range(0, n):
            if (b_check_square(i)):
                print(f"{i} = {int(sqrt(i))}^2")

        print('\n')

def b_check_square(val : int):
    """Check if number can be squared

    Parameters
    ----------
    val : int
        Number which will be checked

    Returns
    -------
    bool
        Result of the check
    """
    i = 0
    i_sqr = 0
    while (i_sqr <= val):
        i_sqr = i * i
        if (i_sqr == val):
            return True
        i += 1

    return False

if __name__ == "__main__":
    main()