#[derive(Debug, PartialEq)]
pub enum KgmErrors {
    InvalidFileExtType,
    FileNotFound,
    FileAlreadyInUse, // FileWriteError
    FileReadError,

}

#[derive(Debug, PartialEq)]
pub enum CoreErrors {
    FileNotFound,

    
}
