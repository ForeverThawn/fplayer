use std::process::Command;
use std::env;
use std::path::Path;

mod errors;

#[macro_use]
mod kgm;
use crate::kgm::decrypt_kgm;

fn main() -> Result<(), errors::CoreErrors>{
    let args: Vec<String> = env::args().collect();

    if args.len() < 2 {
        return Ok(())
    }
    
    let file_path = args[1].clone();
    if !Path::new(&file_path).exists() {
        return Err(errors::CoreErrors::FileNotFound)
    }

    if args[1].ends_with(".kgm") || args[1].ends_with(".vpr") {
        decrypt_kgm!(&file_path);
    }

    let mut fplayer_terminal = Command::new("core.com").args(&args).spawn().unwrap();
    let _result = fplayer_terminal.wait().unwrap();
    Ok(())
}