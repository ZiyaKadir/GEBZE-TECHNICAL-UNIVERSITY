% Define places as nodes
node(1, 'admin office').
node(2, 'cafeteria').
node(3, 'engineering bld').
node(4, 'library').
node(5, 'social sciences bld').
node(6, 'lecture hall A').
node(7, 'institute Y').
node(8, 'institute X').

:- dynamic object/6.
:- dynamic deliveryPerson/6.
:- dynamic current_time/1.

current_time(0).

% Delivery personnel
% deliveryPerson(ID, Capacity, WorkHours, Start-time, End-time, CurrentLocation)
deliveryPerson(1, 30, 0,  8, 12 , 0).
deliveryPerson(2, 25, 0,  8, 16 , 0).
deliveryPerson(3, 20, 0, 8, 20 , 0).

% Objects to be delivered
% object(ID, Weight, PickupPlace, DropPlace, Urgency, DeliveryPerson)
object(1, 10, 1, 2, low, 0).
object(2, 20, 2, 3, medium, 0).
object(3, 15, 3, 1, high, 0).
object(4, 5, 4, 6, low, 0).
object(5, 25, 7, 8, high, 0). % This object is in transit

% Map routes
edge(1, 2, 4). % admin office to cafeteria
edge(1, 3, 3). % admin office to engineering bld
edge(1, 4, 1). % admin office to library
edge(2, 4, 5). % cafeteria to library
edge(4, 3, 5). % library to engineering bld
edge(2, 5, 2). % cafeteria to social sciences bld
edge(4, 5, 2). % library to social sciences bld
edge(3, 6, 2). % engineering bld to lecture hall A
edge(6, 7, 3). % lecture hall A to institute Y
edge(4, 7, 3). % library to institute Y
edge(5, 8, 8). % social sciences bld to institute X

% Reverse routes
edge(2, 1, 4). % cafeteria to admin office
edge(3, 1, 3). % engineering bld to admin office
edge(4, 1, 1). % library to admin office
edge(4, 2, 5). % library to cafeteria
edge(3, 4, 5). % engineering bld to library
edge(5, 2, 2). % social sciences bld to cafeteria
edge(5, 4, 2). % social sciences bld to library
edge(6, 3, 2). % lecture hall A to engineering bld
edge(7, 6, 3). % institute Y to lecture hall A
edge(7, 4, 3). % institute Y to library
edge(8, 5, 8). % institute X to social sciences bld



% Predicate to find the shortest path and total cost between two places
shortestPath(StartNode, EndNode, Path, TotalCost) :-
    findall(Cost, shortestPathHelper(StartNode, EndNode, [StartNode], 0, _, Cost), Costs),
    min_list(Costs, TotalCost),
    shortestPathHelper(StartNode, EndNode, [StartNode], 0, Path, TotalCost), !.

% Base case: Reached the destination node.
shortestPathHelper(EndNode, EndNode, Path, TotalCost, Path, TotalCost).

% Recursive case: Find a path from StartNode to EndNode.
shortestPathHelper(StartNode, EndNode, Visited, CurrentCost, Path, TotalCost) :-
    edge(StartNode, NextNode, StepCost),
    \+ member(NextNode, Visited),
    NewCost is CurrentCost + StepCost,
    shortestPathHelper(NextNode, EndNode, [NextNode | Visited], NewCost, Path, TotalCost).

% Wrapper predicate to initiate the search.
findShortestPath(StartNode, EndNode, Path, TotalCost) :-
    shortestPath(StartNode, EndNode, Path, TotalCost),
    %write('Shortest Path: '), write(Path), nl,
    %write('Total Cost: '), write(TotalCost), nl,
    repeat, !.



main(ObjectID, CurrentTime) :-
    current_time(Time),
    %write('Time = '), write(Time), nl,
    find_undelivered_object(UndeliveredObject, Result_object),
    find_avaliable_guy(Avaliable_ID, Time, Result_guy),
    
    %deliveryPerson(1,_,T_time,_,_,_),
    
    %write('Deneme time'), write(T_time), nl,
    (Result_object = 1, Result_guy = 1 ->
       %write('Assigned value'), nl,
       assign_delivery(UndeliveredObject, Avaliable_ID)
        ;
          write(' ')
          %write('Time = '), write(Time), nl
    ),
    %write('Result guy'), write(Result_guy), nl,
    %write('Result object') , write(Result_object), nl,
    
    (Time = CurrentTime ->
           object(ObjectID, _, _, _, _, Person),
           (Person >= 1 , Person =< 5 ->
           deliveryPerson(Person, _, WorkHours, _, _, _),
           (WorkHours = 0 ->
                 write('The package delivered by '), write(Person), nl
           ;
                 write('The Package is in transmit right now by '), write(Person), nl
           )
           ;
                 write('Package wait to transfer') ,nl
           )

    ;

      increase_time(),
      main(ObjectID, CurrentTime)
    ).
    

 % Find undelivered objects
find_undelivered_object(UndeliveredObjectID, Result) :-
    (once(object(UndeliveredObjectID, _, _, _, _, 0)),
        Result = 1
    ;   Result = 0
    ).
    
find_avaliable_guy(Avaliable_ID, Time, Result) :-
    (once(deliveryPerson(Avaliable_ID, _, 0 , Start_time, End_time, _)),
        (Start_time =< Time, Time =< End_time ->
            Result = 1
        ;
            Result = 0
        )
    ;   Result = 0
    ).
    

% Assign delivery task to available delivery person
assign_delivery(ObjectID, DeliveryPersonID) :-

    % Check if the object exists and has no assigned delivery person
    object(ObjectID, Weight, PickupPlace, DropPlace, Urgency, 0),


    % Check if there is a delivery person available
    deliveryPerson(DeliveryPersonID, Capacity, 0, StartTime, EndTime, _),


    % Check capacity and work hours
    Capacity >= Weight,


    findShortestPath(PickupPlace, DropPlace, _, TotalCost),
    %write(TotalCost), nl,
    Newtotal is TotalCost,

    % Update the object with the delivery person
    retract(object(ObjectID, Weight, PickupPlace, DropPlace, Urgency, 0)),
    assert(object(ObjectID, Weight, PickupPlace, DropPlace, Urgency, DeliveryPersonID)),
    

    % Update the delivery person's status
    retract(deliveryPerson(DeliveryPersonID, Capacity, 0, StartTime, EndTime, 0)),
    assert(deliveryPerson(DeliveryPersonID, Capacity, Newtotal, StartTime, EndTime, ObjectID)).




increase_time() :-
    retract(current_time(CurrentTime)),
    NewTime is CurrentTime + 1,
    assert(current_time(NewTime)),

    % Teslimat personelinin her biri için çalisma saatlerini azalt
    forall(deliveryPerson(DeliveryPersonID, Capacity, Work_hours, StartTime, EndTime, CurrentLocation),
           (
               Work_hours > 0, % Eger çalisma saati sifirdan büyükse
               NewWork_hours is Work_hours - 1, % Çalisma saatini azalt
               retract(deliveryPerson(DeliveryPersonID, Capacity, Work_hours, StartTime, EndTime, CurrentLocation)),
               assert(deliveryPerson(DeliveryPersonID, Capacity, NewWork_hours, StartTime, EndTime, CurrentLocation))
           ;
               true % Eger çalisma saati zaten sifirsa, hiçbir sey yapma
           )
    ).
    %format('Time increased to ~w~n', [NewTime]).





