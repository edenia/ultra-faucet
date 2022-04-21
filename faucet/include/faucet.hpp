#pragma once

#include <eosio/eosio.hpp>
#include <eosio/asset.hpp>

#include "../ricardian/faucet_ricardian.hpp"

using namespace std;
using namespace eosio;

namespace faucets {
  const int64_t TOKENS_PER_REQUEST = 500;
  const int64_t TOKEN_PRECISION = 8;
  const std::string TOKEN_SYMBOL = "UOS";

  struct faucet {
    name account;
    eosio::time_point_sec interval;
    uint32_t max_tokens_per_interval;
    eosio::time_point until;
    uint32_t transferred_tokens;

    uint64_t primary_key() const { return account.value; }
  };
  EOSIO_REFLECT(
    faucet,
    account,
    interval,
    max_tokens_per_interval,
    until,
    transferred_tokens
  )
  typedef eosio::multi_index<"faucets"_n, faucet> faucet_table;

  class contract : public eosio::contract {
    public:
      using eosio::contract::contract;

      // Admin only
      void addfaucet(name account, eosio::time_point_sec interval, uint32_t max_tokens_per_interval);
      void rmfaucet(name account);

      // Faucet only
      void givetokens(name faucet, name to);
  };

  EOSIO_ACTIONS(contract, "faucet"_n,
                action(addfaucet, account, interval, max_tokens_per_interval),
                action(rmfaucet, account),
                action(givetokens, faucet, to))
} // namespace faucets