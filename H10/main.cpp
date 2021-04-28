/*******************************************

Pāvels Žuravļovs, pz20014

Izveidot programmu valodā C++.  Ja programma darbojas ar failu, nedrīkst dublēt visa faila saturu operatīvajā atmiņā.
Ar faila komponenti tiek saprasts fiksēta garuma ieraksts. Sīkākās prasības sk. Laboratorijas darbu noteikumos.

 ---------------------------------------------------------------------------------------------------------------------------

H10. Doti divi bināri faili f1 un f2, kuru komponentes ir ieraksti ar struktūru: atslēga (int), vārds (nepārsniedz 30 simbolus).
Failu komponentes sakārtotas pēc atslēgām dilstošā secībā. Uzrakstīt programmu, kas apvieno failus f1 un f2 failā f3 tā,
lai arī f3 komponentes būtu dilstošā secībā (failos nedrīkst parādīties divas komponentes ar vienādu atslēgu vērtību).
Programmu veidot tā, lai pilns faila saturs netiktu ielādēts operatīvajā atmiņā. Uzrakstīt arī palīgprogrammas, kas ļauj izveidot failus f1 un f2 un izdrukā failu saturu.

Programma izveidota: 2021/04/21, pabeigta 2021/04/27

*******************************************/

#include <iostream>
#include <fstream>
#include <vector>
#include <map>

#include <time.h>
#include <random>

using std::cout;
using std::endl;

void out_to_bin_file_from_map(const char *filename, std::map<int, std::string, std::greater<int>> &dict, const size_t &K_size, const size_t &V_size)
{
    std::ofstream ofs(filename, std::ios_base::out | std::ios_base::binary);
    for (auto it = dict.begin(); it != dict.end(); ++it)
    {
        char *cstr = new char[V_size];
        for(int i = 0; i < V_size; ++i)
        {
            if (i < it->second.size())
                cstr[i] = it->second[i];
            else
                cstr[i] = '\0';
        }
        cstr[V_size-1] = '\0';
        ofs.write((char*)&it->first, K_size);
        ofs.write(cstr, V_size);
    }
    ofs.close();
}

void in_to_map_from_bin_file(const char *filename, std::map<int, std::string, std::greater<int>> &dict, const size_t &K_size, const size_t &V_size)
{
    std::ifstream ifs(filename, std::ios_base::out | std::ios_base::binary);
    ifs.seekg(0, std::ios_base::end);
    size_t f_length = ifs.tellg();

    if (f_length % (K_size+V_size) != 0)
    {
        ifs.close();
        throw "in_to_map_from_bin_file::ERROR::File Size and Memory Block Size does not match!";
    }
    cout<<"in_to_map_from_bin_file::Correct File Size, there is "<<f_length/(K_size+V_size)<<" records in bin file."<<endl;

    ifs.seekg(0, std::ios_base::beg);

    std::vector<std::pair<int, std::string>> key_duplicates;
    for (int i = 0; i < f_length/(K_size+V_size); ++i)
    {
        int num;
        char *buff = new char[V_size];

        ifs.read((char*)&num, sizeof(num));
        ifs.read(buff, V_size);

        std::pair<int, std::string> p(num, buff);
        delete [] buff;

        if (dict.find(num) == dict.end())
            dict.emplace(p);
        else
            key_duplicates.push_back(p);
    }
    ifs.close();

    int largest_idx = dict.begin()->first;

    for(auto d_it = key_duplicates.begin(); d_it != key_duplicates.end(); ++d_it)
        dict[++largest_idx]=d_it->second;
}

template <typename Tk, typename Tv, typename Ts = std::less<Tk>>
void print_dict(std::map<Tk, Tv, Ts> &dict)
{
    for (auto it = dict.begin(); it != dict.end(); ++it)
    {
        cout<<it->first<<" "<<it->second<<endl;
    }
}

int main()
{
    const short int SIZE = 20, LIMIT = 30;
    std::string words[SIZE] = {"Tester", "Joker", "Hannah", "Boy", "Master", "Boxing", "Club", "If you possess this trait", "Tourist",
        "Beretta", "Ocean", "Metro", "Tasty beans", "Unimaginatively", "World", "War", "Notebook", "Dark", "Vendor", "Hornet"};
    std::map<int, std::string, std::greater<int>> dict;

    std::mt19937 gen(time(NULL));
    std::uniform_int_distribution<> dist(-5, 5);
    for (unsigned int i = 0; i < SIZE/2; ++i)
    {
        uint32_t id = dist(gen);
        dict.emplace(std::pair<int, std::string>(id, words[i]));
    }

    out_to_bin_file_from_map("./f1.bin", dict, sizeof(int), sizeof(char)*(LIMIT+1));
    cout<<"First Map: "<<endl;
    print_dict<int, std::string, std::greater<int>>(dict);

    dict.clear();

    for (unsigned int i = SIZE/2; i < SIZE; ++i)
    {
        uint32_t id = dist(gen);
        dict.emplace(std::pair<int, std::string>(id, words[i]));
    }

    cout<<endl<<"Second Map: "<<endl;
    out_to_bin_file_from_map("./f2.bin", dict, sizeof(int), sizeof(char)*(LIMIT+1));
    print_dict<int, std::string, std::greater<int>>(dict);

    try
    {
        in_to_map_from_bin_file("./f1.bin", dict, sizeof(int), sizeof(char)*(LIMIT+1));
    }
    catch (const char *err)
    {
        cout<<err<<endl;
    }

    cout<<endl<<"Summed Map: "<<endl;
    out_to_bin_file_from_map("./f3.bin", dict, sizeof(int), sizeof(char)*(LIMIT+1));
    print_dict<int, std::string, std::greater<int>>(dict);

    cout<<endl<<"====================READING FROM BINARY FILES===================="<<endl;

    dict.clear();
    in_to_map_from_bin_file("./f1.bin", dict, sizeof(int), sizeof(char)*(LIMIT+1));
    cout<<"File \"f1.bin\" content: "<<endl;
    print_dict<int, std::string, std::greater<int>>(dict);

    cout<<endl;

    dict.clear();
    in_to_map_from_bin_file("./f2.bin", dict, sizeof(int), sizeof(char)*(LIMIT+1));
    cout<<"File \"f2.bin\" content: "<<endl;
    print_dict<int, std::string, std::greater<int>>(dict);

    cout<<endl;

    dict.clear();
    in_to_map_from_bin_file("./f3.bin", dict, sizeof(int), sizeof(char)*(LIMIT+1));
    cout<<"File \"f3.bin\" content: "<<endl;
    print_dict<int, std::string, std::greater<int>>(dict);

    return 0;
}
