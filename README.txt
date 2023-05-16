Determinant Computation


Descrption: 

The project developed can compute the determinant and identify the largest element of a 3x3 matrix M. The parent process forks 3 child processes. 
All 3 children processes run concurrently and contribute to the computation of finding the determinant and the largest element in 3x3 matrix M. 
The code runs by simply executing the make file by entering the command "make" in the terminal and then running the generated executable code that is 
named "DET" by simply typing the following command "./DET". 

After running the code, a detailed and explanation will be printed in the command shell. 
First, matrix M will be printed followed by a message identifying every running process and the values executed within this process. 
In Addition, the time that every child process took will be printed as well. 
Finally, the final values of the determinant and the largest element of matrix M will be printed in the parent process.


Note: Since the children processes run concurrently, some children processes will run in different order which cause the variation in the 
print statements. 
I met one of the TAs to confirm that my code is functioning properly, he told me that this is a normal thing to happen and 
I will not lose grades as long as my code is returning the correct determinant value and the correct largest element. 
Please run the code more than once to see what I mean by this comment.


Usage:

Input: 

In order to change the matrix and test other matrices, please go to line 79 and you will find the following comment 
"//initializing the matrix M". Start filling the desired values to be tested. 

    Example: shared_stuff->M[0][1]= 20; //In that line, shared_stuff[row =0][column=1] is assigned to the value 20.

Finally, enter the following commands in the shell to run the code: "make" followed by "./DET"


Output: (may vary depending on which child process will run first)

-------------------------------------------------------------------------------------
                      Child 2  process started excuting  

Child[2] --> pid = 3523 and ppid = 3521

Child Process [2]: working with element [2] of D

The value of D[2]= 55600

The largest value in row [2]= 70

-------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------
                      Child 3  process started excuting  

Child[3] --> pid = 3524 and ppid = 3521

Child Process [3]: working with element [3] of D

The value of D[3]= -10500

The largest value in row [3]= 40

-------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------

                    Printing the 3x3 matrix M 

20  20  50  
10  6  70  
40  3  2  

-------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------
                      Child 1  process started excuting  

Child[1] --> pid = 3522 and ppid = 3521

Child Process [1]: working with element [1] of D

The value of D[1]= -3960

The largest value in row [1]= 50

-------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------
                        Parent process started excuting  

parent --> pid = 3521

The det value of the matrix M [R] = 41140

The largest value of the matrix M [L] = 70


-------------------------------------------------------------------------------------
                        The time required to perform all operations operations  


Start Time: 1634761100.636579 sec from Epoch (1970‐01‐01 00:00:00 +0000 (UTC))

End Time: 1634761100.637333 sec from Epoch (1970‐01‐01 00:00:00 +0000 (UTC))

Elapsed Time: 754 micro sec

-------------------------------------------------------------------------------------

Contribution:

I would like to thank the TAs who helped me to understand the materials until this moment: Ola Mohammed, Ziqiang Wang. 
I would like to thank my friends for helping me to fix my code bugs and achieve a better design: Ethan Leir, Zakaria Ismail, and Neso Academy.



Author:

Name: Daniah Mohammed
St#: 101145902
Date: 2021-10-19