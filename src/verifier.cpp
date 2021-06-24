#include <verifier.h>
#include <iostream>
#include <proof.h>
#include <rust/include/librustbellman.h>

bool Verifier::Verify(Transaction& tx) {
    auto const zkproof = tx.gpf;

    // std::vector<char> inputs;
    // tx.raw.data(inputs);

    const std::string inputs("this is payment address, so let's get started it.");

    auto ctx_verify = librust_verification_ctx_init();
    bool check_ret = librust_verification_check(ctx_verify, (const char*)zkproof.data(), inputs.data());
    std::cout << "verification check res: " << std::boolalpha << check_ret << std::endl;
    librust_verification_ctx_free(ctx_verify);

    return check_ret;
}