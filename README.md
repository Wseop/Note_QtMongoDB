# Note_QtMongoDB
Qt Project에서 MongoDB를 사용하기 위한 환경 설정 방법 및 사용 코드 예제
## 프로젝트 환경
* Windows 10
* Qt 6.4.0 MinGW 64-bit
* mongo-c-driver 1.22.1
* mongo-cxx-driver r3.7.0
## Build & Install MongoDB C++ Driver 
### 1. MSYS2 설치
* [MSYS2를 설치 후](https://www.msys2.org/) MSYS2-MinGW64를 관리자 권한으로 실행
* driver build를 위한 tool download
```
# pacman --noconfirm -Syu (실행 후 창 닫힘)
# pacman --noconfirm -S mingw-w64-x86_64-gcc mingw-w64-x86_64-cmake
# pacman --noconfirm -S mingw-w64-x86_64-extra-cmake-modules make tar
# pacman --noconfirm -S mingw64/mingw-w64-x86_64-cyrus-sasl
# pacman --noconfirm -S mingw-w64-x86_64-toolchain
```
* 그 외 build 중 추가로 필요한 tool이 있을 경우 pacman으로 설치
### 2. Mongo C driver 설치
* [Mongo C driver releases page](https://github.com/mongodb/mongo-c-driver/releases)
* Preparing a build
```
# wget https://github.com/mongodb/mongo-c-driver/releases/download/1.22.1/mongo-c-driver-1.22.1.tar.gz
# tar xzf mongo-c-driver-1.22.1.tar.gz
# cd mongo-c-driver-1.22.1
# mkdir cmake-build
# cd cmake-build
# cmake -DENABLE_AUTOMATIC_INIT_AND_CLEANUP=OFF .. -G "MinGW Makefiles" -DCMAKE_INSTALL_PREFIX=[설치 경로]
```
* cmake 설정이 완료되면 아래 메세지 출력
```
build files have been written to: .../mongo-c-driver-1.22.1/cmake-build
```
* Build & Install
```
# cmake --build . --target install
```
### 3. Mongocxx driver 설치
* [Mongocxx driver releases page](https://github.com/mongodb/mongo-cxx-driver/releases)
* Preparing a build
```
# wget https://github.com/mongodb/mongo-cxx-driver/releases/download/r3.7.0/mongo-cxx-driver-r3.7.0.tar.gz
# tar xzf mongo-cxx-driver-r3.7.0.tar.gz
# cd mongo-cxx-driver-r3.7.0/build
# cmake .. -G "MinGW Makefiles" -DCMAKE_PREFIX_PATH=[mongo-c-driver 설치 경로] -DCMAKE_INSTALL_PREFIX=[설치 경로]
```
* cmake 설정이 완료되면 아래 메세지 출력
```
build files have been written to: .../mongo-cxx-driver-r3.7.0/build
```
* Build & Install
```
# cmake --build . --target install
```
## MongoDB Library 사용
* Qt Project에서 libbsoncxx, libmongocxx 라이브러리 추가
* 프로젝트 실행 파일이 존재하는 디렉토리에 libbsoncxx.dll, libmongocxx.dll, lbbson-1.0.dll, libmongoc-1.0.dll 복사하여 사용
* 추가) libzstd.dll과 zlib1.dll도 함께 추가 필요, msys2 - mingw64가 설치된 폴더에 있다. (이전에는 없이 실행이 됐는데 어느순간 필요해졌음. 왜?...)
