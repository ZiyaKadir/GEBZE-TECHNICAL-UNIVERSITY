classify(SepalLength, SepalWidth, PetalLength, PetalWidth, Class) :-
    (   PetalLength =< 2.6
    ->  Class = 'Iris-setosa'
    ;   PetalLength > 2.6,
        PetalLength =< 4.95
    ->  (   PetalWidth =< 1.55
        ->  Class = 'Iris-versicolor'
        ;   PetalWidth > 1.55
        ->  Class = 'Iris-virginica'
        )
    ;   PetalLength > 4.95,
        PetalWidth =< 1.75
    ->  (   SepalWidth =< 3.1
        ->  Class = 'Iris-virginica'
        ;   SepalWidth > 3.1,
            SepalLength =< 6.5
        ->  Class = 'Iris-virginica'
        ;   SepalLength > 6.5
        ->  Class = 'Iris-versicolor'
        )
    ;   PetalWidth > 1.75
    ->  Class = 'Iris-virginica'
    ).


