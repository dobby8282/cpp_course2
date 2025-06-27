/*
 * 파일명: 08_stl_algorithm_basic.cpp
 * 
 * 주제: STL 알고리즘 기초 (STL Algorithm Basics)
 * 정의: 컨테이너에 적용할 수 있는 다양한 알고리즘 함수들
 * 
 * 핵심 개념:
 * - STL 알고리즘: 반복자를 통해 컨테이너와 독립적으로 동작하는 함수들
 * - 반복자 기반: begin()과 end()를 사용하여 범위 지정
 * - 제네릭 프로그래밍: 타입과 컨테이너에 무관하게 동작
 * - 함수형 프로그래밍: 부작용 없이 데이터를 처리하는 순수 함수들
 * 
 * 알고리즘 분류:
 * - 비변경 알고리즘: find, count, binary_search (원본 수정 안함)
 * - 변경 알고리즘: sort, replace, transform (원본 수정)
 * - 수치 알고리즘: accumulate, max_element, min_element
 * - 집합 알고리즘: set_union, set_intersection
 * 
 * 사용 시기:
 * - 표준화된 알고리즘이 필요할 때 (직접 구현보다 안전하고 효율적)
 * - 다양한 컨테이너에 동일한 로직을 적용할 때
 * - 함수형 프로그래밍 스타일을 원할 때
 * - 코드 가독성과 재사용성을 높이고 싶을 때
 * 
 * 장점:
 * - 검증된 효율적인 구현
 * - 컨테이너 독립적 (vector, list, array 등 모두 사용 가능)
 * - 코드 중복 제거
 * - 표준화된 인터페이스로 가독성 향상
 * 
 * 함수 객체 활용:
 * - greater<int>(): 사용자 정의 비교 조건
 * - 람다 함수: 커스텀 로직을 간단히 작성
 * - 조건자(Predicate): 참/거짓을 반환하는 함수
 * 
 * 관련 개념:
 * - 함수형 프로그래밍: map, filter, reduce 패턴
 * - 람다 표현식: C++11부터 지원하는 익명 함수
 * - 범위 기반 알고리즘: C++20의 ranges 라이브러리
 * - 병렬 알고리즘: C++17의 execution policy
 * 
 * 주의사항:
 * - 이진 검색은 정렬된 범위에서만 동작
 * - 일부 알고리즘은 원본을 수정 (sort, replace 등)
 * - 반복자 무효화 주의 (컨테이너 수정 시)
 * - 빈 범위에 대한 처리 필요 (max_element 등)
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main() {
    vector<int> numbers = {5, 2, 8, 1, 9, 3};

    cout << "원본: ";
    for (int n : numbers) cout << n << " ";
    cout << endl;

    cout << "\n=== 정렬 알고리즘 ===" << endl;
    sort(numbers.begin(), numbers.end());
    cout << "오름차순: ";
    for (int n : numbers) cout << n << " ";
    cout << endl;

    sort(numbers.begin(), numbers.end(), greater<int>());
    cout << "내림차순: ";
    for (int n : numbers) cout << n << " ";
    cout << endl;

    cout << "\n=== 검색 알고리즘 ===" << endl;
    sort(numbers.begin(), numbers.end());  // 이진 검색을 위해 정렬

    int target = 5;
    if (binary_search(numbers.begin(), numbers.end(), target)) {
        cout << target << "을(를) 찾았습니다." << endl;
    }

    auto it = find(numbers.begin(), numbers.end(), 8);
    if (it != numbers.end()) {
        cout << "8의 위치: " << distance(numbers.begin(), it) << endl;
    }

    cout << "\n=== 수치 알고리즘 ===" << endl;
    int sum = accumulate(numbers.begin(), numbers.end(), 0);
    cout << "합계: " << sum << endl;

    int maxVal = *max_element(numbers.begin(), numbers.end());
    int minVal = *min_element(numbers.begin(), numbers.end());
    cout << "최댓값: " << maxVal << ", 최솟값: " << minVal << endl;

    cout << "\n=== 변경 알고리즘 ===" << endl;
    replace(numbers.begin(), numbers.end(), 5, 50);  // 5를 50으로 변경
    cout << "5를 50으로 변경: ";
    for (int n : numbers) cout << n << " ";
    cout << endl;

    return 0;
}