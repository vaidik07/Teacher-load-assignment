# Teacher-load-assignment

INTRODUCTION
In the teacher load assignment problem, we are given a set of N teachers and a set of M subjects. Each teacher has an integer workload capacity, which you can 
think of as the number of hours that the teacher is available to teach. Each teacher also has a list of subjects they have the background to teach. We would like to propose a program which solves the above discussed problem. It is compiled in Visual Studio Code with GCC compiler where the concepts of Graphs, Ford Fulkerson Algorithm for Max Flow and File Handling is used. The source code for this program is around 400 lines. This system is designed to help an institution allocate the subject sections to teachers in an efficient and equally distributed way.

Explanation Of different functions used in the main.cpp file 


Function returning vector (f)

This function takes a string profn as input, which represents a name of a file containing a list of subjects. It opens the file with the name profn.txt using an ifstream object named input_file. The function then checks whether the file is open by using the is_open() function of the ifstream object. If the file cannot be opened, the function prints "can't" on the console. If the file is successfully opened, the function reads each line of the file using the getline() function, which stores each line as a string in a variable named subj. The function then searches for the string subj in a map named m and obtains the corresponding integer value associated with it. This value is used as an index for the vector v, and the value at that index is set to 1. After reading all the lines of the file, the function closes the input file and returns the vector v. Overall, this function reads a file containing a list of subjects and returns a vector of integers with a 1 at the index corresponding to each subject in the list. This vector can be used to represent which subjects are present for a given profn.


Course_distribute

This function course_distribute() is a part of a program that distributes courses among faculty members. Here's an explanation of how the function works:

1. It reads the names of faculty members from a file named "faculty.txt" and assigns each faculty member a vector of integers indicating the subjects they can teach. This is done using the f() function, which takes the name of the faculty member as an argument and returns a vector of integers representing the subjects they can teach.

2. For each faculty member, it calculates the number of course sections they can teach for each subject they are qualified to teach. This is done by first calculating the total number of subjects that the faculty member can teach, and then dividing the load (which is apredefined constant) equally among those subjects. If a faculty member can teach only one subject, then they are assigned the entire load for that subject. This calculation is done in the following lines of code:
for(int j=0;j<course;j++)

{

int s=0;

if(v1[j]==1)

{




course_section[j]+=(load/sum);

s+=load/sum;

if(j==last_index)

{

course_section[j]+=(load-s);

}
Finally, it prints the number of course sections per subject. This is done using the printKey() function to map the integer index of the subject to its corresponding string key.


Graph_make
This is a function called `graph_make` which is used to create a graph that represents the allocation problem. The function initializes a 2D matrix called `graph` with appropriate values that represent the edges in the graph. First, the function initializes the edges from the source node to the professors by iterating over the number of professors and setting the edge weights to the `load` variable, which represents the maximum number of courses a professor can teach. Then, the function initializes the edges from the courses to the sink node by iterating over the number of courses and setting the edge weights to the number of course sections that need to be assigned to that course. Finally, the function sets the edge weights between professors and courses by iterating over the `total` vector, which stores the courses that each professor can teach. If a professor can teach a particular course, the edge weight between the corresponding professor and course is set to `INT_MAX` to represent an edge with an infinite weight, which effectively prevents such an allocation from being made in the solution.

Overall, this function sets up the graph that can be used to solve the allocation problem using the Ford-Fulkerson algorithm.


Ford Fulkerson

Ford fulkerson This function implements the Ford-Fulkerson algorithm for finding the maximum flow in a flow network. It takes as input a 2D array `graph` representing the capacity of each edge in the network, as well as the source `s` and sink `t` nodes. The function first creates a residual graph `rGraph` which initially has the same capacities as the original graph. It then repeatedly runs a BFS algorithm to find an augmenting path from the source to the sink in the residual graph. An augmenting path is a path in the residual graph where each edge has a positive residual capacity (i.e., the capacity minus the flow). If an augmenting path is found, the function determines the maximum amount of flow that can be sent along the path (i.e., the minimum residual capacity of any edge in the path). It then updates the residual capacities of the edges in the path, subtracting the flow from forward edges and adding it to backward edges. The function also keeps track of the total flow sent so far. The function repeats this process until no more augmenting paths can be found in the residual graph. Once this happens, the maximum flow in the original graph has been found, and the function returns this value.














