#ifndef PEDIDOS_H
#define PEDIDOS_H

#include "sqlite3.h"

// Declara��es das fun��es (apenas assinaturas)
void realizarPedido(sqlite3 *db);
void listarPedidos(sqlite3 *db);

#endif
