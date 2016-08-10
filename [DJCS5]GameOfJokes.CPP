/*
-----Question-----
Two players play a game where each round has 1 winner. 
The game ends when: 
- One of them gets 20 points and other has < 19 points ( strictly less than 19).
- Or if the score ties at 19:19, both continue to play until the absolute difference between the scores is 2. 
- Given the final score of a game in format of two integers A and B i.e.
  print the number of different sequences of gaining points by them that 
  leads to this final score
- Print the answer modulo 10e9+7
Input format:
Line 1       : t - no. of test cases
Line 2-(t+1) : a, b-> games won by player A and player B
Output format:
Single integer value
*/

#include <vector>
#include <iostream>
using namespace std;
typedef uint64_t ull;

static const ull MOD= 1000000000+7;

/*---utility functions for max and min ---*/
int max(int a, int b){
    return a>b? a: b;
}
int min(int a, int b){
    return a<b? a:b;
}

/*--Pre-process all combinations---*/
vector <vector<ull>> Pascal(){
    vector<vector<ull>> arr (40, vector<ull>(40, 0));
    arr [0][0]=1, arr[0][1]=1, arr[1][0]=1;
    for(int i=1; i<40; i++){
        for(int j=0; j<i+1; j++){
            if (j==0 || j==i){
                arr[i][j]=1;
            }
            else{
                arr[i][j]= (arr[i-1][j-1]%MOD+arr[i-1][j]%MOD)%MOD;
            }
        }
    }
    return arr;
}

/*---calculate exponent value quickly---*/
ull FastExpo(ull x, int n){
    ull result=1;
    while(n>0){
        if(n%2==1) result= (result*x)%MOD;
        x= (x*x)%MOD;
        n= n/2;
    }
    return result%MOD;
}

/*----solving the problem----*/
ull solve(int a, int b, vector<vector<ull>> combos){
    
    /*
    Invalid results:
    - If neither reaches 19
    - If both winning score is above 20, but the difference is less or greater than 2
    - If the winning score is 20 but the losing score is not 18 or less
    */

    if ((a<=19 && b<=19) || (max(a,b)>20 && !(abs(b-a)==2)) || (max(a,b)==20 && !(min(a,b)<19))){
        return 0;
    }
    else{
        /*
        In a+b games, fix the last game as won
        We can now distribute the loser's wins among
        the remaining spaces. Automatically the winner's games
        are arranged
        */
        if(max(a,b)==20 && min(a,b)<19){
            return combos[a+b-1][min(a,b)];
        }
        else{
        /*
        - Otherwise distribute all games so that we get 19:19
        - After that the only possible outcome is a winner through
          a lead of TWO. 
        - As every game alternates between having two
          outcomes (winner A or winner B) then only one (TIE), till
          we reach the loser's count of wins.
        - This amounts to  exp(2, loser's games- 19 games won already)
        - As these distributions are dependent, we do a multiplication (AND)
        */
            return (combos[38][19]*(FastExpo(2,(min(a,b)-19))))%MOD;
        }
    }
}

/*--input and function calls---*/
int main() {
    vector <vector<ull>> combs = Pascal();
    int t, a, b;
    cin>>t;
    while(t--){
        cin>>a>>b;
        cout<<solve(a,b, combs)<<"\n";
    }
    return 0;
}
