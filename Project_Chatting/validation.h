#pragma once

#include <regex>
#include <iostream>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::regex;

class Validation {
public:
    // 일반적인 입력 유효성 검사
    bool validateInput(const string& input, const regex& pattern, const string& errorMessage);

    // 이메일 유효성 검사
    bool emailValidation(const string& email);

    // 비밀번호 유효성 검사
    bool passwordValidation(const string& pw);

    // 전화번호 유효성 검사
    bool phoneNumValidation(const string& phoneNum);

    // 생년월일 유효성 검사
    bool birthdayValidation(const string& birthday);
};