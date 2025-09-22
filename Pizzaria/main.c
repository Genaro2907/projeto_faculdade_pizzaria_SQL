#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include "database.h"
#include "pizzas.h"
#include "bebidas.h"
#include "pedidos.h"

void menuPizzas(sqlite3 *db) {
    int opcao;
    do {
        printf("\n=== MENU PIZZAS ===\n");
        printf("1. Cadastrar Pizza\n");
        printf("2. Listar Pizzas\n");
        printf("3. Excluir Pizza\n");
        printf("0. Voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: cadastrarPizza(db); break;
            case 2: listarPizzas(db); break;
            case 3: excluirPizza(db); break;
            case 0: break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}

void menuBebidas(sqlite3 *db) {
    int opcao;
    do {
        printf("\n=== MENU BEBIDAS ===\n");
        printf("1. Cadastrar Bebida\n");
        printf("2. Listar Bebidas\n");
        printf("3. Excluir Bebida\n");
        printf("0. Voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: cadastrarBebida(db); break;
            case 2: listarBebidas(db); break;
            case 3: excluirBebida(db); break;
            case 0: break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}

void menuPedidos(sqlite3 *db) {
    int opcao;
    do {
        printf("\n=== MENU PEDIDOS ===\n");
        printf("1. Realizar Pedido\n");
        printf("2. Listar Pedidos\n");
        printf("3. Excluir Pedido\n");
        printf("0. Voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: realizarPedido(db); break;
            case 2: listarPedidos(db); break;
            case 3: excluirPedido(db); break;
            case 0: break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}

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
        printf("1. Pizzas\n");
        printf("2. Bebidas\n");
        printf("3. Pedidos\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: menuPizzas(db); break;
            case 2: menuBebidas(db); break;
            case 3: menuPedidos(db); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
    
    sqlite3_close(db);
    return 0;
}

