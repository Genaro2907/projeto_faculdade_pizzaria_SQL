#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include "database.h"

void criarTabelas(sqlite3 *db) {
    char *err_msg = 0;
    
    const char *sql_pizzas = "CREATE TABLE IF NOT EXISTS Pizzas ("
                             "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                             "sabor TEXT NOT NULL, "
                             "tamanho TEXT NOT NULL, "
                             "preco REAL NOT NULL, "
                             "ingredientes TEXT);";
    
    const char *sql_bebidas = "CREATE TABLE IF NOT EXISTS Bebidas ("
                              "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                              "nome TEXT NOT NULL, "
                              "tipo TEXT NOT NULL, "
                              "preco REAL NOT NULL, "
                              "tamanho TEXT NOT NULL);";
    
    const char *sql_pedidos = "CREATE TABLE IF NOT EXISTS Pedidos ("
                              "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                              "cliente TEXT NOT NULL, "
                              "pizza_id INTEGER, "
                              "bebida_id INTEGER, "
                              "quantidade_pizza INTEGER, "
                              "quantidade_bebida INTEGER, "
                              "total REAL NOT NULL, "
                              "data TEXT NOT NULL, "
                              "FOREIGN KEY(pizza_id) REFERENCES Pizzas(id), "
                              "FOREIGN KEY(bebida_id) REFERENCES Bebidas(id));";
    
    int rc = sqlite3_exec(db, sql_pizzas, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao criar tabela Pizzas: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
    
    rc = sqlite3_exec(db, sql_bebidas, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao criar tabela Bebidas: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
    
    rc = sqlite3_exec(db, sql_pedidos, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao criar tabela Pedidos: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
}
