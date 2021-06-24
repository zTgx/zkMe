#pragma once

#include <utils/uint256.h>
#include <proof.h>

struct RawTransaction {
    uint256 spend_address;
    uint256 out_address;
    uint256 value;
    uint256 txHash;

    static RawTransaction Mock();
    void data(std::vector<char>& v);
};

class Transaction {
    public:
        Transaction() {}

    public:
        void buildGroth16Proof(RawTransaction&);

    public:
        static Transaction Mock();

    public:
        GrothProof gpf{0};
        const uint256 pvk;
        RawTransaction raw;
};