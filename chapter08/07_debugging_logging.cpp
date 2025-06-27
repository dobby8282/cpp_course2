/*
 * 파일명: 07_debugging_logging.cpp
 * 
 * 주제: 디버깅과 로깅 (Debugging & Logging)
 * 정의: 프로그램의 실행 상태를 추적하고 문제를 진단하는 도구들
 * 
 * 핵심 개념:
 * - 로깅 시스템: 프로그램 실행 과정을 기록하여 문제 진단과 모니터링 지원
 * - 로그 레벨: DEBUG, INFO, WARNING, ERROR로 메시지 중요도 분류
 * - 디버그 매크로: 조건부 컴파일로 디버그 코드 포함/제외
 * - assert: 프로그램 가정을 검증하는 디버깅 도구
 * 
 * 로그 레벨 체계:
 * - DEBUG: 개발 시 상세한 실행 흐름 추적용
 * - INFO: 일반적인 정보성 메시지 (정상 동작 기록)
 * - WARNING: 문제가 될 수 있는 상황 경고
 * - ERROR: 실제 오류 발생 시 중요한 문제 기록
 * 
 * 로깅 전략:
 * - 이중 출력: 콘솔과 파일에 동시 기록
 * - 타임스탬프: 각 로그에 시간 정보 포함
 * - 레벨 필터링: 설정한 레벨 이상만 출력
 * - 버퍼 플러시: 즉시 파일에 기록하여 데이터 손실 방지
 * 
 * 사용 시기:
 * - 복잡한 비즈니스 로직의 실행 흐름 추적
 * - 프로덕션 환경에서 문제 발생 원인 분석
 * - 성능 모니터링 및 시스템 상태 기록
 * - 사용자 행동 패턴 분석 및 통계 수집
 * 
 * 디버깅 기법:
 * - 조건부 컴파일: _DEBUG 매크로로 디버그 코드 분리
 * - assert 사용: 프로그램 가정 검증으로 논리 오류 조기 발견
 * - 단계별 로깅: 함수 진입/종료, 변수 값 변화 추적
 * - 예외 상황 기록: 오류 발생 시 상세한 컨텍스트 정보 저장
 * 
 * 장점:
 * - 문제 발생 시 신속한 원인 파악 가능
 * - 프로덕션 환경에서 실시간 모니터링
 * - 개발 단계에서 논리 오류 조기 발견
 * - 시스템 동작 패턴 분석으로 최적화 방향 제시
 * 
 * 성능 고려사항:
 * - 로그 레벨로 불필요한 메시지 필터링
 * - 파일 I/O 비용 최소화 (버퍼링, 비동기 처리)
 * - 디버그 코드는 릴리즈 빌드에서 제외
 * - 로그 파일 크기 관리 (로테이션, 압축)
 * 
 * 관련 개념:
 * - 정적 멤버: 클래스 레벨에서 공유되는 로거 인스턴스
 * - RAII: 로그 파일 자동 닫기로 리소스 누수 방지
 * - 매크로 프로그래밍: 조건부 컴파일로 코드 최적화
 * - 예외 처리: 로깅과 예외의 연계로 문제 상황 완전 추적
 * 
 * 주의사항:
 * - 과도한 로깅은 성능 저하 원인
 * - 민감한 정보(비밀번호 등)는 로그에 기록 금지
 * - 로그 파일 크기 증가로 인한 디스크 공간 관리 필요
 * - 멀티스레드 환경에서는 스레드 안전성 고려
 */

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <cassert>
#include <sstream>
using namespace std;

enum class LogLevel {
    DEBUG,
    INFO,
    WARNING,
    ERROR
};

class Logger {
private:
    static ofstream logFile;
    static LogLevel currentLevel;

    static string getCurrentTime() {
        auto now = chrono::system_clock::now();
        auto time_t = chrono::system_clock::to_time_t(now);
        auto tm = *localtime(&time_t);

        stringstream ss;
        ss << "[" << tm.tm_hour << ":" << tm.tm_min << ":" << tm.tm_sec << "]";
        return ss.str();
    }

    static string levelToString(LogLevel level) {
        switch (level) {
            case LogLevel::DEBUG: return "DEBUG";
            case LogLevel::INFO: return "INFO";
            case LogLevel::WARNING: return "WARNING";
            case LogLevel::ERROR: return "ERROR";
            default: return "UNKNOWN";
        }
    }

public:
    static void initialize(const string& filename, LogLevel level = LogLevel::INFO) {
        logFile.open(filename, ios::app);
        currentLevel = level;
        log(LogLevel::INFO, "로그 시스템 초기화");
    }

    static void log(LogLevel level, const string& message) {
        if (level < currentLevel) return;

        string logMessage = getCurrentTime() + " [" + levelToString(level) + "] " + message;

        cout << logMessage << endl;  // 콘솔 출력
        if (logFile.is_open()) {
            logFile << logMessage << endl;  // 파일 출력
            logFile.flush();
        }
    }

    static void debug(const string& message) { log(LogLevel::DEBUG, message); }
    static void info(const string& message) { log(LogLevel::INFO, message); }
    static void warning(const string& message) { log(LogLevel::WARNING, message); }
    static void error(const string& message) { log(LogLevel::ERROR, message); }

    static void close() {
        log(LogLevel::INFO, "로그 시스템 종료");
        if (logFile.is_open()) {
            logFile.close();
        }
    }
};

// 정적 멤버 초기화
ofstream Logger::logFile;
LogLevel Logger::currentLevel = LogLevel::INFO;

// 디버깅용 매크로
#ifdef _DEBUG
    #define DEBUG_LOG(msg) Logger::debug(msg)
    #define ASSERT_MSG(condition, msg) assert((condition) && (msg))
#else
    #define DEBUG_LOG(msg)
    #define ASSERT_MSG(condition, msg)
#endif

class Calculator {
private:
    double lastResult;

public:
    Calculator() : lastResult(0) {
        Logger::info("Calculator 객체 생성");
    }

    double add(double a, double b) {
        DEBUG_LOG("덧셈 연산: " + to_string(a) + " + " + to_string(b));

        lastResult = a + b;
        Logger::info("덧셈 완료: " + to_string(lastResult));
        return lastResult;
    }

    double divide(double a, double b) {
        DEBUG_LOG("나눗셈 연산: " + to_string(a) + " / " + to_string(b));

        if (b == 0) {
            Logger::error("0으로 나누기 시도!");
            throw invalid_argument("0으로 나눌 수 없습니다.");
        }

        // assert를 사용한 조건 검사
        ASSERT_MSG(b != 0, "나누는 수가 0이 아니어야 합니다");

        lastResult = a / b;
        Logger::info("나눗셈 완료: " + to_string(lastResult));
        return lastResult;
    }

    double getLastResult() const {
        DEBUG_LOG("마지막 결과 조회: " + to_string(lastResult));
        return lastResult;
    }

    ~Calculator() {
        Logger::info("Calculator 객체 소멸");
    }
};

int main() {
    // 로그 시스템 초기화
    Logger::initialize("app.log", LogLevel::DEBUG);

    cout << "=== 디버깅과 로깅 시스템 ===" << endl;

    try {
        Calculator calc;

        Logger::info("프로그램 시작");

        double result1 = calc.add(10, 5);
        Logger::info("첫 번째 계산 결과: " + to_string(result1));

        double result2 = calc.divide(20, 4);
        Logger::info("두 번째 계산 결과: " + to_string(result2));

        // 경고 상황
        Logger::warning("0으로 나누기를 시도합니다.");

        // 오류 발생 시뮬레이션
        double result3 = calc.divide(10, 0);  // 예외 발생

    }
    catch (const exception& e) {
        Logger::error("예외 발생: " + string(e.what()));
        cout << "프로그램에서 오류가 발생했지만 로그에 기록되었습니다." << endl;
    }

    // 디버그 정보
    DEBUG_LOG("메인 함수 종료 준비");

    Logger::info("프로그램 정상 종료");
    Logger::close();

    cout << "\n로그가 'app.log' 파일에 저장되었습니다." << endl;

    return 0;
}