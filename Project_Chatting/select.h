#pragma once

#include <string>
#include <cstdlib>

#include "dao.h"
#include "Ui.h"

class Select {
public:
    Ui ui;
    Dao dao;

    string email;
    int selectNum;
    int isTrue;
    int backButton;

public:
    // 시작 메뉴
    void select();

    // 메인 선택 메뉴
    void mainSelect(const string& email);
};
