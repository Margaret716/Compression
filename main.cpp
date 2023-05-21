#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <bitset>
#include <map>
#include <sstream>
#include <iterator>

std::vector <char> single_letters;
std::map<char, std::string> dictionary;

int n;
int size;
int if_letter_in_vector;
std::string sentence;
std::string file_content;

void convert_binary() {

    size = static_cast<int>(single_letters.size());
    n = ceil(log2(size));

    for (int i = 0; i < single_letters.size(); i++)
    {
        std::string key = std::bitset<8>(i).to_string();
        std::string key1 = key.substr(8 - n, n);
        dictionary[single_letters[i]] = key1;

        //std::cout<< "key: " << key << " key1: " << dictionary[single_letters[i]] << " i: " << i << " single_letters[i]: " << single_letters[i]<<std::endl;
    }
}

int main()
{
    std::ifstream ofs;
    ofs.open("C:/Users/mlewa/CLionProjects/kompresja/output.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();

    std::ifstream file;
    file.open("C:/Users/mlewa/CLionProjects/kompresja/input.txt");

    if(file.fail())
    {
        std::cout << "File fail";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    
    file_content = buffer.str();
    file.close();


    for (char znak: file_content) {
            if_letter_in_vector = 0;
            for (char i: single_letters)
            {
                if (znak == i)
                    if_letter_in_vector = 1;
            }

            if (if_letter_in_vector == 0)
                single_letters.push_back(znak);
        }


    std::sort(single_letters.begin(), single_letters.end());
    convert_binary();

    int sent_len = static_cast<int>(sentence.length());

    int r = (8 - (3 + sent_len * n) % 8) % 8;
    std::string r_bin = std::bitset<3>(r).to_string();

    std::stringstream temp;
    temp << r_bin;

    for (char i : file_content)
    {
        temp << dictionary[i];
    }


    for (int i = 0; i < r; i++)
    {
        temp << "1";
    }

    std::string temp1;
    temp >> temp1;

    std::fstream final_compressed_sentence;
    final_compressed_sentence.open("C:/Users/mlewa/CLionProjects/kompresja/output.txt", std::ios::out| std::ios::app);

    final_compressed_sentence<< char(single_letters.size());

    for(char single_letter : single_letters)
    {
        final_compressed_sentence << single_letter;
    }

    for(int i = 0; i < temp1.length(); i += 8)
    {
        std::string substr = temp1.substr(i, 8);
        std::bitset<8> bits(substr);

        final_compressed_sentence << char(bits.to_ulong());
        std::cout << char(bits.to_ulong());
    }

}
