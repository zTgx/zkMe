use crate::proof::ProvingContext;

#[no_mangle]
pub extern "C" fn librust_proving_ctx_init() -> *mut ProvingContext {
    println!("init proving context");

    let ctx = Box::new(ProvingContext::new());

    Box::into_raw(ctx)
}

#[no_mangle]
pub extern "C" fn librust_proof(ctx: *mut ProvingContext) -> bool {
    let ret = unsafe { &mut *ctx }.spend_proof();

    ret
}

#[no_mangle]
pub extern "C" fn librust_proving_ctx_free(ctx: *mut ProvingContext) {
    println!("release proving context");

    unsafe {
        drop(Box::from_raw(ctx));
    }
}