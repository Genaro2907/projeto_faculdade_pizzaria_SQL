#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"
#include "pizzas.h"
#include "util.h"

void cadastrarPizza(sqlite3 *db) {
    char sabor[50], tamanho[20], ingredientes[200];
    char preco_str[20];
    float preco;
    int i, j;

    printf("\n--- Cadastro de Pizza ---\n");

    printf("Sabor: ");
    limparBuffer();
    scanf(" %[^\n]", sabor);

    printf("Tamanho: ");
    limparBuffer();
    scanf(" %[^\n]", tamanho);

    printf("Preço: ");
    limparBuffer();
    scanf(" %[^\n]", preco_str);

    char preco_clean[20];
    j = 0;
    for (i = 0; preco_str[i]; i++) {
        if ((preco_str[i] >= '0' && preco_str[i] <= '9') ||
            preco_str[i] == ',' || preco_str[i] == '.') {
            preco_clean[j++] = preco_str[i];
        }
    }
    preco_clean[j] = '\0';


    for (i = 0; preco_clean[i]; i++) {
        if (preco_clean[i] == ',') {
            preco_clean[i] = '.';
        }
    }

    preco = atof(preco_clean);

    printf("Ingredientes: ");
    limparBuffer();
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

void excluirPizza(sqlite3 *db) {
    int id;
    listarPizzas(db);
    printf("Digite o ID da pizza que deseja excluir: ");
    scanf("%d", &id);

    char sql[100];
    sprintf(sql, "DELETE FROM Pizzas WHERE id = %d;", id);

    char *err_msg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao excluir pizza: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("Pizza excluída com sucesso!\n");
    }
}
