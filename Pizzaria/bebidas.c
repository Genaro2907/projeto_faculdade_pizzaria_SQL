#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"
#include "bebidas.h"
#include "util.h"

void cadastrarBebida(sqlite3 *db) {
    char nome[50], tipo[20], tamanho[10];
    char preco_str[20];
    float preco;
    int i;

    printf("\n--- Cadastro de Bebida ---\n");
    
    printf("Nome: ");
    limparBuffer();
    scanf(" %[^\n]", nome);
    
    printf("Tipo: ");
    limparBuffer();
    scanf(" %[^\n]", tipo);
    
    printf("Tamanho: ");
    limparBuffer();
    scanf(" %[^\n]", tamanho);
    
    printf("Preco: ");
    limparBuffer();
    scanf(" %[^\n]", preco_str);


    for (i = 0; preco_str[i]; i++) {
        if (preco_str[i] == ',') {
            preco_str[i] = '.';
        }
    }

    preco = atof(preco_str);

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

    limparBuffer();
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
        printf("Preco: R$ %.2f\n", sqlite3_column_double(stmt, 3));
        printf("Tamanho: %s\n", sqlite3_column_text(stmt, 4));
        printf("----------------------------\n");
    }
    
    sqlite3_finalize(stmt);
}

void excluirBebida(sqlite3 *db) {
    int id;
    listarBebidas(db);
    printf("Digite o ID da bebida que deseja excluir: ");
    scanf("%d", &id);

    char sql[100];
    sprintf(sql, "DELETE FROM Bebidas WHERE id = %d;", id);

    char *err_msg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao excluir bebida: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("Bebida excluída com sucesso!\n");
    }
}



