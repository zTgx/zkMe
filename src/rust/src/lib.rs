#[no_mangle]
pub extern "C" fn hello_world() {
    println!("Hello world from Bellman.");
}

#[cfg(test)]
mod tests {
    #[test]
    fn it_works() {
        assert_eq!(2 + 2, 4);
    }
}

extern crate bellman;
extern crate bls12_381;


pub mod prove;
pub mod verify;
pub mod proof;
pub mod circuit;