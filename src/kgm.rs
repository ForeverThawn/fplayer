use lazy_static::lazy_static;
use std::sync::Mutex;
use crate::errors::KgmErrors;

use std::fs::File;
use std::io::{self, Read, Write, Seek};

lazy_static! {
    static ref VPR_HEADER: Mutex<Vec<u8>> = Mutex::new(vec![
        0x05, 0x28, 0xBC, 0x96, 0xE9, 0xE4, 0x5A, 0x43,
        0x91, 0xAA, 0xBD, 0xD0, 0x7A, 0xF5, 0x36, 0x31
    ]);

    static ref KGM_HEADER: Mutex<Vec<u8>> = Mutex::new(vec![
        0x7C, 0xD5, 0x32, 0xEB, 0x86, 0x02, 0x7F, 0x4B,
        0xA8, 0xAF, 0xA6, 0x8E, 0x0F, 0xFF, 0x99, 0x14
    ]);

    static ref VPR_MASK_DIFF: Mutex<Vec<u8>> = Mutex::new(vec![
        0x25, 0xDF, 0xE8, 0xA6, 0x75, 0x1E, 0x75, 0x0E,
        0x2F, 0x80, 0xF3, 0x2D, 0xB8, 0xB6, 0xE3, 0x11, 0x00
    ]);

    // static ref MASK_V2: Mutex<Vec<u8>> = Mutex::new(Vec::new());

    static ref TABLE_1: Mutex<Vec<u8>> = Mutex::new(vec![
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x01, 0x21, 0x01, 0x61, 0x01, 0x21, 0x01, 0xe1, 0x01, 0x21, 0x01, 0x61, 0x01, 0x21, 0x01,
        0xd2, 0x23, 0x02, 0x02, 0x42, 0x42, 0x02, 0x02, 0xc2, 0xc2, 0x02, 0x02, 0x42, 0x42, 0x02, 0x02,
        0xd3, 0xd3, 0x02, 0x03, 0x63, 0x43, 0x63, 0x03, 0xe3, 0xc3, 0xe3, 0x03, 0x63, 0x43, 0x63, 0x03,
        0x94, 0xb4, 0x94, 0x65, 0x04, 0x04, 0x04, 0x04, 0x84, 0x84, 0x84, 0x84, 0x04, 0x04, 0x04, 0x04,
        0x95, 0x95, 0x95, 0x95, 0x04, 0x05, 0x25, 0x05, 0xe5, 0x85, 0xa5, 0x85, 0xe5, 0x05, 0x25, 0x05,
        0xd6, 0xb6, 0x96, 0xb6, 0xd6, 0x27, 0x06, 0x06, 0xc6, 0xc6, 0x86, 0x86, 0xc6, 0xc6, 0x06, 0x06,
        0xd7, 0xd7, 0x97, 0x97, 0xd7, 0xd7, 0x06, 0x07, 0xe7, 0xc7, 0xe7, 0x87, 0xe7, 0xc7, 0xe7, 0x07,
        0x18, 0x38, 0x18, 0x78, 0x18, 0x38, 0x18, 0xe9, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
        0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x08, 0x09, 0x29, 0x09, 0x69, 0x09, 0x29, 0x09,
        0xda, 0x3a, 0x1a, 0x3a, 0x5a, 0x3a, 0x1a, 0x3a, 0xda, 0x2b, 0x0a, 0x0a, 0x4a, 0x4a, 0x0a, 0x0a,
        0xdb, 0xdb, 0x1b, 0x1b, 0x5b, 0x5b, 0x1b, 0x1b, 0xdb, 0xdb, 0x0a, 0x0b, 0x6b, 0x4b, 0x6b, 0x0b,
        0x9c, 0xbc, 0x9c, 0x7c, 0x1c, 0x3c, 0x1c, 0x7c, 0x9c, 0xbc, 0x9c, 0x6d, 0x0c, 0x0c, 0x0c, 0x0c,
        0x9d, 0x9d, 0x9d, 0x9d, 0x1d, 0x1d, 0x1d, 0x1d, 0x9d, 0x9d, 0x9d, 0x9d, 0x0c, 0x0d, 0x2d, 0x0d,
        0xde, 0xbe, 0x9e, 0xbe, 0xde, 0x3e, 0x1e, 0x3e, 0xde, 0xbe, 0x9e, 0xbe, 0xde, 0x2f, 0x0e, 0x0e,
        0xdf, 0xdf, 0x9f, 0x9f, 0xdf, 0xdf, 0x1f, 0x1f, 0xdf, 0xdf, 0x9f, 0x9f, 0xdf, 0xdf, 0x0e, 0x0f,
        0x00, 0x20, 0x00, 0x60, 0x00, 0x20, 0x00, 0xe0, 0x00, 0x20, 0x00, 0x60, 0x00, 0x20, 0x00, 0xf1,
    ]);

    static ref TABLE_2: Mutex<Vec<u8>> = Mutex::new(vec![
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x01, 0x23, 0x01, 0x67, 0x01, 0x23, 0x01, 0xef, 0x01, 0x23, 0x01, 0x67, 0x01, 0x23, 0x01,
        0xdf, 0x21, 0x02, 0x02, 0x46, 0x46, 0x02, 0x02, 0xce, 0xce, 0x02, 0x02, 0x46, 0x46, 0x02, 0x02,
        0xde, 0xde, 0x02, 0x03, 0x65, 0x47, 0x65, 0x03, 0xed, 0xcf, 0xed, 0x03, 0x65, 0x47, 0x65, 0x03,
        0x9d, 0xbf, 0x9d, 0x63, 0x04, 0x04, 0x04, 0x04, 0x8c, 0x8c, 0x8c, 0x8c, 0x04, 0x04, 0x04, 0x04,
        0x9c, 0x9c, 0x9c, 0x9c, 0x04, 0x05, 0x27, 0x05, 0xeb, 0x8d, 0xaf, 0x8d, 0xeb, 0x05, 0x27, 0x05,
        0xdb, 0xbd, 0x9f, 0xbd, 0xdb, 0x25, 0x06, 0x06, 0xca, 0xca, 0x8e, 0x8e, 0xca, 0xca, 0x06, 0x06,
        0xda, 0xda, 0x9e, 0x9e, 0xda, 0xda, 0x06, 0x07, 0xe9, 0xcb, 0xe9, 0x8f, 0xe9, 0xcb, 0xe9, 0x07,
        0x19, 0x3b, 0x19, 0x7f, 0x19, 0x3b, 0x19, 0xe7, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
        0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x08, 0x09, 0x2b, 0x09, 0x6f, 0x09, 0x2b, 0x09,
        0xd7, 0x39, 0x1b, 0x39, 0x5f, 0x39, 0x1b, 0x39, 0xd7, 0x29, 0x0a, 0x0a, 0x4e, 0x4e, 0x0a, 0x0a,
        0xd6, 0xd6, 0x1a, 0x1a, 0x5e, 0x5e, 0x1a, 0x1a, 0xd6, 0xd6, 0x0a, 0x0b, 0x6d, 0x4f, 0x6d, 0x0b,
        0x95, 0xb7, 0x95, 0x7b, 0x1d, 0x3f, 0x1d, 0x7b, 0x95, 0xb7, 0x95, 0x6b, 0x0c, 0x0c, 0x0c, 0x0c,
        0x94, 0x94, 0x94, 0x94, 0x1c, 0x1c, 0x1c, 0x1c, 0x94, 0x94, 0x94, 0x94, 0x0c, 0x0d, 0x2f, 0x0d,
        0xd3, 0xb5, 0x97, 0xb5, 0xd3, 0x3d, 0x1f, 0x3d, 0xd3, 0xb5, 0x97, 0xb5, 0xd3, 0x2d, 0x0e, 0x0e,
        0xd2, 0xd2, 0x96, 0x96, 0xd2, 0xd2, 0x1e, 0x1e, 0xd2, 0xd2, 0x96, 0x96, 0xd2, 0xd2, 0x0e, 0x0f,
        0x00, 0x22, 0x00, 0x66, 0x00, 0x22, 0x00, 0xee, 0x00, 0x22, 0x00, 0x66, 0x00, 0x22, 0x00, 0xfe,    
    ]);

    static ref MASK_V2_PREDEF: Mutex<Vec<u8>> = Mutex::new(vec![
        0xB8, 0xD5, 0x3D, 0xB2, 0xE9, 0xAF, 0x78, 0x8C, 0x83, 0x33, 0x71, 0x51, 0x76, 0xA0, 0xCD, 0x37,
        0x2F, 0x3E, 0x35, 0x8D, 0xA9, 0xBE, 0x98, 0xB7, 0xE7, 0x8C, 0x22, 0xCE, 0x5A, 0x61, 0xDF, 0x68,
        0x69, 0x89, 0xFE, 0xA5, 0xB6, 0xDE, 0xA9, 0x77, 0xFC, 0xC8, 0xBD, 0xBD, 0xE5, 0x6D, 0x3E, 0x5A,
        0x36, 0xEF, 0x69, 0x4E, 0xBE, 0xE1, 0xE9, 0x66, 0x1C, 0xF3, 0xD9, 0x02, 0xB6, 0xF2, 0x12, 0x9B,
        0x44, 0xD0, 0x6F, 0xB9, 0x35, 0x89, 0xB6, 0x46, 0x6D, 0x73, 0x82, 0x06, 0x69, 0xC1, 0xED, 0xD7,
        0x85, 0xC2, 0x30, 0xDF, 0xA2, 0x62, 0xBE, 0x79, 0x2D, 0x62, 0x62, 0x3D, 0x0D, 0x7E, 0xBE, 0x48,
        0x89, 0x23, 0x02, 0xA0, 0xE4, 0xD5, 0x75, 0x51, 0x32, 0x02, 0x53, 0xFD, 0x16, 0x3A, 0x21, 0x3B,
        0x16, 0x0F, 0xC3, 0xB2, 0xBB, 0xB3, 0xE2, 0xBA, 0x3A, 0x3D, 0x13, 0xEC, 0xF6, 0x01, 0x45, 0x84,
        0xA5, 0x70, 0x0F, 0x93, 0x49, 0x0C, 0x64, 0xCD, 0x31, 0xD5, 0xCC, 0x4C, 0x07, 0x01, 0x9E, 0x00,
        0x1A, 0x23, 0x90, 0xBF, 0x88, 0x1E, 0x3B, 0xAB, 0xA6, 0x3E, 0xC4, 0x73, 0x47, 0x10, 0x7E, 0x3B,
        0x5E, 0xBC, 0xE3, 0x00, 0x84, 0xFF, 0x09, 0xD4, 0xE0, 0x89, 0x0F, 0x5B, 0x58, 0x70, 0x4F, 0xFB,
        0x65, 0xD8, 0x5C, 0x53, 0x1B, 0xD3, 0xC8, 0xC6, 0xBF, 0xEF, 0x98, 0xB0, 0x50, 0x4F, 0x0F, 0xEA,
        0xE5, 0x83, 0x58, 0x8C, 0x28, 0x2C, 0x84, 0x67, 0xCD, 0xD0, 0x9E, 0x47, 0xDB, 0x27, 0x50, 0xCA,
        0xF4, 0x63, 0x63, 0xE8, 0x97, 0x7F, 0x1B, 0x4B, 0x0C, 0xC2, 0xC1, 0x21, 0x4C, 0xCC, 0x58, 0xF5,
        0x94, 0x52, 0xA3, 0xF3, 0xD3, 0xE0, 0x68, 0xF4, 0x00, 0x23, 0xF3, 0x5E, 0x0A, 0x7B, 0x93, 0xDD,
        0xAB, 0x12, 0xB2, 0x13, 0xE8, 0x84, 0xD7, 0xA7, 0x9F, 0x0F, 0x32, 0x4C, 0x55, 0x1D, 0x04, 0x36,
        0x52, 0xDC, 0x03, 0xF3, 0xF9, 0x4E, 0x42, 0xE9, 0x3D, 0x61, 0xEF, 0x7C, 0xB6, 0xB3, 0x93, 0x50,
    ]);



}

fn get_mask(
    pos: usize,
) -> u8 {
    let mut offset = pos >> 4;
    let mut value = 0;

    let table1 = TABLE_1.lock().unwrap();
    let table2 = TABLE_2.lock().unwrap();

    while offset >= 0x11 {
        value ^= table1[offset % 272];
        offset >>= 4;
        value ^= table2[offset % 272];
        offset >>= 4;
    }

    let final_pos = pos % 272;
    let mask_v2_predef = MASK_V2_PREDEF.lock().unwrap();

    mask_v2_predef[final_pos] ^ value
}

fn get_ext_from_file_name(
    file_name: String
) -> Result<String, KgmErrors> {
    // kgm => mp3
    if file_name.contains(".kgm") && !file_name.contains(".kgma") {
        Ok(String::from("mp3"))
    } 
    // vpr => null
    else if file_name.contains(".vpr") {
        Ok(String::from("flac"))
    } 
    // kgma => kgm
    else if file_name.contains(".kgma") { 
        Ok(String::from("flac"))
    }

    else {
        Err(KgmErrors::InvalidFileExtType)
    }
}

pub fn decrypt_kgm(
    file_name: &str,
    psw_fn: &str, 
) {
    let mut infile = if !psw_fn.is_empty() {
        File::open(psw_fn)
    } else {
        File::open(file_name)
    };

    if infile.is_err() {
        eprintln!("Cannot read file \"{}\"", file_name);
        return;
    }

    let mut infile = infile.unwrap();
    let mut b_header_len = [0u8; 4];

    // 0x10 位 4字节 确定文件头 默认是00
    infile.seek(io::SeekFrom::Start(0x10)).unwrap();
    infile.read_exact(&mut b_header_len).unwrap();

    // 默认
    let header_len = if psw_fn.is_empty() {
        u32::from_le_bytes(b_header_len)
    } else {
        0
    };

    let mut key = [0u8; 17];
    infile.seek(io::SeekFrom::Start(0x1c)).unwrap();
    infile.read_exact(&mut key[..16]).unwrap();
    key[16] = 0;

    if !psw_fn.is_empty() {
        infile = File::open(file_name).unwrap();
    }

    let file_metadata = infile.metadata().unwrap();
    let mut file_data = vec![0u8; file_metadata.len() as usize - header_len as usize];
    infile.seek(io::SeekFrom::Start(header_len as u64)).unwrap();
    infile.read_exact(&mut file_data).unwrap();

    for i in 0..file_data.len() {
        let med8 = key[i % 17] ^ file_data[i];
        let med8 = med8 ^ (med8 & 0xf) << 4;

        let msk8 = get_mask(i);
        let msk8 = msk8 ^ (msk8 & 0xf) << 4;
        file_data[i] = med8 ^ msk8;
    }

    if file_name.contains(".vpr") {
        let vpr_mask_diff = VPR_MASK_DIFF.lock().unwrap();
        for i in 0..file_data.len() {
            file_data[i] ^= vpr_mask_diff[i % 17];
        }
    }

    // 后期 记得错误处理
    let ext = get_ext_from_file_name(file_name.to_string()).unwrap();
    let out_file_name = format!("{}.{}", file_name, &ext);
    let mut outfile = File::create(out_file_name).unwrap();

    outfile.write_all(&file_data).unwrap();
}

#[allow(unused_macros)]
macro_rules! decrypt_kgm {
    // 默认psw空
    ($file_name: expr) => {
        decrypt_kgm($file_name, "")
    };

    // 一般情况
    ($file_name: expr, $psw_fn: expr) => {
        decrypt_kgm($file_name, $psw_fn)
    };
}

mod tests {
    #[test]
    fn get_ext_works() {
        let files = ["a.kgm", "b.vpr", "c.kgma"];
        let exts = ["mp3", "flac", "flac"];

        for (f, e) in files.iter().zip(exts.iter()) {
            assert_eq!(super::get_ext_from_file_name(f.to_string()).unwrap(), e.to_string());
        }

        let error_file = "d.mp3";
        let error_exts = super::KgmErrors::InvalidFileExtType;
        assert_eq!(super::get_ext_from_file_name(error_file.to_string()).unwrap_err(), error_exts);
    }
}