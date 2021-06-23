#include <prove.h>
#include <rust/include/librustbellman.h>
#include <iostream>
#include <proof.h>

void
Prove::initContext() {
    auto ctx = librust_proving_ctx_init();

    unsigned char* zkproof = (unsigned char*)malloc(GROTH_PROOF_SIZE);
    unsigned char* inputs = (unsigned char*)"this is payment address, so let's get started it.";
    librust_proof(ctx, inputs, zkproof);

    

    librust_proving_ctx_free(ctx);
}