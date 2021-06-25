#include <verifier.h>
#include <transaction.h>
#include <iostream>

int main(int argc, char** argv) {
    // transaction needed to be verified
    auto tx = RawTransaction::Mock();
    auto msg = Message::Mock();
    msg.build(tx);

    // verify
    if (!Verifier::Verify(msg)) {
        std::cout << "verify failed." << std::endl;
        return -1;
    }

    std::cout << "verify success." << std::endl;

    return 0;
}
