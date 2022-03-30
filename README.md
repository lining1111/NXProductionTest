# NX板子监控软件

    这个工程的主要目的是为了实现c++来进行通信和后续的算法内容，然后通过swig被go调用，然后在进行编译，包括交叉编译

    查看当前环境变量
    go env

## 编译 win64 exe

    //sudo apt-get install gcc-mingw-w64
    CGO_ENABLED=1 GOOS=windows GOARCH=amd64 CC=x86_64-w64-mingw32-gcc AR=X86_64-w64-ming32-ar CXX=X86_64-w64-ming32-g++ CGO_CXXFLAGS="-g -O2 -std=c++11" go build

## 编译arm64

    CGO_ENABLED=1 GOOS=linux GOARCH=arm64 CC=aarch64-linux-gnu-gcc AR=aarch64-linux-gnu-ar CXX=aarch64-linux-gnu-g++ CGO_CXXFLAGS="-g -O2 -std=c++11"  go build
