struct [[eosio::table]] counter{
    name counter;
    uint64_t value;
    uint64_t primary_key() const { return counter.value; }
};
typedef multi_index<"counter"_n, counter> counter_table;
