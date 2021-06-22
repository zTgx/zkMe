
use bellman::{
    Circuit,
    ConstraintSystem,
    SynthesisError
};
use bellman::groth16::{
    Proof,
    generate_random_parameters,
    prepare_verifying_key,
    create_random_proof,
    verify_proof,
};

pub struct Amount {
    pub pay_address: String,
    pub value: String,
    pub out_address: String,
}

pub struct Tx {
    pub hash: String,
    pub amount: Amount,
}

/*

*/
impl Circuit<bls12_381::Scalar> for Tx {
    fn synthesize<CS: ConstraintSystem<bls12_381::Scalar>>(
        self, 
        cs: &mut CS
    ) -> Result<(), SynthesisError> {
        Ok(())
}

}