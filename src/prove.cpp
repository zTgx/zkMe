#include <prove.h>
#include <rust/include/librustbellman.h>
#include <iostream>

void
Prove::initContext() {
    auto ctx = librust_proving_ctx_init();
    librust_proof(ctx);
    librust_proving_ctx_free(ctx);
}