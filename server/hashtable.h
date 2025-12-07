#include <stddef.h>
#include <stdint.h>

// hashtable node, should be embedded inot the payload
struct HNode
{
    HNode *next = NULL;
    uint64_t hcode = 0;
};

// simple fixed-size hashtable
struct HTab
{
    HNode **tab = NULL; // array of slots
    size_t mask = 0;    // power of 2 array size, 2^n -1
    size_t size = 0;    // number of keys;
};

// the real hashtable interface.
// its uses 2 hashtables for progressive hashing.
struct HMap
{
    HTab newer;
    HTab older;
    size_t migrate_pos = 0;
};

HNode *hm_lookup(HMap *hmap, HNode *key, bool (*eq)(HNode *, HNode *));
void hm_insert(HMap *hmap, HNode *node);
HNode *hm_delete(HMap *hmap, HNode *key, bool (*eq)(HNode *, HNode *));
void hm_clear(HMap *hmap);
size_t hm_size(HMap *hmap);

// invoke the callback on each node until it retruns false
void hm_foreach(HMap *hmap, bool (*f)(HNode *, void *), void *arg);