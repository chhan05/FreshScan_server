#include "sqlite3.h"
#include <stdio.h>
#include <stdlib.h>
#pragma comment(lib,"sqlite3.lib")

// 수정
int update_item(const char* db_path, int id, const char* new_name, const char* new_expiration_date, const char* new_purchase_date) {
    sqlite3* db;
    char* err_msg = 0;
    int rc = sqlite3_open(db_path, &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return rc;
    }

    char sql[256];
    snprintf(sql, sizeof(sql),
        "UPDATE items SET name = '%s', expirationDate = '%s', purchaseDate = '%s' WHERE id = %d;",
        new_name, new_expiration_date, new_purchase_date, id);

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
    else {
        printf("Record updated successfully.\n");
    }

    sqlite3_close(db);
    return rc;
}

// 삭제
int delete_item(const char* db_path, int id) {
    sqlite3* db;
    char* err_msg = 0;
    int rc = sqlite3_open(db_path, &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return rc;
    }

    char sql[128];
    snprintf(sql, sizeof(sql), "DELETE FROM items WHERE id = %d;", id);

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
    else {
        printf("Record deleted successfully.\n");
    }

    sqlite3_close(db);
    return rc;
}

// 지우기(테스트용)
int main(void) {
    int answer;
    int id = 1;
    const char db_path, new_name, new_expiration_date, new_purchase_date = ""; // 설정 필요
    scanf_s("%d", &answer);
    if (answer == 0) {
        update_item(db_path, id, new_name, new_expiration_date, new_purchase_date);
    }
    else {
        delete_item(db_path, id);
    }
}