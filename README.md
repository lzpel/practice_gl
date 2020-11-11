# GLTFを表示するサンプル

## ビルド方法

sdl2/ glfw/ glfw-gltf/ 共通

```
#依存ライブラリをdependency/以下に配置する
./setup.sh

# CMakeを使ってビルドするときは、次のように必ずソースディレクトリとは別にビルド専用のディレクトリを作成し、その中でビルドします。
mkdir build
cd build
cmake ..
make
```