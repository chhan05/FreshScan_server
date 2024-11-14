#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>

#define HOST "localhost"
#define USER "root"
#define PASS "han*2942"
#define DB "freshscan_product"

int main(void) {
    MYSQL* conn;
    char query[512];

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
    
    // 변수 내용
    const char* table_name = "t100001";
    const char* name = "test";
    const char* expiration_date = "XXXX-XX-XX";

    // INSERT 쿼리 작성
    snprintf(query, sizeof(query),
        "INSERT INTO %s (name, expiration_date) VALUES ('%s', '%s')",
        table_name, name, expiration_date);

    // 쿼리 실행
    if (mysql_query(conn, query)) {
        fprintf(stderr, "쿼리 실패: %s\n", mysql_error(conn));
    }
    else {
        printf("데이터 삽입 성공\n");
    }
    

    // MySQL 연결 닫기
    mysql_close(conn);

    return 0;
}