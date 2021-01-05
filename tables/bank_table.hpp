struct [[eosio::table, eosio::contract("areaxdrop")]] bank{
  uint64_t set_id;
  asset balance;
  string description;
  uint64_t primary_key() const { return set_id; }
};
typedef multi_index<"banks"_n, bank> banks_table;