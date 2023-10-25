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
    // ���� �޴�
    void select();

    // ���� ���� �޴�
    void mainSelect(const string& email);
};
