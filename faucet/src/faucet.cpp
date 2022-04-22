#include <eosio/system.hpp>
#include <cmath>

#include "../include/faucet.hpp"

namespace faucets {
  void contract::addfaucet(name account, eosio::time_point_sec interval, uint32_t max_tokens_per_interval) {
    require_auth(get_self());

    faucet_table _faucet(get_self(), get_self().value);
    auto faucet_itr = _faucet.find(account.value);

    check(faucet_itr == _faucet.end(), "Faucet account is already registered");

    _faucet.emplace(get_self(), [&](auto& row) {
      row.account = account;
      row.interval = interval;
      row.max_tokens_per_interval = max_tokens_per_interval;
      row.until = current_time_point() + seconds(interval.sec_since_epoch());
      row.transferred_tokens = 0;
    });
  }

  void contract::rmfaucet(name account) {
    require_auth(get_self());

    faucet_table _faucet(get_self(), get_self().value);
    auto faucet_itr = _faucet.find(account.value);

    check(faucet_itr != _faucet.end(), "Faucet does not exist");

    _faucet.erase(faucet_itr);
  }

  void contract::givetokens(name faucet, name to) {
    require_auth(faucet);

    faucet_table _faucet(get_self(), get_self().value);
    auto faucet_itr = _faucet.find(faucet.value);

    check(faucet_itr != _faucet.end(), "Faucet does not exist");

    time_point now = current_time_point();
    if(now > faucet_itr->until) {
      uint32_t intervalSecs = faucet_itr->interval.sec_since_epoch();
      float windowGap = (now.sec_since_epoch() - faucet_itr->until.sec_since_epoch()) / intervalSecs;
      
      time_point newUntil = faucet_itr->until + seconds(intervalSecs) + time_point(seconds(floor(windowGap) * intervalSecs));

      _faucet.modify(faucet_itr, get_self(), [&]( auto& row ) {
        row.until = newUntil;
        row.transferred_tokens = 0;
      });
    }

    check( now <= faucet_itr->until &&
      faucet_itr->transferred_tokens + TOKENS_PER_REQUEST <= faucet_itr->max_tokens_per_interval, "Not so fast...");

    _faucet.modify(faucet_itr, get_self(), [&]( auto& row ) {
      row.transferred_tokens = faucet_itr->transferred_tokens + TOKENS_PER_REQUEST;
    });

    asset amount = asset(TOKENS_PER_REQUEST * pow(10, TOKEN_PRECISION), symbol(TOKEN_SYMBOL, TOKEN_PRECISION));
    string memo = "Faucet transfer";

    eosio::action(
      permission_level {get_self(), "transferer"_n},
      "eosio.token"_n,
      "transfer"_n,
      std::make_tuple(get_self(), to, amount, memo)
    ).send();
  }
} // namespace faucets

EOSIO_ACTION_DISPATCHER(faucets::actions)
EOSIO_ABIGEN(actions(faucets::actions),
             table("faucets"_n, faucets::faucet),
             ricardian_clause("datastorage", faucets::datastorage_clause),
             ricardian_clause("datausage", faucets::datausage_clause),
             ricardian_clause("dataownership",
                              faucets::dataownership_clause),
             ricardian_clause("datadistribution",
                              faucets::datadistribution_clause),
             ricardian_clause("datafuture", faucets::datafuture_clause))