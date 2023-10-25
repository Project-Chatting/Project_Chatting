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

    // 객체 정보를 문자열로 변환하여 반환
    string toString() const {
        string str = "이메일: " + email + "\n비밀번호: " + pw + "\n전화번호: " + phoneNum + "\n생년월일: " + birthday + "\n";
        return str;
    }
};
