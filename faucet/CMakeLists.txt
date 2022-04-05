# All cmake projects need these
cmake_minimum_required(VERSION 3.16)
project(faucet)

# clsdk requires C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Libraries for building contracts and tests
find_package(clsdk REQUIRED)

# Build faucet.wasm contract
add_executable(faucet src/faucet.cpp)
target_link_libraries(faucet eosio-contract-simple-malloc)

# Generate faucet.abi
add_executable(faucet-abigen src/faucet.cpp)
target_link_libraries(faucet-abigen eosio-contract-abigen)
add_custom_command(TARGET faucet-abigen POST_BUILD
    COMMAND cltester faucet-abigen.wasm >faucet.abi
)

# Builds tests.wasm
add_executable(tests tests/tests.cpp)
target_link_libraries(tests cltestlib-debug)

# These symlinks help vscode
execute_process(COMMAND ln -sf ${clsdk_DIR} ${CMAKE_CURRENT_BINARY_DIR}/clsdk)
execute_process(COMMAND ln -sf ${WASI_SDK_PREFIX} ${CMAKE_CURRENT_BINARY_DIR}/wasi-sdk)

# Generate compile_commands.json to aid vscode and other editors
set(CMAKE_EXPORT_COMPILE_COMMANDS on)