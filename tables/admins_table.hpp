struct [[eosio::table, eosio::contract("areaxdrop")]] admin{
    name admin;
    name group;
    bool is_active = true;
    uint64_t primary_key() const { return group.value; }
};
typedef multi_index<"admins"_n, admin> admins_table;