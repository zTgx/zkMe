#include <vector>

class Prove {
    public:
        Prove() {}
        void initContext();
        std::vector<unsigned char> buildProof(const char*);
};