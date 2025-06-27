/*
 * 파일명: 06_file_io_exception.cpp
 * 
 * 주제: 파일 I/O와 예외 (File I/O & Exception)
 * 정의: 파일 작업 시 발생할 수 있는 예외를 안전하게 처리
 * 
 * 핵심 개념:
 * - 파일 스트림 예외: 파일 열기, 읽기, 쓰기 중 발생하는 오류들
 * - 상태 확인: is_open(), fail(), bad(), eof() 등으로 파일 상태 검사
 * - RAII 파일 관리: 파일 핸들을 RAII 객체로 감싸서 자동 닫기 보장
 * - 예외 전파: 하위 함수의 예외를 상위로 안전하게 전달
 * 
 * 파일 스트림 상태:
 * - good(): 모든 상태가 정상
 * - eof(): 파일 끝에 도달
 * - fail(): 논리적 오류 (형식 오류 등)
 * - bad(): 물리적 오류 (하드웨어 문제 등)
 * 
 * 파일 예외 종류:
 * - 파일 열기 실패: 권한 없음, 파일 없음, 디스크 공간 부족
 * - 읽기 실패: 파일 손상, 네트워크 오류, 하드웨어 문제
 * - 쓰기 실패: 디스크 가득참, 읽기 전용 파일, 권한 부족
 * - 파일 시스템 오류: 디렉토리 없음, 잘못된 경로
 * 
 * 사용 시기:
 * - 파일 시스템과 상호작용하는 모든 작업
 * - 설정 파일, 로그 파일, 데이터 파일 처리
 * - 네트워크 드라이브나 외부 저장소 접근
 * - 사용자가 제공한 파일 경로 처리
 * 
 * 안전한 파일 처리 패턴:
 * - 파일 열기 후 즉시 상태 확인
 * - 읽기/쓰기 후 오류 상태 검사
 * - RAII로 파일 자동 닫기 보장
 * - 의미있는 예외 메시지 제공
 * 
 * 장점:
 * - 파일 작업 실패를 안전하게 처리
 * - 리소스 누수 방지 (열린 파일 핸들)
 * - 사용자에게 명확한 오류 정보 제공
 * - 프로그램 안정성 향상
 * 
 * 관련 개념:
 * - 파일 스트림: ifstream, ofstream, fstream
 * - 바이너리 vs 텍스트 모드
 * - 파일 시스템 API: filesystem 라이브러리 (C++17)
 * - 에러 코드 vs 예외: 각각의 장단점
 * 
 * 주의사항:
 * - 파일 경로에 특수 문자나 유니코드 주의
 * - 대용량 파일 처리 시 메모리 사용량 고려
 * - 멀티스레드 환경에서 파일 접근 동기화
 * - 임시 파일 처리 시 정리 책임 명확화
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
using namespace std;

class FileManager {
public:
    static void writeFile(const string& filename, const vector<string>& lines) {
        ofstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("파일을 생성할 수 없습니다: " + filename);
        }

        for (const auto& line : lines) {
            file << line << endl;
            if (file.fail()) {
                throw runtime_error("파일 쓰기 중 오류가 발생했습니다.");
            }
        }

        cout << "파일 쓰기 완료: " << filename << endl;
    }

    static vector<string> readFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("파일을 열 수 없습니다: " + filename);
        }

        vector<string> lines;
        string line;

        while (getline(file, line)) {
            lines.push_back(line);
        }

        if (file.bad()) {
            throw runtime_error("파일 읽기 중 오류가 발생했습니다.");
        }

        cout << "파일 읽기 완료: " << filename << " (" << lines.size() << "줄)" << endl;
        return lines;
    }

    static void copyFile(const string& source, const string& destination) {
        try {
            auto content = readFile(source);
            writeFile(destination, content);
            cout << "파일 복사 완료: " << source << " -> " << destination << endl;
        }
        catch (const exception& e) {
            throw runtime_error("파일 복사 실패: " + string(e.what()));
        }
    }
};

// RAII를 사용한 안전한 파일 클래스
class SafeFile {
private:
    fstream file;
    string filename;

public:
    SafeFile(const string& fname, ios::openmode mode) : filename(fname) {
        file.open(filename, mode);
        if (!file.is_open()) {
            throw runtime_error("파일 열기 실패: " + filename);
        }
        cout << "파일 열기: " << filename << endl;
    }

    ~SafeFile() {
        if (file.is_open()) {
            file.close();
            cout << "파일 닫기: " << filename << endl;
        }
    }

    void writeLine(const string& line) {
        file << line << endl;
        if (file.fail()) {
            throw runtime_error("쓰기 오류: " + filename);
        }
    }

    string readLine() {
        string line;
        if (!getline(file, line)) {
            if (file.eof()) {
                throw runtime_error("파일 끝에 도달했습니다.");
            } else {
                throw runtime_error("읽기 오류: " + filename);
            }
        }
        return line;
    }
};

int main() {
    cout << "=== 파일 I/O 예외 처리 ===" << endl;

    // 1. 기본 파일 작업
    try {
        vector<string> testData = {
            "첫 번째 줄",
            "두 번째 줄",
            "세 번째 줄"
        };

        FileManager::writeFile("test.txt", testData);
        auto readData = FileManager::readFile("test.txt");

        cout << "읽은 내용:" << endl;
        for (const auto& line : readData) {
            cout << "  " << line << endl;
        }

    }
    catch (const exception& e) {
        cout << "파일 작업 오류: " << e.what() << endl;
    }

    // 2. 존재하지 않는 파일 읽기
    try {
        FileManager::readFile("nonexistent.txt");
    }
    catch (const exception& e) {
        cout << "예상된 오류: " << e.what() << endl;
    }

    // 3. 파일 복사
    try {
        FileManager::copyFile("test.txt", "backup.txt");
    }
    catch (const exception& e) {
        cout << "복사 오류: " << e.what() << endl;
    }

    // 4. RAII 파일 클래스 사용
    cout << "\n=== RAII 파일 클래스 ===" << endl;
    try {
        {
            SafeFile outFile("safe_test.txt", ios::out);
            outFile.writeLine("RAII로 안전하게 관리되는 파일");
            outFile.writeLine("예외가 발생해도 파일이 닫힙니다");
            // 강제 예외 발생
            // throw runtime_error("테스트 예외");
        } // 여기서 SafeFile 소멸자가 자동으로 파일을 닫음

        SafeFile inFile("safe_test.txt", ios::in);
        cout << "읽은 줄: " << inFile.readLine() << endl;
        cout << "읽은 줄: " << inFile.readLine() << endl;

    }
    catch (const exception& e) {
        cout << "RAII 파일 오류: " << e.what() << endl;
    }

    return 0;
}