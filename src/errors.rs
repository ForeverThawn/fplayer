#[derive(Debug, PartialEq)]
pub enum KgmErrors {
    InvalidFileExtType,
    FileNotFound,
    FileAlreadyInUse, // FileWriteError
    FileReadError,

}

