#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include "database.h"
#include "pizzas.h"
#include "bebidas.h"
#include "pedidos.h"

int main() {
    sqlite3 *db;
    int rc = sqlite3_open("pizzaria.db", &db);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Não foi possível abrir o banco de dados: %s\n", sqlite3_errmsg(db));
        return 1;
    }
    
    printf("Conectado ao banco de dados SQLite com sucesso!\n");
    
    criarTabelas(db);
    
    int opcao;
    
    do {
        printf("\n=== SISTEMA PIZZARIA ===\n");
        printf("1. Cadastrar Pizza\n");
        printf("2. Cadastrar Bebida\n");
        printf("3. Listar Pizzas\n");
        printf("4. Listar Bebidas\n");
        printf("5. Realizar Pedido\n");
        printf("6. Listar Pedidos\n");
        printf("7. Excluir Pizza\n");
        printf("8. Excluir Bebida\n");
        printf("9. Excluir Pedido\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1:
                cadastrarPizza(db);
                break;
            case 2:
                cadastrarBebida(db);
                break;
            case 3:
                listarPizzas(db);
                break;
            case 4:
                listarBebidas(db);
                break;
            case 5:
                realizarPedido(db);
                break;
            case 6:
                listarPedidos(db);
                break;
            case 7:
                excluirPizza(db);
                break;
            case 8:
                excluirBebida(db);
                break;
            case 9:
                excluirPedido(db);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
    
    sqlite3_close(db);
    return 0;
}

