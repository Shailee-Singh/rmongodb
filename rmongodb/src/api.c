#include <R.h>
#include <R_ext/Rdynload.h>
#include <R_ext/Visibility.h>

#include "symbols.h"
#include "api_bson.h"
#include "api_mongo.h"

int sock_init();

static const R_CallMethodDef callMethods[] = {
    { ".mongo.create", (DL_FUNC) mongo_create, 0 },
    { ".mongo.connect", (DL_FUNC) rmongo_connect, 1 },
    { ".mongo.get.socket", (DL_FUNC) mongo_get_socket, 1 },
    { ".mongo.is.connected", (DL_FUNC) mongo_is_connected, 1 },
    { ".mongo.get.err", (DL_FUNC) mongo_get_err, 1 },
    { ".mongo.get.server.err", (DL_FUNC) mongo_get_server_err, 1 },
    { ".mongo.get.server.err.string", (DL_FUNC) mongo_get_server_err_string, 1 },

    { ".mongo.bson.empty", (DL_FUNC) mongo_bson_empty, 0},
    { ".mongo.bson.clear", (DL_FUNC) mongo_bson_clear, 1},
    { ".mongo.bson.copy", (DL_FUNC) mongo_bson_copy, 1},
    { ".mongo.bson.size", (DL_FUNC) mongo_bson_size, 1},
    { ".mongo.bson.print", (DL_FUNC) mongo_bson_print, 1},
    { ".mongo.bson.to.list", (DL_FUNC) mongo_bson_to_list, 1},

    { ".mongo.bson.iterator.create", (DL_FUNC) mongo_bson_iterator_create, 1},
    { ".mongo.bson.find", (DL_FUNC) mongo_bson_find, 3},
    { ".mongo.bson.iterator.more", (DL_FUNC) mongo_bson_iterator_more, 1},
    { ".mongo.bson.iterator.next", (DL_FUNC) mongo_bson_iterator_next, 1},
    { ".mongo.bson.iterator.key", (DL_FUNC) mongo_bson_iterator_key, 1},
    { ".mongo.bson.iterator.type", (DL_FUNC) mongo_bson_iterator_type, 1},
    { ".mongo.bson.iterator.value", (DL_FUNC) mongo_bson_iterator_value, 1},

    { ".mongo.oid.create", (DL_FUNC) mongo_oid_create, 0},
    { ".mongo.oid.time", (DL_FUNC) mongo_oid_time, 1},
    { ".mongo.oid.from.string", (DL_FUNC) mongo_oid_from_string, 1},
    { ".mongo.string.from.oid", (DL_FUNC) mongo_string_from_oid, 1},
    { ".mongo.oid.print", (DL_FUNC) mongo_oid_print, 1},

    { ".mongo.timestamp.create", (DL_FUNC) mongo_timestamp_create, 2},
    { ".mongo.code.create", (DL_FUNC) mongo_code_create, 1},
    { ".mongo.code.w.scope.create", (DL_FUNC) mongo_code_w_scope_create, 2},
    { ".mongo.symbol.create", (DL_FUNC) mongo_symbol_create, 1},
    { ".mongo.undefined.create", (DL_FUNC) mongo_undefined_create, 0},

    { ".mongo.bson.buffer.create", (DL_FUNC) mongo_bson_buffer_create, 0},
    { ".mongo.bson.from.buffer", (DL_FUNC) mongo_bson_from_buffer, 1},
    { ".mongo.bson.buffer.append.int", (DL_FUNC) mongo_bson_buffer_append_int, 3},
    { ".mongo.bson.buffer.append.bool", (DL_FUNC) mongo_bson_buffer_append_bool, 3},
    { ".mongo.bson.buffer.append.long", (DL_FUNC) mongo_bson_buffer_append_long, 3},
    { ".mongo.bson.buffer.append.double", (DL_FUNC) mongo_bson_buffer_append_double, 3},
    { ".mongo.bson.buffer.append.complex", (DL_FUNC) mongo_bson_buffer_append_complex, 3},
    { ".mongo.bson.buffer.append.null", (DL_FUNC) mongo_bson_buffer_append_null, 2},
    { ".mongo.bson.buffer.append.undefined", (DL_FUNC) mongo_bson_buffer_append_undefined, 2},
    { ".mongo.bson.buffer.append.time", (DL_FUNC) mongo_bson_buffer_append_time, 3},
    { ".mongo.bson.buffer.append.timestamp", (DL_FUNC) mongo_bson_buffer_append_timestamp, 3},
    { ".mongo.bson.buffer.append.string", (DL_FUNC) mongo_bson_buffer_append_string, 3},
    { ".mongo.bson.buffer.append.code", (DL_FUNC) mongo_bson_buffer_append_code, 3},
    { ".mongo.bson.buffer.append.code.w.scope", (DL_FUNC) mongo_bson_buffer_append_code_w_scope, 3},
    { ".mongo.bson.buffer.append.symbol", (DL_FUNC) mongo_bson_buffer_append_symbol, 3},
    { ".mongo.bson.buffer.append.oid", (DL_FUNC) mongo_bson_buffer_append_oid, 3},
    { ".mongo.bson.buffer.append.bson", (DL_FUNC) mongo_bson_buffer_append_bson, 3},
    { ".mongo.bson.buffer.append.element", (DL_FUNC) mongo_bson_buffer_append_element, 3},
    { ".mongo.bson.buffer.append", (DL_FUNC) mongo_bson_buffer_append, 3},
    { ".mongo.bson.buffer.start.object", (DL_FUNC) mongo_bson_buffer_start_object, 2},
    { ".mongo.bson.buffer.start.array", (DL_FUNC) mongo_bson_buffer_start_array, 2},
    { ".mongo.bson.buffer.finish.object", (DL_FUNC) mongo_bson_buffer_finish_object, 1},

    { ".mongo.insert", (DL_FUNC) rmongo_insert, 3 },
    { ".mongo.update", (DL_FUNC) rmongo_update, 5 },
    { ".mongo.remove", (DL_FUNC) rmongo_remove, 3 },
    { ".mongo.find.one", (DL_FUNC) rmongo_find_one, 4 },
    { ".mongo.find", (DL_FUNC) rmongo_find, 7 },
    { ".mongo.cursor.next", (DL_FUNC) rmongo_cursor_next, 1 },
    { ".mongo.cursor.value", (DL_FUNC) mongo_cursor_value, 1 },
    { ".mongo.cursor.destroy", (DL_FUNC) rmongo_cursor_destroy, 1 },
    { ".mongo.index.create", (DL_FUNC) mongo_index_create, 4 },
    { ".mongo.count", (DL_FUNC) rmongo_count, 3 },
    { ".mongo.command", (DL_FUNC) mongo_command, 3 },
    { ".mongo.simple.command", (DL_FUNC) mongo_simple_command, 4 },
    { ".mongo.drop.database", (DL_FUNC) mongo_drop_database, 2 },
    { ".mongo.drop.collection", (DL_FUNC) mongo_drop_collection, 2 },
    { ".mongo.reset.error", (DL_FUNC) mongo_reset_error, 2 },
    { ".mongo.get.last.error", (DL_FUNC) mongo_get_last_error, 2 },
    { ".mongo.get.prev.error", (DL_FUNC) mongo_get_prev_error, 2 },
    { ".mongo.is.master", (DL_FUNC) mongo_get_prev_error, 2 },
    { ".mongo.add.user", (DL_FUNC) mongo_add_user, 4 },

    { NULL, NULL, 0 }
};


static void* _malloc(size_t size) {
    return (void*)Calloc(size, char);
}


static void* _realloc(void* p, size_t size) {
    return (void*)Realloc(p, size, char);
}


static void _free(void* p) {
    Free(p);
}

static void _err_handler(const char* errmsg) {
    error(errmsg);
}


void attribute_visible R_init_rmongo(DllInfo *dll) {
    R_registerRoutines(dll, NULL, callMethods, NULL, NULL);

    sock_init();
	install_mongo_symbols();
    bson_set_malloc(_malloc);
    bson_set_realloc(_realloc);
    bson_set_free(_free);
    bson_set_printf((printf_func)Rprintf);
    bson_set_errprintf((printf_func)Rprintf);
    set_bson_err_handler(_err_handler);

    Rprintf("rmongodb package (mongo-r-driver) loaded\n");
}