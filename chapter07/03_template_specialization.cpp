/*
 * 파일명: 03_template_specialization.cpp
 * 
 * 주제: 템플릿 특수화 (Template Specialization)
 * 정의: 특정 타입에 대해 템플릿의 특별한 구현을 제공
 * 
 * 핵심 개념:
 * - 템플릿 특수화: 일반 템플릿과 다른 동작이 필요한 특정 타입을 위한 별도 구현
 * - 완전 특수화: 모든 템플릿 매개변수를 구체적 타입으로 지정하는 특수화
 * - 부분 특수화: 일부 템플릿 매개변수만 특수화 (클래스 템플릿에서만 가능)
 * - 특수화 우선순위: 특수화된 버전이 일반 템플릿보다 우선 선택됨
 * 
 * 특수화의 종류:
 * - 클래스 템플릿 특수화: template<> class ClassName<Type>
 * - 함수 템플릿 특수화: template<> void functionName<Type>(Type param)
 * - 멤버 함수 특수화: 특정 타입에 대한 멤버 함수만 특수화
 * 
 * 사용 시기:
 * - 특정 타입에 대해 최적화된 구현이 필요할 때
 * - 일반 템플릿으로는 올바르게 동작하지 않는 타입이 있을 때
 * - 특수한 출력 형식이나 처리 방식이 필요할 때
 * - 타입별로 다른 알고리즘이 더 효율적일 때
 * 
 * 장점:
 * - 타입별 최적화 가능
 * - 특수한 동작이 필요한 타입에 대한 유연한 처리
 * - 일반 템플릿의 기본 동작 유지하면서 예외 케이스 처리
 * - 컴파일 타임에 최적의 구현 선택
 * 
 * 관련 개념:
 * - SFINAE: 템플릿 인수 추론 실패 시 오류가 아닌 후보에서 제외
 * - 태그 디스패치: 타입 특성에 따른 함수 선택 기법
 * - 타입 특성 (Type Traits): 타입의 속성을 검사하는 메타프로그래밍
 * - 컨셉 (Concepts): C++20의 템플릿 제약 조건
 * 
 * 주의사항:
 * - 특수화는 선언 후에 정의해야 함
 * - 부분 특수화는 함수 템플릿에서 지원되지 않음
 * - 과도한 특수화는 코드 복잡성 증가
 * - 특수화와 오버로딩의 우선순위 규칙 이해 필요
 */

#include <iostream>
#include <string>
using namespace std;

// 일반 템플릿
template<typename T>
class Printer {
public:
    void print(T value) {
        cout << "일반: " << value << endl;
    }
};

// string에 대한 특수화
template<>
class Printer<string> {
public:
    void print(string value) {
        cout << "문자열 특수화: \"" << value << "\"" << endl;
    }
};

// bool에 대한 특수화
template<>
class Printer<bool> {
public:
    void print(bool value) {
        cout << "불린 특수화: " << (value ? "참" : "거짓") << endl;
    }
};

// 함수 템플릿과 특수화
template<typename T>
void describe(T value) {
    cout << "알 수 없는 타입: " << value << endl;
}

// int 특수화
template<>
void describe<int>(int value) {
    cout << "정수 " << value << "입니다." << endl;
}

// double 특수화
template<>
void describe<double>(double value) {
    cout << "실수 " << value << "입니다." << endl;
}

int main() {
    Printer<int> intPrinter;
    Printer<string> stringPrinter;
    Printer<bool> boolPrinter;
    Printer<double> doublePrinter;

    intPrinter.print(42);
    stringPrinter.print("Hello World");
    boolPrinter.print(true);
    doublePrinter.print(3.14);

    cout << "\n함수 템플릿 특수화:" << endl;
    describe(100);
    describe(3.14159);
    describe("문자열");  // 일반 템플릿 사용

    return 0;
}