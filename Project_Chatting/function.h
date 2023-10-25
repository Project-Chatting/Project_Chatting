#pragma once

#include <string>
#include <iostream>
#include <random>
#include <sstream>
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>

using std::cout;
using std::cin;
using std::endl;
using std::string;

class Function {
public:
    // ���α׷� ����
    void exit(const string& str);

    // ���ڿ��� SHA-256 �ؽ÷� ��ȯ
    string sha256Hash(const string& pw);

    // ���� ���� ����
    string randomNum();
};
