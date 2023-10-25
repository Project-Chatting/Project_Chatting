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

    // 데이터베이스 연결 정보
    const string server = "tcp://127.0.0.1:3306"; // 데이터베이스 주소
    const string username = "root"; // 데이터베이스 사용자
    const string password = "root"; // 데이터베이스 접속 비밀번호

    // SQL 관련 변수
    string sqlQuery;
    Dto dto;
    Function function;
    Validation validation;
    Ui ui;

    // MySQL 드라이버 및 연결 객체
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

    // 사용자 정보
    string phoneNum;
    string birthday;
    string startMenu;
    string answer;

    // 비밀번호 및 검증
    int emailVerifie;
    int pwVerifie = 1;

    // 비밀번호 해시
    string hashedPassword;
    string storedHashedPassword;


    // 이메일 찾기
    string foundEmail;

    // 검증 번호 및 토큰
    string validationEmail;
    string validationNum;
    string sendrandomNum;



public:
    // 생성자
    Dao();

    // 새로운 사용자 정보 삽입
    void insert(const Dto& dto);

    // 전화번호가 이미 존재하는지 확인
    bool isPhoneNumberExists(const string& phoneNumber);

    // 이메일이 이미 존재하는지 확인
    bool isEmailExists(const string& email);

    // 이메일에 대한 해시된 비밀번호 가져오기
    string getHashedPassword(const string& email);

    // 전화번호와 생년월일로 이메일 찾기
    string findEmail(const string& phoneNumber, const string& birthDate);

    // 비밀번호 업데이트
    int updatePassword(const string& email, string& newHashedPassword);

    // 내 프로필 정보를 출력
    void myProfile(const string& email);

    // 닉네임 업데이트
    void nickName(const string& email);

    // 상태를 업데이트
    void updateStatus(const string& email);

    // 노래 정보를 업데이트
    void updateSong(const string& email);

    // 비밀번호를 수정
    void modifyPw(const string& email);

    // 사용자를 삭제
    int deleteUser(const string& email);

    // 회원 가입
    void join();        

    // 로그인
    string login();       

    // 이메일 찾기
    void findEmail();   

    // 비밀번호 찾기
    void findPw();     

    // 채팅 시작
    void chattingStart(const string& email);

    // 입장시 대화방 최근대화를 보여줌
    void beforeChat();

    // 원하는 메시지 검색
    void search_content_Message();

    // 기간별 메시지 검색
    void search_day_Message();

    // 닉네임을 가져옴
    string getNick();

    // 메시지 필터링 
    string filter(string beforeword);

    // 로그인 여부를 판별
    int loginCheckBefore(const string& email);
    void loginCheckAfter(const string& email);
    int checkLoginStatus(const string& email);

    int chat_recv();
    
    // 소멸자
    ~Dao();
};