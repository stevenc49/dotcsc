    #include <exception>

    int * problemNum = new int;
    int (* p [100])() = {problem1, problem2, problem3};

    ...

    try {
        cout << (*p[*problemNum-1])();
    }
    catch (exception){
        cout << "No such problem";
    }
