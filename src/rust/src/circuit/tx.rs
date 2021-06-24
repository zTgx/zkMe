

use bellman::{
    gadgets::{
        boolean::{AllocatedBit, Boolean},
        multipack,
        sha256::sha256,
    },
    groth16, Circuit, ConstraintSystem, SynthesisError,
};
use sha2::{Digest, Sha256};
use ff::PrimeField;

pub struct Amount {
    // pub pay_address: Option<[u8; 2]>,
    // pub value: String,
    // pub out_address: String,
}

fn sha256d<Scalar: PrimeField, CS: ConstraintSystem<Scalar>>(
    mut cs: CS,
    data: &[Boolean],
) -> Result<Vec<Boolean>, SynthesisError> {
    // Flip endianness of each input byte
    let input: Vec<_> = data
        .chunks(8)
        .map(|c| c.iter().rev())
        .flatten()
        .cloned()
        .collect();

    let mid = sha256(cs.namespace(|| "SHA-256(input)"), &input)?;
    let res = sha256(cs.namespace(|| "SHA-256(mid)"), &mid)?;

    // Flip endianness of each output byte
    Ok(res
        .chunks(8)
        .map(|c| c.iter().rev())
        .flatten()
        .cloned()
        .collect())
}

pub struct Tx {
    // pub hash: String,
    // pub amount: Amount,
    pub pay_address: Option<[u8; 33]>,
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
            vec![None; 33 * 8]
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
        let hash = sha256d(cs.namespace(|| "SHA-256(preimage)"), &preimage_bits)?;

        // Expose the vector of 32 boolean variables as compact public inputs.
        multipack::pack_into_inputs(cs.namespace(|| "pack hash"), &hash)
}

}