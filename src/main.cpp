#include <verifier.h>
#include <transaction.h>
#include <iostream>
#include <prover.h>

int main(int argc, char** argv) {
    // transaction needed to be verified
    auto tx = RawTransaction::Mock();

    auto prover = Prover::inst(tx.txHash);
    auto msg = prover.BuildMessage();

    // verify
    if (!Verifier::Verify(msg)) {
        std::cout << "verify failed." << std::endl;
        return -1;
    }

    std::cout << "verify success." << std::endl;

    return 0;
}
