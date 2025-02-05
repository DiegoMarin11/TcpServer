#include <stdio.h>
#include <stdlib.h>
#include <bson/bson.h>
#include <mongoc/mongoc.h>
//#include <Interface.h>

#define DB_ADDRESS "mongodb://172.26.80.1:27017/"

// MongoDB global variables
/**/
mongoc_client_t *client;
mongoc_database_t *database;
mongoc_collection_t *collection;

// Initialize MongoDB
void init_mongo() {
    mongoc_init();
    client = mongoc_client_new("mongodb://172.26.80.1:27017/");
    if (!client) {
        fprintf(stderr, "Failed to connect to MongoDB.\n");
        exit(EXIT_FAILURE);
    }
    printf("Connection stablished!");
    database = mongoc_client_get_database(client, "arquitecturas");
    collection = mongoc_client_get_collection(client, "arquis", "arqui");
}

// Insert Data
void insert_data(const char *name, const char *description, int response) {
    bson_t *document;
    bson_error_t error;

    document = bson_new();
    BSON_APPEND_UTF8(document, "Name", name);
    BSON_APPEND_UTF8(document, "description", description);

    if (!mongoc_collection_insert_one(collection, document, NULL, NULL, &error)) {
        fprintf(stderr, "Insert failed: %s\n", error.message);
        response = 0;
    } else {
        response = 1;
    }

    bson_destroy(document);
}

// Fetch Data
void fetch_data() {
    if (!client) return;

    bson_t *query = bson_new();
    mongoc_cursor_t *cursor = mongoc_collection_find_with_opts(collection, query, NULL, NULL);
    const bson_t *doc;
    char *str;

    while (mongoc_cursor_next(cursor, &doc)) {
        str = bson_as_canonical_extended_json(doc, NULL);
        printf("%s\n", str);
        bson_free(str);
    }

    bson_destroy(query);
    mongoc_cursor_destroy(cursor);
}

// Cleanup
void close_mongo() {
    if (collection) mongoc_collection_destroy(collection);
    if (database) mongoc_database_destroy(database);
    if (client) mongoc_client_destroy(client);
    mongoc_cleanup();
}