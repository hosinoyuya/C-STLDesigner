******************** STL ver 2.3 X element basic model ********************

*** Notice *** ------------------------------------------------------*
* XエレメントによるSTL基本形（バス配線で寄生容量接続有り）のテンプレート

*--------------------------------------------------------------------*


*** STL Circuit *** -------------------------------------------------*

Vs1             101     0       PULSE( 0 2 1n 100p 100p 0.9n 2n )
Rin1            101     102     50

*** Subspaces ***
X1_STL_3        102     0       optpt1  0       ckt_Z50 Length=100m N=1
C1              optpt1  0       10p
X2_STL_8        optpt1  0       optpt2  0       ckt_Z50 Length=100m N=1
C2              optpt2  0       10p
X3_STL_3        optpt2  0       optpt3  0       ckt_Z50 Length=100m N=1
*****************

RT1             optpt3  0       50

*--------------------------------------------------------------------*


*** Versus Circuit *** ----------------------------------------------*

Vsvs1          1001    0       PULSE( 0 2 1n 100p 100p 0.9n 2n )
Rinvs1         1001    1002    50
Tvs1           1002    0       vspt1   0       z0=50   TD=630.8p
Tvs2           vspt1   0       vspt2   0       z0=50   TD=630.8p
Tvs3           vspt2   0       vspt3   0       z0=50   TD=630.8p
RTvs1          vspt3   0       50

*--------------------------------------------------------------------*


*** Trigger Circuit *** ---------------------------------------------*

*--------------------------------------------------------------------*


*** Netlist Commands *** --------------------------------------------*

.WIDTH OUT=132
.TRAN 10p 40n 20n
.PRINT v(optpt1) v(optpt2) v(optpt3) v(vspt1) v(vspt2) v(vspt3)


.INCLUDE data/char_imp/single_MSline_1GHz/Z40_sta.hsp
.INCLUDE data/char_imp/single_MSline_1GHz/Z45_sta.hsp
.INCLUDE data/char_imp/single_MSline_1GHz/Z50_sta.hsp
.INCLUDE data/char_imp/single_MSline_1GHz/Z55_sta.hsp
.INCLUDE data/char_imp/single_MSline_1GHz/Z60_sta.hsp
.INCLUDE data/char_imp/single_MSline_1GHz/Z65_sta.hsp
.INCLUDE data/char_imp/single_MSline_1GHz/Z70_sta.hsp
.INCLUDE data/char_imp/single_MSline_1GHz/Z75_sta.hsp
.INCLUDE data/char_imp/single_MSline_1GHz/Z80_sta.hsp
.INCLUDE data/char_imp/single_MSline_1GHz/Z85_sta.hsp
.INCLUDE data/char_imp/single_MSline_1GHz/Z90_sta.hsp
.INCLUDE data/char_imp/single_MSline_1GHz/Z95_sta.hsp
.INCLUDE data/char_imp/single_MSline_1GHz/Z100_sta.hsp
.INCLUDE data/char_imp/single_MSline_1GHz/Z105_sta.hsp
.INCLUDE data/char_imp/single_MSline_1GHz/Z110_sta.hsp
.INCLUDE data/char_imp/single_MSline_1GHz/Z115_sta.hsp
.INCLUDE data/char_imp/single_MSline_1GHz/Z120_sta.hsp
.END
*--------------------------------------------------------------------*
