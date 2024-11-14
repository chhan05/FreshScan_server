#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>

#define HOST "localhost"
#define USER "root"
#define PASS "han*2942"
#define DB "freshscan"

int main(void) {
    FILE* file;
    MYSQL* conn;
    MYSQL_RES* res;
    MYSQL_ROW row;
    char line[256];
    char query[512];
    char* id, * name, * gender, * age, * client_id, * client_pass;

    // MySQL 초기화 및 연결
    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() 실패\n");
        return EXIT_FAILURE;
    }

    if (mysql_real_connect(conn, HOST, USER, PASS, DB, 3306, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() 실패\n");
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    // 파일 열기
    fopen_s(&file, "test.txt", "r");
    if (file == NULL) {
        printf("파일을 열 수 없습니다.\n");
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    // 파일의 각 줄을 읽어와서 MySQL에 INSERT
    while (fgets(line, sizeof(line), file) != NULL) {
        // 개행 문자 제거
        line[strcspn(line, "\n")] = 0;

        // 콤마(,)로 구분된 필드를 파싱
        id = strtok(line, ",");
        name = strtok(NULL, ",");
        gender = strtok(NULL, ",");
        age = strtok(NULL, ",");
        client_id = strtok(NULL, ",");
        client_pass = strtok(NULL, ",");

        // INSERT 쿼리 작성
        snprintf(query, sizeof(query),
            "INSERT INTO client_table (id, name, gender, age, client_id, client_pass) VALUES ('%s', '%s', '%s', '%s', '%s', '%s')",
            id, name, gender, age, client_id, client_pass);

        // 쿼리 실행
        if (mysql_query(conn, query)) {
            fprintf(stderr, "쿼리 실패: %s\n", mysql_error(conn));
        }
        else {
            printf("데이터 삽입 성공: %s\n", line);
        }
    }

    // 파일과 MySQL 연결 닫기
    fclose(file);
    mysql_close(conn);

    return 0;
}