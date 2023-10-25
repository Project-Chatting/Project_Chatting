#include "validation.h"

bool Validation::validateInput(const string& input, const regex& pattern, const string& errorMessage) {
	if (regex_match(input, pattern)) {
		return 1;
	}
	else {
		cout << errorMessage << endl;
		return 0;
	}
}

bool Validation::emailValidation(const string& email) {
	regex pattern(R"(\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Z|a-z]{2,7}\b)");
	return validateInput(email, pattern, "잘못된 이메일 형식입니다. 다시 입력해 주세요.\n");
}

bool Validation::passwordValidation(const string& password) {
	regex pattern("^(?=.*[A-Z])(?=.*[a-z])(?=.*[0-9])(?=.*[!@#\\$%^&\\*\\+=\\-~]).{8,15}$");
	return validateInput(password, pattern, "잘못된 비밀번호 형식입니다. 다시 입력해 주세요.");
}

bool Validation::phoneNumValidation(const string& phoneNum) {
	regex pattern(R"(^01([016789])?(\d{3,4})(\d{4})$)");
	return validateInput(phoneNum, pattern, "잘못된 전화번호 형식입니다. 다시 입력해 주세요.");
}

bool Validation::birthdayValidation(const string& birthday) {
	regex pattern("^(19|20)\\d{2}(0[1-9]|1[0-2])(0[1-9]|[12]\\d|3[01])$");
	return validateInput(birthday, pattern, "잘못된 생년월일 형식입니다. 다시 입력해 주세요.");
}
