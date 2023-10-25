#pragma once
#ifndef EMAIL_HELPER_H
#define EMAIL_HELPER_H

#include <string>
#include <fstream>
#include <iostream>

using std::cout;
using std::cin;
using std::endl;
using std::string;

// 이메일 수신자 및 발신자 정보
extern string TO;
extern string FROM;

// 랜덤 번호 및 API 키 정보
extern string randomNum;
extern string apiKey;

// 이메일 전송 함수
int sendEmail(const string& random, const string& email);

#endif
