/* Your code here! */
#ifndef MAZE_H
#define MAZE_H
#include "cs225/PNG.h"
#include "dsets.h"
#include <vector>
#include <list>

using namespace std;
using namespace cs225;

class SquareMaze {
    private:
        //the structure of each cell
        struct Cell {
            Cell(int i, int j, bool rightWall, bool downWall) : 
                x(j), y(i), rightWall(rightWall), downWall(downWall), visited(false), distance(0) {}
            size_t x;
            size_t y;
            bool rightWall;
            bool downWall;
            //parameters aiming for BFS and path recording
            int distance; //distance from the start
            bool visited; 
            Cell* prev;
        };
    public:
        /**
         * The defualt constructor of SquareMaze.
         */
        SquareMaze();
        /**
         * The destructor of SquareMaze.
         */
        ~SquareMaze();
        /**
         * Makes a new SquareMaze of the given height and width.
         * If this object already represents a maze it will clear all the existing data before doing so. 
         * The code selects random walls to delete without creating a cycle, until there are no more walls that could be deleted without creating a cycle. 
         *
         * @param width The width of the SquareMaze (number of cells)
         * @param height The height of the SquareMaze (number of cells)
         */
        void makeMaze(int width, int height);
        /**
         * This determines whether it is possible to travel in the given direction from the square at coordinates (x,y).
         *
         * @param x The x coordinate of the current cell
         * @param y The y coordinate of the current cell
         * @param dir The desired direction to move from the current cell
         * @return whether you can travel in the specified direction
         */
        bool canTravel(int x, int y, int dir) const;
        /**
         * Sets whether or not the specified wall exists.
         *
         * @param x The x coordinate of the current cell
         * @param y The y coordinate of the current cell
         * @param dir Either 0 (right) or 1 (down), which specifies which wall to set.
         * @param exists true if setting the wall to exist, false otherwise
         */
        void setWall(int x, int y, int dir, bool exists);
        /**
         * Select the square in the bottom row with the largest distance from the origin as the destination of the maze. 
         * solveMaze() returns the winning path from the origin to the destination as a vector of integers, 
         * where each integer represents the direction of a step, using the same encoding as in canTravel().
         *
         * @return a vector of directions taken to solve the maze
         */
        vector<int> solveMaze();
        /**
         * Draws the maze without the solution.
         *
         * @return a pointer to a PNG object that represents the unsolved SquareMaze
         */
        PNG* drawMaze() const;
        /**
         * This function calls drawMaze(), then solveMaze(); 
         * it modifies the PNG from drawMaze() to show the solution vector and the exit.
         *
         * @return a pointer to a PNG object that represents the solved SquareMaze
         */
        PNG* drawMazeWithSolution();
    private:
        /**
         * This function is a helper function for solveMaze(). 
         * It performs a BFS on the maze to find the longest path from the origin to the destination. 
         *
         * @param cur The current cell
         */
        void solveMazeHelper(Cell* cur);
        /**
         * This function records the longest path found in solveMazeHelper() and stores it in soln.
         *
         * @param longest_cell The cell that is the destination of the longest path
         * @param soln The vector that stores the longest path
         */
        void locatepath(Cell* longest_cell, vector<int> & soln);

        size_t width_; //width of the maze
        size_t height_; //height of the maze
        vector<vector<Cell*> > maze_; //represent the maze in a 2D vector
        Cell* exit_; //the exit of the maze
};
#endif