# 日記

### Day02

BootLoaderのビルドのためにedk2の設定を2箇所書き換える必要がある。

- ビルドターゲット設定：edk2/Conf/target.txt（みかん本参照）
- クロスコンパイル設定：edk2/Conf/tools_def.txt（[参照](https://github.com/sarisia/mikanos-docker?tab=readme-ov-file#m1-mac-%E3%81%A7%E3%81%AE%E5%8B%95%E4%BD%9C%E3%81%AF)）

メモリマップをUEFI経由で取得し、特定のメモリ領域に格納。
その後、これまたUEFIの機能を使ってメモリマップの情報をcsv形式で出力。UEFIは割と何でもできる（気がする）。
OSがあればシステムコールを使ってファイルの入出力をするけど、UEFIを使ってファイル操作できるのは驚き。
BootLoaderで出力したcsvファイルは`disk.img`をマウントして確認可能。

### Day03

やっとカーネルを起動する。
BootLoaderのプログラムからUEFI経由でkernel.elfをメモリにロードし、実行の権限をカーネルに移す。

UEFIの機能を使って画面描画をする。
フレームバッファの開始アドレスを取得した後、ピクセル毎に値を書き込む。