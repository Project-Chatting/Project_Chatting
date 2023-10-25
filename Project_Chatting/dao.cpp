#include "dao.h"

SOCKET client_sock_;
string my_nick_;


Dao::Dao() {
    // MySQL 드라이버 초기화
    try {
        driver = mysql::get_mysql_driver_instance();
    }
    catch (SQLException& e) {
        cout << "MySQL 드라이버를 초기화하는 데 실패했습니다. 오류 메시지: " << e.what() << endl;
        exit(1);
    }

    // 데이터베이스에 연결
    try {
        con = driver->connect(server, username, password);
        con->setSchema("projectChatting");
        stmt = con->createStatement();
        stmt->execute("set names euckr");
    }
    catch (SQLException& e) {
        cout << "데이터베이스에 연결하는 데 실패했습니다. 오류 메시지: " << e.what() << endl;
        exit(1);
    }
}

void Dao::insert(const Dto& dto) {
    try {
        sqlQuery = "INSERT INTO user(email, pw, phone, birth, joinDate) VALUES (?, ?, ?, ?, CURRENT_TIMESTAMP)";
        pstmt = con->prepareStatement(sqlQuery);
        pstmt->setString(1, dto.getEmail());
        pstmt->setString(2, dto.getPw());
        pstmt->setString(3, dto.getPhoneNum());
        pstmt->setString(4, dto.getBirthday());
        pstmt->execute();
    }
    catch (SQLException& e) {
        cout << "회원 정보를 데이터베이스에 추가하는 데 실패했습니다. 오류 메시지: " << e.what() << endl;
    }
}

bool Dao::isPhoneNumberExists(const string& phoneNumber) {
    try {
        sqlQuery = "SELECT phone FROM user WHERE phone = ?";
        pstmt = con->prepareStatement(sqlQuery);
        pstmt->setString(1, phoneNumber);
        ResultSet* res = pstmt->executeQuery();
        return res->next();
    }
    catch (SQLException& e) {
        cout << "전화번호 확인 중 오류가 발생했습니다. 오류 메시지: " << e.what() << endl;
        return false;
    }
}

bool Dao::isEmailExists(const string& email) {
    try {
        sqlQuery = "SELECT email FROM user WHERE email = ?";
        pstmt = con->prepareStatement(sqlQuery);
        pstmt->setString(1, email);
        ResultSet* res = pstmt->executeQuery();
        return res->next();
    }
    catch (SQLException& e) {
        cout << "이메일 확인 중 오류가 발생했습니다. 오류 메시지: " << e.what() << endl;
        return false;
    }
}

string Dao::getHashedPassword(const string& email) {
    try {
        sqlQuery = "SELECT pw FROM user WHERE email = ?";
        pstmt = con->prepareStatement(sqlQuery);
        pstmt->setString(1, email);
        ResultSet* res = pstmt->executeQuery();
        if (res->next()) {
            return res->getString("pw");
        }
        else {
            return "";
        }
    }
    catch (SQLException& e) {
        cout << "비밀번호 가져오기 중 오류가 발생했습니다. 오류 메시지: " << e.what() << endl;
        return "";
    }
}

string Dao::findEmail(const string& phoneNumber, const string& birthday) {
    try {
        sqlQuery = "SELECT email FROM user WHERE phone = ? AND birth = ?";
        pstmt = con->prepareStatement(sqlQuery);
        pstmt->setString(1, phoneNumber);
        pstmt->setString(2, birthday);
        ResultSet* res = pstmt->executeQuery();
        if (res->next()) {
            return res->getString("email");
        }
        else {
            return "";
        }
    }
    catch (SQLException& e) {
        cout << "이메일 찾기 중 오류가 발생했습니다. 오류 메시지: " << e.what() << endl;
        return "";
    }
}

int Dao::updatePassword(const string& email, string& newHashedPassword) {
    try {
        sqlQuery = "UPDATE user SET pw = ? WHERE email = ?";
        pstmt = con->prepareStatement(sqlQuery);
        pstmt->setString(1, newHashedPassword);
        pstmt->setString(2, email);
        return pstmt->executeUpdate();
    }
    catch (SQLException& e) {
        cout << "비밀번호 업데이트 중 오류가 발생했습니다. 오류 메시지: " << e.what() << endl;
        return -1;
    }
}

void Dao::myProfile(const string& email)
{
    pstmt = con->prepareStatement("SELECT  nick, status, song, birth, phone FROM user WHERE email = ?");
    pstmt->setString(1, email);
    result = pstmt->executeQuery();

    while (result->next())
    {
        cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
        if (result->getString("nick") == "")
        {
            cout << "▷별명 : 없음" << endl;
        }
        else {
            cout << "▷별명 : " << result->getString("nick") << endl;
        }
        if (result->getString("status") == "")
        {
            cout << "▷상메 : 없음" << endl;
        }
        else {
            cout << "▷상메 : " << result->getString("status") << endl;
        }
        if (result->getString("song") == "")
        {
            cout << "▷노래 : 없음" << endl;
        }
        else {
            cout << "▷노래 : " << result->getString("song") << endl;
        }
        cout << "▷생일 : " << result->getString("birth") << endl;
        cout << "▷번호 : " << result->getString("phone") << endl;
        cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
    }
}

void Dao::nickName(const string& email) {
    cout << ">>닉네임 입력 : ";
    cin.ignore();
    getline(cin, nick);
    pstmt = con->prepareStatement("UPDATE user SET nick = ? WHERE email = ?");
    pstmt->setString(1, nick);
    pstmt->setString(2, email);
    pstmt->executeQuery();
    printf("▶업데이트 되었습니다.\n");
}

void Dao::updateStatus(const string& email)
{
    cout << ">>상태메시지 입력 : ";
    cin.ignore();
    getline(cin, status);
    pstmt = con->prepareStatement("UPDATE user SET status = ? WHERE email = ?");
    pstmt->setString(1, status);
    pstmt->setString(2, email);
    pstmt->executeQuery();
    printf("▶업데이트 되었습니다.\n");
}

void Dao::updateSong(const string& email)
{
    cout << ">>노래 입력 : ";
    cin.ignore();
    getline(cin, song);
    pstmt = con->prepareStatement("UPDATE user SET song = ? WHERE email = ?");
    pstmt->setString(1, song);
    pstmt->setString(2, email);
    pstmt->executeQuery();
    printf("▶업데이트 되었습니다.\n");
}

void Dao::modifyPw(const string& email) {
    bool isMatching = false;

    do {
        cout << endl;
        cout << "비밀번호를 입력하세요 : ";
        pw = "";
        while (true) {
            ch = _getch();

            if (ch == 13)
                break;
            else if (ch == 8) {
                if (!pw.empty()) {
                    pw.pop_back();
                    cout << "\b \b";
                }
            }
            else {
                pw += ch;
                cout << '*';
            }
        }

        function.exit(pw);

        string hashedPassword = function.sha256Hash(pw);
        string storedHashedPassword = getHashedPassword(email);


        if (hashedPassword == storedHashedPassword) {
            do {
                ui.pwEx();
                cout << "새로운 비밀번호를 입력하세요 : ";

                pw = "";
                while (true) {
                    ch = _getch();

                    if (ch == 13)
                        break;
                    else if (ch == 8) {
                        if (!pw.empty()) {
                            pw.pop_back();
                            cout << "\b \b";
                        }
                    }
                    else {
                        pw += ch;
                        cout << '*';
                    }
                }

                string hashedPassword = function.sha256Hash(pw);

                cout << endl;

                if (hashedPassword == storedHashedPassword) {
                    isTrue = 1;
                    cout << "\n※ 기존 비밀번호와 동일합니다 ※\n";
                }
                else 

                if (validation.passwordValidation(pw)) {
                    do {
                        cout << "\n비밀번호를 한 번 더 입력하세요 : ";

                        string pw2 = "";
                        while (true) {
                            ch = _getch();

                            if (ch == 13)
                                break;
                            else if (ch == 8) {
                                if (!pw2.empty()) {
                                    pw2.pop_back();
                                    cout << "\b \b";
                                }
                            }
                            else {
                                pw2 += ch;
                                cout << '*';
                            }
                        }

                        function.exit(pw2);

                        if (pw == pw2) {
                            isMatching = 1;
                        }
                        else {
                            isMatching = 0;
                            cout << "\n비밀번호가 일치하지 않습니다. 다시 입력해 주세요." << endl;
                        }
                    } while (!isMatching);

                    if (isMatching) {
                        string newPw = function.sha256Hash(pw);

                        updatePassword(email, newPw);

                            cout << "\n비밀번호가 업데이트 되었습니다." << endl;
                    }
                }
                else {
                    isMatching = 0;
                }
            } while (!isMatching);
        }
        else {
            isMatching = 0;
            cout << "\n비밀번호가 일치하지 않습니다. 다시 입력해 주세요." << endl;
        }
    } while (!isMatching);
}



int Dao::deleteUser(const string& email)
{
    do {
    cout << endl;
    cout << "비밀번호를 입력하세요 : ";
    pw = "";
    while (true) {
        ch = _getch();

        if (ch == 13)
            break;
        else if (ch == 8) {
            if (!pw.empty()) {
                pw.pop_back();
                cout << "\b \b";
            }
        }
        else {
            pw += ch;
            cout << '*';
        }
    }
    cout << endl;

    string hashedPassword = function.sha256Hash(pw);
    string storedHashedPassword = getHashedPassword(email);
    
        if (hashedPassword == storedHashedPassword)
        {
            cout << "정말 삭제하시겠습니까? 삭제한 이후엔 되돌릴 수 없습니다. 1. 계속하기, 2. 그만두기 : ";
            char lastCheck;
            cin >> lastCheck;
            if (lastCheck == '1')
            {
                pstmt = con->prepareStatement("DELETE FROM user WHERE email = ?");
                pstmt->setString(1, email);
                result = pstmt->executeQuery();
                cout << "▶그동안 감사했습니다. 또 이용해주세요." << endl;
                exit(0);
            }
            else if (lastCheck == '2')
            {
                isMatching = 1;
            }
            else { cout << "▶잘못된 입력입니다." << endl; }

        }
        else {
            cout << "▶비밀번호가 다릅니다." << endl;
            isMatching = 0;
        }
    } while (!isMatching);
}

void Dao::join() {

    do {
        void emailEx();
        cout << "이메일을 입력하세요 : ";
        cin >> email;

        function.exit(email);

        dto.setEmail(email);

        if (isEmailExists(email)) {
            cout << "이미 가입된 이메일입니다.\n\n";
            isTrue = 0;
        }
        else {
            validationEmail = email;
            isTrue = validation.emailValidation(dto.getEmail());
        }
    } while (!isTrue);

    do {
        ui.pwEx();
        cout << "비밀번호를 입력하세요 : ";

        pw = "";
        while (true) {
            ch = _getch();

            if (ch == 13)
                break;
            else if (ch == 8) {
                if (!pw.empty()) {
                    pw.pop_back();
                    cout << "\b \b";
                }
            }
            else {
                pw += ch;
                cout << '*';
            }
        }

        function.exit(pw);

        cout << endl;
        if (validation.passwordValidation(pw)) {
            isTrue = 0;
        }
        else {
            isTrue = 1;
        }
    } while (isTrue);

    do {
        isTrue = 1;

        cout << "비밀번호를 한 번 더 입력하세요 : ";

        pw2 = "";
        while (true) {
            ch = _getch();

            if (ch == 13)
                break;
            else if (ch == 8) {
                if (!pw2.empty()) {
                    pw2.pop_back();
                    cout << "\b \b";
                }
            }
            else {
                pw2 += ch;
                cout << '*';
            }
        }

        function.exit(pw2);

        if (pw == pw2) {
            isTrue = 0;
            cout << "\n비밀번호 확인이 완료되었습니다." << endl;
            dto.setPw(function.sha256Hash(pw));
        }
        else {
            isTrue = 1;
            cout << "\n비밀번호가 일치하지 않습니다. 다시 입력해 주세요.\n\n";
        }
    } while (isTrue);

    do {
        ui.phoneEx();
        cout << "전화번호를 입력하세요 : ";
        cin >> phoneNum;

        function.exit(phoneNum);

        dto.setPhoneNum(phoneNum);

        if (isPhoneNumberExists(phoneNum)) {
            cout << "이미 가입된 전화번호입니다." << endl;
            isTrue = 1;
        }
        else {
            isTrue = validation.phoneNumValidation(dto.getPhoneNum());
        }
    } while (!isTrue);

    do {
        ui.birthdayEx();
        cout << "생년월일을 입력하세요 : ";
        cin >> birthday;

        function.exit(birthday);

        dto.setBirthday(birthday);
        isTrue = validation.birthdayValidation(dto.getBirthday());
    } while (!isTrue);

    do {
        cout << endl;
        cout << "인증번호를 받으시려면 y를 입력하세요 : ";
        cin >> answer;

        function.exit(answer);

        if (answer == "Y" || answer == "y") {
            sendrandomNum = function.randomNum();
            sendEmail(sendrandomNum, validationEmail);
            isTrue = 0;
        }
        else {
            isTrue = 1;
            cout << "잘못된 형식입니다 다시입력해주세요\n";
        }
    } while (isTrue);

    do {
        cout << endl;
        cout << "인증번호를 입력하세요 : ";
        cin >> validationNum;

        function.exit(validationNum);

        if (validationNum == sendrandomNum) {
            insert(dto);
            cout << "▶회원가입이 완료되었습니다.\n";
            Sleep(500);
            isTrue = 0;
        }
        else {
            cout << "인증번호가 일치하지 않습니다" << endl;
            isTrue = 1;
        }
    } while (isTrue);
}

string Dao::login() {
    
    do {
        cout << "이메일을 입력하세요: ";
        cin >> email;

        function.exit(email);

        if (isEmailExists(email)) {
            emailVerifie = 0;
        }
        else {
            emailVerifie = 1;
        }

        cout << "비밀번호를 입력하세요: ";
        pw = "";
        while (true) {
            ch = _getch();

            if (ch == 13)
                break;
            else if (ch == 8) {
                if (!pw.empty()) {
                    pw.pop_back();
                    cout << "\b \b";
                }
            }
            else {
                pw += ch;
                cout << '*';
            }
        }

        function.exit(pw);

        hashedPassword = function.sha256Hash(pw);

        storedHashedPassword = getHashedPassword(email);

        if (emailVerifie == 0 && hashedPassword == storedHashedPassword && checkLoginStatus(email) == 0) {
            cout << "\n로그인 성공!" << endl;
            pwVerifie = 1;
            loginCheckNum = 1;
            emailVerifie = 1;
            loginCheckAfter(email);
        }
        else if (checkLoginStatus(email) == 1 && emailVerifie == 0) {
            cout << "\n이미 로그인 중입니다." << endl;
            loginCheckNum = 1;

        }else if(emailVerifie != 0 || pwVerifie != 0){
            cout << "\n이메일 또는 비밀번호가 일치하지 않습니다." << endl;
        }
        cout << endl;

    } while (emailVerifie == 0 || pwVerifie == 0 || loginCheckNum == 0);
    return email;
}

void Dao::findEmail() {
    do {
        do {
            ui.phoneEx();
            cout << "전화번호를 입력하세요: ";
            cin >> phoneNum;

            function.exit(phoneNum);

            if (validation.phoneNumValidation(phoneNum)) {
                isTrue = 0;
            }
            else {
                isTrue = 1;
            }
        } while (isTrue);

        do {
            ui.birthdayEx();
            cout << "생년월일을 입력하세요: ";
            cin >> birthday;

            function.exit(birthday);

            if (validation.birthdayValidation(birthday)) {
                cout << endl;
                isTrue = 0;
            }
            else {
                isTrue = 1;
            }
        } while (isTrue);

        foundEmail = findEmail(phoneNum, birthday);
        isTrue = 0;
        if (!foundEmail.empty()) {
            cout << "찾은 이메일 : " << foundEmail << endl;

            do {
                cout << endl;
                cout << "확인을 완료했으면 y 를 입력해주세요: ";
                cin >> startMenu;

                function.exit(startMenu);

                if (startMenu == "y" || startMenu == "Y") {
                    isTrue = 0;
                }
                else {
                    isTrue = 1;
                    cout << "잘못 입력했습니다." << endl;
                }
            } while (isTrue);
        }
        else {
            isTrue = 1;
            cout << "일치하는 사용자가 없습니다.\n";
        }
    } while (isTrue);
}

void Dao::findPw() {

    do {
        cout << "이메일을 입력하세요 : ";
        cin >> email;

        function.exit(email);

        if (isEmailExists(email)) {
            isTrue = validation.emailValidation(email);
            validationEmail = email;
        }
        else {
            isTrue = 0;
            cout << "일치하는 사용자가 없습니다.\n";
        }
        cout << endl;
    } while (!isTrue);

    do {
        cout << "인증번호를 받으시려면 y를 입력하세요 : ";
        cin >> answer;

        function.exit(answer);

        if (answer == "Y" || answer == "y") {
            sendrandomNum = function.randomNum();
            sendEmail(sendrandomNum, validationEmail);
            isTrue = 0;
        }
        else {
            isTrue = 1;
            cout << "잘못된 형식입니다 다시 입력해 주세요\n";
        }
        cout << endl;
    } while (isTrue);

    do {
        cout << "인증번호를 입력하세요 : ";
        cin >> validationNum;

        function.exit(validationNum);

        if (validationNum == sendrandomNum) {
            isTrue = 0;
        }
        else {
            isTrue = 1;
            cout << "인증번호가 일치하지 않습니다\n\n";
        }
    } while (isTrue);

    do {
        ui.pwEx();
        cout << "새로운 비밀번호를 입력하세요 : ";

        char ch;
        pw = "";
        while (true) {
            ch = _getch();

            if (ch == 13)
                break;
            else if (ch == 8) {
                if (!pw.empty()) {
                    pw.pop_back();
                    cout << "\b \b";
                }
            }
            else {
                pw += ch;
                cout << '*';
            }
        }
        cout << endl;
        function.exit(pw);

        string hashedPassword = function.sha256Hash(pw);

        string storedHashedPassword = getHashedPassword(email);

        if (hashedPassword == storedHashedPassword) {
            isTrue = 1;
            cout << "\n※ 기존 비밀번호와 동일합니다 ※\n";
        }
        else {
            if (validation.passwordValidation(pw)) {
                bool isMatching = 0;

                do {
                    cout << "\n비밀번호를 한 번 더 입력하세요 : ";

                    pw2 = "";
                    while (true) {
                        ch = _getch();

                        if (ch == 13)
                            break;
                        else if (ch == 8) {
                            if (!pw2.empty()) {
                                pw2.pop_back();
                                cout << "\b \b";
                            }
                        }
                        else {
                            pw2 += ch;
                            cout << '*';
                        }
                    }

                    function.exit(pw2);

                    if (pw == pw2) {
                        isMatching = 1;
                    }
                    else {
                        isMatching = 0;
                        cout << "\n비밀번호가 일치하지 않습니다. 다시 입력해 주세요." << endl;
                    }
                } while (!isMatching);

                newPw = function.sha256Hash(pw);
                updatePassword(email, newPw);
                isTrue = 0;
            }
            else {
                isTrue = 1;
            }
        }
    } while (isTrue);

}

void textColor(int foreground, int background)
{
    int color = foreground + background * 16;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int Dao::chat_recv() {
    char buf[MAX_SIZE] = { };
    string msg;

    while (1) {
        ZeroMemory(&buf, MAX_SIZE);
        if (recv(client_sock_, buf, MAX_SIZE, 0) > 0) {
            textColor(7, 0);
            msg = buf;
            //닉네임 : 메시지
            std::stringstream ss(msg);  // 문자열을 스트림화
            string user;
            ss >> user;
            if (user != my_nick_) cout << buf << endl;
        }
        else {
            cout << "Server Off" << endl;
            return -1;
        }
    }
}

void Dao::search_content_Message()
{
    string content;
    cout << ">>내용에 따른 메시지 검색 : ";
    cin >> content;
    pstmt = con->prepareStatement("SELECT nick, time, recv FROM chatting WHERE recv LIKE ?");
    pstmt->setString(1, "%" + content + "%");
    result = pstmt->executeQuery();

    if (!result->next()) {
        cout << "검색 결과가 없습니다." << endl;
    }
    else {
        while (true) {
            string chatname = result->getString(1);
            string time = result->getString(2);
            string recv = result->getString(3);
            cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
            cout << "▷보낸사람 : " << chatname << endl;
            cout << "▷보낸시간 : " << time << endl;
            cout << "▷" << recv << endl;
            if (!result->next()) break;
        }
    }
}
void Dao::search_day_Message()
{
    string startDay, endDay;
    cout << "시작월일 4자리를 입력해주세요.(ex.0201) : ";
    cin >> startDay;// 0303
    cout << "종료월일 4자리를 입력해주세요.(ex.0405) : ";
    cin >> endDay; //0505

    string startMonthDay = "2023" + startDay;
    string endMonthDay = "2023" + endDay;

    pstmt = con->prepareStatement("SELECT nick, time, recv FROM chatting WHERE time BETWEEN ? AND ?");
    pstmt->setString(1, startMonthDay);
    pstmt->setString(2, endMonthDay);
    result = pstmt->executeQuery();

    if (!result->next()) {
        cout << "검색 결과가 없습니다." << endl;
    }
    else {
        while (true) {
            string chatname = result->getString(1);
            string time = result->getString(2);
            string recv = result->getString(3);
            cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
            cout << "▷보낸사람 : " << chatname << endl;
            cout << "▷보낸시간 : " << time << endl;
            cout << "▷" << recv << endl;
            if (!result->next()) break;
        }
    }
}

void Dao::beforeChat()  
{
    pstmt = con->prepareStatement("SELECT nick, time, recv FROM chatting ORDER BY time DESC LIMIT 5");
    result = pstmt->executeQuery();

    string nick[5];
    string time[5];
    string recv[5];
    string msg[5];
    int num = 0;
    
    while (result->next())
    {
        nick[num] = result->getString(1);
        time[num] = result->getString(2);
        recv[num] = result->getString(3);
        num++;
    }
            for (int i = 4; i >= 0; i--) {
                msg[i] += "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n";
                msg[i] += "▷보낸사람 : " + nick[i] + "\n";
                msg[i] += "▷내용 : " + recv[i] + "\n";
                msg[i] += "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n";
                cout << msg[i] << endl;
            }
}

string Dao::getNick()
{
    string getNick = "";
    pstmt = con->prepareStatement("SELECT nick FROM user WHERE email=?");
    pstmt->setString(1, email);
    result = pstmt->executeQuery();
    if (result->next())
    {
        getNick = result->getString(1);
        if (getNick.empty()) {

            getNick = email;
        }
    }
    return getNick;
}

void Dao::chattingStart(const string& email) {
   backButton = false;
   code = 0;
    WSADATA wsa;
    code = WSAStartup(MAKEWORD(2, 2), &wsa); // 변수에 초기화 진행
    if (code == 0)
    {
        cout << "< 채팅방에 입장합니다. >" << endl;
        beforeChat();
        my_nick_ = getNick();
         closesocket(client_sock_);
        client_sock_ = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); 

        SOCKADDR_IN client_addr = {};
        client_addr.sin_family = AF_INET;
        client_addr.sin_port = htons(7777);
        InetPton(AF_INET, TEXT("127.0.0.1"), &client_addr.sin_addr);

        while (1)
        {
            if (!connect(client_sock_, (SOCKADDR*)&client_addr, sizeof(client_addr))) { 
                cout << "※지인을 사칭하여 금전을 요구할 수 있으니, 도용이 의심 된다면 대화를 중단해주시기 바랍니다." << endl;
                send(client_sock_, my_nick_.c_str(), my_nick_.length(), 0);
                break;
            }
            cout << "Connecting..." << endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));  // 시도 간격
        }
        std::thread th2(&Dao::chat_recv,this);
        while (1)
        {
            string text;
            std::getline(cin, text);
            string filtered_text = Dao::filter(text);
            const char* buffer = filtered_text.c_str(); // string형을 char* 타입으로 변환
            send(client_sock_, buffer, strlen(buffer), 0);

            if (text == "/종료")
            {
                closesocket(client_sock_);
                backButton = true;
                break;
            }
        }
        th2.join();
    }
    WSACleanup();
};


string Dao::filter(string beforeword) {

    std::vector<std::pair<string, string>> replacements = {
        {"꺼져", "**"},
        {"바보", "&&"}
        // 추가 대체 문자열을 여기에 추가
    };

    // 대체 작업 반복
    for (const auto& replacement : replacements) {
        const string& findStr = replacement.first;
        const string& replaceStr = replacement.second;
        size_t found = beforeword.find(findStr);
        while (found != string::npos) {
            beforeword.replace(found, findStr.length(), replaceStr);
            found = beforeword.find(findStr, found + replaceStr.length());
        }   //이전 찾은거 부터 다음 단어부터시작

    }
    string afterword = beforeword;
    return afterword;
}

int Dao::loginCheckBefore(const string& email) {
    try {
        sqlQuery = "UPDATE user SET login = 0 WHERE email = ? AND login <> 0";
        pstmt = con->prepareStatement(sqlQuery);
        pstmt->setString(1, email);
        pstmt->executeUpdate();
    }
    catch (SQLException& e) {
        cout << "로그인 상태를 업데이트하는 데 실패했습니다. 오류 메시지: " << e.what() << endl;
    }
    return 0;

}

void Dao::loginCheckAfter(const string& email) {
    try {
        sqlQuery = "UPDATE user SET login = 1 WHERE email = ? AND login <> 1";
        pstmt = con->prepareStatement(sqlQuery);
        pstmt->setString(1, email);
        pstmt->executeUpdate();
    }
    catch (SQLException& e) {
        cout << "로그인 상태를 업데이트하는 데 실패했습니다. 오류 메시지: " << e.what() << endl;
    }
}

int Dao::checkLoginStatus(const string& requestedEmail) {
    try {
        sqlQuery = "SELECT login FROM user WHERE email = ?";
        pstmt = con->prepareStatement(sqlQuery);
        pstmt->setString(1, requestedEmail);
        result = pstmt->executeQuery();

        if (result->next()) {
            return result->getInt(1);
        }
    }
    catch (SQLException& e) {
        cout << "로그인 상태를 확인하는 데 실패했습니다. 오류 메시지: " << e.what() << endl;
    }
}

Dao::~Dao() {
    if (con) {
        delete con;
        con = nullptr;
    }
}
