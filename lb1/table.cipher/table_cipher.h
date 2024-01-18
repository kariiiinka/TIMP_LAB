#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
class table_cipher{
    public:
    uint key;
    double rows;
    std::string i_value;
    std::string t;
    std::vector<std::vector<std::string>> st_to_vec;
    std::string encrypt(std::string st);
    std::string decrypt(std::string st);
    void write_str_to_v(std::string st,std::vector<std::vector<std::string>> &v);
    void write_str_to_v(std::vector<std::vector<std::string>> &v,std::string st);
    table_cipher(double k,std::string& initial_value);
};