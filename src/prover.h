#include <vector>
#include <proof.h>
#include <utils/uint256.h>
#include <transaction.h>

class Prover {
    private:
        GrothProof gpf{0};
        uint256 pvk;
        uint256 inputs;

    public:
        void build();

        static Prover inst(uint256&);

        Message BuildMessage();

    public:
        Prover(uint256& inputs) {
            this->inputs = inputs;
        }

};