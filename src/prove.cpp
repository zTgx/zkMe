#include <prove.h>
#include <rust/include/librustbellman.h>
#include <iostream>
#include <proof.h>
#include <vector>

void
Prove::initContext() {
    auto ctx = librust_proving_ctx_init();

    unsigned char* zkproof = (unsigned char*)malloc(GROTH_PROOF_SIZE);
    unsigned char* inputs = (unsigned char*)"this is payment address, so let's get started it.";

    bool proof_ret = librust_proof(ctx, inputs, zkproof);
    std::cout << "proof ret: " << std::boolalpha << proof_ret << std::endl;

    // std::vector<unsigned char> proof_vec (zkproof, zkproof + sizeof(zkproof) / sizeof(unsigned char) );

    // for (auto& el : proof_vec)
    //     printf("%02hhx", el);

    // std::cout << '\n';

    librust_proving_ctx_free(ctx);

    auto ctx_verify = librust_verification_ctx_init();

    bool check_ret = false;
    std::cout << "check_ret init status = " << std::boolalpha << check_ret << std::endl;
    check_ret = librust_verification_check(ctx_verify, (const char*)zkproof, (const char*)inputs);
    std::cout << "update check result: " << std::boolalpha << check_ret << std::endl;

    librust_verification_ctx_free(ctx_verify);

}