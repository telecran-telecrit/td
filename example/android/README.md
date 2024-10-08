# TDLib Android example

This is an example of building `TDLib` for Android.
You need a Bash shell on Linux, macOS, or Windows with some common tools, a C++ compiler, JDK, PHP, perl, and gperf pre-installed.

## WIN dependencies:
* [Install bash git 2.6+ or bash 4.3+](https://github.com/git-for-windows/git/releases/)
* [Install gpref 3.0.1 for win32](https://gnuwin32.sourceforge.net/packages/gperf.htm)
* [Install Java JDK 17+](https://www.oracle.com/java/technologies/javase/jdk17-archive-downloads.html)
* [Install PHP 8.1+](https://www.php.net/downloads)
* [Install Perl 5](https://www.perl.org/get.html)
* [Install cmake 3+ and make 3.80+](https://cmake.org/cmake/help/latest/command/install.html)
* [Install llvm deps for git bash](https://github.com/Adriankhl/llvm-git-bash)
* [Install Clang 3.4+ or GCC 4.9+](https://habr.com/ru/articles/167281/)
* [Install Clang++ for windows from Visual Studio 16 2019+](https://www.wikihow.com/Install-Clang-on-Windows)
* [Install Visual Studio 16 2019+](https://learn.microsoft.com/en-us/visualstudio/releases/2019/release-notes)
* [Install ninja 1.12+](https://github.com/ninja-build/ninja/releases)

## LIN dependencies:
* apt-get install ***
* or
* yum install ***

* Add %JAVA_HOME% to system variables.
* Add %JAVA_HOME%/bin to system %PATH% variable.
* Add gpref/bin to system %PATH% variable.
* Add all other required binaries dependencies to system %PATH% variable.

## Building TDLib for Android

* Run the script `./check-environment.sh` to check that you have all required Unix tools and Java utilities. If the script exits with an error message, install the missing tool.
* Run the script `./fetch-sdk.sh` to download Android SDK to a local directory.
* Run the script `./build-openssl.sh` to download and build OpenSSL for Android.
* Run the script `./build-tdlib.sh` to build TDLib for Android.
* The built libraries are now located in the `tdlib/libs` directory. If [Java](https://github.com/tdlib/td#using-java) interface was built, then corresponding Java code is located in the `tdlib/java` directory, and standalone Java documentation can be found in the `tdlib/javadoc` directory. You can also use archives `tdlib/tdlib.zip` and `tdlib/tdlib-debug.zip`, which contain all aforementioned data.

If you already have installed Android SDK and NDK, you can skip the second step and specify existing Android SDK root path and Android NDK version as the first and the second parameters to the subsequent scripts. Make sure that the SDK includes android-34 platform and CMake 3.22.1.

If you already have prebuilt OpenSSL, you can skip the third step and specify path to the prebuild OpenSSL as the third parameter to the script `./build-tdlib.sh`.

If you want to update TDLib to a newer version, you need to run only the script `./build-tdlib.sh`.

You can specify different OpenSSL version as the fourth parameter to the script `./build-openssl.sh`. By default OpenSSL 1.1.1 is used because of much smaller binary footprint and better performance than newer OpenSSL versions.

You can build shared OpenSSL libraries instead of static ones by passing any non-empty string as the fifth parameter to the script `./build-openssl.sh`. This can reduce total application size if you have a lot of other code that uses OpenSSL and want it to use the same shared library.

You can build TDLib against shared standard C++ library by specifying "c++_shared" as the fourth parameter to the script `./build-tdlib.sh`. This can reduce total application size if you have a lot of other C++ code and want it to use the same shared library.

You can also build TDLib with [JSON interface](https://github.com/tdlib/td#using-json) instead of [Java](https://github.com/tdlib/td#using-java) interface by passing "JSON" as the fifth parameter to the script `./build-tdlib.sh`.

You can also build TDLib with [JSON interface](https://github.com/tdlib/td#using-json) that can be called from Java by passing "JSONJava" as the fifth parameter to the script `./build-tdlib.sh`.

You can pass an empty string instead of any script parameter to use its default value. For example, you can use the command `./build-tdlib.sh '' '' '' '' 'JSON'` to build TDLib with [JSON interface](https://github.com/tdlib/td#using-json) using default values for other parameters.

Alternatively, you can use Docker to build TDLib for Android. Use `docker build --output tdlib .` to build the latest TDLib commit from Github, or `docker build --build-arg COMMIT_HASH=<commit-hash> --output tdlib .` to build specific commit. The output archives will be placed in the directory "tdlib" as specified. Additionally, you can specify build arguments "TDLIB_INTERFACE", "ANDROID_NDK_VERSION", "OPENSSL_VERSION", "BUILD_SHARED_OPENSSL_LIBS", and "ANDROID_STL" to the provided Dockerfile. For example, use `docker build --build-arg TDLIB_INTERFACE=JSON --output tdlib .` to build the latest TDLib with JSON interface.
