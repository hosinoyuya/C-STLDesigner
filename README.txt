C-STLDesigner3について

現在、C-STLDesigner3はvisual studioで開発・実行をしているため、
それに沿って使い方をまとめます。

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
また、visual studioのソリューション構成がReleaseになっていることを確認し、ビルドを行うと
C-STLDesigner3のReleaseフォルダ内にSTLdesigner3.exeができます。これをコマンドプロンプトで
実行しても設計を行えます。(コマンド引数は同様に.ymlファイルのパスにしてください)

※.ymlの作り方についてはconfigフォルダに、SPICEファイルの作り方はtemplateフォルダに
それぞれまとめます。

設計結果のSPICESファイルはoutputフォルダに保存されます。

