******************** STL ver 2.3 alone design crosstalk model ********************

*** Notice *** -------------------------------------------------*
* クロストーク系の孤立波整形用のテンプレート

*--------------------------------------------------------------------*


*** STL Circuit *** -------------------------------------------------*

Vs1             101     0       PULSE( 0 2 80p 20p 20p 80p 50n )
Rin1            101     102     50
Rin2            202     0       50

X1_STL_10       102     202     0       optpt1  optpt2  0 ckt_Z50 Length=100m N=2

RT1             optpt1  0       50
RT2             optpt2  0       50

*--------------------------------------------------------------------*


*** Versus Circuit *** ----------------------------------------------*

*** Versus TL 1 ***
Vs1001          1001    0       PULSE( 0 2 80p 20p 20p 80p 50n )
Rin1001         1001    1002    50
T1001           1002    0       vspt1   0       z0=50   TD=630.8p
RT1001          vspt1   0       50

*** Versus TL 2 ***
Rin2001         2002    0       50
T2001           2002    0       vspt2   0       z0=50   TD=630.8p
RT2001          vspt2   0       50

*--------------------------------------------------------------------*


*** Trigger Circuit *** ---------------------------------------------*

*--------------------------------------------------------------------*


*** Netlist Commands *** --------------------------------------------*

* プリントアウト幅（80 or 132）
.WIDTH OUT=132
.PRINT v(optpt1) v(optpt2)  v(vspt1) v(vspt2) 
.TRAN 2p 1.4n 0.6n

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



