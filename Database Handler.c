/* Database Handler for Chat Logs */
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>

sqlite3 *db;

void init_db() {
    if (sqlite3_open("chat_logs.db", &db)) {
        printf("Error opening database: %s\n", sqlite3_errmsg(db));
        exit(1);
    }
    char *query = "CREATE TABLE IF NOT EXISTS messages (id INTEGER PRIMARY KEY, user TEXT, message TEXT, timestamp DATETIME DEFAULT CURRENT_TIMESTAMP);";
    sqlite3_exec(db, query, 0, 0, 0);
}

void log_message(const char *user, const char *message) {
    char query[512];
    snprintf(query, sizeof(query), "INSERT INTO messages (user, message) VALUES ('%s', '%s');", user, message);
    sqlite3_exec(db, query, 0, 0, 0);
    printf("Message logged successfully!\n");
}

void display_logs() {
    char *query = "SELECT * FROM messages;";
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, query, -1, &stmt, 0);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        printf("ID: %d | User: %s | Message: %s | Timestamp: %s\n",
            sqlite3_column_int(stmt, 0),
            sqlite3_column_text(stmt, 1),
            sqlite3_column_text(stmt, 2),
            sqlite3_column_text(stmt, 3));
    }
    sqlite3_finalize(stmt);
}

int main() {
    init_db();
    log_message("User1", "Hello, how are you?");
    log_message("User2", "I'm good, thanks for asking!");
    printf("Chat Logs:\n");
    display_logs();
    sqlite3_close(db);
    return 0;
}
