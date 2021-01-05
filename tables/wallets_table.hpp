//scope: payer
//ram payer: contract
struct [[eosio::table, eosio::contract("areaxdrop")]] wallet {
  symbol symbol;
  asset balance;
  uint64_t primary_key() const { return symbol.code().raw(); }
};
typedef multi_index<name("wallets"), wallet> wallets_table;