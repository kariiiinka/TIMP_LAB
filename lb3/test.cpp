#include <iostream>
#include <UnitTest++/UnitTest++.h>
#include "includer.h"
#include <locale>
struct KeyB_fixture {
    modAlphaCipher * p;
    KeyB_fixture()
    {
        p = new modAlphaCipher(L"В");
    }
    ~KeyB_fixture()
    {
        delete p;
    }
};

SUITE(modAlpha_test)
{
    SUITE(KeyTest) {
        TEST(ValidKey) {
            std::wstring res =modAlphaCipher(L"АБВ").encrypt(L"ААААА") ;
            std::wstring temp = L"АБВАБ";
            if(temp==res){
                CHECK(true);
            }
            else{
                CHECK(false);
            }
            
        }
     TEST(LongKey) {
            std::wstring res = modAlphaCipher(L"АБВГДЕЁЖЗИ").encrypt(L"ААААА");
            std::wstring temp = L"АБВГД";
            if(temp==res){
                CHECK(true);
            }
            else{
                CHECK(false);
            }
        }
        TEST(LowCaseKey) {
            std::wstring res = modAlphaCipher(L"бвг").encrypt(L"ААААА");
            std::wstring temp = L"БВГБВ";
            if(temp==res){
                CHECK(true);
            }
            else{
                CHECK(false);
            }
        }
        TEST(DigitsInKey) {
            CHECK_THROW(modAlphaCipher cp(L"Б1"),cipher_error);
        }
        TEST(PunctuationInKey) {
            CHECK_THROW(modAlphaCipher cp(L"Б,Г"),cipher_error);
        }
        TEST(WhitespaceInKey) {
            CHECK_THROW(modAlphaCipher cp(L"Б Г"),cipher_error);
        }
        TEST(EmptyKey) {
            CHECK_THROW(modAlphaCipher cp(L""),cipher_error);
        }
        TEST(WeakKey) {
            CHECK_THROW(modAlphaCipher(L"ААА").encrypt(L"ОЧЕНЬДЛИННЫЙТЕКСТДЛЯПРОВЕРКИ"),cipher_error);
        }
        TEST(KeyFromWrongAlphabet) {
            CHECK_THROW(modAlphaCipher cp(L"ABC"),cipher_error);
        }
    }
    SUITE(EncryptTest) {
        TEST_FIXTURE(KeyB_fixture, UpCaseString) {
            std::wstring res = p->encrypt(L"ШИФРОВАЛЬЩИЦАПОПРОСТУЗАБЫЛАРЯДКЛЮЧЕВЫХМНОЖИТЕЛЕЙИТЭГОВ");
            std::wstring temp = L"ЪКЦТРДВНЮЫКШВСРСТРУФХЙВГЭНВТБЁМНАЩЖДЭЧОПРИКФЖНЖЛКФЯЕРД";
            if(temp==res){
                CHECK(true);
            }
            else{
                CHECK(false);
            }
        }
        TEST_FIXTURE(KeyB_fixture, LowCaseString) {
            std::wstring res = p->encrypt(L"шифровальщицапопростузабыларядключевыхмножителейитэгов") ;
            std::wstring temp = L"ЪКЦТРДВНЮЫКШВСРСТРУФХЙВГЭНВТБЁМНАЩЖДЭЧОПРИКФЖНЖЛКФЯЕРД";
            if(temp==res){
                CHECK(true);
            }
            else{
                CHECK(false);
            }
        }
        TEST_FIXTURE(KeyB_fixture, StringWithWhitspaceAndPunct) {
            std::wstring res = p->encrypt(L"Шифровальщица, попросту забыла, ряд, ключевых, множителей, и тэгов, !!!") ;
            std::wstring temp = L"ЪКЦТРДВНЮЫКШВСРСТРУФХЙВГЭНВТБЁМНАЩЖДЭЧОПРИКФЖНЖЛКФЯЕРД";
            if(temp==res){
                CHECK(true);
            }
            else{
                CHECK(false);
            }
        }
        TEST_FIXTURE(KeyB_fixture, StringWithNumbers) {
            std::wstring res = p->encrypt(L"С новым 2024 годом!");
            std::wstring temp = L"УПРДЭОЕРЁРО";
            if(temp==res){
                CHECK(true);
            }
            else{
                CHECK(false);
            }
        }
        TEST_FIXTURE(KeyB_fixture, EmptyString) {
            CHECK_THROW(p->encrypt(L""),cipher_error);
        }
        TEST_FIXTURE(KeyB_fixture, NoAlphaString) {
            CHECK_THROW(p->encrypt(L"!%^#*8791362"),cipher_error);
        }
        TEST(MaxShiftKey) {
            std::wstring res = modAlphaCipher(L"Я").encrypt(L"ШИФРОВАЛЬЩИЦАПОПРОСТУЗАБЫЛАРЯДКЛЮЧЕВЫХМНОЖИТЕЛЕЙИТЭГОВ");
            std::wstring temp = L"ЧЗУПНБЯКЫШЗХЯОНОПНРСТЖЯАЪКЯПЮГЙКЭЦДБЪФЛМНЁЗСДКДИЗСЬВНБ";
            if(temp==res){
                CHECK(true);
            }
            else{
                CHECK(false);
            }
        }
        TEST_FIXTURE(KeyB_fixture,EnglishString) {
            CHECK_THROW(p->encrypt(L"CIPHERWOMANFORGOTABOUTKEYMULTIPLIERSANDTEGS"),cipher_error);
        }
    }
    SUITE(DecryptText) {
        TEST_FIXTURE(KeyB_fixture, UpCaseString) {
            std::wstring res = p->decrypt(L"ЪКЦТРДВНЮЫКШВСРСТРУФХЙВГЭНВТБЁМНАЩЖДЭЧОПРИКФЖНЖЛКФЯЕРД") ;
            std::wstring temp = L"ШИФРОВАЛЬЩИЦАПОПРОСТУЗАБЫЛАРЯДКЛЮЧЕВЫХМНОЖИТЕЛЕЙИТЭГОВ";
            if(temp==res){
                CHECK(true);
            }
            else{
                CHECK(false);
            }
        }
        TEST_FIXTURE(KeyB_fixture, LowCaseString) {
            CHECK_THROW(p->decrypt(L"ъкЦТРДВНЮЫКШВСРСТРУФХЙВГЭНВТБЁМНАЩЖДЭЧОПРИКФЖНЖЛКФЯЕРД"),cipher_error);
        }
        TEST_FIXTURE(KeyB_fixture, WhitespaceString) {
            CHECK_THROW(p->decrypt(L"ЪКЦТР ДВНЮЫКШВСРСТРУФХЙВГЭНВ ТБЁМНАЩЖДЭЧОП РИКФЖНЖ ЛКФЯЕРД"),cipher_error);
        }
        TEST_FIXTURE(KeyB_fixture, DigitsString) {
            CHECK_THROW(p->decrypt(L"УПРДЭО2024ЕРЁРО"),cipher_error);
        }
        TEST_FIXTURE(KeyB_fixture, PunctString) {
            CHECK_THROW(p->decrypt(L"ХТВ,УЖУУКБ"),cipher_error);
        }
        TEST_FIXTURE(KeyB_fixture, EmptyString) {
            CHECK_THROW(p->decrypt(L""),cipher_error);
        }
        TEST(MaxShiftKey) {
            std::wstring res = modAlphaCipher(L"Я").decrypt(L"ЧЗУПНБЯКЫШЗХЯОНОПНРСТЖЯАЪКЯПЮГЙКЭЦДБЪФЛМНЁЗСДКДИЗСЬВНБ") ;
            std::wstring temp = L"ШИФРОВАЛЬЩИЦАПОПРОСТУЗАБЫЛАРЯДКЛЮЧЕВЫХМНОЖИТЕЛЕЙИТЭГОВ";
            if(temp==res){
                CHECK(true);
            }
            else{
                CHECK(false);
            }
        }
        TEST_FIXTURE(KeyB_fixture,EnglishString) {
            CHECK_THROW(p->encrypt(L"ASODUF"),cipher_error);
        }
    }
}
SUITE(table_cipher_test){
    SUITE(encrypt_test){
        TEST(right_key){
            std::string test2="";
            std::string test = "TESTSTRING";
            table_cipher t (4, test2);
            CHECK_THROW(t.encrypt(test),table_error);
        }
        TEST(long_key){
            std::string test2="";
            std::string test = "TESTSTRING";
            table_cipher t (4, test2);
            CHECK_THROW(t.encrypt(test),table_error);
        }
        TEST(short_key){
            std::string test2="";
            std::string test = "TESTSTRING";
            table_cipher t (4, test2);
            CHECK_THROW(t.encrypt(test),table_error);
        }
        TEST(upcase_text){
            std::string test = "TESTSTRING";
            std::string test2="";
            table_cipher t (4,test2);
            CHECK_EQUAL("TISRETGTSN",t.encrypt(test));
        }
        TEST(lowcase_text){
            std::string test = "teststring";
            std::string test2="";
            table_cipher t (4,test2);
            CHECK_EQUAL("TISRETGTSN",t.encrypt(test));
        }
        TEST(text_with_spaces){
            std::string test = "test string";
            std::string test2="";
            table_cipher t (4,test2);
            CHECK_EQUAL("TISRETGTSN",t.encrypt(test));
        }
        TEST(non_int_key){
            std::string test = "TESTSTRING";
            std::string test2="";
            table_cipher t (4.9,test2);
            CHECK_EQUAL("TISRETGTSN",t.encrypt(test));
        }
    }
    SUITE(decrypt_test){
        TEST(right_key){
            std::string test2="";
            std::string test = "TISRETGTSN";
            table_cipher t (4, test2);
            CHECK_THROW(t.decrypt(test),table_error);
        }
        TEST(long_key){
            std::string test2="";
            std::string test = "TISRETGTSN";
            table_cipher t (4, test2);
            CHECK_THROW(t.decrypt(test),table_error);
        }
        TEST(short_key){
            std::string test2="";
            std::string test = "TISRETGTSN";
            table_cipher t (4, test2);
            CHECK_THROW(t.decrypt(test),table_error);
        }
        TEST(upcase_text){
            std::string test = "TISRETGTSN";
            std::string test2=" ";
            table_cipher t (4,test2);
            CHECK_EQUAL("TESTSTRING",t.decrypt(test));
        }
        TEST(lowcase_text){
            std::string test = "tisretgtsn";
            std::string test2=" ";
            table_cipher t (4,test2);
            CHECK_EQUAL("TESTSTRING",t.decrypt(test));
        }
        TEST(text_with_spaces){
            std::string test = "tisr etgtsn";
            std::string test2=" ";
            table_cipher t (4,test2);
            CHECK_EQUAL("TESTSTRING",t.decrypt(test));
        }
        TEST(non_int_key){
            std::string test = "TISRETGTSN";
            std::string test2=" ";
            table_cipher t (4.9,test2);
            CHECK_EQUAL("TESTSTRING",t.decrypt(test));
        }
    }
}
int main(){
    std::locale loc("ru_RU.UTF-8");
    std::locale::global(loc);
    return UnitTest::RunAllTests();
}
