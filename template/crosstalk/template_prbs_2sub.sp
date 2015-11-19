******************** STL ver 2.3 eye design crosstalk model - 2subspace ********************

*** Notice *** -------------------------------------------------*
* クロストーク系のアイパターン整形用のテンプレートです．
* 遠端付近が細かく分割されるよう，サブスペースを分けています．

*--------------------------------------------------------------------*


*** STL Circuit *** -------------------------------------------------*

Vs1             101     0       LFSR( 0 2 20p 20p 20p 10g 3 [8,7,4,3,2])
Rin1            101     102     50
Vs2             201     0       LFSR( 0 2 20p 20p 20p 10g 8 [8,7,4,3,2])
Rin2            201     202     50

X1_STL_4        102     202     0       103     203     0 ckt_Z50 Length=70m N=2
X2_STL_6        103     203     0       optpt1  optpt2  0 ckt_Z50 Length=30m N=2

RT1             optpt1  0       50
RT2             optpt2  0       50

*--------------------------------------------------------------------*


*** Versus Circuit *** ----------------------------------------------*

*** Versus TL 1 ***
Vs1001          1001    0       LFSR( 0 2 20p 20p 20p 10g 3 [8,7,4,3,2])
Rin1001         1001    1002    50
T1001           1002    0       vspt1   0       z0=50   TD=630.8p
RT1001          vspt1   0       50

*** Versus TL 2 ***
Vs2001          2001    0       LFSR( 0 2 20p 20p 20p 10g 8 [8,7,4,3,2])
Rin2001         2001    2002    50
T2001           2002    0       vspt2   0       z0=50   TD=630.8p
RT2001          vspt2   0       50

*--------------------------------------------------------------------*


*** Trigger Circuit *** ---------------------------------------------*
Vs10001         10001   0       PULSE( 0 2 0p 20p 20p 80p 200p )
Rin10001        10001   10002   50
* PRBSが100pずれるので，調整用
TPRBSFIX        10002   0       10003   0       z0=50   TD=100p
T10001          10003   0       trgpt1   0       z0=50   TD=630.8p
RT10001         trgpt1  0       50

*--------------------------------------------------------------------*


*** Netlist Commands *** --------------------------------------------*

* プリントアウト幅（80 or 132）
.WIDTH OUT=132
.PRINT v(optpt1) v(optpt2)  v(vspt1) v(vspt2)  v(trgpt1)
* 合計 29801 プロット（25GHz サンプリング, 150サイクル, 1周期200プロット）
.TRAN 4p 50n 0p

.INCLUDE data/char_imp/center_distance_z0_interval/Z40_sta.hsp
.INCLUDE data/char_imp/center_distance_z0_interval/Z45_sta.hsp
.INCLUDE data/char_imp/center_distance_z0_interval/Z50_sta.hsp
.INCLUDE data/char_imp/center_distance_z0_interval/Z55_sta.hsp
.INCLUDE data/char_imp/center_distance_z0_interval/Z60_sta.hsp
.INCLUDE data/char_imp/center_distance_z0_interval/Z65_sta.hsp
.INCLUDE data/char_imp/center_distance_z0_interval/Z70_sta.hsp
.INCLUDE data/char_imp/center_distance_z0_interval/Z75_sta.hsp
.INCLUDE data/char_imp/center_distance_z0_interval/Z80_sta.hsp
.INCLUDE data/char_imp/center_distance_z0_interval/Z85_sta.hsp
.INCLUDE data/char_imp/center_distance_z0_interval/Z90_sta.hsp
.INCLUDE data/char_imp/center_distance_z0_interval/Z95_sta.hsp
.INCLUDE data/char_imp/center_distance_z0_interval/Z100_sta.hsp
.INCLUDE data/char_imp/center_distance_z0_interval/Z105_sta.hsp
.INCLUDE data/char_imp/center_distance_z0_interval/Z110_sta.hsp
.INCLUDE data/char_imp/center_distance_z0_interval/Z115_sta.hsp
.INCLUDE data/char_imp/center_distance_z0_interval/Z120_sta.hsp
.END

*--------------------------------------------------------------------*


