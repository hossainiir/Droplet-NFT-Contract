struct [[eosio::table,eosio::contract("areaxdrop")]] token {
  symbol symbol;
  name contract;
  uint64_t primary_key() const { return symbol.code().raw(); }
};
typedef multi_index<name("tokens"), token> tokens_table;