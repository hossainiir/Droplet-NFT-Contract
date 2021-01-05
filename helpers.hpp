uint32_t now(){return current_time_point().sec_since_epoch();}

bool isGroupTbond(string group){
  const size_t first_break = group.find(".");
  auto str = group.substr(first_break + 1);
  return str == "tbond" || str == "tbonds";
};

string symbolToLowercase(asset quantity){
  auto sym = quantity.symbol.code().to_string();
  transform(sym.begin(), sym.end(), sym.begin(), ::tolower);
  return sym;
}

struct st_transfer {
  name          from;
  name          to;
  asset         quantity;
  std::string   memo;
};

struct st_mintsetitem{
  name account;
  uint64_t setId;
  string assetUrl;
  string title;
};

uint32_t get_random(uint64_t seed,uint32_t to){
  eosio::checksum256 result;
  auto s = now() + seed;
  result = eosio::sha256((char *)&s, sizeof(s));
  s = result.get_array()[1];
  s <<= 32;
  s |= result.get_array()[0];
  return (uint32_t)(s % to);
};