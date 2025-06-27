/*
 * 파일명: 05_virtual_function_basic.cpp
 * 
 * 주제: 가상 함수 기초 (Virtual Function Basics)
 * 정의: 런타임에 실제 객체 타입에 따라 호출될 함수가 결정되는 함수
 * 
 * 핵심 개념:
 * - 가상 함수 (Virtual Function): virtual 키워드로 선언된 함수
 * - 동적 바인딩: 런타임에 실제 객체 타입을 기반으로 함수 호출 결정
 * - override 키워드: 가상 함수를 재정의할 때 사용하는 명시적 키워드 (C++11)
 * - 다형성 구현: 같은 인터페이스로 다양한 객체의 서로 다른 동작 실행
 * 
 * 가상 함수 vs 일반 함수:
 * - 가상 함수: 런타임에 실제 객체 타입의 함수 호출 (동적 바인딩)
 * - 일반 함수: 컴파일 타임에 포인터 타입의 함수 호출 (정적 바인딩)
 * 
 * 사용 시기:
 * - 상속 계층에서 다형성이 필요할 때
 * - 포인터나 참조를 통해 서로 다른 자식 객체를 동일하게 처리할 때
 * - 런타임에 객체의 실제 타입에 따른 동작이 필요할 때
 * 
 * 관련 개념:
 * - 가상 함수 테이블 (vtable): 가상 함수 포인터들을 저장하는 테이블
 * - 순수 가상 함수: = 0으로 선언하여 반드시 재정의해야 하는 함수
 * - 가상 소멸자: 상속 관계에서 올바른 소멸자 호출을 위한 virtual destructor
 * 
 * 주의사항:
 * - 가상 함수는 약간의 성능 오버헤드가 있음 (간접 호출)
 * - override 키워드 사용으로 실수 방지 권장
 * - 기본 클래스 포인터 삭제 시 가상 소멸자 필요
 */

#include <iostream>
using namespace std;

class Animal {
public:
    // 가상 함수
    virtual void makeSound() {
        cout << "동물이 소리를 냅니다." << endl;
    }

    // 일반 함수
    void move() {
        cout << "동물이 움직입니다." << endl;
    }
};

class Dog : public Animal {
public:
    void makeSound() override {  // override 키워드 사용 권장
        cout << "멍멍!" << endl;
    }

    void move() {
        cout << "개가 뛰어다닙니다." << endl;
    }
};

class Cat : public Animal {
public:
    void makeSound() override {
        cout << "야옹!" << endl;
    }

    void move() {
        cout << "고양이가 조용히 걷습니다." << endl;
    }
};

int main() {
    Dog dog;
    Cat cat;

    cout << "=== 직접 호출 ===" << endl;
    dog.makeSound();  // 멍멍!
    cat.makeSound();  // 야옹!

    cout << "\n=== 포인터로 호출 ===" << endl;
    Animal* animals[] = {&dog, &cat};

    for (Animal* animal : animals) {
        animal->makeSound();  // 가상 함수: 실제 타입의 함수 호출
        animal->move();       // 일반 함수: Animal의 함수 호출
    }

    return 0;
}