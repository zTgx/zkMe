#include <transaction.h>

Transaction 
Transaction::Mock() {
    auto tx = Transaction();

    tx.UpdateHash();
    tx.BuildGrothProof();

    return tx;
}

void 
Transaction::UpdateHash() const {

}

void 
Transaction::BuildGrothProof() const {
    
}
