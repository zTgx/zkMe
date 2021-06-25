#include <prove.h>
#include <rust/include/librustbellman.h>
#include <iostream>
#include <proof.h>
#include <vector>
#include <cstring>

void
Prove::build() {
    // build groth16 proof
    std::vector<unsigned char> zkproof(GROTH_PROOF_SIZE);
    std::string inputs = this->inputs.ToString();

    auto ctx = librust_proving_ctx_init();
    bool proof_res = librust_proof(ctx, (const char*)inputs.data(), zkproof.data());
    std::cout << "proof res: " << std::boolalpha << proof_res << std::endl;
    librust_proving_ctx_free(ctx);

    for(int i=0;i<zkproof.size();i++) {
        this->gpf[i] = zkproof[i];
    }
}

void 
Prove::setInputs(uint256& inputs) {
    this->inputs = inputs;
}

uint256
Prove::getInputs() {
    return this->inputs;
}

GrothProof 
Prove::getProof() {
    return this->gpf;
}
