-include ../.env

compile:
	@mkdir -p build
	@cd build && eosio-cpp --abigen -I ../include -R ../ricardian --contract faucet_contract -o faucet.wasm ../src/faucet.cpp
	@cd build && cp faucet.* ..
	@echo "compiled"

deploy:
	cleos -u $(CONTRACT_ENDPOINT) set contract $(CONTRACT_ACCOUNT) ./
	@echo "deployed"

set-permission:
	@cleos -u $(CONTRACT_ENDPOINT) set account permission $(CONTRACT_ACCOUNT) transferer $(PUBLIC_TRANSFERER_KEY) active -p $(CONTRACT_ACCOUNT)@active
	@cleos -u $(CONTRACT_ENDPOINT) set account permission $(CONTRACT_ACCOUNT) transferer --add-code -p $(CONTRACT_ACCOUNT)@active
	@cleos -u $(CONTRACT_ENDPOINT) set action permission $(CONTRACT_ACCOUNT) eosio.token transfer transferer -p $(CONTRACT_ACCOUNT)@active
