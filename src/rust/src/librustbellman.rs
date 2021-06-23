
use crate::circuit::tx::Tx;
use bellman::groth16;
use bls12_381::Bls12;
use rand::rngs::OsRng;
use sha2::{Digest, Sha256};
use libc::{c_char, c_uchar};
use std::ffi::CStr;
use crate::proof::VerificationContext;
use crate::proof::ProvingContext;


const GROTH_PROOF_SIZE: usize = 
      48 // π_A
    + 96 // π_B
    + 48; // π_C

#[no_mangle]
pub extern "C" fn librust_proving_ctx_init() -> *mut ProvingContext {
    println!("init proving context");

    let ctx = Box::new(ProvingContext::new());

    Box::into_raw(ctx)
}

#[no_mangle]
pub extern "C" fn librust_proof(ctx: *mut ProvingContext, inputs: *const c_char, zkproof: *mut [c_uchar; GROTH_PROOF_SIZE]) -> bool {

    let s = unsafe {
        CStr::from_ptr(inputs).to_string_lossy().into_owned()
    };

    let mut a: [u8; 33] = [0u8;33];
    a.copy_from_slice(&s.as_bytes()[0..33]);

    let proof = unsafe { &mut *ctx }.spend_proof(a);

    // Write proof out to caller
    proof
    .write(&mut (unsafe { &mut *zkproof })[..])
    .expect("should be able to serialize a proof");

    true
}

// https://doc.rust-lang.org/std/primitive.pointer.html#:~:text=unsafe%20%7B%0A%20%20%20%20drop(Box%3A%3Afrom_raw(my_speed))%3B%0A%7D
#[no_mangle]
pub extern "C" fn librust_proving_ctx_free(ctx: *mut ProvingContext) {
    println!("release proving context");

    unsafe {
        drop(Box::from_raw(ctx));
    }
}

////
/// 
/// 

#[no_mangle]
pub extern "C" fn librust_verification_ctx_init()  -> *mut VerificationContext {
    let ctx = Box::new(VerificationContext::new());

    Box::into_raw(ctx)
}

#[no_mangle]
pub extern "C" fn librust_verification_check(ctx: *mut VerificationContext, pvk: *const c_char, proof: *const c_char, inputs: *const c_char) -> bool {
    // unsafe { &mut *ctx }.verify_proof(pvk, proof, inputs);

    true
}

#[no_mangle]
pub extern "C" fn librust_verification_ctx_free(_ctx: *mut VerificationContext) {

}