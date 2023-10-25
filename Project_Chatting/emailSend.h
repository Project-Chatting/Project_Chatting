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

// �̸��� ������ �� �߽��� ����
extern string TO;
extern string FROM;

// ���� ��ȣ �� API Ű ����
extern string randomNum;
extern string apiKey;

// �̸��� ���� �Լ�
int sendEmail(const string& random, const string& email);

#endif
