#ifndef DB_INTERFACE_H
#define DB_INTERFACE_H

void init_mongo();
void insert_data(const char *name, const char *description, int response);
void fetch_data();
void close_mongo();

#endif