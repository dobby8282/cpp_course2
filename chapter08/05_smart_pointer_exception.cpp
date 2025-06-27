/*
 * 파일명: 05_smart_pointer_exception.cpp
 * 
 * 주제: 스마트 포인터와 예외 (Smart Pointer & Exception)
 * 정의: unique_ptr, shared_ptr을 사용하여 예외 상황에서도 메모리 누수 방지
 * 
 * 핵심 개념:
 * - 스마트 포인터: 자동 메모리 관리를 제공하는 RAII 기반 포인터 래퍼
 * - 자동 소멸: 스코프를 벗어나거나 예외 발생 시 자동으로 메모리 해제
 * - 소유권 관리: unique_ptr(단독 소유), shared_ptr(공유 소유)
 * - 예외 안전성: 예외 발생 시에도 메모리 누수 완전 방지
 * 
 * 스마트 포인터 종류:
 * - unique_ptr: 단독 소유권, 복사 불가, 이동 가능
 * - shared_ptr: 공유 소유권, 참조 카운팅, 복사 가능
 * - weak_ptr: shared_ptr 순환 참조 해결용 (소유권 없음)
 * - make_unique/make_shared: 안전한 스마트 포인터 생성 함수
 * 
 * raw pointer의 문제점:
 * - 수동 메모리 관리로 인한 실수 위험
 * - 예외 발생 시 메모리 누수 가능
 * - 더블 프리나 댕글링 포인터 위험
 * - 소유권이 불분명하여 누가 해제할지 모호
 * 
 * 사용 시기:
 * - 동적 메모리 할당이 필요한 모든 상황
 * - 예외가 발생할 수 있는 복잡한 로직
 * - 객체의 수명이 스코프를 넘어서는 경우
 * - 팩토리 패턴이나 빌더 패턴 구현 시
 * 
 * 장점:
 * - 자동 메모리 관리로 누수 방지
 * - 예외 안전성 자동 보장
 * - 소유권 명확화 (unique vs shared)
 * - 현대적이고 안전한 C++ 스타일
 * 
 * 성능 특성:
 * - unique_ptr: raw pointer와 거의 동일한 성능
 * - shared_ptr: 참조 카운팅으로 약간의 오버헤드
 * - make_shared: 메모리 할당 최적화 (객체+제어블록 한번에)
 * - 컴파일러 최적화로 인라인화 가능
 * 
 * 관련 개념:
 * - RAII: Resource Acquisition Is Initialization
 * - 이동 의미론: std::move와 함께 효율적인 소유권 이전
 * - 팩토리 패턴: 객체 생성을 캡슐화하는 디자인 패턴
 * - 예외 중립성: 예외를 변경하지 않고 안전하게 전파
 * 
 * 주의사항:
 * - shared_ptr 순환 참조 주의 (weak_ptr로 해결)
 * - 이미 관리되는 객체를 raw pointer로 다시 관리하면 안됨
 * - 배열에는 unique_ptr<T[]> 또는 vector<T> 사용
 * - 커스텀 deleter 필요한 경우 별도 지정
 */

#include <iostream>
#include <memory>
#include <vector>
#include <stdexcept>
using namespace std;

class Resource {
public:
    int value;

    Resource(int v) : value(v) {
        cout << "Resource 생성: " << value << endl;
    }

    ~Resource() {
        cout << "Resource 소멸: " << value << endl;
    }

    void process() {
        if (value < 0) {
            throw invalid_argument("음수 값은 처리할 수 없습니다.");
        }
        cout << "Resource 처리: " << value << endl;
    }
};

// 위험한 방식 (raw pointer)
void dangerousFunction() {
    cout << "\n=== 위험한 방식 (Raw Pointer) ===" << endl;

    Resource* res1 = new Resource(10);
    Resource* res2 = new Resource(20);

    try {
        res1->process();
        res2->process();

        // 예외 발생 시뮬레이션
        throw runtime_error("처리 중 오류 발생!");

        // 아래 코드는 실행되지 않음 -> 메모리 누수!
        delete res1;
        delete res2;
    }
    catch (const exception& e) {
        cout << "오류: " << e.what() << endl;
        // 예외 처리에서 수동으로 정리해야 함
        delete res1;
        delete res2;
    }
}

// 안전한 방식 (unique_ptr)
void safeFunction() {
    cout << "\n=== 안전한 방식 (unique_ptr) ===" << endl;

    auto res1 = make_unique<Resource>(30);
    auto res2 = make_unique<Resource>(40);

    try {
        res1->process();
        res2->process();

        // 예외 발생 시뮬레이션
        throw runtime_error("처리 중 오류 발생!");
    }
    catch (const exception& e) {
        cout << "오류: " << e.what() << endl;
    }
    // unique_ptr이 자동으로 메모리 해제
}

// shared_ptr 사용
void sharedPtrExample() {
    cout << "\n=== shared_ptr 예제 ===" << endl;

    vector<shared_ptr<Resource>> resources;

    try {
        resources.push_back(make_shared<Resource>(50));
        resources.push_back(make_shared<Resource>(60));
        resources.push_back(make_shared<Resource>(-10));  // 문제가 될 값

        for (auto& res : resources) {
            res->process();  // -10에서 예외 발생
        }
    }
    catch (const exception& e) {
        cout << "처리 오류: " << e.what() << endl;
    }
    // shared_ptr들이 자동으로 메모리 해제
}

// 팩토리 함수와 예외 안전성
unique_ptr<Resource> createResource(int value) {
    if (value == 0) {
        throw invalid_argument("0은 유효하지 않은 값입니다.");
    }
    return make_unique<Resource>(value);
}

int main() {
    cout << "=== 스마트 포인터와 예외 안전성 ===" << endl;

    // 위험한 방식 시연
    try {
        dangerousFunction();
    }
    catch (...) {
        cout << "dangerousFunction에서 예외 발생" << endl;
    }

    // 안전한 방식 시연
    try {
        safeFunction();
    }
    catch (...) {
        cout << "safeFunction에서 예외 발생" << endl;
    }

    // shared_ptr 시연
    sharedPtrExample();

    cout << "\n=== 팩토리 함수와 예외 ===" << endl;
    try {
        auto res1 = createResource(100);
        auto res2 = createResource(0);  // 예외 발생
        auto res3 = createResource(200);
    }
    catch (const exception& e) {
        cout << "팩토리 오류: " << e.what() << endl;
    }

    cout << "\n프로그램 종료 - 모든 자원이 안전하게 해제되었습니다." << endl;
    return 0;
}