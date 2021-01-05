struct [[eosio::table, eosio::contract("areaxdrop")]] config{
  name market_contract;
  name marble_contract;
};
typedef singleton<name("config"), config> config_table;