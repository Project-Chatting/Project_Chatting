#include "Function.h"

void Function::exit(const string& str) {
    if (str == "exit") {
        exit(0);
    }
}

string Function::sha256Hash(const string& pw) {
    using namespace CryptoPP;
    string password = pw;
    string hashedPassword;
    SHA256 sha256;
    StringSource(password, true, new HashFilter(sha256, new HexEncoder(new StringSink(hashedPassword))));
    return hashedPassword;
}

string Function::randomNum() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 9);

    std::ostringstream randomStr;
    for (int i = 0; i < 6; ++i) {
        randomStr << dis(gen);
    }

    return randomStr.str();
}
