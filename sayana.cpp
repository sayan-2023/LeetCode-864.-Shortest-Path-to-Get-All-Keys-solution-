#include<bits/stdc++.h>
using namespace namespace std;
// Sayan_Dutta

class Solution {
public:
    // ALL four diresctions
    const int dx[4] = {-1, 1, 0, 0};
    const int dy[4] = {0, 0, -1, 1};

    // Checking if new coordinates are going out of grid on not
    bool isValid(int x, int y, int rows, int cols) {
        return (x>=0 and x<rows and y>=0 and y<cols);
    }
public:

    int shortestPathAllKeys(vector<string>& grid) {

        int rows = grid.size();
        int cols = grid[0].size();

        int keys = 0;
        
        // {i, j, mask}
        queue<vector<int>> q;

        for(int i=0; i<rows; i++) {
            for(int j=0; j<cols; j++) {

                if(islower(grid[i][j])) {
                    keys++;//How many keys present in the gird
                }

                if(grid[i][j] == '@') {
                    q.push({i, j, 0});// coordinates where BFS is started
                }
            }
        }
        set<vector<int>> vis; // {i,j, currMask}
        int steps = 0;
        //DO BFS
        while(not q.empty()) {
            int sz = q.size();

            for(int i=0; i<sz; i++) {

                vector<int> currCell = q.front();
                q.pop();

                int x = currCell[0];
                int y = currCell[1];
                int mask = currCell[2];

                // If we have collected all keys the return steps
                // If the no.of set bits is equal to no.of keys
                //it means we traversed all the key
                if(__builtin_popcount(mask) == keys){
                    return steps;
                }

                for(int k=0; k<4; k++){
                    int newX = x + dx[k];// changing  the  X coordinate
                    int newY = y + dy[k]; //changing the y coordinate

                    if (isValid(newX, newY, rows, cols) == false or grid[newX][newY] == '#') {
                        continue;
                    }

                    char newChar = grid[newX][newY];
                    int newMask = mask;

                    // If new char is lowercase, means we find a key so add it to our mask.
                    if (islower(newChar)) {
                        newMask |= (1 << (newChar - 'a'));// set the bits becuse new key is found
                    }

                    // If we visisted already and we find the lock and also we have key of the lock then do BFS other wise not. 
                    if(
                        vis.find({newX, newY, newMask}) != vis.end() or
                      (isupper(newChar) and !(mask&(1<<(newChar-'A')))) 
    
                      )
                  // !(mask&(1<<(newChar-'A')) it means key of that lock is not found
                    continue;
                    // This is the case where we can't do any BFS.(Because it is visited and we face lock and we not have key of that lock)
                    
                    // Lastly push new char and newmask (Do normal BFS)
                    q.push({newX, newY, newMask});
                    vis.insert({newX, newY, newMask}); // Track the position and also status of masks which contain the information about keys .
                }
            }

            // Increase steps at each iteration
            steps++;
        }

        return -1;
    }
};


