#pragma once

#include <utils/uint256.h>
#include <proof.h>

class Transaction {
    public:
        Transaction() {}

    public:
        void UpdateHash() const;
        void BuildGrothProof() const;

    public:
        static Transaction Mock();

    private:
        const uint256 hash;
        const GrothProof gpf{0};
        uint256 randomPublicKey;
};