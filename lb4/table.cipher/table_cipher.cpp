/** @file
* @author Демина К.С.
* @version 1.0
* @date 18.01.24
* @copyright ИБСТ ПГУ
* @brief Исполняемый файл для модуля Table_cipher
*/
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
    text_validation(st);
    double length=st.length();
    key_validation(key,st);
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
    text_validation(st);
    double length=st.length();
    key_validation(key,st);
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

void table_cipher::text_validation(std::string &text){
    for (int i = 0; i < text.length(); i++)
    {
        if(!isalpha(text[i])){
            throw table_error("Invalid text: "+ text);
            exit(1);
        }
        text[i]=toupper(text[i]);
    }
    
}
void table_cipher::key_validation(uint &key,std::string &text){
    if(key>text.length()){
        throw table_error ("Слишком длинный ключ: "+std::to_string(key));
        exit(1);
    }
    if(key==1 or key==text.length()){
        throw table_error ("Слишком короткий ключ или ключ равен длине слова: "+std::to_string(key));
        exit(1);
    }
}
