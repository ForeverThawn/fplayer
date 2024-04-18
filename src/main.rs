
mod errors;

#[macro_use]
mod kgm;
use crate::kgm::decrypt_kgm;

fn main() {
    // let file_result = File::open("Mood(Clean).kgm");

    // match file_result {
    //     Ok(file) => println!("File opened successfully: {:?}", file),
    //     Err(error) => eprintln!("Error opening file: {}", error),
    // }
    decrypt_kgm!("../samples/Mood(Clean).kgm");
    decrypt_kgm!("../samples/YOASOBI - Monster.kgma");
    decrypt_kgm!("../samples/Alan Walker - Sing Me to Sleep (Instrumental).vpr");
}