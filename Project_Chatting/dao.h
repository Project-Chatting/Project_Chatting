#pragma once

#include <WS2tcpip.h>
#include <WinSock2.h>
#include <string>
#include <sstream>
#include <iostream>
#include <thread>
#include <mysql/jdbc.h>
#include <conio.h> 
#include <Windows.h>

#include "dto.h"
#include "ui.h"
#include "function.h"
#include "validation.h"
#include "emailSend.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using namespace sql;

#define MAX_SIZE 1024

class Dao {
private:

    // �����ͺ��̽� ���� ����
    const string server = "tcp://127.0.0.1:3306"; // �����ͺ��̽� �ּ�
    const string username = "root"; // �����ͺ��̽� �����
    const string password = "root"; // �����ͺ��̽� ���� ��й�ȣ

    // SQL ���� ����
    string sqlQuery;
    Dto dto;
    Function function;
    Validation validation;
    Ui ui;

    // MySQL ����̹� �� ���� ��ü
    mysql::MySQL_Driver* driver;
    Connection* con;
    Statement* stmt;
    ResultSet* result;
    PreparedStatement* pstmt;

    string getEmail;
    string email;
    string status;
    string nick;
    string song;
    string pw;
    string pw2;
    string newPw;
    string dbPw;
    bool isMatching = 0;
    char ch;
    int isTrue;
    int index;
    int backButton;
    int code ; 
    int loginCheckNum;

    // ����� ����
    string phoneNum;
    string birthday;
    string startMenu;
    string answer;

    // ��й�ȣ �� ����
    int emailVerifie;
    int pwVerifie = 1;

    // ��й�ȣ �ؽ�
    string hashedPassword;
    string storedHashedPassword;


    // �̸��� ã��
    string foundEmail;

    // ���� ��ȣ �� ��ū
    string validationEmail;
    string validationNum;
    string sendrandomNum;



public:
    // ������
    Dao();

    // ���ο� ����� ���� ����
    void insert(const Dto& dto);

    // ��ȭ��ȣ�� �̹� �����ϴ��� Ȯ��
    bool isPhoneNumberExists(const string& phoneNumber);

    // �̸����� �̹� �����ϴ��� Ȯ��
    bool isEmailExists(const string& email);

    // �̸��Ͽ� ���� �ؽõ� ��й�ȣ ��������
    string getHashedPassword(const string& email);

    // ��ȭ��ȣ�� ������Ϸ� �̸��� ã��
    string findEmail(const string& phoneNumber, const string& birthDate);

    // ��й�ȣ ������Ʈ
    int updatePassword(const string& email, string& newHashedPassword);

    // �� ������ ������ ���
    void myProfile(const string& email);

    // �г��� ������Ʈ
    void nickName(const string& email);

    // ���¸� ������Ʈ
    void updateStatus(const string& email);

    // �뷡 ������ ������Ʈ
    void updateSong(const string& email);

    // ��й�ȣ�� ����
    void modifyPw(const string& email);

    // ����ڸ� ����
    int deleteUser(const string& email);

    // ȸ�� ����
    void join();        

    // �α���
    string login();       

    // �̸��� ã��
    void findEmail();   

    // ��й�ȣ ã��
    void findPw();     

    // ä�� ����
    void chattingStart(const string& email);

    // ����� ��ȭ�� �ֱٴ�ȭ�� ������
    void beforeChat();

    // ���ϴ� �޽��� �˻�
    void search_content_Message();

    // �Ⱓ�� �޽��� �˻�
    void search_day_Message();

    // �г����� ������
    string getNick();

    // �޽��� ���͸� 
    string filter(string beforeword);

    // �α��� ���θ� �Ǻ�
    int loginCheckBefore(const string& email);
    void loginCheckAfter(const string& email);
    int checkLoginStatus(const string& email);

    int chat_recv();
    
    // �Ҹ���
    ~Dao();
};