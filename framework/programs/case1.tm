; the finite set of states
#Q = {0,cnta,wrtc,fndb,fndaA,fndA,accept,accept2,halt_accept,reject,reject2,reject3,reject4,reject5,reject6,reject7,reject8,reject9,reject10,reject11,reject12,reject13,reject14,halt_reject}

; the finite set of input symbols
#S = {a,b}

; the complete set of tape symbols
#G = {a,b,c,_,A,l,e,g,a,I,n,p,u,t}

; the start state
#q0 = 0

; the blank symbol
#B = _

; the set of final states
#F = {halt_accept}

; the number of tapes
#N = 2

; the transition functions

; State 0: start state
0 a_ a_ ** cnta
0 b_ b_ ** reject ; empty a
0 __ __ ** reject ; empty input


cnta a_ A_ r* fndb

fndb b_ b_ ** wrtc
fndb __ __ ** reject ;empty b
fndb a_ a_ r* fndb

wrtc b_ bc rr wrtc
wrtc __ __ l* fndaA
wrtc a_ a_ ** reject

fndaA b_ b_ l* fndaA
fndaA A_ A_ r* accept
fndaA a_ a_ ** fndA

fndA a_ a_ l* fndA
fndA A_ A_ r* cnta

accept b_ b_ r* accept
accept __ __ ll accept2

accept2 *c c_ ll accept2
accept2 _c c_ ll accept2
accept2 *_ __ l* accept2
accept2 __ __ ** halt_accept



; State reject*: write 'Illgal_Input' on 1st tape
reject *_ *_ r* reject
reject __ __ l* reject2

reject2 *_ __ l* reject2
reject2 __ __ r* reject3

reject3 __ I_ r* reject4
reject4 __ l_ r* reject5
reject5 __ l_ r* reject6
reject6 __ g_ r* reject7
reject7 __ a_ r* reject8
reject8 __ l_ r* reject9
reject9 __ __ r* reject10
reject10 __ I_ r* reject11
reject11 __ n_ r* reject12
reject12 __ p_ r* reject13
reject13 __ u_ r* reject14
reject14 __ t_ ** halt_reject