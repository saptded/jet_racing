extern crate cc;

fn main() {
    cc::Build::new()
        .file("src/hpp/Position.h")
        .cpp_link_stdlib("libc++")
        .flag("-std=c++20")
        .compile("lib_server.a");
}
