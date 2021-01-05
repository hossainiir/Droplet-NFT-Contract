void PayFromWallet(name s,name account,asset amount){
  wallets_table tb(s,account.value);
  auto itr = tb.find(amount.symbol.code().raw());
  check(itr != tb.end(),"no deposit");
  check(itr->balance >= amount,"not enuogh amount");
  if(itr->balance == amount){
    tb.erase(itr);
  }else{
    tb.modify(itr,s,[&](auto &_){
      _.balance -= amount;
    });
  }
}

void Deposit(name s,name sender,asset quantity){
  wallets_table tb(s,sender.value);
  auto itr = tb.find(quantity.symbol.code().raw());
  if(itr == tb.end()){
    tb.emplace(s,[&](auto &_){
      _.symbol = quantity.symbol;
      _.balance = quantity;
    });
  }else{
    tb.modify(itr,s,[&](auto &_){
      _.balance += quantity;
    });
  }
}

void TransferToken(name s,name from,name to, asset quantity, string memo){
  tokens_table tokens(s,s.value);
  auto itr = tokens.find(quantity.symbol.code().raw());
  eosio::action(
      permission_level{ s , ACTIVE },
      itr->contract, "transfer"_n,
      std::make_tuple(from, to, quantity, memo)
  ).send();
}

template<name::raw A, typename B, typename... C> void ClearTable(multi_index<A, B, C...>* table) { 
  auto it = table->begin(); 
  while (it != table->end()) { it = table->erase(it); } 
}