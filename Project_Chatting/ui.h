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
    // ���� �޴�
    void start();

    // ȸ�� ���� �޴�
    void join();

    // �α��� �޴�
    void login();

    // �̸��� ã�� �޴�
    void searchEmail();

    // ��й�ȣ ã�� �޴�
    void searchPw();

    // ���� �޴�
    void mainMenu();

    // ������ �޴�
    void myMenu();

    // ä�� �޴�
    void chatting();

    // ���� �޴�
    void setting();

    // ��й�ȣ ��Ģ ����
    void pwEx();

    // �̸��� ����
    void emailEx();

    // ��ȭ��ȣ ����
    void phoneEx();

    // ������� ����
    void birthdayEx();
};
