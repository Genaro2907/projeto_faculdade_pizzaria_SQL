#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "pedidos.h"
#include "pizzas.h"
#include "bebidas.h"

void realizarPedido(sqlite3 *db) {
    char cliente[100], data[20];
    int pizza_id, bebida_id, qtd_pizza, qtd_bebida;
    float total = 0;
    
    printf("\n--- Realizar Pedido ---\n");
    printf("Nome do cliente: ");
    scanf(" %[^\n]", cliente);
    printf("Data (DD/MM/AAAA): ");
    scanf(" %[^\n]", data);
    
    listarPizzas(db);
    printf("ID da Pizza (0 para nenhuma): ");
    scanf("%d", &pizza_id);
    if (pizza_id > 0) {
        printf("Quantidade: ");
        scanf("%d", &qtd_pizza);
    } else {
        qtd_pizza = 0;
    }
    
    listarBebidas(db);
    printf("ID da Bebida (0 para nenhuma): ");
    scanf("%d", &bebida_id);
    if (bebida_id > 0) {
        printf("Quantidade: ");
        scanf("%d", &qtd_bebida);
    } else {
        qtd_bebida = 0;
    }
    
    if (pizza_id > 0) {
        char sql[100];
        sprintf(sql, "SELECT preco FROM Pizzas WHERE id = %d;", pizza_id);
        
        sqlite3_stmt *stmt;
        int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
        
        if (rc == SQLITE_OK && sqlite3_step(stmt) == SQLITE_ROW) {
            total += sqlite3_column_double(stmt, 0) * qtd_pizza;
        }
        sqlite3_finalize(stmt);
    }
    
    if (bebida_id > 0) {
        char sql[100];
        sprintf(sql, "SELECT preco FROM Bebidas WHERE id = %d;", bebida_id);
        
        sqlite3_stmt *stmt;
        int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
        
        if (rc == SQLITE_OK && sqlite3_step(stmt) == SQLITE_ROW) {
            total += sqlite3_column_double(stmt, 0) * qtd_bebida;
        }
        sqlite3_finalize(stmt);
    }
    
    char sql[500];
    sprintf(sql, "INSERT INTO Pedidos (cliente, pizza_id, bebida_id, quantidade_pizza, quantidade_bebida, total, data) "
            "VALUES ('%s', %d, %d, %d, %d, %.2f, '%s');", 
            cliente, pizza_id, bebida_id, qtd_pizza, qtd_bebida, total, data);
    
    char *err_msg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao realizar pedido: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("Pedido realizado com sucesso! Total: R$ %.2f\n", total);
    }
}

void listarPedidos(sqlite3 *db) {
    printf("\n--- Pedidos Realizados ---\n");
    
    const char *sql = "SELECT Pedidos.id, Pedidos.cliente, Pizzas.sabor, Bebidas.nome, "
                     "Pedidos.quantidade_pizza, Pedidos.quantidade_bebida, Pedidos.total, Pedidos.data "
                     "FROM Pedidos "
                     "LEFT JOIN Pizzas ON Pedidos.pizza_id = Pizzas.id "
                     "LEFT JOIN Bebidas ON Pedidos.bebida_id = Bebidas.id;";
    
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao preparar consulta: %s\n", sqlite3_errmsg(db));
        return;
    }
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        printf("ID: %d\n", sqlite3_column_int(stmt, 0));
        printf("Cliente: %s\n", sqlite3_column_text(stmt, 1));
        printf("Pizza: %s\n", sqlite3_column_text(stmt, 2) ? (const char*)sqlite3_column_text(stmt, 2) : "Nenhuma");
        printf("Bebida: %s\n", sqlite3_column_text(stmt, 3) ? (const char*)sqlite3_column_text(stmt, 3) : "Nenhuma");
        printf("Qtd Pizza: %d\n", sqlite3_column_int(stmt, 4));
        printf("Qtd Bebida: %d\n", sqlite3_column_int(stmt, 5));
        printf("Total: R$ %.2f\n", sqlite3_column_double(stmt, 6));
        printf("Data: %s\n", sqlite3_column_text(stmt, 7));
        printf("----------------------------\n");
    }
    
    sqlite3_finalize(stmt);
}
