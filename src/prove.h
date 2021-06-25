#include <vector>
#include <proof.h>
#include <utils/uint256.h>

class Prove {
    private:
        GrothProof gpf{0};
        uint256 pvk;
        uint256 inputs;

    public:
        void setInputs(uint256&);
        uint256 getInputs();

        GrothProof getProof();
        void build();

    public:
        Prove() {}
};