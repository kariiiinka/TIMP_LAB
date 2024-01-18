#include "table_cipher.h"
void table_cipher::write_str_to_v(std::string st, std::vector<std::vector<std::string>> &v) {
    int l = 0;
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v[i].size(); j++) {
            if (l < st.length()) { 
                v[i][j] = st[l];
                l++;
            }
            else {
                break;
            }
        }
    }
}
void table_cipher::write_str_to_v(std::vector<std::vector<std::string>> &v,std::string st) {
    int l = 0;
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v[i].size(); j++) {
            if (l < st.length()) { 
                v[i][j] = st[l];
                l++;
            }
            else {
                break;
            }
        }
    }
    l = 0;
    for (int j = key - 1; j >= 0; j--) {
        for (int i = 0; i < rows; i++) {
            if (l < st.length()) {
                if(v[i][j]==" "){
                    continue;
                }
                v[i][j] = st[l];
                l++;
            } else {
                break;
            }
        }
    }
}
table_cipher::table_cipher(double k,std::string& initial_value){
    key=k;
    i_value=initial_value;
}
std::string table_cipher::encrypt(std::string st){
    st.erase(std::remove(st.begin(), st.end(), ' '), st.end());
    double length=st.length();
    rows=std::ceil(length/key);
    st_to_vec=std::vector<std::vector<std::string>>(rows, std::vector<std::string>(key, i_value));
    write_str_to_v(st,st_to_vec);
    std::string res="";
   
    for(int j =key-1;j>=0;j--){
        for(int i=0;i<rows;i++){
            res=res+st_to_vec[i][j];
        }
    }
    res.erase(std::remove(res.begin(), res.end(), ' '), res.end());
    return res;
}
std::string table_cipher::decrypt(std::string st) {
    st.erase(std::remove(st.begin(), st.end(), ' '), st.end());
    double length=st.length();
    rows=std::ceil(length/key);
    st_to_vec=std::vector<std::vector<std::string>>(rows, std::vector<std::string>(key, i_value));
    write_str_to_v(st_to_vec,st);
    std::string res = "";
    for (int i = 0; i <rows; i++) {
        for (int j = 0; j < key; j++) {
            res = res + st_to_vec[i][j];
        }
    }
    res.erase(std::remove(res.begin(), res.end(), ' '), res.end());
    return res;
}
