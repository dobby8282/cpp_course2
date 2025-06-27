/*
 * 파일명: 09_lambda_stl_algorithm.cpp
 * 
 * 주제: 람다와 STL 알고리즘 (Lambda with STL Algorithms)
 * 정의: 람다 표현식을 STL 알고리즘과 함께 사용하여 강력한 기능 구현
 * 
 * 핵심 개념:
 * - 조건자(Predicate): 참/거짓을 반환하는 람다 함수
 * - 변환 함수: 입력을 다른 형태로 변환하는 람다
 * - 비교 함수: 정렬 기준을 정의하는 람다
 * - 함수형 프로그래밍: 불변성과 순수 함수를 지향하는 패러다임
 * 
 * STL 알고리즘 분류:
 * - 검색: find_if, search, binary_search
 * - 계산: count_if, accumulate, inner_product
 * - 변환: transform, replace_if, generate
 * - 정렬: sort, stable_sort, partial_sort
 * - 제거: remove_if, unique, erase
 * 
 * 람다의 역할:
 * - 조건 정의: find_if, count_if, remove_if에서 조건 지정
 * - 변환 로직: transform에서 요소 변환 방법 정의
 * - 비교 기준: sort에서 정렬 순서 결정
 * - 부작용 처리: for_each에서 상태 변경이나 출력
 * 
 * 사용 시기:
 * - 복잡한 조건이나 변환 로직이 필요할 때
 * - 함수형 프로그래밍 스타일로 코드를 작성할 때
 * - 지역적으로만 사용되는 로직을 간결하게 표현할 때
 * - STL 알고리즘의 유연성을 극대화하고 싶을 때
 * 
 * 함수형 프로그래밍 패턴:
 * - Map: transform으로 각 요소를 변환
 * - Filter: remove_if, copy_if로 조건에 맞는 요소 선별
 * - Reduce: accumulate, for_each로 요소들을 하나의 값으로 축약
 * - Find: find_if로 조건에 맞는 요소 검색
 * 
 * 관련 개념:
 * - RAII: 자원 관리를 자동화하는 C++ 패턴
 * - 범위 기반 알고리즘: C++20 ranges 라이브러리
 * - 병렬 알고리즘: std::execution::par로 병렬 처리
 * - 함수 합성: 여러 람다를 조합하여 복잡한 로직 구성
 * 
 * 주의사항:
 * - remove_if는 실제 삭제가 아닌 요소 이동 (erase와 함께 사용)
 * - 참조 캡처 시 람다가 변수보다 오래 살면 댕글링 참조 위험
 * - 복잡한 람다는 별도 함수로 분리하는 것이 좋음
 * - 성능이 중요한 곳에서는 람다 오버헤드 고려
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int main() {
    vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    cout << "=== find_if: 조건 검색 ===" << endl;
    // 첫 번째 짝수 찾기
    auto it = find_if(numbers.begin(), numbers.end(), [](int n) {
        return n % 2 == 0;
    });

    if (it != numbers.end()) {
        cout << "첫 번째 짝수: " << *it << endl;
    }

    cout << "\n=== count_if: 조건 계산 ===" << endl;
    // 5보다 큰 수의 개수
    int count = count_if(numbers.begin(), numbers.end(), [](int n) {
        return n > 5;
    });
    cout << "5보다 큰 수의 개수: " << count << endl;

    cout << "\n=== sort: 정렬 기준 ===" << endl;
    vector<string> words = {"banana", "apple", "cherry", "date"};

    // 길이 순으로 정렬
    sort(words.begin(), words.end(), [](const string& a, const string& b) {
        return a.length() < b.length();
    });

    cout << "길이 순 정렬: ";
    for (const string& word : words) cout << word << " ";
    cout << endl;

    cout << "\n=== for_each: 캡처 사용 ===" << endl;
    int sum = 0;
    for_each(numbers.begin(), numbers.end(), [&sum](int n) {
        sum += n;
    });
    cout << "총합: " << sum << endl;

    return 0;
}