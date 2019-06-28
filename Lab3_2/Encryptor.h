#pragma once

#include <string>
#include <map>

class Encryptor {
public:
	std::string encrypt(std::string in, const int key);
	std::string decrypt(std::string in, const int key);
private: 
	void isInvalidKey(std::string in, const int key);
	void isInvalidMsg(std::string in, const int key);

};

class encryptException: public std::invalid_argument {
	
public:
    explicit encryptException (const std::string& what_arg): //explicit запрещает компилятору приравнивать "Object a = 5" и "Object a(5)".
														//Делает доступным только второе
        std::invalid_argument(what_arg) {}
    explicit encryptException (const char* what_arg):
        std::invalid_argument(what_arg) {}
};