#include <transaction.h>
#include <prove.h>

Transaction 
Transaction::Mock() {

    Prove p;
    p.initContext();
    
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
