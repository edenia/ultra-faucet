# Faucet Smart Contract

Ultra Testnet Faucets Contest.

[clsdk](https://github.com/gofractally/demo-clsdk) is the compiler used to create the `.abi` and `.wasm` files. Please make sure you are using `Ubuntu 20.04` to successfully compile this Smart Contract. More about this compiler [here](https://eoscommunity.github.io/clsdk-docs/book/contract/basic/index.html).

1. To install `clsdk`, run the following commands:

```sh
sudo apt-get update
sudo apt-get install -yq    \
    binaryen                \
    build-essential         \
    cmake                   \
    gdb                     \
    git                     \
    libboost-all-dev        \
    libcurl4-openssl-dev    \
    libgmp-dev              \
    libssl-dev              \
    libusb-1.0-0-dev        \
    pkg-config              \
    wget


mkdir ~/work

cd ~/work
wget https://github.com/WebAssembly/wasi-sdk/releases/download/wasi-sdk-12/wasi-sdk-12.0-linux.tar.gz
tar xf wasi-sdk-12.0-linux.tar.gz

cd ~/work
wget https://github.com/eoscommunity/Eden/releases/download/sdk-v0.1.0-alpha/clsdk-ubuntu-20-04.tar.gz
tar xf clsdk-ubuntu-20-04.tar.gz
```

2. Setting `env` variables:

```sh
export WASI_SDK_PREFIX=~/work/wasi-sdk-12.0
export CLSDK_PREFIX=~/work/clsdk

export PATH=$CLSDK_PREFIX/bin:$PATH
```

3. In your `.env` file, make sure you have set the `CONTRACT_ENDPOINT` and `CONTRACT_ACCOUNT` variables correctly.

4. To compile and deploy the Smart Contract, make sure you are in `/faucet`:

```sh
make compile
make deploy
```

5. To validate if the Smart Contract passes the unit test:

```sh
make test
```

> If you want to follow the official installation instructions, you can consult it [here](https://eoscommunity.github.io/clsdk-docs/book/ubuntu.html).


## About Edenia

<div align="center">
	<a href="https://edenia.com">
		<img src="https://user-images.githubusercontent.com/5632966/178800854-cffb01ea-b55a-44b2-bcfa-872301874a43.png" width="300">
	</a>
</p>

[![Twitter](https://img.shields.io/twitter/follow/EdeniaWeb3?style=for-the-badge)](https://twitter.com/EdeniaWeb3)
![Discord](https://img.shields.io/discord/946500573677625344?color=black&label=discord&logo=discord&logoColor=white&style=for-the-badge)

</div>

Edenia runs independent blockchain infrastructure and develops web3 solutions. Our team of technology-agnostic builders has been operating since 1987, leveraging the newest technologies to make the internet safer, more efficient, and more transparent.

[edenia.com](https://edenia.com/)

