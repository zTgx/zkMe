#include <transaction.h>
#include <iostream>
#include <proof.h>
#include <vector>
#include <ostream>
#include <streambuf>
#include <rust/include/librustbellman.h>
#include <crypto/hash.h>

RawTransaction
RawTransaction::Mock() {
    RawTransaction raw;

    std::string spend_address{"spend_address_A"};
    raw.spend_address = Hash(spend_address.begin(), spend_address.end());

    std::string out_address{"out_address_B"};
    raw.out_address = Hash(out_address.begin(), out_address.end());

    std::string value{"value"};
    raw.value = Hash(value.begin(), value.end());

    raw.txHash = raw.calcTxHash();
    std::cout << "raw tx hash: " << raw.txHash.ToString() << "  " << "size : " << raw.txHash.size() << std::endl;

    return raw;
}

void 
Message::build(uint256& inputs, GrothProof& gpf) {    
    *const_cast<uint256*>(&this->txHash) = inputs;
    this->gpf    = gpf;
}