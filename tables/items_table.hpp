//scope: setId
struct [[eosio::table, eosio::contract("areaxdrop")]] item{
  uint64_t serial;
  uint64_t next_claim;
  asset    last_prize;
  asset    total;
  double   last_random;
  uint64_t primary_key() const { return serial; }
};
typedef multi_index<"items"_n, item> items_table;