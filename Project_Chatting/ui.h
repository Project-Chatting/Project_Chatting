#pragma once

#include <iostream>
#include <string>
#include <Windows.h>

using std::cout;
using std::cin;
using std::endl;
using std::string;

class Ui {
public:
    // 시작 메뉴
    void start();

    // 회원 가입 메뉴
    void join();

    // 로그인 메뉴
    void login();

    // 이메일 찾기 메뉴
    void searchEmail();

    // 비밀번호 찾기 메뉴
    void searchPw();

    // 메인 메뉴
    void mainMenu();

    // 내정보 메뉴
    void myMenu();

    // 채팅 메뉴
    void chatting();

    // 설정 메뉴
    void setting();

    // 비밀번호 규칙 예시
    void pwEx();

    // 이메일 예시
    void emailEx();

    // 전화번호 예시
    void phoneEx();

    // 생년월일 예시
    void birthdayEx();
};
