pub struct ProvingContext {
    pub anno: String,
}
impl ProvingContext {
    pub fn new() -> ProvingContext {
        ProvingContext{
            anno: "ProvingContext".to_string()
        }
    }

    pub fn spend_proof(&self) -> bool {
        println!("spend proof.");

        true
    }
}

pub struct VerificationContext {}
impl VerificationContext {
    pub fn new() -> Self {
        VerificationContext{}
    }


}