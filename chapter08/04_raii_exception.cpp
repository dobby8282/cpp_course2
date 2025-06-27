/*
 * 파일명: 04_raii_exception.cpp
 * 
 * 주제: RAII와 예외 (RAII & Exception)
 * 정의: RAII 패턴으로 예외 발생 시에도 자원이 안전하게 해제되도록 보장
 * 
 * 핵심 개념:
 * - RAII: Resource Acquisition Is Initialization, 자원 획득과 해제를 객체 생명주기와 연결
 * - 스택 되감기: 예외 발생 시 스택 객체들이 자동으로 소멸되는 C++ 메커니즘
 * - 자동 자원 관리: 소멸자를 통한 자원 해제로 수동 관리 실수 방지
 * - 예외 안전성: 예외 상황에서도 자원 누수나 데드락 방지
 * 
 * RAII 원칙:
 * - 생성자에서 자원 획득 (파일 열기, 메모리 할당, 뮤텍스 잠금 등)
 * - 소멸자에서 자원 해제 (파일 닫기, 메모리 해제, 뮤텍스 해제 등)
 * - 객체 수명과 자원 수명을 일치시킴
 * - 예외 발생 시에도 소멸자가 자동 호출됨
 * 
 * 스택 되감기 과정:
 * - 예외 발생 시 catch 블록을 찾기 위해 스택을 거슬러 올라감
 * - 경로상의 모든 지역 객체들의 소멸자가 자동 호출됨
 * - 이를 통해 RAII 객체들이 자동으로 정리됨
 * - 예외 처리 후 프로그램은 안전한 상태로 복구됨
 * 
 * 사용 시기:
 * - 파일, 네트워크 연결, 데이터베이스 연결 등 시스템 자원 관리
 * - 뮤텍스, 세마포어 등 동기화 객체 관리
 * - 동적 메모리 할당/해제가 필요한 경우
 * - 예외가 발생할 수 있는 모든 자원 관리 상황
 * 
 * 장점:
 * - 자원 누수 완전 방지 (메모리, 파일 핸들, 뮤텍스 등)
 * - 예외 안전성 자동 보장
 * - 코드 간소화 (수동 정리 코드 불필요)
 * - 실수 방지 (깜빡하고 자원 해제 안 하는 실수 방지)
 * 
 * RAII 구현 클래스들:
 * - 스마트 포인터: unique_ptr, shared_ptr, weak_ptr
 * - 락 가드: lock_guard, unique_lock, shared_lock
 * - 파일 스트림: ifstream, ofstream (자동 파일 닫기)
 * - 컨테이너: vector, string 등 (자동 메모리 관리)
 * 
 * 관련 개념:
 * - 소멸자 호출 순서: 생성의 역순으로 소멸
 * - 예외 중립성: RAII 객체는 예외를 변경하지 않고 전파
 * - 강한 예외 안전성: RAII로 all-or-nothing 보장
 * - Modern C++: 스마트 포인터 사용으로 수동 메모리 관리 최소화
 * 
 * 주의사항:
 * - 소멸자에서는 예외를 던지면 안됨 (프로그램 종료될 수 있음)
 * - RAII 객체는 복사 가능하거나 이동 가능해야 함
 * - 자원 획득 실패 시 생성자에서 예외 던져야 함
 * - 순환 참조 주의 (shared_ptr 사용 시)
 */

#include <iostream>
#include <fstream>
#include <memory>
#include <mutex>
using namespace std;

// 파일 자원 관리 RAII 클래스
class FileHandler {
private:
    ofstream file;
    string filename;

public:
    FileHandler(const string& fname) : filename(fname) {
        file.open(filename);
        if (!file.is_open()) {
            throw runtime_error("파일을 열 수 없습니다: " + filename);
        }
        cout << "파일 열기 성공: " << filename << endl;
    }

    ~FileHandler() {
        if (file.is_open()) {
            file.close();
            cout << "파일 자동 닫기: " << filename << endl;
        }
    }

    void write(const string& content) {
        if (!file.is_open()) {
            throw runtime_error("파일이 열려있지 않습니다.");
        }
        file << content << endl;
    }

    void forceError() {
        throw runtime_error("강제 오류 발생!");
    }
};

// 뮤텍스 RAII 클래스
class LockGuard {
private:
    mutex& mtx;

public:
    LockGuard(mutex& m) : mtx(m) {
        mtx.lock();
        cout << "뮤텍스 잠금" << endl;
    }

    ~LockGuard() {
        mtx.unlock();
        cout << "뮤텍스 해제" << endl;
    }
};

mutex globalMutex;

void processData() {
    LockGuard lock(globalMutex);  // RAII로 뮤텍스 관리

    cout << "중요한 작업 수행 중..." << endl;

    // 예외 발생 시뮬레이션
    throw runtime_error("작업 중 오류 발생!");

    cout << "작업 완료" << endl;  // 실행되지 않음
}

int main() {
    cout << "=== RAII와 예외 처리 ===" << endl;

    cout << "\n1. 파일 처리 중 예외 발생" << endl;
    try {
        FileHandler file("test.txt");
        file.write("첫 번째 줄");
        file.write("두 번째 줄");
        file.forceError();  // 예외 발생
        file.write("세 번째 줄");  // 실행되지 않음
    }
    catch (const exception& e) {
        cout << "파일 처리 오류: " << e.what() << endl;
    }
    // FileHandler 소멸자가 자동으로 파일을 닫음

    cout << "\n2. 뮤텍스 처리 중 예외 발생" << endl;
    try {
        processData();
    }
    catch (const exception& e) {
        cout << "데이터 처리 오류: " << e.what() << endl;
    }
    // LockGuard 소멸자가 자동으로 뮤텍스를 해제

    cout << "\n3. 스마트 포인터와 예외" << endl;
    try {
        auto ptr1 = make_unique<int>(42);
        auto ptr2 = make_unique<string>("Hello");

        cout << "*ptr1 = " << *ptr1 << endl;
        cout << "*ptr2 = " << *ptr2 << endl;

        throw runtime_error("스마트 포인터 테스트 오류!");
    }
    catch (const exception& e) {
        cout << "스마트 포인터 오류: " << e.what() << endl;
    }
    // 스마트 포인터들이 자동으로 메모리 해제

    cout << "\n모든 자원이 안전하게 해제되었습니다." << endl;
    return 0;
}