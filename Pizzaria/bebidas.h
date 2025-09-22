#ifndef BEBIDAS_H
#define BEBIDAS_H

#include <sqlite3.h>

void cadastrarBebida(sqlite3 *db);
void listarBebidas(sqlite3 *db);

#endif
