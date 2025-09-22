#define PEDIDOS_H

#include <sqlite3.h>

void realizarPedido(sqlite3 *db);
void listarPedidos(sqlite3 *db);

#endif
