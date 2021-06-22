

use bellman::{
    gadgets::{
        boolean::{AllocatedBit, Boolean},
        multipack,
        sha256::sha256,
    },
    groth16, Circuit, ConstraintSystem, SynthesisError,
};
use sha2::{Digest, Sha256};

pub struct Amount {
    // pub pay_address: Option<[u8; 2]>,
    // pub value: String,
    // pub out_address: String,
}

pub struct Tx {
    // pub hash: String,
    // pub amount: Amount,
    pub pay_address: Option<[u8; 2]>,
}

/*

*/
impl Circuit<bls12_381::Scalar> for Tx {
    fn synthesize<CS: ConstraintSystem<bls12_381::Scalar>>(
        self, 
        cs: &mut CS
    ) -> Result<(), SynthesisError> {

        let bit_values = if let Some(pay_address) = self.pay_address {
            pay_address
                .into_iter()
                .map(|byte| (0..8).map(move |i| (byte >> i) & 1u8 == 1u8))
                .flatten()
                .map(|b| Some(b))
                .collect()
        } else {
            vec![None; 2 * 8]
        };

        // Witness the bits of the pay_address.
        let preimage_bits = bit_values
            .into_iter()
            .enumerate()
            // Allocate each bit.
            .map(|(i, b)| {
                AllocatedBit::alloc(cs.namespace(|| format!("preimage bit {}", i)), b)
            })
            // Convert the AllocatedBits into Booleans (required for the sha256 gadget).
            .map(|b| b.map(Boolean::from))
            .collect::<Result<Vec<_>, _>>()?;

        // Compute hash = SHA-256(preimage).
        let hash = sha256(cs.namespace(|| "SHA-256(mid)"), &preimage_bits)?;

        // let public_input = hash
        // .chunks(8)
        // .map(|c| c.iter().rev())
        // .flatten()
        // .cloned()
        // .collect();

        // Expose the vector of 32 boolean variables as compact public inputs.
        multipack::pack_into_inputs(cs.namespace(|| "pack hash"), &hash)
}

}