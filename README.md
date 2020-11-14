# glpractice

C++/OpenGLの練習

## ディレクトリ構成

- glfw/
    - glfwで三角形を描画するだけ
- glfw-audio/
    - glfwとportaudioで音を鳴らす
    - 未完成
- glfw-engine/
    - 自作ゲームエンジン
    - まだ木構造を持ち座標軸を表示するだけ
- glfw-gltf/
    - tinygltfでgltfを描画してみた
    - Sketchfabで漁った幾つかのモデルはバグで正しく描画できない。
- sdl2/
    - sdl2で三角形を描画するだけ
    
各ディレクトリはそれぞれ課題を持つ独立したプログラム。で以下のようにCMakeでビルドできる。CLionで開くと簡単。

```
#依存ライブラリをdependency/以下に配置する
./setup.sh

# CMakeを使ってビルドするときは、次のように必ずソースディレクトリとは別にビルド専用のディレクトリを作成し、その中でビルドします。
mkdir build
cd build
cmake .
make
```
