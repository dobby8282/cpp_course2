/*
 * 파일명: 09_polymorphism_dynamic_binding.cpp
 * 
 * 주제: 다형성과 동적 바인딩 (Polymorphism & Dynamic Binding)
 * 정의: 하나의 인터페이스로 다양한 타입의 객체를 처리하는 능력
 * 
 * 핵심 개념:
 * - 다형성 (Polymorphism): 같은 인터페이스로 서로 다른 객체들을 다루는 능력
 * - 동적 바인딩: 런타임에 실제 객체 타입에 따라 호출할 함수를 결정
 * - 가상 함수 테이블: 각 클래스마다 가상 함수 포인터들을 저장하는 테이블
 * - 업캐스팅: 자식 객체를 부모 타입으로 참조하는 것
 * 
 * 다형성의 종류:
 * - 컴파일 타임 다형성: 함수 오버로딩, 템플릿 (정적 바인딩)
 * - 런타임 다형성: 가상 함수를 통한 동적 바인딩 (이 예제)
 * 
 * 사용 시기:
 * - 공통 인터페이스를 가진 여러 클래스를 통일된 방식으로 처리할 때
 * - 확장 가능한 시스템을 설계할 때 (새로운 타입 추가가 쉬움)
 * - 코드의 유연성과 재사용성을 높이고 싶을 때
 * - 의존성을 줄이고 느슨한 결합을 원할 때
 * 
 * 장점:
 * - 코드의 확장성과 유연성 향상
 * - 새로운 클래스 추가 시 기존 코드 변경 최소화
 * - 인터페이스와 구현의 분리
 * - 코드 재사용성 증대
 * 
 * 관련 개념:
 * - SOLID 원칙: 특히 개방-폐쇄 원칙 (확장에는 열려있고 수정에는 닫혀있음)
 * - 전략 패턴: 알고리즘을 캡슐화하여 교체 가능하게 만드는 패턴
 * - 팩토리 패턴: 객체 생성을 추상화하는 패턴
 * - 의존성 역전: 구체적인 클래스가 아닌 추상화에 의존
 * 
 * 주의사항:
 * - 가상 함수 호출은 일반 함수보다 약간의 성능 오버헤드 존재
 * - 메모리 사용량 증가 (vtable로 인한)
 * - 과도한 추상화는 코드 복잡성 증가
 * - 가상 소멸자 필수 (메모리 누수 방지)
 */

#include <iostream>
using namespace std;

class Vehicle {
protected:
    string brand;

public:
    Vehicle(string b) : brand(b) {}
    virtual ~Vehicle() {}

    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void getInfo() {
        cout << "브랜드: " << brand << endl;
    }
};

class Car : public Vehicle {
public:
    Car(string b) : Vehicle(b) {}

    void start() override {
        cout << brand << " 자동차 시동을 켭니다. 부릉부릉!" << endl;
    }

    void stop() override {
        cout << brand << " 자동차를 정지합니다." << endl;
    }
};

class Motorcycle : public Vehicle {
public:
    Motorcycle(string b) : Vehicle(b) {}

    void start() override {
        cout << brand << " 오토바이 시동을 켭니다. 붕붕!" << endl;
    }

    void stop() override {
        cout << brand << " 오토바이를 정지합니다." << endl;
    }
};

// 다형성을 활용한 함수
void driveVehicle(Vehicle* vehicle) {
    vehicle->getInfo();
    vehicle->start();
    cout << "운전 중..." << endl;
    vehicle->stop();
    cout << endl;
}

int main() {
    // 각각의 객체 생성
    Car car1("현대");
    Motorcycle motorcycle1("혼다");
    Car car2("BMW");

    // 배열을 사용한 다형성
    Vehicle* garage[3] = {&car1, &motorcycle1, &car2};

    cout << "=== 차고의 모든 차량 운전 ===" << endl;
    for (int i = 0; i < 3; i++) {
        driveVehicle(garage[i]);
    }

    cout << "=== 개별 차량 운전 ===" << endl;
    Vehicle* selectedVehicle = &car1;
    driveVehicle(selectedVehicle);

    selectedVehicle = &motorcycle1;
    driveVehicle(selectedVehicle);

    return 0;
}