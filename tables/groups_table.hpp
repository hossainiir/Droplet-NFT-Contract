struct [[eosio::table]] group {
    string title;
    string description;
    name group_name;
    name manager;
    uint64_t supply;
    uint64_t issued_supply;
    uint64_t supply_cap;
    uint64_t primary_key() const { return group_name.value; }
};
typedef multi_index<name("groups"), group> groups_table;
