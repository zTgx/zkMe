#include <main.h>
#include <rust/include/rust_header.h>
#include <verifier.h>
#include <transaction.h>

int main(int argc, char** argv) {
    std::cout << "Main." << std::endl;

    hello_world();

    auto tx = Transaction::Mock();

    auto verifier = Verifier::Strict();
    if (!verifier.verify(tx)) {
        std::cout << "verify failed." << std::endl;
        return -1;
    }

    std::cout << "verify success." << std::endl;

    return 0;
}
