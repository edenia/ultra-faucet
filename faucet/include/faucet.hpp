#include <eosio/eosio.hpp>
#include <eosio/asset.hpp>

using namespace std;
using namespace eosio;

CONTRACT faucet_contract : public contract {
  public:
    using contract::contract;

    const int64_t TOKENS_PER_REQUEST = 500;
    const int64_t TOKEN_PRECISION = 8;
    const std::string TOKEN_SYMBOL = "UOS";

    // Admin only
    ACTION addfaucet(name account, eosio::time_point_sec interval, uint32_t max_tokens_per_interval);
    ACTION rmfaucet(name account);

    // Faucet only
    ACTION givetokens(name faucet, name to);
  private: 
    TABLE faucet {
      name                      account;
      eosio::time_point_sec     interval;
      uint32_t                  max_tokens_per_interval;
      eosio::time_point         until;
      uint32_t                  transferred_tokens;

      uint64_t primary_key() const { return account.value; }
    };
    typedef eosio::multi_index<"faucets"_n, faucet> faucet_table;
};