#pragma once

#include <uint256.h>

class Transaction {
    private:
        const uint256 hash;
        void UpdateHash() const;
    
    public:
        uint256 randomPublicKey;

};