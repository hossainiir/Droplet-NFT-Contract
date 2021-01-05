//scope: serial
struct [[eosio::table]] attribute {
    name attribute_name;
    int64_t points;
    bool locked;
    uint64_t primary_key() const { return attribute_name.value; }
};
typedef multi_index<name("attributes"), attribute> attributes_table;