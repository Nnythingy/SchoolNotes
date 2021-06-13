This file includes terms/jargon/lingo explained by a Singaporean.

## [Big O Notation](https://en.wikipedia.org/wiki/Big_O_notation)
Agar Agar how long your program will take in terms of input. 

## Loops
Like someone who is nagging, will keep repeating and never stop until its time to go home (A condition is met/broken).
Always ensure that the condition can be reached or can end, if not the nagging will not stop

### [While Loops](https://en.wikipedia.org/wiki/While_loop)
Only when condition true, then will run code
###### Example: 
    while (you score an A for your exam) {
      you can stay at home;
    }
    // This means that if you do not score an A for exams, you cannot stay at home at all
    // Does not matter if there are no exams to take, no A, no home

### [Do - While Loops](https://en.wikipedia.org/wiki/Do_while_loop)
Run code 1 time, then after that check
###### Example: 
    do {
      you can stay at home;
    } while (you score an A for your exam);
    //This means that you start staying at home first before the exams, only after exams results release if you do not score an A, you cannot stay at home

### [For Loops](https://en.wikipedia.org/wiki/For_loop)
Concept similar to while loops, and many different intepretations
But usually there is a range set to keep repeating.
Similar to your mother asking you to start peeling carrots from 1pm to 7pm

###### Example: 
    for (int time = 1pm (initialisation); time less than 7pm (condition must be true to keep looping); time ticks (updating a counter so loop can end) ) {
        peel carrots;
    }
    // This means you start peeling carrots from 1pm to 7pm
    
### [For - each Loops](https://en.wikipedia.org/wiki/Foreach_loop)
Use the things inside the set for the code, then loop them until the set has ended
Do note that python for loops are similar to this

###### Example: 
    foreach carrot in bag:
        peel carrot
    
    // This means you peel all the carrots in the bag given
## [Pointers](https://en.wikipedia.org/wiki/Pointer_(computer_programming))
This has already been well explained in the slides for [cs1010](https://github.com/Nnythingy/SchoolNotes/tree/main/cs1010) and [cs2040c](https://github.com/Nnythingy/SchoolNotes/tree/main/cs2040C) which uses the analogy of a pokeball which I personally like.
Hence my attempt to create an analogy would be just trying to reinvent the wheel. 

Variable = Your phone and the value/data stored would be your phone model (eg: iPhone 12)
Pointer = Your phone number

When you call a number (pointer), it will find the correct phone (variable) to call and be able to call you.
The number is hence just a reference for other people to contact your phone. Different phone, different number.

### [Call by Reference](https://en.wikipedia.org/wiki/Evaluation_strategy#Call_by_reference)
Your friend has a project and creates a survey for people with iPhone 12 to answer. 
A call by reference is your friend calling your number to specifically ask you to fill in the survey.
Following the previous analogy, a call by reference would just mean that calling your number to get exactly your phone and hence your phone model.

Used when you die die need to interact with that specific variable in your function

### [Call by Value](https://en.wikipedia.org/wiki/Evaluation_strategy#Call_by_value)
Your friend has a project and creates a survey for people with iPhone 12 to answer. 
A call by value is your friend calling any number and ask them to fill in the survey if they have an iPhone 12.
Following the previous analogy, a call by value would just mean that the iPhone 12 is the focus and anyone with an iPhone 12 would be the same.

Used most of the time since you just wanna do cool math with the input

[The difference](https://www.geeksforgeeks.org/difference-between-call-by-value-and-call-by-reference/), explained by people who know what they are doing.

## [Fuzzing](https://en.wikipedia.org/wiki/Fuzzing)
It is the concept of guess and check
Repeatedly guessing and then checking to see the results.
Some uses can be to guess inputs to purposes make the code fail.

###### Example:
Your mother dabao lunch home. You know she dabao from the nearby hawker center.
Although it is not time to eat yet, you want to know what she dabao so you keep asking her:
"What you dabao? Is it from _______ stall?" replacing the blank with all the stalls in the hawker center one by one
