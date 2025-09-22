#ifndef PIZZAS_H
#define PIZZAS_H

#include <sqlite3.h>

void cadastrarPizza(sqlite3 *db);
void listarPizzas(sqlite3 *db);

#endif
