******************** STL ver 2.3 tlsim basic model ********************

*** Notice *** ------------------------------------------------------*
* OrCAD の tlsim 用STL基本形（バス配線で寄生容量接続有り）のテンプレート

*--------------------------------------------------------------------*


*** STL Circuit *** -------------------------------------------------*

Vs1             101     0       PULSE( 0 2 1n 200p 200p 1.8n 4n )
Rin1            101     102     50

N1_STL_3        102     0       optpt1  0       L=100m  rlgc_name=Z50   file=./data/char_imp/ntl_rlgc.inc
C1              optpt1  0       10p
N2_STL_8        optpt1  0       optpt2  0       L=100m  rlgc_name=Z50   file=./data/char_imp/ntl_rlgc.inc
C2              optpt2  0       10p
N3_STL_3        optpt2  0       optpt3  0       L=100m  rlgc_name=Z50   file=./data/char_imp/ntl_rlgc.inc

RT1             optpt3  0       50

*--------------------------------------------------------------------*


*** Versus Circuit *** ----------------------------------------------*

Vsvs1          1001    0       PULSE( 0 2 1n 200p 200p 1.8n 4n )
Rinvs1         1001    1002    50
Tvs1           1002    0       vspt1   0       z0=50   TD=630.8p      R=1e-5
Tvs2           vspt1   0       vspt2   0       z0=50   TD=630.8p      R=1e-5
Tvs3           vspt2   0       vspt3   0       z0=50   TD=630.8p      R=1e-5
RTvs1          vspt3   0       50

*--------------------------------------------------------------------*


*** Trigger Circuit *** ---------------------------------------------*

*--------------------------------------------------------------------*


*** Netlist Commands *** --------------------------------------------*

.node_param     optpt1  print
.node_param     optpt2  print
.node_param     optpt3  print
.node_param     vspt1   print
.node_param     vspt2   print
.node_param     vspt3   print

.END


*--------------------------------------------------------------------*
