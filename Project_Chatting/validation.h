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
    // �Ϲ����� �Է� ��ȿ�� �˻�
    bool validateInput(const string& input, const regex& pattern, const string& errorMessage);

    // �̸��� ��ȿ�� �˻�
    bool emailValidation(const string& email);

    // ��й�ȣ ��ȿ�� �˻�
    bool passwordValidation(const string& pw);

    // ��ȭ��ȣ ��ȿ�� �˻�
    bool phoneNumValidation(const string& phoneNum);

    // ������� ��ȿ�� �˻�
    bool birthdayValidation(const string& birthday);
};