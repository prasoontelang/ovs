#ifndef OVSDB_PROVIDER_H
#define OVSDB_PROVIDER_H

#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>

#include "ovsdb.h"
#include "ovsdb-intf.h"
#include "openvswitch/json.h"
#include "transaction.h"
#include "util.h"

typedef struct _DB_INTERFACE_CONTEXT_T {
    /**
     * @brief the OVSDB implementation of the database that contains the tables,
     * rows, data of the storage.
     */
    struct ovsdb *db;
    /**
     * @brief a structure of ovsdb_servers which are a map of DB names to DB
     * objects, locks in use in the servers, uuid of the server, list of
     * completed triggers, and map of waiters by lock name
     */
    struct ovsdb_session *session;
    /** @brief if the state of the database is read only */
    bool read_only;
} DB_INTERFACE_CONTEXT_T;

uint32_t
ovsdb_open_context(DB_INTERFACE_CONTEXT_T **ppContext, ...);

uint32_t
ovsdb_close_context(DB_INTERFACE_CONTEXT_T *pContext);

struct ovsdb_txn *
ovsdb_execute_compose_intf(
    PDB_INTERFACE_CONTEXT_T pContext,
    const struct json *params,
    const char *role,
    const char *id,
    long long int elapsed_msec,
    long long int *timeout_msec,
    bool *durable,
    struct json **resultsp
);

struct ovsdb_txn_progress *
ovsdb_txn_propose_commit_intf(
    PDB_INTERFACE_CONTEXT_T pContext,
    struct ovsdb_txn *txn,
    bool durable
);

bool ovsdb_txn_progress_is_complete_intf(PDB_INTERFACE_CONTEXT_T pContext,
    const struct ovsdb_txn_progress *p);

#endif /* OVSDB_PROVIDER_H */
