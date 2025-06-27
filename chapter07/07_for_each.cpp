/*
 * 파일명: 10_loop_comparison.cpp
 * 
 * 주제: C++ 반복문 비교 (Loop Comparison in C++)
 * 정의: for_each, range-based for, 일반 for문의 특징과 사용법 비교
 * 
 * 핵심 개념:
 * - for_each: STL 알고리즘 중 하나로 함수형 프로그래밍 스타일
 * - range-based for: C++11부터 도입된 간편한 반복문 (Java의 enhanced for와 유사)
 * - 일반 for문: 전통적인 C 스타일 반복문으로 가장 세밀한 제어 가능
 * - 반복자: 컨테이너 요소에 접근하는 일반화된 방법
 * 
 * 각 방식의 특징:
 * - for_each: 함수 객체나 람다와 함께 사용, STL 알고리즘과 일관성
 * - range-based for: 가장 간결하고 읽기 쉬움, 실수 위험 적음
 * - 일반 for문: 인덱스 접근 가능, 복잡한 제어 로직 구현 가능
 * 
 * 사용 시기:
 * - for_each: 함수형 프로그래밍, 복잡한 로직을 함수로 분리할 때
 * - range-based for: 단순 순회, 코드 가독성이 중요할 때
 * - 일반 for문: 인덱스가 필요하거나 특수한 순회 패턴이 필요할 때
 * 
 * 관련 개념:
 * - 반복자 (Iterator): begin(), end() 함수
 * - 람다 표현식: 익명 함수 생성
 * - STL 알고리즘: transform, find_if, count_if 등
 * - auto 키워드: 타입 자동 추론으로 코드 간소화
 * 
 * 주의사항:
 * - range-based for에서는 인덱스 접근 불가
 * - for_each는 #include <algorithm> 필요
 * - 일반 for문에서 size() 반환 타입 주의 (size_t vs int)
 * - 반복 중 컨테이너 크기 변경 시 주의 필요
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> numbers = {1, 2, 3, 4, 5};
    
    cout << "=== 기본 출력 ===" << endl;
    
    // 1. for_each 사용
    cout << "for_each: ";
    for_each(numbers.begin(), numbers.end(), [](int n) {
        cout << n << " ";
    });
    cout << endl;
    
    // 2. range-based for 사용 (C++11)
    cout << "range-based for: ";
    for (int n : numbers) {
        cout << n << " ";
    }
    cout << endl;
    
    // 3. 일반 for문
    cout << "일반 for문: ";
    for (int i = 0; i < numbers.size(); i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;
    
    cout << "\n=== 요소 수정 (각 요소를 2배로) ===" << endl;
    
    // 1. for_each - 참조로 받아야 수정 가능
    vector<int> data1 = {1, 2, 3, 4, 5};
    for_each(data1.begin(), data1.end(), [](int& n) { n *= 2; });
    cout << "for_each 결과: ";
    for (int n : data1) cout << n << " ";
    cout << endl;
    
    // 2. range-based for - 참조로 받아야 수정 가능
    vector<int> data2 = {1, 2, 3, 4, 5};
    for (int& n : data2) { n *= 2; }
    cout << "range-based for 결과: ";
    for (int n : data2) cout << n << " ";
    cout << endl;
    
    // 3. 일반 for문
    vector<int> data3 = {1, 2, 3, 4, 5};
    for (int i = 0; i < data3.size(); i++) { data3[i] *= 2; }
    cout << "일반 for문 결과: ";
    for (int n : data3) cout << n << " ";
    cout << endl;
    
    cout << "\n=== 인덱스가 필요한 경우 ===" << endl;
    vector<string> fruits = {"사과", "바나나", "체리"};
    
    // for_each - 외부 변수 필요
    int index = 0;
    for_each(fruits.begin(), fruits.end(), [&index](const string& fruit) {
        cout << index++ << ":" << fruit << " ";
    });
    cout << endl;
    
    // 일반 for문 - 인덱스 쉽게 사용
    for (int i = 0; i < fruits.size(); i++) {
        cout << i << ":" << fruits[i] << " ";
    }
    cout << endl;
    
    cout << "\n=== 결론 ===" << endl;
    cout << "• for_each: 함수형 프로그래밍 스타일" << endl;
    cout << "• range-based for: 가장 간단하고 안전" << endl;
    cout << "• 일반 for문: 인덱스 필요시 사용" << endl;
    
    return 0;
}