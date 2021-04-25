/*******************************************

Pāvels Žuravļovs, pz20014

Izveidot programmu valodā C++.  Ja programma darbojas ar failu, nedrīkst dublēt visa faila saturu operatīvajā atmiņā.
Ar faila komponenti tiek saprasts fiksēta garuma ieraksts. Sīkākās prasības sk. Laboratorijas darbu noteikumos.

 ---------------------------------------------------------------------------------------------------------------------------

H10. Doti divi bināri faili f1 un f2, kuru komponentes ir ieraksti ar struktūru: atslēga (int), vārds (nepārsniedz 30 simbolus).
Failu komponentes sakārtotas pēc atslēgām dilstošā secībā. Uzrakstīt programmu, kas apvieno failus f1 un f2 failā f3 tā,
lai arī f3 komponentes būtu dilstošā secībā (failos nedrīkst parādīties divas komponentes ar vienādu atslēgu vērtību).
Programmu veidot tā, lai pilns faila saturs netiktu ielādēts operatīvajā atmiņā. Uzrakstīt arī palīgprogrammas, kas ļauj izveidot failus f1 un f2 un izdrukā failu saturu.

Programma izveidota: 2021/04/21


\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0 - 31 nulls
*******************************************/

#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using std::cout;
using std::endl;

void out_to_bin_file_from_map(const char *filename, std::map<int, char*, std::greater<int>> &dict, const size_t &K_size, const size_t &V_size)
{
    std::ofstream ofs(filename, std::ios_base::out | std::ios_base::binary);
    for (auto it = dict.begin(); it != dict.end(); ++it)
    {
        ofs.write((char*)&it->first, K_size);
        ofs.write((char*)it->second, V_size);
    }
    ofs.close();
}

void in_to_map_from_bin_file(const char *filename, std::map<int, char*, std::greater<int>> &dict, const size_t &K_size, const size_t &V_size)
{
    std::ifstream ifs(filename, std::ios_base::out | std::ios_base::binary);
    ifs.seekg(0, std::ios_base::end);
    size_t f_length = ifs.tellg();

    if (f_length % (K_size+V_size) != 0)
    {
        ifs.close();
        throw "in_to_map_from_bin_file::ERROR::File Size and Memory Block Size does not match!";
    }
    cout<<"in_to_map_from_bin_file::Correct File Size."<<endl;

    ifs.seekg(0, std::ios_base::beg);

    std::vector<char*> key_duplicates;
    for (int i = 0; i < f_length/(K_size+V_size); ++i)
    {
        int num;
        char *cstr = new char[V_size];

        ifs.read((char*)&num, sizeof(num));
        ifs.read(cstr, V_size);

        if (dict.find(num) == dict.end())
            dict.emplace(std::pair<int, char*>(num, cstr));
        else
            key_duplicates.push_back(cstr);
    }
    ifs.close();

    auto it = dict.begin();
    int largest_idx = it->first;

    for(auto d_it = key_duplicates.begin(); d_it != key_duplicates.end(); ++d_it)
        dict[++largest_idx]=*d_it;
}

int main()
{
    /*** implement input; fix char* decay(?) ***/
    const short int LIMIT = 30;
    const char* fi;
    std::map<int, char*, std::greater<int>> dict;

    //f1 dict
    dict.insert({0, "te1st\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"});
    dict.insert({1, "Rg\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"});
    dict.insert({3, "Jokers\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"});

    out_to_bin_file_from_map("./f1.bin", dict, sizeof(int), sizeof(char)*(LIMIT+1));

    cout<<"First Dict: "<<endl;
    for (auto it = dict.begin(); it != dict.end(); ++it)
    {
        cout<<it->first<<" "<<it->second<<endl;
    }

    dict.clear();

    //f2 dict
    dict.insert({9, "Jhan\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"});
    dict.insert({-1, "Logi\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"});
    dict.insert({2, "Yan Han\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"});
    out_to_bin_file_from_map("./f2.bin", dict, sizeof(int), sizeof(char)*(LIMIT+1));

    cout<<endl<<"Second Dict: "<<endl;
    for (auto it = dict.begin(); it != dict.end(); ++it)
    {
        cout<<it->first<<" "<<it->second<<endl;
    }

    try
    {
        in_to_map_from_bin_file("./f1.bin", dict, sizeof(int), sizeof(char)*(LIMIT+1));
    }
    catch (const char *err)
    {
        cout<<err<<endl;
    }

    cout<<endl<<"Summed Dict: "<<endl;
    for (auto it = dict.begin(); it != dict.end(); ++it)
    {
        cout<<it->first<<" "<<it->second<<endl;
    }

    cout<<endl;
    // FIXME
    auto it = dict.begin();
    while (it != dict.end())
    {
        cout<<it->first<<" "<<&it->second<<endl;
        auto *del_it = &it->second;
        ++it;
        cout<<&*del_it<<endl;
        delete &*del_it;
    }

    return 0;
}
