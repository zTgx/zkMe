#include <prove.h>
#include <rust/include/librustbellman.h>
#include <iostream>
#include <proof.h>
#include <vector>
#include <cstring>

void
Prove::initContext() {
    std::vector<unsigned char> zkproof(GROTH_PROOF_SIZE);
    const std::string inputs("this is payment address, so let's get started it.");

    // build groth16 proof
    auto ctx = librust_proving_ctx_init();
    bool proof_res = librust_proof(ctx, inputs.data(), zkproof.data());
    std::cout << "proof res: " << std::boolalpha << proof_res << std::endl;
    librust_proving_ctx_free(ctx);

    // verify proof
    auto ctx_verify = librust_verification_ctx_init();
    bool check_ret = librust_verification_check(ctx_verify, (const char*)zkproof.data(), inputs.data());
    std::cout << "verification check res: " << std::boolalpha << check_ret << std::endl;
    librust_verification_ctx_free(ctx_verify);
}

std::vector<unsigned char>
Prove::buildProof(const char* inputss) {
    std::vector<unsigned char> zkproof(GROTH_PROOF_SIZE);
    const std::string inputs("this is payment address, so let's get started it.");

    // build groth16 proof
    auto ctx = librust_proving_ctx_init();
    bool proof_res = librust_proof(ctx, inputs.data(), zkproof.data());
    std::cout << "proof res: " << std::boolalpha << proof_res << std::endl;
    librust_proving_ctx_free(ctx);

    return zkproof;
}
