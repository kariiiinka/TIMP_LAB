#include <iostream>
#include <cctype>
#include <clocale>
#include <string>
#include "table_cipher.h"
#include <boost/program_options.hpp>
using namespace std;
int main(int argc, char **argv)
{
        string st;
        uint action;
        double key;
        while(true){
            cout<<"Введите ключ: ";
            cin>>key;
            cout<<"Введите тип операции: 1 - зашифрование, 2 - Расшифрование, 0 - Завершение программы"<<endl;
            cin>>action;
            std::string i_value=" ";
            table_cipher cipher(key,i_value);
            if (action==1){
                cout<<"Введите строку для шифрования: ";
                cin>>st;
                if(key>st.length()){
                std::cerr<<"Ключ не может быть длиннее слова"<<std::endl;
                exit(1);
                }
                std::cout<<"Зашифрованная строка: "<<cipher.encrypt(st)<<std::endl;
            }
            else if (action==2){
                cout<<"Введите строку для расшифрования: ";
                cin>>st;
                if(key>st.length()){
                std::cerr<<"Ключ не может быть длиннее слова"<<std::endl;
                exit(1);
                }
                std::cout<<"Расшифрованная строка: "<<cipher.decrypt(st)<<std::endl;
            }
            else{
                cout<<"Программа завершила работу"<<endl;
                exit(0);
            }
        }
    return 0;
}
