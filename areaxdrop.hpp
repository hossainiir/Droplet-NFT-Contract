#include <string>
#include <eosio/eosio.hpp>
#include <eosio/print.hpp>
#include <eosio/asset.hpp>
#include <eosio/transaction.hpp>
#include <eosio/fixed_bytes.hpp>
#include <eosio/system.hpp>
#include <eosio/crypto.hpp>
#include <eosio/singleton.hpp>

using namespace eosio;

using eosio::indexed_by;
using eosio::const_mem_fun;
using eosio::asset;
using eosio::permission_level;
using eosio::action;
using eosio::name;

using std::string;
using std::vector;
using std::map;

const auto mul = 10000000000000000;

name marble_contract = ""_n;
name market_contract = ""_n;

const auto symbol_tlos = symbol(symbol_code("TLOS"),4);

#include "tables/config_table.hpp"
#include "tables/wallets_table.hpp"
#include "tables/amounts_table.hpp"
#include "tables/attributes_table.hpp"
#include "tables/bank_table.hpp"
#include "tables/counters_table.hpp"
#include "tables/drops_table.hpp"
#include "tables/groups_table.hpp"
#include "tables/items_table.hpp"
#include "tables/marbleConfig_table.hpp"
#include "tables/marbleItems_table.hpp"
#include "tables/tokens_table.hpp"

#include "names.hpp"
#include "helpers.hpp"
#include "sharedActions.hpp"
#include "controllers/admin_controller.hpp"
#include "controllers/common_controller.hpp"

class [[eosio::contract("areaxdrop")]] areaxdrop : public contract {
  public:
    using contract::contract;
    areaxdrop(name receiver, name code, datastream<const char*> ds):
    contract(receiver, code, ds),
    _common_controller(get_self()),
    _admin_controller(get_self())
    {
    }

    //admins
    ACTION setconfig(name market_contract,name marble_contract);
    ACTION addtoken(name contract,symbol symbol);    
    ACTION rmvtoken(symbol symbol);
    ACTION creatdropset(asset prize,name account,name group,asset price,uint64_t count,string data);
    ACTION setdropitem(uint64_t set_id,uint64_t stars,uint8_t cooldown,asset min,asset max,double chance);
    //common
    ACTION claimrewards(name owner,uint64_t serial,uint64_t set_id);
    void mintsetitem(name account,uint64_t setId,string assetUrl,string title);
    //listeners
    void transfer(name sender, name receiver);

  private:
    //controllers
    admin_controller _admin_controller;
    common_controller _common_controller;
};
