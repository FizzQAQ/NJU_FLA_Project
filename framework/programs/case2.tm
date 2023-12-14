; the finite set of states
#Q = {0,fndc1,fndc2,tofinal,fnda,rtnc,rtn0,fndb,accept,accept2,accept3,accept4,accept5,halt_accept,reject,reject2,reject3,reject4,reject5,reject6,reject7,halt_reject}

; the finite set of input symbols
#S = {a,b,c}

; the complete set of tape symbols
#G = {a,b,c,A,B,_,f,l,s,e,t,r,u}

; the start state
#q0 = 0

; the blank symbol
#B = _

; the set of final states
#F = {halt_accept}

; the number of tapes
#N = 1

; the transition functions

; State 0: start state
0 a A r fndc1
0 b B r fndc2
0 c c r tofinal
0 _ _ * reject


fndc1 a a r fndc1
fndc1 b b r fndc1
fndc1 c c r fnda
fndc1 _ _ l reject

fnda A A r fnda
fnda B B r fnda
fnda c c r reject
fnda b b r reject
fnda _ _ l reject
fnda a A l rtnc 

rtnc A A l rtnc
rtnc B B l rtnc
rtnc c c l rtn0

rtn0 a a l rtn0
rtn0 b b l rtn0
rtn0 A A r 0
rtn0 B B r 0

fndc2 a a r fndc2
fndc2 b b r fndc2
fndc2 c c r fndb
fndc2 _ _ l reject

fndb A A r fndb
fndb B B r fndb
fndb c c r reject
fndb a a r reject
fndb b B l rtnc 


tofinal A A r tofinal
tofinal B B r tofinal
tofinal a a r reject
tofinal b b r reject
tofinal c c r reject
tofinal _ _ l accept

accept A _ l accept
accept B _ l accept
accept c _ l accept
accept _ _ r accept2
accept2 _ t r accept3
accept3 _ r r accept4
accept4 _ u r accept5
accept5 _ e * halt_accept


; State reject*: write 'Illgal_Input' on 1st tape
reject * * r reject
reject _ _ l reject2

reject2 * _ l reject2
reject2 _ _ r reject3

reject3 _ f r reject4
reject4 _ a r reject5
reject5 _ l r reject6
reject6 _ s r reject7
reject7 _ e * halt_reject

