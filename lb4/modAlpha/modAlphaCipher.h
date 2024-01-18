/** @file
* @author Демина К.С.
* @version 1.0
* @date 18.01.24
* @copyright ИБСТ ПГУ
* @brief Заголовочный файл для модуля Gronsfeld
*/
#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <cctype>
#include <locale>
/** @brief Шифрование методом Гронсфельда
* @details Ключ устанавливается в конструкторе.
* Расшифрование и зашифрование просходит с помощью методов encrypt и decrypt
* @warning Реализована поддержка только для русского языка
*/
class modAlphaCipher
{
private:
    /**
    * @brief Русский алфавит по порядку
    */
    std::wstring numAlpha = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
    /**
    * @brief Ассоциативный массив "номер по символу"
    */
    std::map <wchar_t,int> alphaNum;
    /**
    * @brief Ключ
    */
    std::vector <int> key;
    /**
    * @brief Преобразование строка-вектор
    */ 
    std::vector<int> convert(const std::wstring& s); 
    /**
    * @brief Преобразование вектор-строка
    */
    std::wstring convert(const std::vector<int>& v); 
    /**
    * @brief Получение валидного ключа
    * @details Строчные символы ключа автоматически преобразуются к
    заглавным.
    * Все не-буквы удаляются
    * @param [in] key Ключ. Строка не должна быть пустой
    * @return Обработаный ключ
    * @throw cipher_error, если ключ пустой или присутствуют символы, не входящие в заданный алфавит
    */
    std::wstring getValidKey(const std::wstring & s); //обработка ошибок при инициализации ключа
    /**
    * @brief Получение валидного открытого текста
    * @details Строчные символы текста автоматически преобразуются к
    заглавным.
    * Все не-буквы удаляются
    * @param [in] open_text Открытый текст. Строка не должна быть пустой
    * @return Обработаный открытый текст
    * @throw cipher_error, если открытый текст пустой или присутствуют символы, не входящие в заданный алфавит
    */
    std::wstring getValidOpenText(const std::wstring & s);//обработка ошибок при вводе открытого текста
    /**
    * @brief Получение валидного шифротекста
    * @details Строчные символы шифротекста автоматически преобразуются к
    заглавным.
    * Все не-буквы удаляются
    * @param [in] cipher_text Шифро текст. Строка не должна быть пусой
    * @return Обработаный шифро текст
    * @throw cipher_error, если шифротекст пустой или присутствуют символы, не входящие в заданный алфавит
    */
    std::wstring getValidCipherText(const std::wstring & s);//обработка ошибок при вводе шифро текста
public:
    /**
    * @brief Запретим конструктор без параметров
    */
    modAlphaCipher()=delete;
    /**
    * @brief Конструктор для установки ключа
    */
    modAlphaCipher(const std::wstring& skey);
    /**
    * @brief Зашифрование
    * @details Строчные символы открытого текста автоматически преобразуются к
    заглавным.
    * Все не-буквы удаляются
    * @param [in] open_text Открытый текст. Строка не должна быть пустой.
    * @return Зашифрованная строка
    * @throw cipher_error, если открытый текст пустой или присутствуют символы, не входящие в заданный алфавит
    */
    std::wstring encrypt(const std::wstring& open_text); //зашифрование
    /**
    * @brief Расшифрование
    * @details Строчные символы шифротекста автоматически преобразуются к
    заглавным.
    * Все не-буквы удаляются
    * @param [in] cipher_text Шифро текст. Строка не должна быть пустой.
    * @return Расшифрованная строка
    * @throw cipher_error, если текст пустой или присутствуют символы, не входящие в заданный алфавит
    */
    std::wstring decrypt(const std::wstring& cipher_text);//расшифрование
    
};
/** @brief Класс ошибок для шифрования методом Гронсфельда
* @details Используется для обозначения специфических ошибок, возникающих при работе с модулем
* @warning Вывод сообщений об ошибках только на английском языке
*/
class cipher_error: public std::invalid_argument
{
public:
    explicit cipher_error (const std::string& what_arg):
        std::invalid_argument(what_arg) {}
    explicit cipher_error (const char* what_arg):
        std::invalid_argument(what_arg) {}
};
