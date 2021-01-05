//scope: setId
struct [[eosio::table, eosio::contract("areaxdrop")]] drop{
  uint64_t stars;
  uint8_t cooldown;
  asset min;
  asset max;
  double chance;
  uint64_t primary_key() const { return stars; }
};
typedef multi_index<"drops"_n, drop> drops_table;