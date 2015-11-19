******************************** STL Designer 2 tlsim Template ********************************

*** Notice *** ------------------------------------------------------*
* STLのtlsimを用いたEMI設計用(IBISモデル使用)のテンプレート
* 2.3バージョン用の記述
* STLのセグメント数は2以上の整数でなければ動きません（1以下は不可）
* STL化するエレメントを指定します．
* 凡例：(T|W|X)_STL_伝送線のセグメント数（分割する数）
* ノード（観測点等のつなぎ目）には数字か pt を含む文字列のみとします（exp: \w*pt\d*）
* 行途中のコメントはSTL Designer 2 のパラメタ設定に利用します．

*** PRBSの使い方
* 凡例：
* LFSR(L[V], H[V], delay, TR, TF, bitrate, seed, tap(ADS_default = [8,4,3,2])
* Vs1	101	0 LFSR( 0 2 200p 200p 200p 500meg 3 [8,4,3,2])


*** サンプリング電圧のインクルードのやり方
* 改行位置などに注意が必要です
* Vs1	101	0 PWL(
* .INCLUDE ./data/500Mbps-3.3V-koritsuha-2 )

*--------------------------------------------------------------------*


*** STL Circuit *** -------------------------------------------------*

Vs1             in1     0       PULSE( 0 1 1n 0p 0p 2n 4n )

*** IBIS buffer model ***
bdrvr_out b1_vcc 101 0 in1 b1_en b1_pc 0 Model=VIRTEX5XC5VFX70T_LVCMOS25_F_12_Typ_27degC File=./data/IBIS/ibis_models.inc
v_en1           b1_en   0       1V
v_vcc1          b1_vcc  0       2.5V
v_pc1           b1_pc   0       2.5V

*** LSI package model ***
R_pkg1          101     102     331.37m
L_pkg1          102     103     3.70n
C_pkg1          103     0       2.22p

*** transmission line (not STL) ***
TML505          103     0       104     0       z0=50   TD=750p         R=1e-5
Tcable          104     0       105     0       z0=50   TD=4100p        R=1e-5

*** Current Probe ***
V_CP1           105     106     0.000000e+000

*** STL PCB ***
N1_STL_3        106     0       optpt1  0       L=200m  rlgc_name=Z50   file=./data/char_imp/ntl_rlgc.inc
C1              optpt1  0       30p
N2_STL_6        optpt1  0       optpt2  0       L=200m  rlgc_name=Z50   file=./data/char_imp/ntl_rlgc.inc
C2              optpt2  0       30p
N3_STL_6        optpt2  0       optpt3  0       L=200m  rlgc_name=Z50   file=./data/char_imp/ntl_rlgc.inc
***************


*** transmission line (not STL) ***
Tcable2         optpt3  0       107     0       z0=50   TD=4100p        R=1e-5
TML5052         107     0       108     0       z0=50   TD=750p         R=1e-5

*** LSI package model ***
C_pkg1          108     0       2.22p
R_pkg1          108     109     331.37m
L_pkg1          109     optpt0     3.70n

*** IBIS buffer model ***
bdrvr_in b2_vcc optpt0 0 b2_in gnd b2_pc 0 Model=VIRTEX5XC5VFX70T_LVCMOS25_F_12_Typ_27degC File=./data/IBIS/ibis_models.inc
v_in2           b2_in   0       1V
v_vcc2          b2_vcc  0       2.5V
v_pc2           b2_pc   0       2.5V

*--------------------------------------------------------------------*


*** Versus Circuit *** ----------------------------------------------*

Vsvs1           1001    0       PULSE( 0 5 1n 0p 0p 2n 4n )
Rinvs1          1001    1002    50
TvsML505_1      1002    0       1004    0       z0=50   TD=750p         R=1e-5
Tvscable1       1004    0       1005    0       z0=50   TD=4100p        R=1e-5
Tvs1            1005    0       vspt1   0       z0=50   TD=1261.6p      R=1e-5
Tvs2            vspt1   0       vspt2   0       z0=50   TD=1261.6p      R=1e-5
Tvs3            vspt2   0       vspt3   0       z0=50   TD=1261.6p      R=1e-5
Tvscable2       vspt3   0       1006    0       z0=50   TD=4100p        R=1e-5
TvsML505_2      1006    0       1007    0       z0=50   TD=750p         R=1e-5

*** time delay for buffer&package
Tvsbuf2         1007    0       vspt0   0       z0=50   TD=2387p      R=1e-5

RTvs1           vspt0   0       50

*--------------------------------------------------------------------*


*** Trigger Circuit *** ---------------------------------------------*

*--------------------------------------------------------------------*


*** Netlist Commands *** --------------------------------------------*

.node_param     optpt0  print
.node_param     optpt1  print
.node_param     optpt2  print
.node_param     optpt3  print
.node_param     vspt0   print
.node_param     vspt1   print
.node_param     vspt2   print
.node_param     vspt3   print

*** Current Output ***
.print I(V_CP1)

.END


*--------------------------------------------------------------------*
