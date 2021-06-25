use crate::circuit::tx::Tx;
use bellman::{
    groth16,

    gadgets::{
        multipack,
    },
};
use bls12_381::Bls12;
use rand::rngs::OsRng;
use sha2::{Digest, Sha256};

// https://doc.rust-lang.org/std/mem/fn.size_of.html
// use std::mem;

pub struct ProvingContext {
    pub anno: String,
}
impl ProvingContext {
    pub fn new() -> ProvingContext {
        ProvingContext{
            anno: "ProvingContext".to_string()
        }
    }

    pub fn spend_proof(&self, inputs: [u8; 32]) -> (groth16::Proof<Bls12>, groth16::PreparedVerifyingKey<Bls12>) {
        // Create parameters for our circuit. In a production deployment these would
        // be generated securely using a multiparty computation.
        let params = {
            let c = Tx { hash: None };
            groth16::generate_random_parameters::<Bls12, _, _>(c, &mut OsRng).unwrap()
        };

        // Prepare the verification key (for proof verification).
        let pvk = groth16::prepare_verifying_key(&params.vk);

        // Create an instance of our circuit (with the preimage as a witness).
        let c = Tx {
            hash: Some(inputs),
        };

        // Create a Groth16 proof with our parameters.
        let proof = groth16::create_random_proof(c, &params, &mut OsRng).unwrap();

        (proof, pvk)
    }
}

pub struct VerificationContext {}
impl VerificationContext {
    pub fn new() -> Self {
        VerificationContext{}
    }

    pub fn verify_proof(&self, pvk: &groth16::PreparedVerifyingKey<Bls12>, zkproof: groth16::Proof<Bls12>, inputs: &[u8; 32]) -> bool {
        let hash = Sha256::digest(&Sha256::digest(inputs));
        let hash_bits = multipack::bytes_to_bits_le(&hash);
        let inputs = multipack::compute_multipacking(&hash_bits);
    
        // Check the proof!
        groth16::verify_proof(&pvk, &zkproof, &inputs).is_ok()
    }
}