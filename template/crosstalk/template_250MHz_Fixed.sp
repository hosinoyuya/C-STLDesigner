******************** STL ver 2.3 250MHz clock crosstalk model ********************

*** Notice *** ------------------------------------------------------*
* クロストーク系の 250MHz クロック入力，伝送線長400mmのSTL設計用テンプレート
* template_250MHz.sp では差動インピーダンスを元に伝送線幅候補を決定していたため，これを特性インピーダンスを元に伝送線幅候補を決定するように修正しました．
* これは修論発表後に引継ぎ用に用意したテンプレートで，発表などでは使用していません．

*--------------------------------------------------------------------*


*** STL Circuit *** -------------------------------------------------*

Vs1             101     0       PWL(
.INCLUDE ./data/input_data/250MHz_81132A_2V_20pulse )
Rin1            101     102     50
Rin2            0       202     50

X1_STL_4        102     202     0       103     203     0 ckt_Z50 Length=50m  N=2 
X2_STL_5        103     203     0       104     204     0 ckt_Z50 Length=300m N=2 
X3_STL_7        104     204     0       optpt1  optpt2  0 ckt_Z50 Length=50m  N=2 

RT1             optpt1  0       50
RT2             optpt2  0       50

*--------------------------------------------------------------------*


*** Versus Circuit *** ----------------------------------------------*

*** Versus TL 1 ***
Vs1001          1001    0       PWL(
.INCLUDE ./data/input_data/250MHz_81132A_2V_20pulse )
Rin1001         1001    1002    50
T1001           1002    0       vspt1   0       z0=50   TD=2523.2p
RT1001          vspt1   0       50

*** Versus TL 2 ***
T2001           0       0       vspt2   0       z0=50   TD=2523.2p

*--------------------------------------------------------------------*


*** Trigger Circuit *** ---------------------------------------------*

*--------------------------------------------------------------------*


*** Netlist Commands *** --------------------------------------------*

* プリントアウト幅（80 or 132）
.WIDTH OUT=132
.TRAN 5p 53n 40n
.PRINT v(optpt1) v(optpt2) v(vspt1) v(vspt2)

.INCLUDE data/char_imp/const_spacing/Z40_sta.hsp
.INCLUDE data/char_imp/const_spacing/Z45_sta.hsp
.INCLUDE data/char_imp/const_spacing/Z50_sta.hsp
.INCLUDE data/char_imp/const_spacing/Z55_sta.hsp
.INCLUDE data/char_imp/const_spacing/Z60_sta.hsp
.INCLUDE data/char_imp/const_spacing/Z65_sta.hsp
.INCLUDE data/char_imp/const_spacing/Z70_sta.hsp
.INCLUDE data/char_imp/const_spacing/Z75_sta.hsp
.INCLUDE data/char_imp/const_spacing/Z80_sta.hsp
.INCLUDE data/char_imp/const_spacing/Z85_sta.hsp
.INCLUDE data/char_imp/const_spacing/Z90_sta.hsp
.INCLUDE data/char_imp/const_spacing/Z95_sta.hsp
.INCLUDE data/char_imp/const_spacing/Z100_sta.hsp
.END

*--------------------------------------------------------------------*
