#include <verifier.h>

Verifier Verifier::Strict() {
    return Verifier();
}

bool Verifier::verify(const Transaction& tx) {
    (void)tx;
    
    return true;
}