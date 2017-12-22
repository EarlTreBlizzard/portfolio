%Earl Blizzard
%11/18/2016
%Tab sapce: 8


% -----------------------------
%		follows
% -----------------------------

% follows(S , T) can be given a state S 
% and can produce the next state T.

follows(S,T) :- moveRight(S,T).

follows(S,T) :- moveLeft(S,T).

% -----------------------------
%		moveRight
% -----------------------------

% moveRight is a subdivision of follows

% moves a canniabl and a missionary to the right side of the river.

moveRight(banks([AHead|ATail] , [BHead|BTail] , onLeft , C , D) , banks(ATail , BTail , onRight , [AHead|C] , [BHead|D])).

% moves two canniabls across the river.

moveRight(banks([AHead1| [AHead2 | ATail]] , B , onLeft , C , D) , banks(ATail , B , onRight , [AHead1| [AHead2| C]] , D)).

% moves two missionaries across the river.

moveRight(banks(A , [BHead1| [BHead2 | BTail]] , onLeft , C , D) , banks(A , BTail , onRight , C , [BHead1| [BHead2 | D]])).

% moves only one canniabl across the river.

moveRight(banks([AHead| ATail] , B , onLeft , C , D) , banks(ATail , B , onRight , [AHead| C] , D)).

% moves only one missionary across the river.
moveRight(banks(A , [BHead | BTail] , onLeft , C , D) , banks(A , BTail , onRight , C , [BHead| D])).

% ---------------------------
%		moveLeft
%----------------------------

% moveLeft is a subdivision of follows

% moves a canniabl and a missionary to the right side of the river.

moveLeft(banks(A , B , onRight , [CHead | CTail] , [DHead | DTail]) , banks([CHead | A] , [DHead | B] , onLeft , CTail , DTail)).

% moves two canniabls across the river.

moveLeft(banks(A , B , onRight , [CHead1 | [CHead2 | CTail]] , D) , banks([CHead1 | [CHead2 | A]] , B , onLeft , CTail , D)).

% moves two missionaries across the river.

moveLeft(banks(A , B , onRight , C , [DHead1 | [DHead2 | DTail]]) , banks(A , [DHead1 | [DHead2 | B]] , onLeft , C , DTail)).

% moves only one canniabl across the river.

moveLeft(banks(A , B , onRight , C , [DHead | DTail]) , banks(A , [DHead | B] , onLeft , C , DTail)).

% moves only one missionary across the river.

moveLeft(banks(A , B , onRight , [CHead | CTail] , D) , banks([CHead | A] , B , onLeft , CTail , D)).

% ---------------------------
%		admissable
% ---------------------------

% states whether a state is alowed or not.

% cannibals can never exced missionaries
admissibleBank(A,B) :-
	length(A,LA), length(B,LB), \+(LA>LB).

% there can be no missionaries on a bank.
admissibleBank(_,B) :-
	length(B,0).

admissible(banks(A,B,_,C,D)) :-
	admissibleBank(A,B),
	admissibleBank(C,D).



% --------------------------
%	Plan
% --------------------------


lengthen([St | Rest], [NewSt, St | Rest]) :-
	follows(St, NewSt),
	admissible(NewSt),
	\+(member(NewSt, [St | Rest])).

plan([Goal | Rest], Goal, [Goal | Rest]).

plan(Partialplan, Goal, Fullplan) :-
	lengthen(Partialplan, Longerplan),
	plan(Longerplan, Goal, Fullplan).


showplan([]).

showplan([banks(A , B , T , C , D) | Rest]) :-
write(A), write(B), write(T), write(C), write(D), nl,
showplan(Rest).

run :-
EmptGroup  = [],
FullCannaibl   = [c,c,c,c,c],
FullMishionary   = [m,m,m,m,m],
FirstState = banks(FullCannaibl , FullMishionary , onLeft , EmptGroup , EmptGroup),
GoalState  = banks(EmptGroup, EmptGroup , onRight , FullCannaibl  , FullMishionary),
plan([FirstState], GoalState, Aplan),
reverse(Aplan, Fwdplan),
showplan(Fwdplan),
nl.






