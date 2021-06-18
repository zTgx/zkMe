#[no_mangle]
pub extern "C" fn hello_world() {
    println!("Hello world from bellman.");
}

#[cfg(test)]
mod tests {
    #[test]
    fn it_works() {
        assert_eq!(2 + 2, 4);
    }
}
