class common_controller{
  public:
    common_controller(name self){
      s = self;
    }

    void claimRewards(name owner,uint64_t serial,uint64_t set_id){
      require_auth(owner);
      
      marble_items_table mitb(marble_contract,marble_contract.value);
      auto iitr = mitb.find(serial);
      check(iitr != mitb.end(),"item not found");
      check(owner == iitr->owner,"you are not the owner");

      attributes_table atrtb(marble_contract,serial);
      auto atitr = atrtb.find("stars"_n.value);
      auto stars = atitr->points % 1000;
      
      drops_table dtb(s,set_id);
      auto dritr = dtb.find(stars);

      banks_table btb(s,s.value);
      auto bitr = btb.find(set_id);
      check(bitr->balance >= dritr->max,"No more prize");

      items_table itb(s,set_id);
      auto itr = itb.find(serial);
      check(itr != itb.end(),"item not found in set");
      check(itr->next_claim  < now() , "Cooldown time");


      auto r = get_random(owner.value+now()+set_id+stars,10000);
      auto amount = r <= dritr->chance*100 ? dritr->max : dritr->min;

      btb.modify(bitr,s,[&](auto &_){
        _.balance -= amount;
      });

      itb.modify(itr,s,[&](auto &_){
        _.next_claim = now() + dritr->cooldown*3600;
        _.last_prize = amount;
        _.total += amount;
        _.last_random= r/100.0;
      });
      
      TransferToken(s,s,owner,amount,"Reward from item : "+std::to_string(serial));
    }

  private:
    name s;
};