struct [[eosio::table]] marble_config{
  std::string contract_name;
  std::string contract_version;
  name admin;
  uint64_t last_serial;
};
typedef singleton<name("config"), marble_config> marbleconfig_table;