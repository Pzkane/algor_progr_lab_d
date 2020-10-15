#    Ievadot loģiski nepareizus datus, programmai jāizdod atbilstošs paziņojums. Jābūt iespējai programmu izpildīt atkārtoti.
#    Atrādot programmu, jāatrāda
#    a) programmas teksts,  b) testa piemēri,  c) programma darbībā.
#
#    *************************************************************
#    
#    Vārds, Uzvārds: Pāvels Žuravļovs
#    Apliec. num.: pz20014
#    Uzdevuma veikšanas datums: 2020/10/01
#    Valoda: Python
#
#    B25. Sastādīt programmu, kura saskaita un atņem racionālus skaitļus, racionālos skaitļus uzdodot kā divu veselu  skaitļu pāri
#    (1/3 tiek uzdota kā divi skaitļi 1 un 3). Rezultātam jābūt kā nesaīsināmam daļskaitlim. Uzrakstīt funkciju,
#    kas  saskaita 2 racionālus skaitļus un funkciju, kas pārveido racionālu skaitli par nesaīsināmu daļskaitli.
#    
#    *************************************************************
#
#
#    TESTA PIEMĒRI:
#
#     Ievads  |          Vēlamā reakcija         |            Rezultāts                |         Piezīmes
#    –––––––––+––––––––––––––––––––––––––––––––––+–––––––––––––––––––––––––––––––––––––+–––––––––––––––––––––––––
#    abcdg    | Paziņojums par nepareizo ievadi  | Programma izvada "invalid literal"  |
#    –––––––––+––––––––––––––––––––––––––––––––––+–––––––––––––––––––––––––––––––––––––+–––––––––––––––––––––––––
#        0    | Paziņojums par dalīšanu ar 0     | Programma izvada "denominator cannot| Skaitlis tiek ievadīts 
#             |                                  | be zero"                            | saucējā
#    –––––––––+––––––––––––––––––––––––––––––––––+–––––––––––––––––––––––––––––––––––––+–––––––––––––––––––––––––
#        -8   | Paziņojums par nepareizu skaitļu | Programma izvada "number is less    | Skaitlis tiek ievadīts
#             |                                  | than zero"                          | saucējā
#    –––––––––+––––––––––––––––––––––––––––––––––+–––––––––––––––––––––––––––––––––––––+–––––––––––––––––––––––––
#        k    | Paziņojums par nepareizu darbību | Programma izvada "CLI supports only | Burts tiek ievadīts
#             |                                  | these operations: +, -              | darbības izvēles laikā
#    –––––––––+––––––––––––––––––––––––––––––––––+–––––––––––––––––––––––––––––––––––––+–––––––––––––––––––––––––
#     1, 2, 3,| Atbilde: 1/1                     | Programma izvada 1/1                | Izveidotie rac. skaitl.:
#     6, +    |                                  |                                     | 1/2 + 3/6

from functools import reduce

class LessThanZeroError(Exception):
    def __init__(self):
        message = 'number is less than zero'
        super().__init__(message)

class NotANumberError(Exception):
    def __init__(self):
        message = 'not a number'
        super().__init__(message)

def main():
    quit = False
    while True:
        fractions = list()
        print("Input 'e' to exit")
        # Try to listen to user numbers
        try:
            for i in range(2):
                n = input("Enter "+str(i+1)+". number numerator: ")
                if n == 'e':
                    quit = True
                    return
                validate_fraction_number(int(n), True)

                m = input("Enter "+str(i+1)+". number denominator: ")
                validate_fraction_number(int(m))

                fractions.append(int(n))
                fractions.append(int(m))

            while True:
                op = input("Operation type (+/-): ")
                if not (op == "+" or op == "-"):
                    print("CLI supports only these operations: +, -")
                else:
                    break;

            if quit:
                return

            # Error handling for 'calculate_fractions' function, but validation above excluded exceptions
            try:
                new_fraction = calculate_fractions(fractions, op)

                for (i,num) in enumerate(fractions):
                    print(num, sep='', end='')
                    if not (i % 2):
                        print("/", sep='', end='')
                    elif i != len(fractions)-1:
                        print(" "+op+" ", sep='', end='')
                    else:
                        print(" = ", sep='', end='')

                print_fractions(new_fraction)

                print(" = ", sep='', end='')

                new_fraction = to_indivisible_fraction(new_fraction)
                print_fractions(new_fraction)

                print(" ")
            except Exception as exc:
                print("Exception: ", end='')
                print(exc)
        except Exception as exc:
            print("Exception: ", end='')
            print(exc)

def validate_fraction_number(number, numerator = False):
    """Validates if user input was a number

    Parameters
    ----------
    number : int
        Number which data type will be tested
    numerator : bool
        Determines whenever '-' is allowed in the 'number' parameter

    Raises
    ------
    ZeroDivisionError
        If 'number' is 0
    LessThanZeroError
        If 'number' is less than 0
    NotANumberError
        If 'number' is not a number
    """

    if not isinstance(number, int):
        raise NotANumberError

    if not numerator:
        if number == 0:
            raise ZeroDivisionError('denominator cannot be zero')
        if number < 0:
            raise LessThanZeroError

def print_fractions(fractions: list):
    # Print pretty fraction
    for (i,num) in enumerate(fractions):
        print(num, sep='', end='')
        if not (i % 2):
            print("/", sep='', end='')            

def to_indivisible_fraction(fraction: list):
    """Converts fraction to the indivisible fraction

    Parameters
    ----------
    fraction : list
        List which contains integer values where FIRST number is numerator and SECOND - denominator

    Returns
    -------
    list
        List representing indivisible fraction in which first element is numerators and second - denominator
    """

    indivisible_fraction = list()
    numerator = fraction[0]
    denominator = fraction[1]

    gcf = greatest_common_factor(abs(numerator), abs(denominator))
    indivisible_fraction.append(numerator//gcf)
    indivisible_fraction.append(denominator//gcf)

    return indivisible_fraction

def greatest_common_factor(a, b):
    """Get GCF of 2 numbers. Function uses Euclid's Algorithm.

    Parameters
    ----------
    a, b : int
        Numbers from which GCF is calculated

    Returns
    -------
    int
        Greatest common factor of a and b
    """

    if a == 0 or b == 0:
        return 0
    elif a == b:
        return a
    elif a > b:
        return greatest_common_factor(a-b, b)
    else:
        return greatest_common_factor(a, b-a);

def calculate_fractions(fractions: list, operation: str):
    """Returns addition or subtraction from given fractions

    Parameters
    ----------
    fractions : list
        List which contains integer values where each EVEN number is numerator and each ODD - denominator
    operation : str
        Determines which operation should be performed between fractions

    Returns
    -------
    list
        a list representing fraction in which first element is numerators and second - denominator

    Raises
    ------
    ZeroDivisionError
        If one of the denominator values is 0
    LessThanZeroError
        If one of the denominator values is less than 0
    """
    numerators = list()
    denominators = list()
    denominator_multpl = 1
    for (i, val) in enumerate(fractions):
        if not i % 2:
            numerators.append(val)
        else:
            if val < 0:
                raise LessThanZeroError
            else:
                denominator_multpl *= val
                denominators.append(val)

    new_numerators = list()
    arr_index = 0
    for (i, val) in enumerate(fractions):
        if not i % 2:
            if val == 0:
                raise ZeroDivisionError

            new_numerators.append(denominator_multpl // denominators[arr_index] * numerators[arr_index])
            arr_index += 1

    calculated_fraction = list()
    if operation == "+":
        calculated_fraction.append(reduce(lambda a,b : a+b, new_numerators))
    if operation == "-":
        calculated_fraction.append(reduce(lambda a,b : a-b, new_numerators))

    calculated_fraction.append(denominator_multpl)
    return calculated_fraction

if __name__ == "__main__":
    main()
