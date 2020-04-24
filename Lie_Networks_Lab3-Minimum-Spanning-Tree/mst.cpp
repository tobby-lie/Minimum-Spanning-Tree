// Tobby Lie
// Introductions to Networks: Lab 3

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <tuple>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <chrono>
#include <climits>

void MST(std::string input_file)
{
    typedef std::vector<std::vector<int>> Matrix; // vector of vectors to represent a matrix
    typedef std::vector<int> Row; // rows for the matrix
    
    int dimension_n = 0; // must be variable size based on number of nodes which is fist line of txt file
    Matrix matrix; // used for adjacency matrix
    
    /* START EXECUTION TIME FOR FILE READ IN TO ADJACENCY MATRIX */
    auto start_read_file = std::chrono::high_resolution_clock::now();
    
    std::ifstream in_file;
    in_file.open(input_file.c_str()); // open specified input file
    
    if(in_file.fail()) // check for file open failure, if fail, return from function
    {
        std::cout << "--------------------------------------" << std::endl;
        std::cout << "* Specified input file failed to open!" << std::endl;
        std::cout << "--------------------------------------" << std::endl;
        return;
    } // end if
    
    std::string line_str = "";
    std::getline(in_file, line_str); //  get first line of txt file to get number of nodes
    
    dimension_n = stoi(line_str); // number of nodes is the dimension of matrix
    // need to create dynamically sized adjacency matrix n x n, n being number of nodes
    
    // create dimension_n by dimension_n square adjaceny matrix filled with zeros
    for(int i = 0; i < dimension_n; i++)
    {
        Row row(dimension_n); // create row with dimension_n

        for(int j = 0; j < dimension_n; j++)
        {
            row[j] = 0;
        } // end for
        matrix.push_back(row);
    } // end for
    
    // create adjacency matrix
    int count = 0;
    while(std::getline(in_file, line_str)) // read through each line
    {
        int row = 0;
        int col = 0;
        int cost = 0;
        
        std::istringstream ss(line_str);
        
        do
        {
            int component; // read each component of ss
            ss >> component;
            
            // depending on count, extract and place component in appropriate spots
            if(count == 0)
            {
                row = component;
            }
            else if(count == 1)
            {
                col = component;
            }
            else if(count == 2)
            {
                cost = component;
            }
            count++;
        }while(ss); // end of do while
        
        count = 0; // reset count
        
        matrix[row-1][col-1] = cost; // insert cost into appropriate link
    }// end of while
    
    in_file.close(); // close file
    
    auto stop_read_file = std::chrono::high_resolution_clock::now();
    
    auto dur_read_file_ms = std::chrono::duration_cast<std::chrono::milliseconds>(stop_read_file - start_read_file);
    
    /* STOP EXECUTION TIME FOR FILE READ IN TO ADJACENCY MATRIX */
    
    int edge; // number of edges
    
    int visit[dimension_n]; // create array to check visited vertices
    
    // initialize visit array to false
    for(int i = 0; i < dimension_n; i++)
    {
        visit[i] = false;
    } // end for
    
    edge = 0; // set number of edges to 0
    
    // number of edges in minimum spanning tree will always be less
    // than dimension_n - 1 where dimension_n is the number of vertices
    // or nodes in the graph
    
    visit[0] = true; // choose 0th vertex and make it true since you have visited this first
    
    int x; // row number
    int y; // col number
    
    // print edge and weight
    std::cout << "-----------------------------" << std::endl;
    std::cout << "|        Edge : Weight      |" << std::endl;
    std::cout << "-----------------------------" << std::endl;
    
    int cost_accumulator = 0; // keeps tally of overall cost
    
    typedef std::vector<std::tuple<int, int>> vec_of_tuples; // vector of tuples
    vec_of_tuples tup_vec;
    
    /* START EXECUTION TIME FOR MST ALGORITHM */
    auto start_mst = std::chrono::high_resolution_clock::now();
    
    // MST using Prim's algorithm
    while(edge < dimension_n - 1)
    {
        // spanning tree consists of dimension_n - 1 edges
            
        // For every vertex in the set S, find all adjacent vertices
        // calculate the distance form vertex chosen
        // if vertex is visited already discard
        // otherwise choose another vertext closer to chosen vertex
        
        int min = INT_MAX; // cannot store any value beyond INT_MAX limit per the compiler
        x = 0; // set x to 0
        y = 0; // set y to 0
        
        for(int i = 0; i < dimension_n; i++)
        {
            if(visit[i]) // if node has been visited
            {
                // go through row
                for(int j = 0; j < dimension_n; j++)
                {
                    // if node at j has not been visited and node [i][j] in
                    // adjaceny exists
                    if(!visit[j] && matrix[i][j])
                    {
                        // not chosen and there exists an edge
                        if(min > matrix[i][j])
                        {
                            min = matrix[i][j]; // update new min
                            x = i; // update x
                            y = j; // updatey
                        } // end if
                    } // end if
                } // end for
            } // end if
        } // end for
        
        // print out edge for given iteration and its associated weight
        std::cout << x + 1 << " ---> " << y + 1 << " : " << matrix[x][y] << std::endl;
        tup_vec.push_back(std::make_tuple(x + 1, y + 1)); // add these edge nodes as tuple to vector
        cost_accumulator += matrix[x][y]; // add to overall cost
        visit[y] = true; // node at y has now been visited
        edge++; // increment edge
    } // end while
    
    auto stop_mst = std::chrono::high_resolution_clock::now();
    
    auto dur_mst_ms = std::chrono::duration_cast<std::chrono::milliseconds>(stop_mst - start_mst);
    
    /* STOP EXECUTION TIME FOR MST ALGORITHM */
    
    // add the two execution times
    // one for file read in
    // second for MST algorithm
    auto dur_ms = dur_read_file_ms.count() + dur_mst_ms.count();
                
    std::cout << "-----------------------------" << std::endl;
    std::cout << "| Total execution time = " << dur_ms << " ms" << std::endl;
    std::cout << "-----------------------------" << std::endl;
    std::cout << "| Minimum Spanning Tree (T) |" << std::endl;
    std::cout << "-----------------------------" << std::endl;
    
    // sort vector in order by first tuple element
    std::sort(tup_vec.begin(), tup_vec.end());
    
    std::vector<std::vector<std::tuple<int, int>>> vec_of_vec; // vector of vector of tuples
    vec_of_tuples vec_of_tup;
    
    // display minimum spanning tree
    auto it = tup_vec.begin(); // start at top of sorted tup_vec
    std::tuple<int, int> next_node; // holds next node to traverse to
    
    // go until tup_vec is empty
    while(!tup_vec.empty())
    {
        next_node = tup_vec[0]; // start at beginning node
        vec_of_tup.push_back(next_node); // add to vec_of_tup
        tup_vec.erase(tup_vec.begin()); // erase first node
        it = tup_vec.begin(); // point to new first node
        
        // go through all tup_vec elements
        while(it != tup_vec.end())
        {
            // if next node first element is same as prev node second element
            // then we chose this node to traverse with
            if(std::get<1>(next_node) == std::get<0>(*it))
            {
                next_node = *it; // next node picks up where this node was
                vec_of_tup.push_back(next_node); // put node into vec_of_tup
                tup_vec.erase(it); // erase current node
                it = tup_vec.begin(); // iterator starts at new bginning
            } // end if
            else
            {
                it++; // increment iterator if next node is not updated
            } // end else
        } // end while
        vec_of_vec.push_back(vec_of_tup); // add vec_of_tup to vec_of_vec
        vec_of_tup.clear(); // clear vec_of_tup for next iteration
    } // end while
    
    // go through vec_of_vec and display all paths in MST
    for(int i = 0; i < vec_of_vec.size(); i++)
    {
        // go though all elements of each row to display
        for(auto it = vec_of_vec[i].begin(); it != vec_of_vec[i].end(); it++)
        {
            std::cout << "(" << std::get<0>(*it) << "," << std::get<1>(*it) << ")";
            // display arrow if next iterator is not end
            if(!(std::next(it, 1) == vec_of_vec[i].end()))
            {
                std::cout << "-->";
            } // end if
        } // end for
        // if i++ is equal to end of for loop then print out endl
        if(!(i + 1 == vec_of_vec.size()))
        {
            std::cout << std::endl;
        } // end if
    } // end for
    
    // display minimum cost
    std::cout << std::endl;
    std::cout << "-----------------------------" << std::endl;
    std::cout << "| Minimum Cost = " << cost_accumulator << std::endl;
    std::cout << "-----------------------------" << std::endl;
}

int main() {
    
    // display prompt
    std::string command = "";
    std::string command_part = "";
    std::vector<std::string> command_vec;
    while(1)
    {
        std::cout << "-----------------------" << std::endl;
        std::cout << "Command List: " << std::endl;
        std::cout << "-----------------------" << std::endl;
        std::cout << "mymst <test-input-file>" << std::endl;
        std::cout << "mymst exit" << std::endl;
        std::cout << "-----------------------" << std::endl;
        std::cout << ">";
        std::getline(std::cin, command);
        
        std::istringstream iss(command);
        
        while(iss >> command_part)
        {
            command_vec.push_back(command_part);
        }
        
        if(command_vec.size() > 2 || command_vec.size() < 2)
        {
            std::cout << "* Error: Only two inputs are accepted!" << std::endl;;
        }
        else if(command_vec[0] != "mymst")
        {
            std::cout << "* Error: Invalid first input!" << std::endl;
        }
        else if(command_vec[1] == "exit")
        {
            std::cout << "* Goodbye!" << std::endl;
            exit(1);
        }
        else
        {
            MST(command_vec[1]);
        }
        
        command_vec.clear();
    }

    return 0;
}
