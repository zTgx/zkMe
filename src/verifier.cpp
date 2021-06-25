#include <verifier.h>
#include <iostream>
#include <proof.h>
#include <rust/include/librustbellman.h>
#include <utils/uint256.h>

bool Verifier::Verify(Message& msg) {
    auto const zkproof   = msg.gpf;
    const uint256 inputs = msg.txHash;
    std::string input = inputs.ToString();

    std::cout << "verify inputs: " << inputs.ToString() << std::endl;

    auto ctx_verify = librust_verification_ctx_init();
    bool check_ret = librust_verification_check(ctx_verify, (const char*)zkproof.data(), (const char*)input.data());
    std::cout << "verification check res: " << std::boolalpha << check_ret << std::endl;
    librust_verification_ctx_free(ctx_verify);

    return check_ret;
}
