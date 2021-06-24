#ifndef RUST_LIB
#define RUST_LIB

#ifdef __cplusplus
extern "C" {
#endif
    /// Creates a proving context. Please free this when you're done.
    void * librust_proving_ctx_init(); 

    /// This function constructs a proof given the necessary witness information. 
    bool librust_proof(void *ctx, unsigned char* inputs, unsigned char *zkproof);

    // Free a proving context.
    void librust_proving_ctx_free(void *);

    /// Creates a verification context. Please free this
    /// when you're done.
    void * librust_verification_ctx_init();

    /// Checks the validity of the
    /// transaction given the binding signature.
    bool librust_verification_check(void *ctx, const char* proof, const char* inputs);

    /// Frees a verification context.
    void librust_verification_ctx_free(void *);

    void hello_world();

#ifdef __cplusplus
}
#endif

#endif