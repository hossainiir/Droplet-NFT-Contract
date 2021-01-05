struct [[eosio::table]] marble_item {
    uint64_t serial;
    name group;
    name owner;
    //uint64_t mint; //edition?

    uint64_t primary_key() const { return serial; }
    uint128_t by_group() const { return (uint128_t)10000000000000000 * group.value + serial; }
    uint128_t by_owner() const { return (uint128_t)10000000000000000 * owner.value + serial; }

    // EOSLIB_SERIALIZE(item, (serial)(group)(owner))
};
typedef multi_index<name("items"), marble_item,
    indexed_by<"bygroup"_n, const_mem_fun<marble_item, uint128_t, &marble_item::by_group>>,
    indexed_by<"byowner"_n, const_mem_fun<marble_item, uint128_t, &marble_item::by_owner>>
> marble_items_table;
