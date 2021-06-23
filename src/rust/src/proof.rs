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

pub struct ProvingContext {
    pub anno: String,
}
impl ProvingContext {
    pub fn new() -> ProvingContext {
        ProvingContext{
            anno: "ProvingContext".to_string()
        }
    }

    pub fn spend_proof(&self, inputs: [u8; 33]) -> (groth16::Proof<Bls12>, groth16::PreparedVerifyingKey<Bls12>) {
        println!("spend proof.");

        let preimage = inputs;

        // Create parameters for our circuit. In a production deployment these would
        // be generated securely using a multiparty computation.
        let params = {
            let c = Tx { pay_address: None };
            groth16::generate_random_parameters::<Bls12, _, _>(c, &mut OsRng).unwrap()
        };

        // Prepare the verification key (for proof verification).
        let pvk = groth16::prepare_verifying_key(&params.vk);

        // Pick a preimage and compute its hash.
        let hash = Sha256::digest(&preimage);

        // Create an instance of our circuit (with the preimage as a witness).
        let c = Tx {
            pay_address: Some(preimage),
        };

        // Create a Groth16 proof with our parameters.
        (groth16::create_random_proof(c, &params, &mut OsRng).unwrap(), pvk)
    }
}

pub struct VerificationContext {}
impl VerificationContext {
    pub fn new() -> Self {
        VerificationContext{}
    }

    pub fn verify_proof(&self, pvk: &groth16::PreparedVerifyingKey<Bls12>, proof: &[u8], inputs: &[u8]) -> bool {
        let proof_data = groth16::Proof::<Bls12>::read(&(unsafe { &*proof })[..]);
        if let Ok(proof) = proof_data {
            let hash_bits = multipack::bytes_to_bits_le(&inputs);
            let inputs = multipack::compute_multipacking(&hash_bits);
        
            // Check the proof!
            return groth16::verify_proof(&pvk, &proof, &inputs).is_ok();    
        }

        return false;
    }
}