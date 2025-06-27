/*
 * 파일명: 08_lambda_basic.cpp
 * 
 * 주제: 람다 표현식 기초 (Lambda Expression Basics)
 * 정의: 익명 함수를 생성하는 C++11의 기능
 * 
 * 핵심 개념:
 * - 람다 표현식: 이름 없는 함수를 즉석에서 정의하는 문법
 * - 캡처 절: 주변 스코프의 변수를 람다 내부에서 사용하는 방법
 * - 함수 객체: 컴파일러가 람다를 함수 객체(클래스)로 변환
 * - 클로저: 람다가 생성하는 함수 객체 인스턴스
 * 
 * 람다 문법 구조:
 * - [캡처절](매개변수) -> 반환타입 { 함수 본체 }
 * - []: 캡처 없음
 * - [=]: 모든 변수를 값으로 캡처
 * - [&]: 모든 변수를 참조로 캡처
 * - [x, &y]: x는 값으로, y는 참조로 캡처
 * 
 * 캡처 방식:
 * - 값 캡처: 람다 생성 시점의 값을 복사 (람다 내에서 수정 불가)
 * - 참조 캡처: 원본 변수를 직접 참조 (람다 내에서 수정 가능)
 * - mutable: 값 캡처된 변수도 람다 내에서 수정 가능하게 함
 * 
 * 사용 시기:
 * - STL 알고리즘에 간단한 조건이나 연산이 필요할 때
 * - 콜백 함수를 간단히 정의하고 싶을 때
 * - 지역적으로만 사용되는 짧은 함수가 필요할 때
 * - 함수형 프로그래밍 스타일을 구현할 때
 * 
 * 장점:
 * - 코드 간결성: 별도 함수 정의 없이 즉석에서 로직 작성
 * - 지역성: 사용되는 곳 근처에서 정의하여 가독성 향상
 * - 유연성: 주변 변수를 쉽게 활용 가능
 * - STL과의 완벽한 호환성
 * 
 * 관련 개념:
 * - std::function: 람다를 포함한 모든 호출 가능 객체를 저장
 * - 함수 포인터: C 스타일 함수 포인터의 현대적 대안
 * - 함수형 프로그래밍: map, filter, reduce 패턴 구현
 * - 템플릿: auto와 함께 사용하여 타입 추론
 * 
 * 성능 특성:
 * - 컴파일 타임에 최적화됨 (인라인화 가능)
 * - 캡처 오버헤드: 값 캡처는 복사 비용, 참조 캡처는 포인터 저장
 * - 일반 함수보다 빠를 수 있음 (템플릿 특성)
 * 
 * 주의사항:
 * - 참조 캡처 시 댕글링 참조 위험 (람다가 변수보다 오래 살 때)
 * - 값 캡처는 람다 생성 시점의 값 고정
 * - 재귀 람다는 std::function 필요
 * - 과도한 사용은 코드 복잡성 증가
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

int main() {
    cout << "=== 기본 람다 ===" << endl;

    // 가장 간단한 람다
    auto hello = []() {
        cout << "Hello Lambda!" << endl;
    };
    hello();

    // 매개변수를 받는 람다
    auto add = [](int a, int b) {
        return a + b;
    };
    cout << "5 + 3 = " << add(5, 3) << endl;

    // 반환 타입을 명시한 람다
    auto divide = [](double a, double b) -> double {
        return b != 0 ? a / b : 0;
    };
    cout << "10.0 / 3.0 = " << divide(10.0, 3.0) << endl;

    cout << "\n=== 캡처 절 ===" << endl;
    int x = 10;
    int y = 20;

    // 값으로 캡처
    auto lambda1 = [x, y]() {
        cout << "값 캡처: x=" << x << ", y=" << y << endl;
    };

    // 참조로 캡처
    auto lambda2 = [&x, &y]() {
        x += 5;
        y += 10;
        cout << "참조 캡처 후: x=" << x << ", y=" << y << endl;
    };

    // 모든 변수를 값으로 캡처
    auto lambda3 = [=]() {
        cout << "모든 변수 값 캡처: x=" << x << ", y=" << y << endl;
    };

    lambda1();
    lambda2();
    lambda3();

    cout << "\n=== STL과 함께 사용 ===" << endl;
    vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // 짝수만 출력
    cout << "짝수: ";
    for_each(numbers.begin(), numbers.end(), [](int n) {
        if (n % 2 == 0) cout << n << " ";
    });
    cout << endl;

    return 0;
}