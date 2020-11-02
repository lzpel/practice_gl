# SDL2-CLion-Windows

- WindowsとCLionとSDL2でゲーム開発環境を整える
- Minimal example of animating OpenGL on SDL2, developed by CLion in Windows

## 用語

CMakeはコンパイラに依存しないビルド自動化のためのフリーソフトウェアであり、様々なオペレーティングシステムで動作させることができます。

MinGW（Minimalist GNU for Windows）はGCC などの開発環境をWindowsで利用できるようにしてくれるソフトウェア群です。C/C++コンパイラgcc/g++、作業自動化ツールmake等を含みます。

CLionはJetBrains社が開発したC/C++の統合開発環境です、CLionのビルド作業はCMakeで自動化されます。CLionのコンパイルやリンクはMinGWのgcc/g++が使われます（MinGW toolchainを用いた場合）

## Linux環境との互換性
以下の方法は`sudo apt-get install -y libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev` 等のコマンドでLinux上の開発環境を整備することとほぼ同等です。したがって同じソースコードをUbuntuとWindowsでコンパイルできます。

## インストール

### Install MinGW-W64

[MinGW-W64-install.exe](https://sourceforge.net/projects/mingw-w64/files/)をダウンロードしインストールします。
- 推奨設定
    - Architecture：CPUが64bitならx86_64、32bitならi686
    - Threads: posix
    - Exception: sjlj
        - m64とm32の両オプションを使用可能にするために指定する
	    - sefは32bit,dwarfは64bitでリンクエラーが生じる。
	- インストール先はCドライブ直下が良い。
	    - 例：　C:\mingw-w64\bin
        - binディレクトリに環境変数PATHを通してください

### Install SDL2

SDL2をシステムにインストールすると設定が汚れるのでプロジェクトにインストールします。

SDL2, SDL2_image, SDL2_mixer 等のSDL関係のライブラリをダウンロードします。
開発目的でMinGWと共に利用するのでdevelとmingwがつくtar.gzファイルをダウンロードしてください。
例：SDL2-devel-2.0.10-mingw.tar.gz, SDL2_image-devel-2.0.5-mingw.tar.gz

tar.gz 圧縮ファイルを展開しbin/、include/、lib/をSDL2-Clion-Windows/直下に配置してください。
面倒くさいのでシェルスクリプトを用意してあります。

1. 直下にSDL2-Clion-Windows/直下にSDL2**.tar.gzファイル達を配置します。
2. setup.shを実行してください。
    - 64bit環境ならば`./setup.sh -x86_64`
    - 32bit環境ならば`./setup.sh -i686`

setup.shは以下のようになっています。
最終行から分かるようにSDL2から始まるtar.gzファイルを検索し、
それぞれtarコマンドで展開しつつbin、lib、includeを直下に配置し他は/dev/nullに捨てています。

```shell script
#!/bin/bash
PREFIX="x86_64"
echo $1while getopts ":i686:x86_64" optKey; do
	case "$optKey" in
		i686) PREFIX="i686"
		x86_64) ;;
  esac
done
find -name "SDL2*.tar.gz" | xargs -I{} tar zxvf {} --transform="s,^[^/]+/x86_64[^/]+/(bin|include|lib),\1,x;s,^SDL2,/dev/null/,x" --absolute-names --show-transformed-names
```

## サンプルの実行

### Write CMakeLists.txt

mygameはプロジェクト名です適宜変更してください。
target_link_librariesでインストールしたSDL2やopenglをリンクしています。
ここで指定したライブラリはg++コマンドのリンクオプションに` -lSDL2 -lSDL2_image `として与えられ、
gccはinclude_directories(./include)に従いinclude/からそれらのライブラリを検索します。

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin")は先ほど配置した/bin内にexeが出力されることを意味します。
dllを検索できる位置にexeを配置しました。

```
cmake_minimum_required(VERSION 3.12)
project(mygame)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin")

include_directories(./include)
link_directories(./lib)

file(GLOB sourcefiles "*.h" "*.cpp")
add_executable(${PROJECT_NAME} ${sourcefiles})

find_package(OpenGL)
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} SDL2_image SDL2 SDL2main)
```
### Write main.cpp
以下の点に注意してください
1. SDL_MAIN_HANDLED マクロを#include <SDL2/SDL.h>の前に定義すること
2. \#include <SDL2/SDL.h>のようにSDL2/を頭につけること

CMSDL_MAIN_HANDLED マクロはmain関数のSDL_mainへの置換を無効化します。SDL2/はC:\MinGW\include\SDL2を参照するために必要です。

```
#define SDL_MAIN_HANDLED
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

static const int width = 480, height = 360, p=1000;

void draw() {
    int t=SDL_GetTicks()%p;
    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
    glColor3f(0.5+0.5*sin(5*M_PI*t/p), 0.5+0.5*sin(7*M_PI*t/p), 0.5+0.5*sin(11*M_PI*t/p));
    glVertex2f(sin(2*M_PI*t/p), 1);
    glVertex2f(-1, -1);
    glVertex2f(1, -1);
    glEnd();
    glFlush();
}

int main(int ArgCount, char **Args) {
    SDL_Window *Window = SDL_CreateWindow("OpenGL Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,SDL_WINDOW_OPENGL);
    SDL_GLContext Context = SDL_GL_CreateContext(Window);
    for (int Running = 1; Running;) {
        SDL_Event Event;
        while (SDL_PollEvent(&Event)) {
            if (Event.type == SDL_QUIT)Running = 0;
        }
        glViewport(0, 0, width, height);
        draw();
        SDL_GL_SwapWindow(Window);
    }
    return 0;
}
```
## Build and Run

![animating-gl](https://user-images.githubusercontent.com/18492524/64553010-87874600-d373-11e9-99d8-51effbe6df2b.gif)

おめでとうございます。