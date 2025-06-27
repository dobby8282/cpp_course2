/*
 * 파일명: 02_custom_exception.cpp
 * 
 * 주제: 사용자 정의 예외 (Custom Exception)
 * 정의: 특정 상황에 맞는 예외 클래스를 직접 정의하여 사용
 * 
 * 핵심 개념:
 * - 사용자 정의 예외: std::exception을 상속받아 만든 커스텀 예외 클래스
 * - 예외 계층 구조: 상속을 통해 예외의 종류를 체계적으로 분류
 * - what() 함수: 예외에 대한 설명 문자열을 반환하는 가상 함수
 * - noexcept: 함수가 예외를 던지지 않음을 명시하는 키워드
 * 
 * 예외 클래스 설계:
 * - 기본 예외 클래스: 공통된 속성과 동작을 정의
 * - 구체적 예외 클래스: 특정 상황에 맞는 세부 예외들
 * - 상속 관계: 일반적인 예외에서 구체적인 예외로 특화
 * - 정보 전달: 생성자를 통해 상세한 오류 정보 제공
 * 
 * 사용 시기:
 * - 표준 예외로는 표현하기 어려운 도메인 특화 오류
 * - 비즈니스 로직에서 발생하는 특별한 예외 상황
 * - 오류에 대한 추가 정보나 맥락이 필요할 때
 * - 예외 처리를 세분화하여 다르게 대응해야 할 때
 * 
 * 장점:
 * - 도메인에 특화된 의미 있는 예외 이름
 * - 예외 상황에 대한 구체적이고 상세한 정보 제공
 * - 예외 처리 로직을 세분화하여 적절한 대응 가능
 * - 코드의 가독성과 유지보수성 향상
 * 
 * 설계 원칙:
 * - std::exception 상속: 표준 예외 처리 메커니즘과 호환
 * - what() 오버라이드: 사용자에게 의미 있는 메시지 제공
 * - 계층적 설계: 일반적인 예외에서 구체적인 예외로 분화
 * - 정보 포함: 예외 발생 시점의 상태 정보 포함
 * 
 * 관련 개념:
 * - 예외 안전성: 강한 보장, 기본 보장, 예외 없음 보장
 * - RAII: 예외 발생 시에도 자원이 안전하게 해제됨
 * - 예외 중립성: 예외를 변경하지 않고 그대로 전파
 * - 오류 코드 vs 예외: 각각의 장단점과 적용 상황
 * 
 * 주의사항:
 * - what() 함수에서는 예외를 던지면 안됨 (noexcept)
 * - 예외 객체는 복사 가능해야 함
 * - 과도한 예외 분류는 복잡성 증가
 * - 예외 생성 비용 고려 (문자열 처리 등)
 */

#include <iostream>
#include <exception>
#include <string>
using namespace std;

// 사용자 정의 예외 클래스
class BankException : public exception {
private:
    string message;

public:
    BankException(const string& msg) : message(msg) {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

class InsufficientFundsException : public BankException {
public:
    InsufficientFundsException(double requested, double available) 
        : BankException("잔액 부족: 요청금액 " + to_string(requested) + 
                       "원, 잔액 " + to_string(available) + "원") {}
};

class InvalidAmountException : public BankException {
public:
    InvalidAmountException() : BankException("유효하지 않은 금액입니다.") {}
};

class BankAccount {
private:
    double balance;

public:
    BankAccount(double initial) : balance(initial) {}

    void deposit(double amount) {
        if (amount <= 0) {
            throw InvalidAmountException();
        }
        balance += amount;
        cout << amount << "원 입금 완료. 잔액: " << balance << "원" << endl;
    }

    void withdraw(double amount) {
        if (amount <= 0) {
            throw InvalidAmountException();
        }
        if (amount > balance) {
            throw InsufficientFundsException(amount, balance);
        }
        balance -= amount;
        cout << amount << "원 출금 완료. 잔액: " << balance << "원" << endl;
    }

    double getBalance() const { return balance; }
};

int main() {
    cout << "=== 사용자 정의 예외 ===" << endl;

    BankAccount account(100000);

    try {
        account.deposit(50000);
        account.withdraw(30000);
        account.withdraw(-1000);  // 잘못된 금액
    }
    catch (const InvalidAmountException& e) {
        cout << "금액 오류: " << e.what() << endl;
    }
    catch (const InsufficientFundsException& e) {
        cout << "잔액 오류: " << e.what() << endl;
    }
    catch (const BankException& e) {
        cout << "은행 오류: " << e.what() << endl;
    }

    try {
        account.withdraw(200000);  // 잔액 부족
    }
    catch (const BankException& e) {
        cout << "거래 실패: " << e.what() << endl;
    }

    cout << "\n최종 잔액: " << account.getBalance() << "원" << endl;

    return 0;
}