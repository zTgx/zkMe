#include <prover.h>
#include <rust/include/librustbellman.h>
#include <iostream>
#include <proof.h>
#include <vector>
#include <cstring>
#include <transaction.h>

Prover 
Prover::inst(uint256& inputs) {
    Prover p(inputs);
    p.build();
    return p;
}

void
Prover::build() {
    // build groth16 proof
    std::vector<unsigned char> zkproof(GROTH_PROOF_SIZE);
    // std::string inputs = this->inputs.ToString();
    // std::cout << "inputs size: " << inputs.size() << this->inputs.size() << std::endl;

    auto ctx = librust_proving_ctx_init();
    // bool proof_res = librust_proof(ctx, (const char*)inputs.data(), zkproof.data());
    bool proof_res = librust_proof(ctx, this->inputs.begin(), zkproof.data());
    std::cout << "proof res: " << std::boolalpha << proof_res << std::endl;
    librust_proving_ctx_free(ctx);

    for(int i=0;i<zkproof.size();i++) {
        this->gpf[i] = zkproof[i];
    }
}

Message
Prover::BuildMessage() {
    Message msg = Message::Mock();

    msg.build(this->inputs, this->gpf);

    return msg;
}

