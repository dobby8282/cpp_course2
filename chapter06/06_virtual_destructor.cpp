/*
 * 파일명: 06_virtual_destructor.cpp
 * 
 * 주제: 가상 소멸자 (Virtual Destructor)
 * 정의: 상속 관계에서 올바른 소멸자 호출을 보장하는 가상 소멸자
 * 
 * 핵심 개념:
 * - 가상 소멸자: virtual로 선언된 소멸자로 올바른 소멸 순서 보장
 * - 메모리 누수 방지: 기본 클래스 포인터로 삭제 시 자식 클래스 소멸자도 호출
 * - 업캐스팅: 자식 객체를 부모 포인터로 가리키는 것
 * - 소멸자 체인: 자식 → 부모 순서로 소멸자가 연쇄 호출됨
 * 
 * 가상 소멸자의 필요성:
 * - 기본 클래스 포인터로 자식 객체 삭제 시 자식 소멸자 누락 방지
 * - 동적 할당된 자원의 안전한 해제 보장
 * - 다형성을 사용하는 클래스 계층에서 필수
 * 
 * 사용 시기:
 * - 상속을 위해 설계된 기본 클래스
 * - 가상 함수를 가진 클래스
 * - 다형성을 통해 객체를 관리하는 경우
 * 
 * 관련 개념:
 * - RAII (Resource Acquisition Is Initialization): 자원 관리 패턴
 * - 스마트 포인터: 자동 메모리 관리를 위한 modern C++ 방식
 * - 소멸자 순서: 생성의 역순으로 소멸 (자식 → 부모)
 * 
 * 주의사항:
 * - 기본 클래스에 가상 함수가 있으면 소멸자도 virtual로 선언
 * - 가상 소멸자는 약간의 성능 오버헤드 존재
 * - = default나 = delete로 명시적 관리 가능
 */

#include <iostream>
using namespace std;

class Base {
public:
    Base() {
        cout << "Base 생성자" << endl;
    }

    // 가상 소멸자 - 중요!
    virtual ~Base() {
        cout << "Base 소멸자" << endl;
    }

    virtual void display() {
        cout << "Base 클래스" << endl;
    }
};

class Derived : public Base {
private:
    int* data;

public:
    Derived() {
        data = new int[10];
        cout << "Derived 생성자 (메모리 할당)" << endl;
    }

    ~Derived() {
        delete[] data;
        cout << "Derived 소멸자 (메모리 해제)" << endl;
    }

    void display() override {
        cout << "Derived 클래스" << endl;
    }
};

int main() {
    cout << "=== 직접 객체 생성 ===" << endl;
    {
        Derived d;
        d.display();
    }

    cout << "\n=== 포인터를 통한 동적 할당 ===" << endl;
    {
        Base* ptr = new Derived();  // 업캐스팅
        ptr->display();             // 가상 함수 호출
        delete ptr;                 // 가상 소멸자 덕분에 Derived 소멸자도 호출
    }

    return 0;
}