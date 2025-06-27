/*
 * 파일명: 02_class_template_basic.cpp
 * 
 * 주제: 클래스 템플릿 기초 (Class Template Basics)
 * 정의: 다양한 타입을 다룰 수 있는 제네릭 클래스
 * 
 * 핵심 개념:
 * - 클래스 템플릿: 타입을 매개변수로 받아 여러 타입에 대해 동작하는 클래스
 * - 타입 매개변수: typename T로 선언하여 다양한 타입을 받을 수 있음
 * - 비타입 매개변수: int SIZE처럼 값을 매개변수로 받는 템플릿 매개변수
 * - 템플릿 인스턴스화: 컴파일러가 특정 타입에 대해 실제 클래스 코드를 생성
 * 
 * 템플릿의 장점:
 * - 코드 재사용성: 하나의 클래스로 여러 타입 지원
 * - 타입 안전성: 컴파일 타임에 타입 검사 수행
 * - 성능: 런타임 오버헤드 없이 제네릭 프로그래밍 가능
 * - 유지보수성: 중복 코드 제거로 관리 용이
 * 
 * 사용 시기:
 * - 동일한 로직을 여러 타입에 적용해야 할 때
 * - 컨테이너 클래스 (Array, List, Stack 등) 구현 시
 * - 타입에 독립적인 알고리즘을 구현할 때
 * - STL과 같은 범용 라이브러리 개발 시
 * 
 * 템플릿 매개변수 종류:
 * - 타입 매개변수: typename T, class T (타입을 받음)
 * - 비타입 매개변수: int N, bool flag (값을 받음)
 * - 템플릿 매개변수: template<class> class Container (다른 템플릿을 받음)
 * 
 * 관련 개념:
 * - 함수 템플릿: 함수에 대한 템플릿
 * - 템플릿 특수화: 특정 타입에 대한 별도 구현
 * - STL 컨테이너: vector, list, map 등이 모두 클래스 템플릿
 * - SFINAE: 템플릿 오버로드 해결 원칙
 * 
 * 주의사항:
 * - 헤더 파일에 구현을 포함해야 함 (템플릿 정의와 구현 분리 어려움)
 * - 컴파일 시간 증가 (각 타입마다 코드 생성)
 * - 에러 메시지가 복잡할 수 있음
 * - 템플릿 인스턴스화는 사용되는 시점에 발생
 */

#include <iostream>
using namespace std;

template<typename T>
class Box {
private:
    T item;

public:
    Box(T i) : item(i) {}

    void setItem(T i) {
        item = i;
    }

    T getItem() {
        return item;
    }

    void display() {
        cout << "Box contains: " << item << endl;
    }
};

// 배열을 관리하는 클래스 템플릿
template<typename T, int SIZE>
class Array {
private:
    T data[SIZE];

public:
    void set(int index, T value) {
        if (index >= 0 && index < SIZE) {
            data[index] = value;
        }
    }

    T get(int index) {
        if (index >= 0 && index < SIZE) {
            return data[index];
        }
        return T{};  // 기본값 반환
    }

    void display() {
        for (int i = 0; i < SIZE; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    // 다양한 타입의 Box 생성
    Box<int> intBox(42);
    Box<string> stringBox("Hello");
    Box<double> doubleBox(3.14);

    intBox.display();
    stringBox.display();
    doubleBox.display();

    // 크기가 고정된 배열
    Array<int, 5> intArray;
    for (int i = 0; i < 5; i++) {
        intArray.set(i, i * 10);
    }
    intArray.display();

    Array<string, 3> stringArray;
    stringArray.set(0, "첫번째");
    stringArray.set(1, "두번째");
    stringArray.set(2, "세번째");
    stringArray.display();

    return 0;
}