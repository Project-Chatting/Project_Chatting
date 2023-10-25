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
    // 프로그램 종료
    void exit(const string& str);

    // 문자열을 SHA-256 해시로 변환
    string sha256Hash(const string& pw);

    // 랜덤 숫자 생성
    string randomNum();
};
