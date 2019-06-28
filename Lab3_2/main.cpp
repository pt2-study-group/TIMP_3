#include <unittest++/UnitTest++.h>
#include "Encryptor.h"

Encryptor enc;

SUITE(KeyTest) {
    TEST(ValidKey) {
        CHECK_EQUAL("ВГАОКПЬЬЛТТЕЯЕШЛПЫУ", enc.encrypt("ПЕТЬКАВЫШЕЛПОГУЛЯТЬ", 7));
    }
    TEST(LongKey) {
        CHECK_EQUAL("ЬТЯЛУГОПЛЕШЫВАКЬТЕП", enc.encrypt("ПЕТЬКАВЫШЕЛПОГУЛЯТЬ", 100));
    }

}

struct KeyB_fixture {
    Encryptor * p;
    KeyB_fixture() {
        p = new Encryptor();
    }
    ~KeyB_fixture() {
        delete p;
    }
};

SUITE(EncryptTest)
{
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        CHECK_EQUAL("КЕУЬШГЬТЫОТЕВПЯПАЛЛ",
                    p->encrypt("ПЕТЬКАВЫШЕЛПОГУЛЯТЬ", 5));
    }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK_EQUAL("КЕУЬШГЬТЫОТЕВПЯПАЛЛ",
                    p->encrypt("петькавышелпогулять", 5));
    }
    TEST_FIXTURE(KeyB_fixture, StringWithWhitspaceAndPunct) {
        CHECK_EQUAL("КЕУЬШГЬТЫОТЕВПЯПАЛЛ",
                    p->encrypt("Петька вышел погулять!!!", 5));
    }
    TEST_FIXTURE(KeyB_fixture, StringWithNumbers) {
        CHECK_EQUAL("ЛЛАИИРРРВИБЯКЛСЗ", p->encrypt("Кирилл брился в 2019 раз", 5));
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p->encrypt("", 5), encryptException);
    }
}

SUITE(DecryptText)
{
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK_THROW(p->decrypt("кеУЬШГЬСЫОТАВПЯВАЛЛ", 5),encryptException);
    }
    TEST_FIXTURE(KeyB_fixture, WhitespaceString) {
        CHECK_THROW(p->decrypt("КЕУ ЬШГ ЬТЫ ОТЕ ВПЯ ПАЛЛ", 5),encryptException);
    }
    TEST_FIXTURE(KeyB_fixture, DigitsString) {
        CHECK_THROW(p->decrypt("ЛЛАИИРРРВИБ2019ЯКЛСЗ", 5),encryptException);
    }
    TEST_FIXTURE(KeyB_fixture, PunctString) {
        CHECK_THROW(p->decrypt("КЕУЬШГ,ЬТЫОТЕВПЯПАЛЛ", 5),encryptException);
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p->decrypt("", 5), encryptException);
    }
}

int main(int argc, char **argv)
{
    return UnitTest::RunAllTests();
}