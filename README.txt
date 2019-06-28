C-STLDesigner3について

STLDesigner3.exeをコマンドプロンプトで実行して設計を行います。
(コマンド引数は同様に.ymlファイルのパスにしてください)

※.ymlの作り方についてはconfigフォルダに、SPICEファイルの作り方はtemplateフォルダに
それぞれまとめます。

設計結果のSPICESファイルについてはoutputフォルダが作成され、保存されます。



現在、C-STLDesigner3はvisual studioで開発・実行をしているため、
visual studioを使った使い方もまとめます。

(事前準備)HSPICEを環境変数のPATHに追加する

・visual studioをインストール(無償のコミュニティ版で問題ないです)
・ソリューションファイル(STLdesigner3.sln)を開く
・ツールバーのプロジェクト→プロパティからC/C++→追加のインクルードディレクトリに
　C-STLDesigner3のincludeへのパスを設定
・同様にプロパティからリンカー→追加のライブラリディレクトリにC-STLDesigner3の
　packages\boost.1.59.0.0を設定

以上で設定は完了

実際に設計する際は、プロパティからデバック→コマンド引数を任意の.ymlファイルのパスに
設定し、デバックなしで開始をすれば設計が開始します。



