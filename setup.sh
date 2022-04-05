#!/usr/bin/env bash
set -ex;
set -o allexport
source .env
set +o allexport

unlock_wallet() {
  cleos -u $CONTRACT_ENDPOINT wallet unlock -n $CONTRACT_ACCOUNT --password $(cat ./secrets/wallet_password.txt) \
    || echo "Wallet has already been unlocked..."
}

create_wallet() {
  mkdir -p ./secrets
  cleos wallet create -n $CONTRACT_ACCOUNT --to-console \
    | awk 'FNR > 3 { print $1 }' \
    | tr -d '"' \
    > ./secrets/wallet_password.txt;
  cleos wallet open;
  unlock_wallet
  cleos wallet import -n $CONTRACT_ACCOUNT --private-key $FAUCET_PRIV_KEY;
  cleos wallet import -n $CONTRACT_ACCOUNT --private-key $FAUCET_EOSIO_PRIV_KEY;
}

create_contract_account() {
  cleos -u $CONTRACT_ENDPOINT create account eosio $CONTRACT_ACCOUNT $FAUCET_PUB_KEY;
}

set_resource_limits() {
  echo "Setting network resources for $CONTRACT_ACCOUNT ..."
  cleos -u $CONTRACT_ENDPOINT push action eosio setalimits \
    '["'$CONTRACT_ACCOUNT'", 1000000, 1,1]' -p eosio@active
}

deploy_smart_contract() {
  cleos -u $CONTRACT_ENDPOINT set contract $CONTRACT_ACCOUNT ./faucet -p $CONTRACT_ACCOUNT@active;
}

run_setup() {
  echo 'Creating Opt-In mailing list account'
  create_wallet
  create_contract_account
  set_resource_limits
  deploy_smart_contract
}

run_setup