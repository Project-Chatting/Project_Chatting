#include "emailSend.h"
#include <curl/curl.h>
#include <string>
#include <ctime>

string TO;
string FROM;
string randomNum;
string apiKey;
std::ifstream keyFile("api_key.txt");

// ���� ��¥ �� �ð� ���ڿ��� �����ϴ� �Լ�
string getCurrentDateTime() {
    time_t t = time(nullptr);
    struct tm now;

#ifdef _WIN32
    gmtime_s(&now, &t); // gmtime_s �Լ� ��� (Windows)
#else
    gmtime_r(&t, &now); // gmtime_r �Լ� ��� (Linux �� �ٸ� �÷���)
#endif

    char buffer[80];
    strftime(buffer, sizeof(buffer), "Date: %a, %d %b %Y %H:%M:%S +0000\r\n", &now);
    return buffer;
}

// CURL ���̺귯������ ȣ��Ǵ� �ݹ� �Լ���, �̸��� ������ �����մϴ�.
static size_t payload_source(void* ptr, size_t size, size_t nmemb, void* userp) {
    string content = getCurrentDateTime() +
        "To: " + TO + "\r\n" \
        "From: " + FROM + " (CodingOn)\r\n" \
        "Subject: ***������ȣ ����***\r\n" \
        "\r\n" \
        "������ȣ : " + randomNum + "\r\n" \
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

// �� �Լ��� �ƹ��͵� �������� �ʵ��� �����˴ϴ�.
size_t discardOutput(void* ptr, size_t size, size_t nmemb, void* userp) {
    return size * nmemb;
}

// �̸��� ���� �Լ�
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

        /* ����ڸ� �� ��ȣ ���� */
        curl_easy_setopt(curl, CURLOPT_USERNAME, "gohshow@gmail.com");
        curl_easy_setopt(curl, CURLOPT_PASSWORD, apiKey.c_str());

        /* �̸��� ������ URL ���� (Gmail SMTP�� ����մϴ�) */
        curl_easy_setopt(curl, CURLOPT_URL, "smtp://smtp.gmail.com:587");

        /* ������ ������ ���� TLS ��� ���� */
        curl_easy_setopt(curl, CURLOPT_USE_SSL, static_cast<long>(CURLUSESSL_ALL));

        /* ���� �̸��� �ּ� ���� */
        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, FROM.c_str());

        /* ������ �̸��� �ּ� �߰� */
        recipients = curl_slist_append(recipients, TO.c_str());
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

        /* ���̷ε� (�̸��� ����)�� �ݹ� �Լ� ���� */
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
        curl_easy_setopt(curl, CURLOPT_READDATA, &content_offset);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, static_cast<long>(1));

        // ���� Ŀ�ǵ� ���ο� ��µǴ� ������ �����ϴ� �ݹ� �Լ��� �����մϴ�.
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, discardOutput);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, NULL);

        /* �̸��� ������ */
        res = curl_easy_perform(curl);

        /* ���� Ȯ�� */
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() ����: %s\n", curl_easy_strerror(res));
        }

        /* ������ ��� ���� */
        curl_slist_free_all(recipients);

        /* ���� */
        curl_easy_cleanup(curl);
    }

    return static_cast<int>(res);
}
