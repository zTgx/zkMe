use proof::VerificationContext;

#[no_mangle]
pub extern "C" fn librust_verification_ctx_init()  -> *mut VerificationContext {
    let ctx = Box::new(VerificationContext::new());

    Box::into_raw(ctx)
}

#[no_mangle]
pub extern "C" fn librust_verification_check() -> bool {
    true
}

#[no_mangle]
pub extern "C" fn librust_verification_ctx_free(_ctx: *mut VerificationContext) {

}