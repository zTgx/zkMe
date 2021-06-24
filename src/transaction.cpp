#include <transaction.h>
#include <iostream>
#include <proof.h>
#include <vector>
#include <ostream>
#include <streambuf>
#include <rust/include/librustbellman.h>
#include <prove.h>
#include <crypto/hash.h>

RawTransaction
RawTransaction::Mock() {
    RawTransaction raw;

    raw.txHash = uint256S("rawTransactionHash");
    raw.spend_address = uint256S("spend_address_A");
    raw.out_address = uint256S("out_address_B");
    raw.value = uint256S("value");

    std::string v = "rawTransaction";

    std::cout << "hash uint256: " << Hash(v.begin(), v.end()).ToString() << std::endl;
    std::cout << "mock uint256: " << uint256S("ok").ToString() << std::endl;

    return raw;
}

void
RawTransaction::data(std::vector<char>& v) {
    std::cout << "spend_address : " << this->spend_address.ToString() << std::endl;

    std::copy( this->spend_address.begin(), this->spend_address.end(), std::back_inserter(v));
    std::copy( this->out_address.begin(), this->out_address.end(), std::back_inserter(v));
    std::copy( this->value.begin(), this->value.end(), std::back_inserter(v));
    std::copy( this->txHash.begin(), this->txHash.end(), std::back_inserter(v));

    std::cout << "sizeof d: " << v.size() << std::endl;

    for(auto& i : v) {
        std::cout << "* : " << i;
    }

    std::cout << "* : " << v.data() << std::endl;
}

Transaction 
Transaction::Mock() {

    // Prove p;
    // p.initContext();
    
    RawTransaction raw = RawTransaction::Mock();
    auto tx = Transaction();
    tx.buildGroth16Proof(raw);

    return tx;
}

void 
Transaction::buildGroth16Proof(RawTransaction& raw) {
    this->raw = raw;

    std::vector<char> v;
    raw.data(v);

    Prove p;
    auto zkproof = p.buildProof(v.data());
    // std::copy(zkproof.begin(), zkproof.end(), this->gpf);
    for(int i=0;i<zkproof.size();i++) {
        this->gpf[i] = zkproof[i];
    }
}
