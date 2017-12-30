/*  ---------------------------------------
 *  Name: Dylan Coakley
 *  Course: Csci 356
 *  Purpose: Programming Assignment #3
 *  Date: December 1, 2017
 *  ---------------------------------------
 *  This program simulates an arbitrary deterministic
 *  Turing Machine. It takes as input the transitions,
 *  and final states if any exist. It then runs through
 *  the machines computation showing the configuration
 *  at each step.
*/

#include <iostream>
#include <algorithm>
#include <string>
#include <cctype>

using namespace std;

#define SENTINEL -1
#define tapeLength 100
#define maxTransitions 100

int getNextPos(int, char);
void showTape(char [], int, int, int);

struct Transition
{
    int fromState, toState;
    char readLetter, writeLetter, direction;
};

int main()
{
    // Create tape
    char tape[tapeLength];
    // Fill the tape with blanks initially
    fill_n(tape, tapeLength, 'B');

    // Read in all the transitions
    Transition t;
    Transition transitions[maxTransitions];
    int numTransitions = 0;

    cout << "Input transitions (-1 to stop):" << endl;

    while(true)
    {
        cin >> t.fromState;

        if(t.fromState == SENTINEL)
            break;

        cin.get(t.readLetter);
        cin >> t.toState;
        cin.get(t.writeLetter);
        cin.get(t.direction);

        transitions[numTransitions] = t;
        numTransitions++;
    }

    // Read in final states if any exist
    char ans;
    int state, numFinal = 0;
    int finalStates[maxTransitions];

    cout << "Final states? (Y/N) ";
    cin >> ans;

    if(toupper(ans) == 'Y')
    {
        cout << "Input final states (-1 to stop):" << endl;
        cin >> state;
        while(state != SENTINEL)
        {
            finalStates[numFinal] = state;
            numFinal++;
            cin >> state;
        }
    }

    // Read input string
    string input;

    cout << "Enter input string:" << endl;
    cin >> input;

    int inputSize = input.size();

    // Put input string on tape
    for(int i = 1; i <= inputSize; i++)
    {
        tape[i] = input[i-1];
    }

    // Set the initial head position and state
    int headPos = 0;
    int currentState = 0;

    cout << "\nTM's Computation Procedure\n";
    showTape(tape, inputSize, headPos, currentState);

    for(int i = 0; i < numTransitions; i++)
    {
        t = transitions[i];
        if(currentState == t.fromState and tape[headPos] == t.readLetter)
        {
            // Restart the search from beginning
            i = -1;

            // Write letter on current tape position
            tape[headPos] = t.writeLetter;
            // Transition to new state
            currentState = t.toState;
            // Move in the indicated direction
            headPos = getNextPos(headPos, t.direction);

            // Show current tape configuration along with head position
            showTape(tape, inputSize, headPos, currentState);
        }
    }

    if(numFinal > 0)
    {
        // Check if state that TM halted on is final
        bool found = false;
        for(int i = 0; i < numFinal; i++)
        {
            if(currentState == finalStates[i])
            {
                found = true;
                cout << "\nInput string accepted by final state q" << currentState << endl;
            }
        }
        if(!found)
            cout << "\nInput string not accepted by any final state" << endl;
    }

    // Show final configuration of tape
    cout << "\nTuring Machine halted with tape:" << endl;
    for(int i = 1; i <= inputSize; i++)
    {
        cout << tape[i];
    }
    cout << endl;

    return 0;
}

// Shows current configuration of tape and head, assuming that it does
// not move beyond the length of the initial input string
void showTape(char tape[], int inputSize, int headPos, int currentState)
{
    for(int i = 0; i <= inputSize + 1; i++)
    {
        if(headPos == i)
            cout << "(q" << currentState << ")";
        cout << tape[i];
    }
    cout << endl;
}

// Gets next position on tape, based on direction
int getNextPos(int pos, char dir)
{
    if(toupper(dir) == 'R')
        return pos + 1;
    else if(toupper(dir) == 'L')
        return pos - 1;
    else
        return pos;
}
