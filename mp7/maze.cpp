/* Your code here! */
#include "maze.h"
#include <vector>
#include <random>
#include <algorithm>
#include <queue>

using namespace std;
using namespace cs225;

SquareMaze::SquareMaze() {
    width_ = 0;
    height_ = 0;
}

SquareMaze::~SquareMaze() {
    for (size_t i = 0; i < height_; i++) {
        for (size_t j = 0; j < width_; j++) {
            delete maze_[i][j];
        }
    }
}


void SquareMaze::makeMaze(int width, int height) {
    if (width != 0 && height != 0){
        for (size_t i = 0; i < height_; i++) {
            for (size_t j = 0; j < width_; j++) {
                delete maze_[i][j];
            }
    }
        maze_.clear();
    }
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis_x(0, width - 1);
    uniform_int_distribution<> dis_y(0, height - 1);
    uniform_int_distribution<> dis_dir(0, 1);
    
    width_ = width;
    height_ = height;
    //set all walls to true
    for (size_t i = 0; i < height_; i++) {
        vector<Cell* > temp;
        for (size_t j = 0; j < width_; j++) {
            Cell* cur = new Cell(i, j, true, true);
            temp.push_back(cur);
        }
        maze_.push_back(temp);
    }
    //randomly remove walls
    DisjointSets set;
    set.addelements(width_ * height_);
    int size = width_ * height_;
    while (set.size(0) != size) {
        //select a random sell
        int x = dis_x(gen);
        int y = dis_y(gen);
        int dir = dis_dir(gen);
        if (dir) {
            if (y != height_ - 1 && set.find(y * width_ + x) != set.find((y + 1) * width_ + x)) {
                set.setunion(y * width_ + x, (y + 1) * width_ + x);
                maze_[y][x]->downWall = false;
            }
        }
        else {
            if (x != width_ - 1 && set.find(y * width_ + x) != set.find(y * width_ + x + 1)) {
                set.setunion(y * width_ + x, y * width_ + x + 1);
                maze_[y][x]->rightWall = false;
            }
        }
    }

}

bool SquareMaze::canTravel(int x, int y, int dir) const {
    if (dir == 0) {
        if (x == width_ - 1) return false;
        else return !maze_[y][x]->rightWall;
    }
    else if (dir == 1) {
        if (y == height_ - 1) return false;
        else return !maze_[y][x]->downWall;
    }
    else if (dir == 2) {
        if (x == 0) return false;
        else return !maze_[y][x - 1]->rightWall;
    }
    else if (dir == 3) {
        if (y == 0) return false;
        else return !maze_[y - 1][x]->downWall;
    }
    return false;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists) {
    if (dir) maze_[y][x]->downWall = exists;
    else maze_[y][x]->rightWall = exists;
}

vector<int> SquareMaze::solveMaze() {
    vector<int> solution_;
    solveMazeHelper(maze_[0][0]);
    int longest = 0;
    int longest_dist = 0;
    for (size_t i = 0; i < width_; i++) {
        if (maze_[height_ - 1][i]->distance > longest_dist) {
            longest = i;
            longest_dist = maze_[height_ - 1][i]->distance;
        }
    }
    exit_ = maze_[height_ - 1][longest];
    locatepath(maze_[height_ - 1][longest], solution_);
    reverse(solution_.begin(), solution_.end());
    return solution_;
}

void SquareMaze::solveMazeHelper(Cell* cur) {
    //BFS
    queue<Cell* > trav;
    trav.push(cur);
    cur->visited = true;
    while (!trav.empty()) {
        Cell* temp = trav.front();
        trav.pop();
        if (canTravel(temp->x, temp->y, 0) && (maze_[temp->y][temp->x + 1]->visited != true)) {
            maze_[temp->y][temp->x + 1]->visited = true;
            maze_[temp->y][temp->x + 1]->prev = temp;
            maze_[temp->y][temp->x + 1]->distance = temp->distance + 1;
            trav.push(maze_[temp->y][temp->x + 1]);
        }
        if (canTravel(temp->x, temp->y, 1) && (maze_[temp->y + 1][temp->x]->visited != true)) {
            maze_[temp->y + 1][temp->x]->visited = true;
            maze_[temp->y + 1][temp->x]->prev = temp;
            maze_[temp->y + 1][temp->x]->distance = temp->distance + 1;
            trav.push(maze_[temp->y + 1][temp->x]);
        }
        if (canTravel(temp->x, temp->y, 2) && (maze_[temp->y][temp->x - 1]->visited != true)) {
            maze_[temp->y][temp->x - 1]->visited = true;
            maze_[temp->y][temp->x - 1]->prev = temp;
            maze_[temp->y][temp->x - 1]->distance = temp->distance + 1;
            trav.push(maze_[temp->y][temp->x - 1]);
        }
        if (canTravel(temp->x, temp->y, 3) && (maze_[temp->y - 1][temp->x]->visited != true)) {
            maze_[temp->y - 1][temp->x]->visited = true;
            maze_[temp->y - 1][temp->x]->prev = temp;
            maze_[temp->y - 1][temp->x]->distance = temp->distance + 1;
            trav.push(maze_[temp->y - 1][temp->x]);
        }
    }
}

void SquareMaze::locatepath(Cell* longest_cell, vector<int> & soln) {
    Cell* cur = longest_cell;
    Cell* prev;
    while (cur != maze_[0][0]) {
        prev = cur->prev;
        if (prev->x < cur->x && prev->y == cur->y) soln.push_back(0);
        else if (prev->y < cur->y && prev->x == cur->x) soln.push_back(1);
        else if (prev->x > cur->x && prev->y == cur->y) soln.push_back(2);
        else if (prev->y > cur->y && prev->x == cur->x) soln.push_back(3);
        cur = prev;
    }
}

PNG* SquareMaze::drawMaze() const {
    //init
    PNG* maze_pic = new PNG(width_*10 + 1, height_*10 + 1);
    for (size_t i = 0; i < width_*10 + 1; i++) {
        if (i < 1 || i > 9) {
            HSLAPixel * pixel = maze_pic->getPixel(i, 0);
            pixel->l = 0;
        }
    }
    for (size_t i = 0; i < height_*10 + 1; i++) {
        HSLAPixel * pixel = maze_pic->getPixel(0, i);
        pixel->l = 0;
    }
    //for each cell...
    for (size_t i = 0; i < height_; i++) {
        for (size_t j = 0; j < width_; j++) {
            if (maze_[i][j]->rightWall) {
                for (size_t k = 0; k < 11; k++) {
                    HSLAPixel * pixel = maze_pic->getPixel((j+1)*10, i*10 + k);
                    pixel->l = 0;
                }
            }
            if (maze_[i][j]->downWall) {
                for (size_t k = 0; k < 11; k++) {
                    HSLAPixel * pixel = maze_pic->getPixel(j*10 + k, (i+1) * 10);
                    pixel->l = 0;
                }
            }
        }
    }
    return maze_pic;
}

PNG* SquareMaze::drawMazeWithSolution() {
    PNG* mazeImage_ = drawMaze();
    //find the path
    vector<int> solution = solveMaze();
    //starting point
    size_t x = 5;
    size_t y = 5;
    //for each step...
    for (size_t i = 0; i < solution.size(); i++){
        if (solution[i] == 0) {
            for (size_t j = 0; j < 11; j++) {
                HSLAPixel * pixel = mazeImage_->getPixel(x + j, y);
                pixel->h = 0;
                pixel->s = 1;
                pixel->l = 0.5;
                pixel->a = 1;
                
            }
            x += 10;
        }
        else if (solution[i] == 1) {
            for (size_t j = 0; j < 11; j++) {
                HSLAPixel * pixel = mazeImage_->getPixel(x, y + j);
                pixel->h = 0;
                pixel->s = 1;
                pixel->l = 0.5;
                pixel->a = 1;
                
            }
            y += 10;
        }
        else if (solution[i] == 2) {
            for (size_t j = 0; j < 11; j++) {
                HSLAPixel * pixel = mazeImage_->getPixel(x - j, y);
                pixel->h = 0;
                pixel->s = 1;
                pixel->l = 0.5;
                pixel->a = 1;
                
            }
            x -= 10;
        }
        else if (solution[i] == 3){
            for (size_t j = 0; j < 11; j++) {
                HSLAPixel * pixel = mazeImage_->getPixel(x, y - j);
                pixel->h = 0;
                pixel->s = 1;
                pixel->l = 0.5;
                pixel->a = 1;
                
            }
            y -= 10;
        }
    }
    //make exit
    for (size_t i = 1; i < 10; i++) {
        HSLAPixel * pixel = mazeImage_->getPixel(exit_->x*10 + i, (exit_->y+1)*10);
        pixel->l = 1;
    }
    return mazeImage_;
}