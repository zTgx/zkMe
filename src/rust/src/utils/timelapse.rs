use std::time::SystemTime;

pub struct TimeElapse {
    now: SystemTime
}

impl TimeElapse {
    pub fn new() -> Self {
        TimeElapse {
            now: SystemTime::now()
        }
    }

    pub fn elapsed(&self) -> u64 {
        match self.now.elapsed() {
            Ok(elapsed) => {
                return elapsed.as_secs();
            }
            Err(e) => {
                // an error occurred!
                panic!("Error: {:?}", e);
            }
        }
    }
}