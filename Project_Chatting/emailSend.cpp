#include "emailSend.h"
#include <curl/curl.h>
#include <string>
#include <ctime>

string TO;
string FROM;
string randomNum;
string apiKey;
std::ifstream keyFile("api_key.txt");

// 현재 날짜 및 시간 문자열을 생성하는 함수
string getCurrentDateTime() {
    time_t t = time(nullptr);
    struct tm now;

#ifdef _WIN32
    gmtime_s(&now, &t); // gmtime_s 함수 사용 (Windows)
#else
    gmtime_r(&t, &now); // gmtime_r 함수 사용 (Linux 및 다른 플랫폼)
#endif

    char buffer[80];
    strftime(buffer, sizeof(buffer), "Date: %a, %d %b %Y %H:%M:%S +0000\r\n", &now);
    return buffer;
}

// CURL 라이브러리에서 호출되는 콜백 함수로, 이메일 내용을 생성합니다.
static size_t payload_source(void* ptr, size_t size, size_t nmemb, void* userp) {
    string content = getCurrentDateTime() +
        "To: " + TO + "\r\n" \
        "From: " + FROM + " (CodingOn)\r\n" \
        "Subject: ***인증번호 전송***\r\n" \
        "\r\n" \
        "인증번호 : " + randomNum + "\r\n" \
        "\r\n";

    size_t len = content.length();
    size_t remaining = len - *reinterpret_cast<size_t*>(userp);

    if (remaining == 0) {
        return 0;
    }

    if (size * nmemb >= remaining) {
        memcpy(ptr, content.c_str() + *reinterpret_cast<size_t*>(userp), remaining);
        *reinterpret_cast<size_t*>(userp) = len;
        return remaining;
    }

    return 0;
}

// 이 함수는 아무것도 수행하지 않도록 설정됩니다.
size_t discardOutput(void* ptr, size_t size, size_t nmemb, void* userp) {
    return size * nmemb;
}

// 이메일 전송 함수
int sendEmail(const string& random, const string& email) {
    FROM = "<gohshow@gmail.com>";
    TO = "<" + email + ">";
    randomNum = random;

    CURL* curl;
    CURLcode res = CURLE_OK;
    struct curl_slist* recipients = NULL;
    size_t content_offset = 0;

    curl = curl_easy_init();

    if (curl) {

        if (keyFile.is_open()) {
            getline(keyFile, apiKey);
            keyFile.close();
        }

        /* 사용자명 및 암호 설정 */
        curl_easy_setopt(curl, CURLOPT_USERNAME, "gohshow@gmail.com");
        curl_easy_setopt(curl, CURLOPT_PASSWORD, apiKey.c_str());

        /* 이메일 서버의 URL 설정 (Gmail SMTP를 사용합니다) */
        curl_easy_setopt(curl, CURLOPT_URL, "smtp://smtp.gmail.com:587");

        /* 안전한 연결을 위해 TLS 사용 설정 */
        curl_easy_setopt(curl, CURLOPT_USE_SSL, static_cast<long>(CURLUSESSL_ALL));

        /* 보낸 이메일 주소 설정 */
        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, FROM.c_str());

        /* 수신자 이메일 주소 추가 */
        recipients = curl_slist_append(recipients, TO.c_str());
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

        /* 페이로드 (이메일 내용)의 콜백 함수 설정 */
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
        curl_easy_setopt(curl, CURLOPT_READDATA, &content_offset);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, static_cast<long>(1));

        // 이제 커맨드 라인에 출력되는 내용을 무시하는 콜백 함수를 설정합니다.
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, discardOutput);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, NULL);

        /* 이메일 보내기 */
        res = curl_easy_perform(curl);

        /* 오류 확인 */
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() 실패: %s\n", curl_easy_strerror(res));
        }

        /* 수신자 목록 해제 */
        curl_slist_free_all(recipients);

        /* 정리 */
        curl_easy_cleanup(curl);
    }

    return static_cast<int>(res);
}
