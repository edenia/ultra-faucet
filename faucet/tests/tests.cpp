#include "include/tester-base.hpp"

TEST_CASE("add faucet") {
   test_chain chain;
   setup(chain);

   chain.as("faucet"_n).act<faucets::actions::addfaucet>("faucet1"_n, 5, 2000);

   CHECK(get_table_size<faucets::faucet_table>() == 1);
}

TEST_CASE("add duplicated faucet") {
   test_chain chain;
   setup(chain);

   chain.as("faucet"_n).act<faucets::actions::addfaucet>(
      "faucet1"_n,
      5,
      2000);

   expect(chain.as("faucet"_n).trace<faucets::actions::addfaucet>(
              "faucet1"_n,
              6,
              2000),
         "Faucet account is already registered");
}

TEST_CASE("remove existing faucet") {
   test_chain chain;
   setup(chain);

   chain.as("faucet"_n).act<faucets::actions::addfaucet>(
      "faucet1"_n,
      5,
      2000);
   chain.as("faucet"_n).act<faucets::actions::rmfaucet>("faucet1"_n);

   CHECK(true);
}

TEST_CASE("remove unexisting faucet") {
   test_chain chain;
   setup(chain);

   expect(chain.as("faucet"_n).trace<faucets::actions::rmfaucet>("faucet1"_n),
         "Faucet does not exist");
}

TEST_CASE("send tokens with wrong authority") {
   test_chain chain;
   setup(chain);

   chain.as("faucet"_n).act<faucets::actions::addfaucet>("faucet1"_n, 5, 2000);

   expect(chain.as("faucet"_n).trace<faucets::actions::givetokens>("faucet1"_n, "testacc"_n), "missing authority of faucet1");
}