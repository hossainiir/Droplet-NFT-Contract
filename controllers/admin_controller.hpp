class admin_controller{
  public:
    admin_controller(name self){
      s = self;
    }

    void setConfig(name market_contract,name marble_contract){
      require_auth(s);
      
      config_table configs(s,s.value);
      if(!configs.exists()){
        config new_conf = {
          market_contract,
          marble_contract,
        };
        configs.set(new_conf, s);
      }else{
        auto conf = configs.get();
        conf.market_contract = market_contract;
        conf.marble_contract = marble_contract;
        configs.set(conf,s);
      }
    }

    void createDropSet(asset prize,name account,name group,asset price,uint64_t count,string data){
      require_auth(s);
      PayFromWallet(s,account,prize);

      counter_table ctb(market_contract,market_contract.value);
      auto citr = ctb.find("setid"_n.value);
      auto new_set_id = citr->value;

      banks_table bankTb(s,s.value);
      bankTb.emplace(s,[&](auto &_){
        _.set_id = new_set_id;
        _.balance = prize;
      });

      eosio::action(
          permission_level{ s , ACTIVE },
          market_contract, "creatsetcntr"_n,
          std::make_tuple(s,account,group,price,count,data)
      ).send();
    }

    void setDropItem(uint64_t set_id,uint64_t stars,uint8_t cooldown,asset min,asset max,double chance){
      require_auth(s);
      drops_table tb(s,set_id);
      auto itr = tb.find(stars);
      if(itr == tb.end()){
        tb.emplace(s,[&](auto &_){
          _.stars = stars;
          _.cooldown = cooldown;
          _.min = min;
          _.max = max;
          _.chance = chance;
        });
      }else{
        tb.modify(itr,s,[&](auto &_){
          _.cooldown = cooldown;
          _.min = min;
          _.max = max;
          _.chance = chance;
        });
      }
    }

    void addToken(name contract,symbol symbol){
      require_auth(s);

      tokens_table tokens(s, s.value);
      tokens.emplace(s,[&](auto &_){
        _.contract = contract;
        _.symbol = symbol;
      });
    }

    void removeToken(symbol symbol){
      require_auth(s);

      tokens_table tokens(s,s.value);
      auto itr = tokens.find(symbol.code().raw());
      tokens.erase(itr);
    }

  private:
    name s;
};