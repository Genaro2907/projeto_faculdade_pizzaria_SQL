#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"

int main() {
    sqlite3 *db;
    char *err_msg = 0;
    
    printf("Iniciando sistema de pizzaria...\n");
    
    int rc = sqlite3_open("pizzaria.db", &db);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao abrir banco: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }
    
    printf("? Banco criado/conectado com sucesso!\n");
    
    const char *sql = "CREATE TABLE IF NOT EXISTS Teste (id INTEGER PRIMARY KEY, nome TEXT);";
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro SQL: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }
    
    printf("? Tabela criada com sucesso!\n");
    printf("Pressione qualquer tecla para sair...\n");
    getchar();
    
    sqlite3_close(db);
    return 0;
}
