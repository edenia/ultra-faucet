-include ../.env

compile:
	@mkdir -p build
	@cd build && cmake `clsdk-cmake-args` .. && make -j $(nproc)
	@cd build && cp faucet.* ..
	@echo "compiled"

deploy:
	cleos -u $(CONTRACT_ENDPOINT) set contract $(CONTRACT_ACCOUNT) ./
	@echo "deployed"

test:
	@cd build && cltester tests.wasm

testv:
	@cd build && cltester -v tests.wasm