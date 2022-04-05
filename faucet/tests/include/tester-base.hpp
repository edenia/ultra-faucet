// cltester definitions
#include <eosio/tester.hpp>
#include <token/token.hpp>

// contract definitions
#include "../../include/faucet.hpp"

// Catch2 unit testing framework. https://github.com/catchorg/Catch2
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

using namespace eosio;


void setup_chain(test_chain& t)
{
   t.create_code_account("testacc"_n);
   t.create_code_account("testacc2"_n);
   t.create_code_account("testacc3"_n);
   t.create_code_account("faucet"_n);
   t.create_code_account("faucet1"_n);
   t.set_code("faucet"_n, "faucet.wasm");

   t.create_code_account("eosio.token"_n);
   t.set_code("eosio.token"_n, CLSDK_CONTRACTS_DIR "token.wasm");

   // Create and issue tokens.
   t.as("eosio.token"_n).act<token::actions::create>("eosio"_n, s2a("1000000.0000 EOS"));
   t.as("eosio.token"_n).act<token::actions::create>("eosio"_n, s2a("1000000.0000 FAUCET"));
   t.as("eosio"_n).act<token::actions::issue>("eosio"_n, s2a("1000000.0000 EOS"), "");
   t.as("eosio"_n).act<token::actions::issue>("eosio"_n, s2a("1000000.0000 FAUCET"), "");
   t.as("eosio"_n).act<token::actions::transfer>("eosio"_n, "faucet"_n, s2a("10000.0000 EOS"), "first transfer");
}

void setup(test_chain& t)
{
   setup_chain(t);
}

template <typename T>
auto get_table_size()
{
   T tb("faucet"_n, eosio::name{"faucet"}.value);
   return std::distance(tb.begin(), tb.end());
}

template <typename T>
auto get_table_size(eosio::name scope)
{
   T tb("faucet"_n, scope.value);
   return std::distance(tb.begin(), tb.end());
}