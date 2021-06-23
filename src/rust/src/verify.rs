use crate::proof::VerificationContext;
use libc::c_char;
use std::ffi::CStr;

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