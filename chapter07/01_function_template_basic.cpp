/*
 * 파일명: 01_function_template_basic.cpp
 * 
 * 주제: 함수 템플릿 기초 (Function Template Basics)
 * 정의: 타입에 독립적인 일반화된 함수를 작성하는 기법
 * 
 * 핵심 개념:
 * - 함수 템플릿: 다양한 타입에 대해 동일한 로직을 적용하는 함수
 * - 타입 매개변수: template<typename T>의 T처럼 실제 타입을 대체하는 변수
 * - 템플릿 인스턴스화: 컴파일러가 특정 타입에 대해 실제 함수를 생성하는 과정
 * - 타입 추론: 컴파일러가 함수 호출 시 자동으로 타입을 결정하는 기능
 * 
 * 템플릿 문법:
 * - template<typename T>: 단일 타입 매개변수
 * - template<typename T, typename U>: 다중 타입 매개변수
 * - typename vs class: 둘 다 사용 가능하지만 typename이 더 명확
 * 
 * 사용 시기:
 * - 동일한 알고리즘을 여러 타입에 적용해야 할 때
 * - 타입별로 함수 오버로딩을 만들기 번거로울 때
 * - 컨테이너나 알고리즘 라이브러리를 만들 때
 * - 제네릭 프로그래밍을 구현할 때
 * 
 * 장점:
 * - 코드 중복 제거 (DRY 원칙)
 * - 타입 안전성 보장
 * - 컴파일 타임에 최적화 가능
 * - 확장성과 재사용성 향상
 * 
 * 관련 개념:
 * - 클래스 템플릿: 클래스를 템플릿으로 만드는 기법
 * - 템플릿 특화: 특정 타입에 대해 별도 구현 제공
 * - SFINAE: 템플릿 인수 추론 실패가 오류가 아닌 경우
 * - 컨셉트 (C++20): 템플릿 매개변수에 제약 조건 추가
 * 
 * 주의사항:
 * - 컴파일 시간 증가 (각 타입마다 함수 생성)
 * - 복잡한 에러 메시지 생성 가능
 * - 헤더 파일에 구현 포함 필요 (링크 단계에서 필요)
 * - 타입 제약이 명시적이지 않음 (C++20 이전)
 */

#include <iostream>
using namespace std;

// 함수 템플릿
template<typename T>
T getMax(T a, T b) {
    return (a > b) ? a : b;
}

// 여러 매개변수를 가진 템플릿
template<typename T>
void mySwap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

// 다중 타입 템플릿
template<typename T, typename U>
void printPair(T first, U second) {
    cout << "(" << first << ", " << second << ")" << endl;
}

int main() {
    // 정수형
    cout << "최댓값(10, 20): " << getMax(10, 20) << endl;

    // 실수형
    cout << "최댓값(3.5, 2.8): " << getMax(3.5, 2.8) << endl;

    // 문자열
    cout << "최댓값(\"apple\", \"banana\"): " << getMax(string("apple"), string("banana")) << endl;

    // swap 테스트
    int x = 5, y = 10;
    cout << "\nswap 전: x=" << x << ", y=" << y << endl;
    mySwap(x, y);  // 함수명 변경
    cout << "swap 후: x=" << x << ", y=" << y << endl;

    // 다중 타입 템플릿
    printPair(42, "hello");
    printPair(3.14, 100);

    return 0;
}