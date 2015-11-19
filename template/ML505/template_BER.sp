******************************** STL Designer 2 ML505 BER Template ver 2.3 ********************************

*** Notice *** ------------------------------------------------------*
* 安達（2013年度修士卒）が設計した，ML505ボード用の Bit Error Rate 低減STL設計
* IBIS を使って ML505 の BER を低減する STL を設計します．
* 関（2014年度修士卒）が 2014/02 に STLDesigner2 のver 2.3 用に修正

*--------------------------------------------------------------------*


*** STL Circuit *** -------------------------------------------------*

Vs1     in1 	0 	PULSE( 0 1 1n 0p 0p 2n 100n)
V_en	enable 	0 	1V
*Vrnd	in1	gnd 	LFSR( 0 1 0 0n 0n 500meg 1 [7,6] rout=0)

*** IBIS buffer model ***
b1 	nd_pu1 	nd_pd1 	101 	in1 	0 	out_of_in1
+file='./data/IBIS/Virtex5-XC5VFX70T.ibs'
+model='LVCMOS25_F_12'
+typ=typ 
+power=on

*** LSI package model ***
R_pkg1 	101 	102 	331.37m
L_pkg1 	102 	103 	3.70n
C_pkg1 	103 	0 	2.22p

*** ML505 inner delay ***
T_ML505_1 	103 	0 	104 	0 	Z0=50 	TD=750ps

*** cable delay ***
T_cable1 	104 	0 	105 	0 	Z0=50 	TD=4100ps

*** STL PCB ***
W1_STL_3 	105	0	106	0	
+RLGCMODEL=Z50
+N=1
+L=200m
C1	106	0 	30p
W2_STL_6 	106	0	107	0	RLGCMODEL=Z50   N=1	L=200m
C2 	107	0	30p
W3_STL_6 	107	0	108	0	RLGCMODEL=Z50   N=1	L=200m
***************

*** cable delay ***
T_cable2 	108 	0 	109 	0 	Z0=50 	TD=4100ps

*** ML505 inner delay ***
T_ML505_2 	109 	0 	110 	0 	Z0=50 	TD=750ps

*** LSI package model ***
C_pkg2 110 0 2.22p
R_pkg2 110 111 331.37m
L_pkg2 111 optpt1 3.70n

*** IBIS buffer model ***
b2 	nd_pu2 	nd_pd2 	optpt1 	0 	enable 	out_of_in2
+file='./data/IBIS/Virtex5-XC5VFX70T.ibs'
+model='LVCMOS25_F_12'
+typ=typ 
+power=on

*--------------------------------------------------------------------*


*** Versus Circuit *** ----------------------------------------------*

*** tercher ***
Vs1001  1001	0 	PULSE( 0 7 1n 0p 0p 2n 100n)
R1000  	1001	1002	50

T1001	1002	0	vspt1	0	Z0=50	TD=16102ps

RT1000	vspt1	0	50

*--------------------------------------------------------------------*


*** Netlist Commands *** --------------------------------------------*

.OP
.WIDTH OUT=200
.OPTION POST
.TRAN 5p 50n 0n
.PRINT v(vspt1) v(optpt1) v(in1) v(out_of_in2)

.MODEL Z30 W ModelType=RLGC N=1
+ Lo=
+ 195.8626245e-9
+ Co=
+ 204.4185703e-12
+ Ro=
+ 0.16151175
+ Go=
+ 0
+ Rs=
+ 8.86911e-05
+ Gd=
+ 2.36459e-11

*---------------------------------
.MODEL Z35 W ModelType=RLGC N=1
+ Lo=
+ 226.6180669e-9
+ Co=
+ 173.161471e-12
+ Ro=
+ 0.201065648
+ Go=
+ 0
+ Rs=
+ 0.000111623
+ Gd=
+ 1.98579e-11

*---------------------------------
.MODEL Z40 W ModelType=RLGC N=1
+ Lo=
+ 256.5548152e-9
+ Co=
+ 149.9708398e-12
+ Ro=
+ 0.246305419
+ Go=
+ 0
+ Rs=
+ 0.000129568
+ Gd=
+ 1.70406e-11

*---------------------------------
.MODEL Z45 W ModelType=RLGC N=1
+ Lo=
+ 286.1832825e-9
+ Co=
+ 132.0964622e-12
+ Ro=
+ 0.296753517
+ Go=
+ 0
+ Rs=
+ 0.000156514
+ Gd=
+ 1.48948e-11

*---------------------------------
.MODEL Z50 W ModelType=RLGC N=1
+ Lo=
+ 314.4612481e-9
+ Co=
+ 118.2503472e-12
+ Ro=
+ 0.354396286
+ Go=
+ 0
+ Rs=
+ 0.000172186
+ Gd=
+ 1.32191e-11

*---------------------------------
.MODEL Z55 W ModelType=RLGC N=1
+ Lo=
+ 342.4542448e-9
+ Co=
+ 107.0104958e-12
+ Ro=
+ 0.417466811
+ Go=
+ 0
+ Rs=
+ 0.000202169
+ Gd=
+ 1.18864e-11

*---------------------------------
.MODEL Z60 W ModelType=RLGC N=1
+ Lo=
+ 371.2631432e-9
+ Co=
+ 97.30288471e-12
+ Ro=
+ 0.492610837
+ Go=
+ 0
+ Rs=
+ 0.000237138
+ Gd=
+ 1.07397e-11

*---------------------------------
.MODEL Z65 W ModelType=RLGC N=1
+ Lo=
+ 399.8740936e-9
+ Co=
+ 89.12927955e-12
+ Ro=
+ 0.579542162
+ Go=
+ 0
+ Rs=
+ 0.000276343
+ Gd=
+ 9.77793e-12

*---------------------------------
.MODEL Z70 W ModelType=RLGC N=1
+ Lo=
+ 426.8033526e-9
+ Co=
+ 82.50170696e-12
+ Ro=
+ 0.674809366
+ Go=
+ 0
+ Rs=
+ 0.000317648
+ Gd=
+ 9.00119e-12

*---------------------------------
.MODEL Z75 W ModelType=RLGC N=1
+ Lo=
+ 455.698894e-9
+ Co=
+ 76.32375927e-12
+ Ro=
+ 0.794533609
+ Go=
+ 0
+ Rs=
+ 0.000367131
+ Gd=
+ 8.27958e-12

*---------------------------------
.MODEL Z80 W ModelType=RLGC N=1
+ Lo=
+ 483.3152145e-9
+ Co=
+ 71.16152363e-12
+ Ro=
+ 0.92945441
+ Go=
+ 0
+ Rs=
+ 0.000419908
+ Gd=
+ 7.6784e-12

*---------------------------------
.MODEL Z85 W ModelType=RLGC N=1
+ Lo=
+ 511.8675139e-9
+ Co=
+ 66.45439571e-12
+ Ro=
+ 1.09469075
+ Go=
+ 0
+ Rs=
+ 0.000480757
+ Gd=
+ 7.13155e-12

*---------------------------------
.MODEL Z90 W ModelType=RLGC N=1
+ Lo=
+ 536.3253761e-9
+ Co=
+ 62.83579215e-12
+ Ro=
+ 1.263104711
+ Go=
+ 0
+ Rs=
+ 0.000565794
+ Gd=
+ 6.71056e-12

*---------------------------------
.MODEL Z95 W ModelType=RLGC N=1
+ Lo=
+ 564.2884856e-9
+ Co=
+ 59.10429483e-12
+ Ro=
+ 1.492760113
+ Go=
+ 0
+ Rs=
+ 0.000632639
+ Gd=
+ 6.27622e-12

*---------------------------------
.MODEL Z100 W ModelType=RLGC N=1
+ Lo=
+ 591.3459733e-9
+ Co=
+ 55.85876276e-12
+ Ro=
+ 1.759324419
+ Go=
+ 0
+ Rs=
+ 0.000706407
+ Gd=
+ 5.8994e-12

*---------------------------------
.MODEL Z105 W ModelType=RLGC N=1
+ Lo=
+ 616.2488904e-9
+ Co=
+ 53.14071975e-12
+ Ro=
+ 2.052545156
+ Go=
+ 0
+ Rs=
+ 0.00078322
+ Gd=
+ 5.58426e-12

*---------------------------------
.MODEL Z110 W ModelType=RLGC N=1
+ Lo=
+ 644.9185142e-9
+ Co=
+ 50.28008245e-12
+ Ro=
+ 2.463054187
+ Go=
+ 0
+ Rs=
+ 0.00089857
+ Gd=
+ 5.25233e-12

*---------------------------------
.MODEL Z115 W ModelType=RLGC N=1
+ Lo=
+ 669.6082546e-9
+ Co=
+ 48.01275848e-12
+ Ro=
+ 2.897710808
+ Go=
+ 0
+ Rs=
+ 0.000991856
+ Gd=
+ 4.98844e-12

*---------------------------------
.MODEL Z120 W ModelType=RLGC N=1
+ Lo=
+ 688.1753022e-9
+ Co=
+ 46.41807648e-12
+ Ro=
+ 3.28407225
+ Go=
+ 0
+ Rs=
+ 0.001070005
+ Gd=
+ 4.8028e-12
*---------------------------------
.END

*--------------------------------------------------------------------*
