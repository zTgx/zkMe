#include <rust/include/librustbellman.h>
#include <verifier.h>
#include <transaction.h>
#include <iostream>

int main(int argc, char** argv) {
    hello_world();

    // transaction needed to be verified
    auto tx = Transaction::Mock();

    // verify
    if (!Verifier::Verify(tx)) {
        std::cout << "verify failed." << std::endl;
        return -1;
    }

    std::cout << "verify success." << std::endl;

    return 0;
}
