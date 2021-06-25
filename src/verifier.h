#pragma once

#include <transaction.h>

class Verifier {
    private:
        Verifier() {}

    public:
        Verifier(const Verifier&) = delete;
        Verifier& operator=(const Verifier&) = delete;
        Verifier(Verifier&&);
        Verifier& operator=(Verifier&&);
    
    public:
        static bool Verify(Message&);
};