/*
 * 파일명: 04_function_overriding.cpp
 * 
 * 주제: 함수 오버라이딩 (Function Overriding)
 * 정의: 자식 클래스에서 부모 클래스의 함수를 재정의하여 다른 동작을 구현하는 기법
 * 
 * 핵심 개념:
 * - 함수 오버라이딩: 상속받은 함수를 자식 클래스에서 새롭게 구현
 * - 함수 시그니처: 함수명, 매개변수 타입과 개수가 부모와 동일해야 함
 * - 스코프 해석 연산자(::): 부모 클래스의 함수를 명시적으로 호출할 때 사용
 * - 정적 바인딩: 컴파일 타임에 어떤 함수를 호출할지 결정 (가상 함수와 대비)
 * 
 * 오버라이딩 vs 오버로딩:
 * - 오버라이딩: 상속 관계에서 같은 이름의 함수를 재정의 (다른 클래스)
 * - 오버로딩: 같은 클래스 내에서 같은 이름, 다른 매개변수의 함수들
 * 
 * 사용 시기:
 * - 부모 클래스의 기본 동작을 자식 클래스에 맞게 수정할 때
 * - 각 자식 클래스마다 다른 구현이 필요할 때
 * - 상속 계층에서 특화된 기능을 제공할 때
 * 
 * 관련 개념:
 * - 가상 함수 (Virtual Function): 런타임에 올바른 함수가 호출되도록 보장
 * - 순수 가상 함수 (Pure Virtual Function): 반드시 오버라이딩해야 하는 함수
 * - 다형성 (Polymorphism): 같은 인터페이스로 다른 동작 수행
 */

#include <iostream>
using namespace std;

class Shape {
protected:
    string name;

public:
    Shape(string n) : name(n) {}

    void display() {
        cout << "도형: " << name << endl;
    }

    double getArea() {
        cout << "기본 도형의 넓이" << endl;
        return 0;
    }
};

class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r) : Shape("원"), radius(r) {}

    // 부모 클래스의 함수 오버라이딩
    double getArea() {
        cout << "원의 넓이 계산" << endl;
        return 3.14159 * radius * radius;
    }

    // 부모 함수 호출하기
    void showInfo() {
        Shape::display();  // 부모 클래스의 display() 호출
        cout << "반지름: " << radius << ", 넓이: " << getArea() << endl;
    }
};

int main() {
    Circle circle(5.0);

    circle.showInfo();

    return 0;
}