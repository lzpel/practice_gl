# SDL2-CLion-Windows
- WindowsとCLionとSDL2でゲーム開発環境を整える
- Minimal example of animating OpenGL on SDL2, developed by CLion in Windows
## 用語
- CMakeはコンパイラに依存しないビルド自動化のためのフリーソフトウェアであり、様々なオペレーティングシステムで動作させることができます。

- MinGW（Minimalist GNU for Windows）はGCC などの開発環境をWindowsで利用できるようにしてくれるソフトウェア群です。C/C++コンパイラgcc/g++、作業自動化ツールmake等を含みます。

- CLionはJetBrains社が開発したC/C++の統合開発環境です、CLionのビルド作業はCMakeで自動化されます。CLionのコンパイルやリンクはMinGWのgcc/g++が使われます（MinGW toolchainを用いた場合）

## Linux環境との互換性
以下の方法は`sudo apt-get install -y libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev` 等のコマンドでLinux上の開発環境を整備することとほぼ同等です。したがって同じソースコードをUbuntuとWindowsでコンパイルできます。

## インストール

### Install MinGW

[mingw-get-setup.exe](https://osdn.net/projects/mingw/downloads/68260/mingw-get-setup.exe/)をダウンロードしインストールします。

- 標準構成で大丈夫です

CLionはMinGWの内makeとg++とgccしか参照しません。
後の操作でMinGWのmsys-bashを用いる場合があります。
上記は標準でインストールされます。

- インストールディレクトリはC:\MinGWにしてください

他でも問題ないかもしれませんがそれを前提に進めます

- MinGWのbinディレクトリを環境変数PATHを通してください

C:\MinGWにインストールした場合、環境変数PATHにC:\MinGW\binを追加してください。
環境変数PATHはdllの検索対象なので後述する段階でbinの中にSDL2で用いるdll（SDL2.dll, libjpeg-9.dll等）をコピーします。
これによりビルドしたexeのの隣にSDL2が依存するdllを配置する必要がなくなります。

#### TIPS: windowsにおけるdllの検索順序
以下の順で検索されます
1. アプリケーションの exe ファイルが存在するディレクトリ
2. システムディレクトリ
3. 16-bit システムディレクトリ
4. Windows ディレクトリ
5. カレントディレクトリ
6. 環境変数 PATH に設定されてたディレクトリ

### Install SDL2, SDL2_image, SDL2_mixer

- SDL2, SDL2_image, SDL2_mixer 等のSDL関係のライブラリをダウンロードします

開発目的でMinGWと共に利用するのでdevelとmingwがつくファイルをダウンロードしてください。
例：SDL2-devel-2.0.10-mingw.tar.gz, SDL2_image-devel-2.0.5-mingw.tar.gz

- tar.gz 圧縮ファイルを展開します

.tar.gzを展開する方法は心当たりがあれば何でもいいです。

MinGWのMSYSというシェルのtarコマンドを利用してみます。

MinGWをC:\MinGW\にインストールした場合`C:\MinGW\msys\1.0\msys.bat`というファイルをダブルクリックしたらシェルが起動します。
`tar -zxvf xxx.tar.gz`でxxx.tar.gzファイルを展開できます。

- 展開されたファイルをMinGWにコピーする

展開されたSDL2-2.0.10ディレクトリにはi686-w64-mingw32とx86_64-w64-mingw32というサブディレクトリがあります。
ビルド対象のアーキテクチャが32bitなら前者、64bitなら後者を使用します。
ビルド対象のアーキテクチャは必ずしも貴方のOSやCPUと一致せず、取り違えるとリンクエラーになるので注意してください。

簡単な調査方法を用意しました。以下のコマンドの結果が4なら前者、8なら後者を使用してください。
```
echo -e "#include<stdio.h>\nint main(){printf(\"%d\",sizeof(void*));return 0;}" > a.c ; gcc a.c -o a ; ./a
```
筆者の環境では4と表示されたのでi686-w64-mingw32ディレクトリを使用します。
i686-w64-mingw32の中にbin, lib, include というサブディレクトリがあります。
以下の手順でコピーします。
1. binの中身はC:\MinGW\binにコピー
2. libの中身はC:\MinGW\libにコピー
3. includeの中身はC:\MinGW\includeにコピー

同様にSDL2_image-2.0.5, SDL2_mixer等の展開済みディレクトリに対しても上記の操作を行ってください。

#### TIPS: .TAR.GZとは何
tarはtarコマンドで生成されるファイルの拡張子でtape archivesの略です。
tarはアーカイブ（複数のファイルを単一ファイルにまとめる）しますが圧縮はしません。

gzはgzipコマンドにより生成されるファイルの拡張子でgzipはバイト列を圧縮するコマンドです。
gzipは圧縮はしますが複数ファイルをアーカイブする機能は持ちません。

.tar.gzとはアーカイブした後に圧縮するという意味です。
linuxは単純な機能のコマンドの集合で高等な操作を実現することを尊ぶ文化なので圧縮とアーカイブ（単一ファイル化）を別々の機能に分けました。

## サンプルの実行

### Write CMakeLists.txt
mygameはプロジェクト名です適宜変更してください。
target_link_librariesでインストールしたSDL2やopenglをリンクしています。
ここで指定したライブラリはg++コマンドのリンクオプションに` -lSDL2 -lSDL2_image `として与えられ、
g++はC:\MinGW\libからそれらのライブラリを検索します
```
cmake_minimum_required(VERSION 3.12)
project(mygame)
file(GLOB sourcefiles "*.h" "*.cpp")
add_executable(${PROJECT_NAME} ${sourcefiles})
find_package(OpenGL)
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} SDL2_image SDL2 SDL2main)
```
### Write main.cpp
以下の点に注意してください
1. SDL_MAIN_HANDLED マクロを定義すること
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
