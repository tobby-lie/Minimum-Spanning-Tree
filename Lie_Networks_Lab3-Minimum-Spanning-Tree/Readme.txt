*******************************************************
*  Name      :  Tobby Lie        
*  Student ID:  103385744               
*  Class     :  CSCI 3761 - Intro to Networks           
*  Lab#      :  3 - Minimum Spanning Tree               
*  Due Date  :  April 23, 2020
*******************************************************


                 Read Me


*******************************************************
*  Description of the program
*******************************************************

The program utilizes socket programming in C++ to create
A client-server interaction of two programs.

*******************************************************
*  Source files
*******************************************************

   Lie_Networks_Lab2-Minimum-Spanning-Tree/main.cpp - 
   Contains code for minimum spanning tree program. 

*******************************************************
*  Executable files after running makefile
*******************************************************

   Lie_Networks_Lab2-Minimum-Spanning-Tree/mst.o - 
   Executable to run mst program.
   
*******************************************************
*  Circumstances of programs
*******************************************************

   The program runs successfully.  
   
   The program was developed and tested on csegrid.  It was 
   compiled, run, and tested on csegrid.ucdenver.pvt.

*******************************************************
*  How to build and run the program
*******************************************************

1. Uncompress the homework. The homework file is compressed.  
   To uncompress it use the following command:
 
       % unzip Lie_Networks_Lab2-Minimum-Spanning-Tree.zip

   Now you should see multiple files:

      Lie_Networks_Lab2-Minimum-Spanning-Tree - top level directory

         - makefile - top level makefile to run mst file
         - Readme.txt - Readme file
	 - mst.cpp - mst file to run mst algorithm on txt files.
	 - You can include any .txt files in the directory to test against.

2. Build the program.

    Make sure you're in the top level directory -- Lie_Networks_Lab2-Socket-Programming
    Compile the program by (this will run makefiles for both client and server)
    % make

3. Run the program by:

   % ./mst

4. Delete the obj files, executables, and core dump by:

   First make sure you are in the top level directory -- Lie_Networks_Lab2-Socket-Programming
   % make clean