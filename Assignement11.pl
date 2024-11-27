parent(pam,bob).
parent(tom,bob).
parent(tom,liz).
parent(bob,ann).
parent(bob,pat).
parent(pat,jim).

male(tom).
male(bob).

male(jim).

female(pam).
female(liz).
female(pat).
female(ann).

offspring(Y, X) :- parent(X, Y).


mother(X, Y) :-
	parent(X, Y),
	female(X).

grandparent(X, Z) :-
	parent(X, Y),
	parent(Y, Z).


different( X, Y) :-
	X = Y, !, fail;
	true.
sister( X, Y):-
    parent( Z, X),
    parent( Z, Y),
    female( X),
    different( X, Y).


predecessor(X, Z) :-
    parent(X, Z).
predecessor(X, Z) :-
    parent(X, Y),
    predecessor(Y, Z).


fallible( X) :-
    man( X).
man( socrates).


hasachild( X) :- parent( X, _).
somebody_has_child :- parent( _, _).


seq( r1, r2).
par( r1, r2).
par( r1, par(r2, r3)).
par( r1, seq(par( r2, r3), r4)).

f( 1, one).
f( s(1), two).
f( s((1)), three).
f( s(s(s(X))),N) :-
	f( X, N).

translate(Number, Word):-
	Number = 1, Word = one;
	Number = 2, Word = two;
	Number = 3, Word = three.

big( bear).
big( elephant).
small( cat).
brown( bear).
black( cat).
gray( elephant).

dark( Z) :-
	black( Z).
dark( Z) :-
	brown( Z).
