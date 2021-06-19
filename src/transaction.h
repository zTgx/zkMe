#pragma once

#include <uint256.h>
#include <proof.h>

class Transaction {
    public:
        Transaction() {}
        
    private:
        const uint256 hash;
        void UpdateHash() const;
    
    public:
        uint256 randomPublicKey;
        GrothProof gpf;
    
    public:
        static Transaction Mock();
};