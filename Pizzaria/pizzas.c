#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "pizzas.h"

void cadastrarPizza(sqlite3 *db) {
    char sabor[50], tamanho[20], ingredientes[200];
    float preco;
    
    printf("\n--- Cadastro de Pizza ---\n");
    printf("Sabor: ");
    scanf(" %[^\n]", sabor);
    printf("Tamanho: ");
    scanf(" %[^\n]", tamanho);
    printf("Preço: ");
    scanf("%f", &preco);
    printf("Ingredientes: ");
    scanf(" %[^\n]", ingredientes);
    
    char sql[500];
    sprintf(sql, "INSERT INTO Pizzas (sabor, tamanho, preco, ingredientes) VALUES ('%s', '%s', %.2f, '%s');", 
            sabor, tamanho, preco, ingredientes);
    
    char *err_msg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao cadastrar pizza: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("Pizza cadastrada com sucesso!\n");
    }
}

void listarPizzas(sqlite3 *db) {
    printf("\n--- Pizzas Cadastradas ---\n");
    
    const char *sql = "SELECT * FROM Pizzas;";
    
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao preparar consulta: %s\n", sqlite3_errmsg(db));
        return;
    }
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        printf("ID: %d\n", sqlite3_column_int(stmt, 0));
        printf("Sabor: %s\n", sqlite3_column_text(stmt, 1));
        printf("Tamanho: %s\n", sqlite3_column_text(stmt, 2));
        printf("Preço: R$ %.2f\n", sqlite3_column_double(stmt, 3));
        printf("Ingredientes: %s\n", sqlite3_column_text(stmt, 4));
        printf("----------------------------\n");
    }
    
    sqlite3_finalize(stmt);
}
