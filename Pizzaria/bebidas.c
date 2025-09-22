#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"
#include "bebidas.h"

void cadastrarBebida(sqlite3 *db) {
    char nome[50], tipo[20], tamanho[10];
    float preco;
    
    printf("\n--- Cadastro de Bebida ---\n");
    printf("Nome: ");
    scanf(" %[^\n]", nome);
    printf("Tipo: ");
    scanf(" %[^\n]", tipo);
    printf("Tamanho: ");
    scanf(" %[^\n]", tamanho);
    printf("Preço: ");
    scanf("%f", &preco);
    
    char sql[300];
    sprintf(sql, "INSERT INTO Bebidas (nome, tipo, preco, tamanho) VALUES ('%s', '%s', %.2f, '%s');", 
            nome, tipo, preco, tamanho);
    
    char *err_msg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao cadastrar bebida: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("Bebida cadastrada com sucesso!\n");
    }
}

void listarBebidas(sqlite3 *db) {
    printf("\n--- Bebidas Cadastradas ---\n");
    
    const char *sql = "SELECT * FROM Bebidas;";
    
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao preparar consulta: %s\n", sqlite3_errmsg(db));
        return;
    }
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        printf("ID: %d\n", sqlite3_column_int(stmt, 0));
        printf("Nome: %s\n", sqlite3_column_text(stmt, 1));
        printf("Tipo: %s\n", sqlite3_column_text(stmt, 2));
        printf("Preço: R$ %.2f\n", sqlite3_column_double(stmt, 3));
        printf("Tamanho: %s\n", sqlite3_column_text(stmt, 4));
        printf("----------------------------\n");
    }
    
    sqlite3_finalize(stmt);
}
