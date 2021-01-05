#include "areaxdrop.hpp"

void areaxdrop::setconfig(name market_contract,name marble_contract){
  _admin_controller.setConfig(market_contract,marble_contract);
}

void areaxdrop::creatdropset(asset prize,name account,name group,asset price,uint64_t count,string data){
  _admin_controller.createDropSet(prize,account,group,price,count,data);
}

void areaxdrop::setdropitem(uint64_t set_id,uint64_t stars,uint8_t cooldown,asset min,asset max,double chance){
  _admin_controller.setDropItem(set_id,stars,cooldown,min,max,chance);
}

void areaxdrop::addtoken(name contract,symbol symbol){
  _admin_controller.addToken(contract,symbol);
}

void areaxdrop::rmvtoken(symbol symbol){
  _admin_controller.removeToken(symbol);
}

void areaxdrop::claimrewards(name owner,uint64_t serial,uint64_t set_id){
  _common_controller.claimRewards(owner,serial,set_id);
}

void areaxdrop::transfer(name sender, name receiver){
  auto transfer_data = unpack_action_data<st_transfer>();
  if (transfer_data.from == _self){
    return;
  }

  if(transfer_data.memo == "deposit"){
    return;
  }else if(transfer_data.memo == "[deposit]"){
    Deposit(_self,sender,transfer_data.quantity);
  }else{
    check(false, "Invalid action");
  }
}

void areaxdrop::mintsetitem(name account,uint64_t setId,string assetUrl,string title){
  check(get_first_receiver() == market_contract, "Market authority is needed");
  
  marbleconfig_table mtb(marble_contract,marble_contract.value);
  auto config = mtb.get();

  items_table tb(_self,setId);
  tb.emplace(_self,[&](auto &_){
    _.serial = config.last_serial+1;
  });
}

extern "C" {
  void apply(name receiver, name code, uint64_t action) {
    auto self = receiver;
    bool isValidToken = false;
    _code = code;
    //Check the tokens and accounts

    if(action != "setconfig"_n.value){
      config_table tb(self,self.value);
      auto conf = tb.get();
      marble_contract = conf.marble_contract;
      market_contract = conf.market_contract;
    }
    if(action == "transfer"_n.value){
      auto transfer_data = unpack_action_data<st_transfer>();
      tokens_table tb(self,self.value);
      auto itr = tb.find(transfer_data.quantity.symbol.code().raw());
      check(itr != tb.end(),"invalid symbol");
      check(itr->contract == code,"Invalid token contract");
      isValidToken = true;
    }

    if( code == self || code == market_contract || isValidToken) { 
      //  TYPE thiscontract( self ); 
      switch( action ) { 
        EOSIO_DISPATCH_HELPER(
          areaxdrop, 
          //listener
          (transfer)
          (mintsetitem)
          //admin
          (addtoken)
          (rmvtoken)
          (setconfig)
          (setdropitem)
          (creatdropset)
          //common
          (claimrewards)
        )
      }
    } 
  }
};