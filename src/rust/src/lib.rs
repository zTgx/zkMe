#[cfg(test)]
mod tests {
    #[test]
    fn it_works() {
        assert_eq!(2 + 2, 4);
    }
}

extern crate bellman;
extern crate bls12_381;

pub mod librustbellman;
pub mod proof;
pub mod circuit;