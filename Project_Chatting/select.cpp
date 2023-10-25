#include "Select.h"

void Select::select() {
    isTrue = 1;
    while (isTrue) {
        do {
            ui.start();
            cout << "▶ ";
            cin >> selectNum;
        } while (selectNum < 0 || selectNum > 4);

        switch (selectNum) {
        case 1:
            ui.login();
            email = dao.login();
            mainSelect(email);
            isTrue = 0;
            break;
        case 2:
            ui.searchEmail();
            dao.findEmail();
            break;
        case 3:
            ui.searchPw();
            dao.findPw();
            break;
        case 4:
            ui.join();
            dao.join();
            break;
        case 0:
            exit(0);
        }
    }
}

void Select::mainSelect(const string& email) {
    isTrue = 1;
    while (isTrue) {
        do {
            ui.mainMenu();
            cout << "▶ ";
            cin >> selectNum;
        } while (selectNum < 0 || selectNum > 4);
        switch (selectNum) {
        case 1:
            ui.myMenu();
            backButton = 1;
            while (backButton) {
                cout << "▶ ";
                cin >> selectNum;
                switch (selectNum) {
                case 1:
                    dao.myProfile(email);
                    break;
                case 2:
                    dao.nickName(email);
                    break;
                case 3:
                    dao.updateStatus(email);
                    break;
                case 4:
                    dao.updateSong(email);
                    break;
                case 0:
                    backButton = 0;
                    break;
                default:
                    cout << "▶잘못된 입력입니다. 다시 입력해주세요." << endl;
                    continue;
                }
            }
            break;
        case 2:
            ui.chatting();
            backButton = 1;
            while (backButton) {
                cout << "▶ ";
                cin >> selectNum;
                switch (selectNum) {
                case 1:
                    dao.chattingStart(email);
                    break;
                case 2:
                    dao.search_content_Message();
                    continue;
                case 3:
                    dao.search_day_Message();
                    continue;
                case 0:
                    backButton = 0;
                    break;
                default:
                    cout << "▶잘못된 입력입니다. 다시 입력해주세요." << endl;
                    continue;
                }
            }
            break;
        case 3:
            ui.setting();
            backButton = 1;
            while (backButton) {
                cout << "▶ ";
                cin >> selectNum;
                switch (selectNum) {
                case 1:
                    dao.modifyPw(email);
                    continue;
                case 2:
                    if (dao.deleteUser(email) == 1);
                    else backButton = 0;
                    break;
                case 0:
                    backButton = 0;
                    break;
                default:
                    cout << "▶잘못된 입력입니다. 다시 입력해주세요." << endl;
                    continue;
                }
            }
            break;
        case 0:
            dao.loginCheckBefore(email);
            exit(0);
        default:
            cout << "▶잘못된 입력입니다. 다시 입력해주세요." << endl;
            continue;
        }
    }
}
