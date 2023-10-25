#pragma once

#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

class Dto {
private:
    string email;
    string pw;
    string phoneNum;
    string birthday;

public:
    // Getter
    string getEmail() const {
        return email;
    }

    string getPw() const {
        return pw;
    }

    string getPhoneNum() const {
        return phoneNum;
    }

    string getBirthday() const {
        return birthday;
    }

    // Setter
    void setEmail(const string& newEmail) {
        email = newEmail;
    }

    void setPw(const string& newPw) {
        pw = newPw;
    }

    void setPhoneNum(const string& newPhoneNum) {
        phoneNum = newPhoneNum;
    }

    void setBirthday(const string& newBirthday) {
        birthday = newBirthday;
    }

    // ��ü ������ ���ڿ��� ��ȯ�Ͽ� ��ȯ
    string toString() const {
        string str = "�̸���: " + email + "\n��й�ȣ: " + pw + "\n��ȭ��ȣ: " + phoneNum + "\n�������: " + birthday + "\n";
        return str;
    }
};
