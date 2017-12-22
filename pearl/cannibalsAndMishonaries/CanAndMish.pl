% cannibal.pl
% Author: Earl Blizzard
% Tab space: 8
% Date: 11/16/2016

% ---------------------------------
%	follows
% ---------------------------------

%% the predicate follows(S ,T) has an input of S,
%% which is a state; and finds the next state T.

% sub sets of follows that help with organization.

follows(S, T) :- moveRight(S, T).

follows(S, T) :- moveLeft(S, T).

% ---------------------------------
%	moveRight
% ---------------------------------

%% when the boat is on the left side
%% of the river then the boat must be moved right
%% these are all of the state changes to the right.

% list A and List B are of equal length.

moveRight(banks([Ahead | ATail] ,[Bhead | BTail] ,true ,[C] ,[D]), T) :-
	length([Ahead | ATail], Int1),
	length([Bhead | BTail], Int2),
	int2 - int1 is int3,
	int3 =:= 0,
	T is banks([Atail], [Btail], false , [Ahead| C] , [Bhead | D]),
	writeln("moveRight").

% list A and List B are of equal length.

moveRight(banks([A] ,[Bhead1 | [Bhead2 | BTail]] ,true ,[C] ,[D]), T) :-
	length([A], Int1),
	length([Bhead1 | [Bhead2 | BTail]], Int2),
	int3 is int2 - int1,
	int3 =:= 0,
	length([C], Int4),
	length([D], Int5),
	int6 is int4 - int5,
	int6 =:= 0,
	T is banks([A], [Btail], false , [C] , [Bhead1 | [Bhead2 | D]]),
	writeln("moveRight").

% list A is less than B in length by 1.

moveRight(banks([Ahead1 | [Ahead2 | ATail]] ,[B] ,true ,[C] ,[D]), T) :- 
	length([B], Int2),
	length([Ahead1 | [Ahead2 | ATail]], Int1),
	int3 is int2 - int1,
	int3 =:= 1,
	T is banks([ATail],[B],false,[Ahead1 | [Ahead2 | C]], [D]),
	writeln("moveRight").

% list A is less than B in length by 2.

moveRight(banks([A] ,[Bhead1 | [Bhead2| BTail]] ,true ,[C] ,[D]), T) :- 
	length([Bhead1 | [Bhead2 |BTail]], Int2),
	length([A], Int1),
	int3 is int2 - int1,
	int3 =:= 2,
	T is banks([A],[B],flase,[C],[Bhead1 | [Bhead2 | D]]),
	writeln("moveRight").

% list B is less than A in length by 2

moveRight(banks([Ahead1 | [Ahead2 |ATail]] ,[B] ,true ,[C] ,[D]), T) :- 
	length([B], Int2),
	length([Ahead1 | [Ahead2 |ATail]], Int1),
	int3 is int1 - int2,
	int3 =:= 2,
	T is banks([ATail],[B],flase,[Ahead1 | [Ahead2 |C]],[D]),
	writeln("moveRight").

% list B is less than A in length by 3

moveRight(banks([Ahead1 | [Ahead2 |ATail]] ,[B] ,true ,[C] ,[D]), T) :- 
	length([B], Int2),
	length([Ahead1 | [Ahead2 |ATail]], Int1),
	int3 is int1 - int2,
	int3 =:= 2,
	T is banks([ATail],[B],flase,[Ahead1 | [Ahead2 |C]],[D]),
	writeln("moveRight").


% ---------------------------------
%		moveLeft
% ---------------------------------

%% when the boat is on the right side
%% of the river then the boat must be moved left
%% these are all of the moves to the left.

% list C and D are equal in length.

moveLeft(banks([A] , [B] , false, [C] , [Dhead| DTail]) , T) :-
	length([C] , Int1),
	length([Dhead| Dtail] , Int2),
	int3 is int2 - int1,
	int3 =:= 0,
	T is banks([A] , [Dhead| B] , true , [C] , [DTail]),
	writeln("moveLeft").

% list C and List D are of equal length.

moveLeft(banks([A] ,[B] ,true ,[Chead | CTail] ,[Dhead | DTail]), T) :-
	length([A], Int1),
	length([B], Int2),
	int3 is int2 - int1,
	int3 =:= 0,
	length([Chead | CTail], Int4),
	length([Dhead | DTail], Int5),
	int6 is int4 - int5,
	int6 =:= 0,
	T is banks([Chead | A], [Dhead | B], false , [CTail] , [DTail]),
	writeln("moveLeft").

% list C is less than D by 1.

moveLeft(banks([A] , [B] , false, [Chead| CTail] , [D]) , T) :-
	length([D] , Int2),
	length([Chead| Ctail] , Int1),
	int3 is int2 - int1,
	int3 =:= 1,
	T is banks([Chead| A] , [B] , true , [Ctail] , [D]).

% list C is less than D by 2.

moveLeft(banks([A] , [B] , false, [Chead| CTail] , [D]) , T) :-
	length([D] , Int2),
	length([Chead| Ctail] , Int1),
	int3 is int2 - int1,
	int3 =:= 2,
	T is banks([Chead | A], [B], true , [Ctail] , [D]),
	writeln("moveLeft").

% list D is less than C by 3.

moveLeft(banks([A] , [B] , false, [Chead | CTail] , [D]) , T) :-
	length([D] , Int2),
	length([C] , Int1),
	int3 is int1 - int2,
	int3 =:= 3,
	T is banks([Chead | A], [B], true , [Ctail] , [D]),
	writeln("moveLeft").


% ------------------------------------
%	admissable
% ------------------------------------

%% this predicate checks to see if a state is
%% valid and returning true is so.

% checks to see if the cannibals out number 
% the missionaries on either side of the bank.

admissable(banks([A] , [B] , _ , [C] , [D])) :-
	length([A] , int1),
	length([B] , int2),
	length([C] , int3),
	length([D] , int4),
	int1 =< int2,
	int3 =< int4.

% checks to see if there are no missionaries 
% on the left bank.

admissable(banks([A] , [B] , _ , [C] , [D])) :-
	length([B] , int2),
	int2 =:= 0.

% checks to see if there are no missionaries
% on the right bank.

admissable(banks([A] , [B] , _ , [C] , [D])) :-
	length([D] , int4),
	int4 =:= 0.


% -----------------------------------
%	thePlan
% -----------------------------------

%% this predicate takes a start and a 
%% goal, and finds a plan that will 
%% move from the goal to the start.

thePlan(Start , Goal , [Plan]) :- 
	follows(Start, Next),
	admissable(Next),
	thePlan(Next , Goal , [Start | []]).

% if the beginigng is the same as the
% goal then there is no plan

thePlan(Start , Goal , Plan) :-
	Start =:= Goal,
	Plan is [Goal].
% thePlan( banks([c,c,c] , [m,m,m] , true , [] , []) , bank( [] , [] , flase , [c,c,c] , [m,m,m]) , Plan)
