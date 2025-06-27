/*
 * 파일명: 08_coding_standards.cpp
 * 
 * 주제: 코딩 표준과 스타일 (Coding Standards & Style)
 * 정의: 일관되고 읽기 쉬운 코드를 작성하기 위한 규칙과 관례
 * 
 * 핵심 개념:
 * - 네이밍 컨벤션: 클래스, 함수, 변수에 대한 일관된 명명 규칙
 * - const 정확성: 변경되지 않는 값과 함수를 const로 명시
 * - RAII 패턴: 자원 관리를 객체 생명주기와 연결
 * - 스마트 포인터: 자동 메모리 관리로 안전성 향상
 * 
 * 네이밍 컨벤션:
 * - 클래스명: PascalCase (StudentManager, FileHandler)
 * - 함수명: camelCase (addStudent, getAverageScore)
 * - 변수명: camelCase 또는 snake_case (일관성 유지)
 * - 상수명: UPPER_SNAKE_CASE (MAX_STUDENTS, PI)
 * - 열거형: scoped enum class 사용
 * 
 * 코드 구조 원칙:
 * - 단일 책임 원칙: 각 클래스와 함수는 하나의 명확한 목적
 * - 캡슐화: private 멤버로 내부 구현 숨김
 * - 입력 검증: 매개변수 유효성 검사
 * - 오류 처리: 예외나 반환값으로 오류 상황 명확히 전달
 * 
 * 사용 시기:
 * - 팀 프로젝트에서 코드 일관성 확보
 * - 장기 유지보수가 필요한 소프트웨어
 * - 라이브러리나 프레임워크 개발
 * - 코드 리뷰와 협업이 중요한 환경
 * 
 * Modern C++ 관례:
 * - auto 키워드로 타입 추론 활용
 * - range-based for loop 사용
 * - 스마트 포인터로 메모리 관리
 * - structured binding으로 가독성 향상
 * - noexcept로 예외 명세 명시
 * 
 * 장점:
 * - 코드 가독성과 이해도 향상
 * - 팀원 간 일관된 코딩 스타일
 * - 버그 발생 가능성 감소
 * - 유지보수 비용 절감
 * 
 * 설계 원칙:
 * - DRY (Don't Repeat Yourself): 중복 코드 최소화
 * - KISS (Keep It Simple, Stupid): 간단하고 명확한 구현
 * - SOLID 원칙: 객체지향 설계의 기본 원칙들
 * - 방어적 프로그래밍: 입력 검증과 오류 처리
 * 
 * 관련 개념:
 * - 코드 리뷰: 동료 검토를 통한 품질 향상
 * - 정적 분석: 컴파일러와 도구를 통한 자동 검사
 * - 단위 테스트: 코드 품질 검증
 * - 문서화: 코드 의도와 사용법 명시
 * 
 * 주의사항:
 * - 과도한 규칙은 생산성 저하 원인
 * - 프로젝트 특성에 맞는 표준 선택
 * - 기존 코드베이스와의 일관성 고려
 * - 도구를 활용한 자동화 (포매터, 린터)
 */

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

// 네임스페이스 사용 (글로벌 using namespace std는 피하기)
using std::cout;
using std::endl;
using std::string;
using std::vector;

namespace MyProject {

    // 상수는 대문자와 언더스코어 사용
    const int MAX_STUDENTS = 100;
    const double PI = 3.14159;

    // 열거형은 class 사용 (scoped enum)
    enum class Grade {
        A_PLUS,
        A,
        B_PLUS,
        B,
        C_PLUS,
        C,
        D,
        F
    };

    // 클래스명은 PascalCase
    class StudentManager {
    private:
        // 멤버 변수는 camelCase 또는 snake_case (일관성 유지)
        vector<string> studentNames;
        vector<double> studentScores;
        int maxCapacity;

        // private 헬퍼 함수
        bool isValidScore(double score) const {
            return score >= 0.0 && score <= 100.0;
        }

        Grade calculateGrade(double score) const {
            if (score >= 97.0) return Grade::A_PLUS;
            if (score >= 93.0) return Grade::A;
            if (score >= 90.0) return Grade::B_PLUS;
            if (score >= 87.0) return Grade::B;
            if (score >= 83.0) return Grade::C_PLUS;
            if (score >= 80.0) return Grade::C;
            if (score >= 70.0) return Grade::D;
            return Grade::F;
        }

    public:
        // 생성자는 명시적 초기화 리스트 사용
        explicit StudentManager(int capacity = MAX_STUDENTS) 
            : maxCapacity(capacity) {
            studentNames.reserve(maxCapacity);
            studentScores.reserve(maxCapacity);
        }

        // 복사 방지 (필요한 경우에만)
        StudentManager(const StudentManager&) = delete;
        StudentManager& operator=(const StudentManager&) = delete;

        // 이동 생성자는 noexcept
        StudentManager(StudentManager&& other) noexcept 
            : studentNames(std::move(other.studentNames)),
              studentScores(std::move(other.studentScores)),
              maxCapacity(other.maxCapacity) {}

        // 함수명은 camelCase
        bool addStudent(const string& name, double score) {
            // 매개변수 검증
            if (name.empty()) {
                cout << "오류: 학생 이름이 비어있습니다." << endl;
                return false;
            }

            if (!isValidScore(score)) {
                cout << "오류: 점수는 0-100 사이여야 합니다." << endl;
                return false;
            }

            if (studentNames.size() >= static_cast<size_t>(maxCapacity)) {
                cout << "오류: 최대 수용 인원을 초과했습니다." << endl;
                return false;
            }

            // 중복 검사
            auto it = std::find(studentNames.begin(), studentNames.end(), name);
            if (it != studentNames.end()) {
                cout << "경고: 이미 존재하는 학생입니다: " << name << endl;
                return false;
            }

            studentNames.push_back(name);
            studentScores.push_back(score);
            return true;
        }

        void displayAllStudents() const {
            cout << "\n=== 학생 목록 (" << studentNames.size() << "명) ===" << endl;

            for (size_t i = 0; i < studentNames.size(); ++i) {
                Grade grade = calculateGrade(studentScores[i]);
                cout << (i + 1) << ". " << studentNames[i] 
                     << " - 점수: " << studentScores[i] 
                     << ", 등급: " << gradeToString(grade) << endl;
            }
        }

        // const 멤버 함수 적극 활용
        double getAverageScore() const {
            if (studentScores.empty()) {
                return 0.0;
            }

            double sum = 0.0;
            for (double score : studentScores) {
                sum += score;
            }
            return sum / studentScores.size();
        }

        size_t getStudentCount() const {
            return studentNames.size();
        }

        // 정적 유틸리티 함수
        static string gradeToString(Grade grade) {
            switch (grade) {
                case Grade::A_PLUS: return "A+";
                case Grade::A:      return "A";
                case Grade::B_PLUS: return "B+";
                case Grade::B:      return "B";
                case Grade::C_PLUS: return "C+";
                case Grade::C:      return "C";
                case Grade::D:      return "D";
                case Grade::F:      return "F";
                default:            return "Unknown";
            }
        }
    };

} // namespace MyProject

// 함수는 camelCase
void demonstrateBestPractices() {
    using namespace MyProject;

    cout << "=== C++ 코딩 표준 데모 ===" << endl;

    // auto 키워드 적극 활용
    auto manager = std::make_unique<StudentManager>(5);

    // 명확한 변수명 사용
    const vector<std::pair<string, double>> testStudents = {
        {"김철수", 95.5},
        {"이영희", 87.3},
        {"박민수", 92.0},
        {"최정화", 78.8}
    };

    // range-based for loop 사용
    for (const auto& [name, score] : testStudents) {
        manager->addStudent(name, score);
    }

    manager->displayAllStudents();

    cout << "\n평균 점수: " << manager->getAverageScore() << endl;
    cout << "총 학생 수: " << manager->getStudentCount() << "명" << endl;

    // 잘못된 입력 테스트
    cout << "\n=== 오류 처리 테스트 ===" << endl;
    manager->addStudent("", 90);        // 빈 이름
    manager->addStudent("홍길동", 150); // 잘못된 점수
    manager->addStudent("김철수", 80);  // 중복 이름
}

int main() {
    try {
        demonstrateBestPractices();
    }
    catch (const std::exception& e) {
        cout << "예외 발생: " << e.what() << endl;
        return 1;
    }

    cout << "\n=== 코딩 표준 정리 ===" << endl;
    cout << "1. 일관된 네이밍 컨벤션 (camelCase, PascalCase)" << endl;
    cout << "2. const 정확성 유지" << endl;
    cout << "3. RAII 패턴 활용" << endl;
    cout << "4. 스마트 포인터 사용" << endl;
    cout << "5. 예외 안전성 보장" << endl;
    cout << "6. 명확한 함수와 변수명" << endl;
    cout << "7. 적절한 주석과 문서화" << endl;

    return 0;
}