/*
 * 파일명: 03_exception_safety.cpp
 * 
 * 주제: 예외 안전성 (Exception Safety)
 * 정의: 예외가 발생해도 프로그램이 일관된 상태를 유지하도록 하는 프로그래밍 기법
 * 
 * 핵심 개념:
 * - 예외 안전성: 예외 발생 시에도 프로그램의 일관성과 자원 안전성을 보장
 * - RAII: Resource Acquisition Is Initialization, 자원 관리 자동화
 * - 스마트 포인터: 자동 메모리 관리로 예외 안전성 확보
 * - 예외 중립성: 예외를 처리하지 않고 안전하게 전파
 * 
 * 예외 안전성 수준:
 * - 기본 보장 (Basic Guarantee): 자원 누수 없음, 객체가 유효한 상태 유지
 * - 강한 보장 (Strong Guarantee): 연산이 성공하거나 아무 변화 없음 (원자성)
 * - 예외 없음 (No-throw Guarantee): 절대 예외를 던지지 않음
 * - 예외 안전하지 않음: 자원 누수나 상태 불일치 발생 가능
 * 
 * RAII 패턴:
 * - 생성자에서 자원 획득, 소멸자에서 자원 해제
 * - 스택 기반 자동 관리로 예외 발생 시에도 안전
 * - 스마트 포인터가 RAII의 대표적 예시
 * - 예외 발생 시 스택 되감기로 자동 정리
 * 
 * 사용 시기:
 * - 동적 메모리나 파일 핸들 등 자원을 관리할 때
 * - 예외가 발생할 수 있는 복잡한 연산에서
 * - 라이브러리나 API를 설계할 때
 * - 멀티스레드 환경에서 안전성이 중요할 때
 * 
 * 설계 원칙:
 * - 자원 관리는 RAII로 자동화
 * - 강한 예외 안전성이 필요한 곳에서는 백업/복원 패턴 사용
 * - 가능한 한 스마트 포인터나 컨테이너 사용
 * - 예외를 던지는 코드는 최소화
 * 
 * 장점:
 * - 메모리 누수 방지
 * - 프로그램 안정성 향상
 * - 자원 관리 실수 예방
 * - 코드의 신뢰성 증대
 * 
 * 관련 개념:
 * - 스마트 포인터: unique_ptr, shared_ptr, weak_ptr
 * - 컨테이너: 자동 메모리 관리되는 STL 컨테이너들
 * - 락 가드: 뮤텍스 관리를 위한 RAII 래퍼
 * - 예외 명세: noexcept 키워드로 예외 없음 보장
 * 
 * 주의사항:
 * - 소멸자에서는 예외를 던지면 안됨
 * - 강한 예외 안전성은 성능 비용이 있을 수 있음
 * - 모든 곳에서 최고 수준의 안전성이 필요한 것은 아님
 * - 예외 안전성과 성능 사이의 균형 고려
 */

#include <iostream>
#include <memory>
#include <vector>
using namespace std;

class Resource {
private:
    string name;

public:
    Resource(const string& n) : name(n) {
        cout << "자원 생성: " << name << endl;
    }

    ~Resource() {
        cout << "자원 해제: " << name << endl;
    }

    void process() {
        cout << "자원 처리: " << name << endl;
    }
};

// 예외 안전하지 않은 클래스
class UnsafeManager {
private:
    Resource* resource1;
    Resource* resource2;

public:
    UnsafeManager() : resource1(nullptr), resource2(nullptr) {}

    void initialize() {
        resource1 = new Resource("자원1");
        // 여기서 예외가 발생하면 resource1이 누수됨
        resource2 = new Resource("자원2");

        // 강제로 예외 발생
        throw runtime_error("초기화 중 오류 발생!");
    }

    ~UnsafeManager() {
        delete resource1;
        delete resource2;
    }
};

// 예외 안전한 클래스 (RAII 사용)
class SafeManager {
private:
    unique_ptr<Resource> resource1;
    unique_ptr<Resource> resource2;

public:
    void initialize() {
        resource1 = make_unique<Resource>("안전자원1");
        resource2 = make_unique<Resource>("안전자원2");

        // 예외가 발생해도 스마트 포인터가 자동으로 정리
        throw runtime_error("초기화 중 오류 발생!");
    }

    void process() {
        if (resource1 && resource2) {
            resource1->process();
            resource2->process();
        }
    }
};

// 강한 예외 안전성을 보장하는 함수
void strongExceptionSafety() {
    vector<int> data = {1, 2, 3, 4, 5};
    vector<int> backup = data;  // 백업 생성

    try {
        // 위험한 작업 시뮬레이션
        data.push_back(6);
        data.push_back(7);

        // 예외 발생 시뮬레이션
        if (data.size() > 6) {
            throw runtime_error("데이터 처리 오류!");
        }

        cout << "작업 성공!" << endl;
    }
    catch (...) {
        data = backup;  // 원래 상태로 복원 (강한 예외 안전성)
        cout << "오류 발생, 원래 상태로 복원" << endl;
        throw;  // 예외 재발생
    }
}

int main() {
    cout << "=== 예외 안전하지 않은 코드 ===" << endl;
    try {
        UnsafeManager unsafe;
        unsafe.initialize();
    }
    catch (const exception& e) {
        cout << "오류: " << e.what() << endl;
    }

    cout << "\n=== 예외 안전한 코드 ===" << endl;
    try {
        SafeManager safe;
        safe.initialize();
    }
    catch (const exception& e) {
        cout << "오류: " << e.what() << endl;
        cout << "하지만 자원은 안전하게 해제됨" << endl;
    }

    cout << "\n=== 강한 예외 안전성 ===" << endl;
    try {
        strongExceptionSafety();
    }
    catch (const exception& e) {
        cout << "최종 오류: " << e.what() << endl;
    }

    return 0;
}