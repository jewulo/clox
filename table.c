//
// Created by jewul on 24/02/2024.
//

#include <stdlib.h>
#include <string.h>

#include "memory.h"
#include "object.h"
#include "table.h"
#include "value.h"


void initTable(Table *table) {
    table->count = 0;
    table->capacity = 0;
    table->entries = NULL;
}

void freeTable(Table* table) {
    FREE_ARRAY(Entry, table->entries, table->capacity);
    initTable(table);
}

// this algorithm is confusing
static Entry* findEntry(Entry *entries, int capacity, ObjString* key) {
    //uint32_t index = key->hash % capacity;        // modulo % is slow as FUCK. See Page 587-588
    uint32_t index = key->hash & (capacity - 1);    // Bit masking is faster and can get us the same result. See Page 588
    Entry* tombstone = NULL;

    for (;;) {
        Entry* entry = &entries[index];
        if (entry->key == NULL) {
            if (IS_NIL(entry->value)) {
                // Empty entry.
                return tombstone != NULL ? tombstone : entry;
            } else {
                // We found a tombstone.
                if (tombstone == NULL) tombstone = entry;
            }
        } else if (entry->key == key) {
            // We found a key.
            return entry;
        }

        // index = (index + 1) % capacity;      // modulo % is slow as FUCK. See Page 587-588
        index = (index + 1) & (capacity - 1);   // Bit masking is faster and can get us the same result. See Page 588
    }
}

bool tableGet(Table* table, ObjString* key, Value* value) {
    if (table->count == 0) return false;

    Entry* entry = findEntry(table->entries, table->capacity, key);
    if (entry->key == NULL) return false;

    *value = entry->value;
    return true;
}

static void adjustCapacity(Table* table, int capacity) {
    Entry* entries = ALLOCATE(Entry, capacity);
    for (int i = 0; i < capacity; i++) {
        entries[i].key = NULL;
        entries[i].value = NIL_VAL;
    }

    table->count = 0;
    for (int i = 0; i < table->capacity; i++) {
        // Entry* entry = from->entries[i]; // error: incompatible types when initializing type 'Entry *' using type 'Entry'
        Entry* entry = &table->entries[i];  // the array-index returns type Entry, the & gives the address of the Entry
        if (entry->key == NULL) continue;
        Entry* dest = findEntry(entries, capacity, entry->key);
        dest->key = entry->key;
        dest->value = entry->value;
        table->count++;
    }

    FREE_ARRAY(Entry, table->entries, table->capacity);
    table->entries = entries;
    table->capacity = capacity;
}

bool tableSet(Table* table, ObjString* key, Value value) {
    if (table->count + 1 > table->capacity * TABLE_MAX_LOAD) {
        int capacity = GROW_CAPACITY(table->capacity);
        adjustCapacity(table, capacity);
    }

    Entry* entry = findEntry(table->entries, table->capacity, key);
    bool isNewKey = (entry->key == NULL);
    if (isNewKey && IS_NIL(entry->value)) table->count++;

    entry->key = key;
    entry->value = value;
    return isNewKey;
}

bool tableDelete(Table* table, ObjString* key) {
    if (table->count == 0) return false;    // nothing to delete

    // Find the entry.
    Entry* entry = findEntry(table->entries, table->capacity, key);

    // ... otherwise, we found it
    // So, place a tombstone in the entry.
    // In clox we use a NULL key and a true value to denote an Entry tombstone.
    entry->key = NULL;
    entry->value = BOOL_VAL(true);
    return true;
}

void tableAddAll(Table* from, Table* to) {
    for (int i = 0; i < from->capacity; i++) {
        // Entry* entry = from->entries[i]; // error: incompatible types when initializing type 'Entry *' using type 'Entry'
        Entry* entry = &from->entries[i];   // the array-index returns type Entry, the & gives the address of the Entry

        if (entry->key != NULL) {
            tableSet(to, entry->key, entry->value);
        }
    }
}

ObjString *tableFindString(Table *table, const char *chars, int length, uint32_t hash) {
    if (table->count == 0) return NULL;

    // uint32_t index = hash % table->capacity;     // modulo % is slow as FUCK. See Page 589
    uint32_t index = hash & (table->capacity - 1);  // Bit masking is faster and can get us the same result. See Page 589
    for (;;) {
        Entry* entry = &table->entries[index];
        if (entry->key == NULL) {
            // Stop if we find an empty non-tombstone entry.
            if (IS_NIL(entry->value)) return NULL;
        } else if (entry->key->length == length
                && entry->key->hash == hash
                && memcmp(entry->key->chars, chars, length) == 0) {
            // We found it
            return entry->key;
        }

        // index = (index + 1) % table->capacity;       // modulo % is slow as FUCK. See Page 589
        index = (index + 1) & (table->capacity - 1);    // Bit masking is faster and can get us the same result. See Page 589
    }
}

void tableRemoveWhite(Table* table) {
    for (int i = 0; i < table->capacity; i++) {
        Entry* entry = &table->entries[i];
        if (entry->key != NULL && !entry->key->obj.isMarked) {
            tableDelete(table, entry->key);
        }
    }
}

void markTable(Table *table) {
    for (int i = 0; i < table->capacity; i++) {
        Entry* entry = &table->entries[i];
        markObject((Obj*)entry->key);
        markValue(entry->value);
    }
}
