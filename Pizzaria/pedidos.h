#ifndef PEDIDOS_H
#define PEDIDOS_H

#include "sqlite3.h"

// Declarações das funções (apenas assinaturas)
void realizarPedido(sqlite3 *db);
void listarPedidos(sqlite3 *db);

#endif
