# LightGBM Jni

Pre requirement:
* Compiled [LightGBM](https://github.com/Microsoft/LightGBM) library
* cmake 3.5
* exported JAVA_HOME

### To run test project:
1. Create symlink `lib_lightgbm.so` -> `/usr/lib/lib_lightgbm.so` so linker can find the library
```bash
sudo ln -s {your path}/lib_lightgbm.so /usr/lib/lib_lightgbm.so
```
2. Compile native code run in project directory
```bash
mkdir build; cd build
cmake ..
make -j
```
3. Run main in Test class with parameter `-Djava.library.path=build`



