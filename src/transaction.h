#pragma once

#include <utils/uint256.h>
#include <proof.h>
#include <crypto/hash.h>

struct RawTransaction { 
    uint256 spend_address;
    uint256 out_address;
    uint256 value; 

    uint256 txHash;

    static RawTransaction Mock();
    void data(std::vector<char>& v);

    uint256 calcTxHash() {
        std::vector<unsigned char> v;

        std::copy( this->spend_address.begin(), this->spend_address.end(), std::back_inserter(v));
        std::copy( this->out_address.begin(), this->out_address.end(), std::back_inserter(v));
        std::copy( this->value.begin(), this->value.end(), std::back_inserter(v));

        return Hash(v.begin(), v.end());
    }
};

class Message {
    public:
        GrothProof gpf{0};
        const uint256 pvk;
        const uint256 txHash;
    
    public:
        static Message Mock() {
            return Message();
        }
    
    public:
        void build(uint256&, GrothProof&);
};