FROM debian:10

RUN echo "deb http://apt.llvm.org/zesty/ llvm-toolchain-zesty main" > /etc/apt/sources.list


RUN wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | sudo apt-key add -
RUN apt update
RUN apt install git cmake ninja-build clang lld -y
RUN git clone --recursive https://github.com/lewissbaker/cppcoro.git cppcoro
RUN cd cppcoro && source init.sh

