#include <cs50.h>
#include <stdio.h>
#include <string.h> 

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min_votes);
void eliminate(int min_votes);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
// voter here is the number of total voters 
// rank here is the total canidates number
// name is the names of candidates 
bool vote(int voter, int rank, string name)
{
// TODO
// iterate through the numbers of candidates and get each candidate's name 
    for (int i = 0; i < candidate_count; i++)
    {
// use strcmp to compare name and candidates[i].name and if the return is 0
        if (strcmp(name, candidates[i].name) == 0)
        {
// add the i(index) to the two-d array which belongs to the voter position and candiates position 
            preferences[voter][rank] = i;
// exit this boolean after the execution
            return true; 
        }
    }
// If there is no matching names, return false to exit the iteration 
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // TODO
// use a nest loops to get voters and candidates, so it will go through from 0 row and go to col before the next row
// therefore, access each individual candidates in preferences
    for (int i = 0; i < voter_count; i++)
    {

        for (int j = 0; j < candidate_count; j++)
        {
// add this if condition to only give votes to the candidates who are no eliminated from the election
// by using preferences[i][j], it gives  
// set bool eliminated to false value 
            if (candidates[preferences[i][j]].eliminated == false)
            {
// access to each preferences to access to the candidates index and increment votes by one
                candidates[preferences[i][j]].votes++;
// use break here to prevent the same candidate get more than one vote after adding one, or just hit the infinite loop 
// this break will stop the loop whereas return will stop the entire execution of the function
                break;
            }
        }
    }
// exit the function with no return value  
   return; 
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // TODO
// go through each candidate
    for (int i = 0; i < candidate_count; i++)
    {
// set a variable to keep the winningcandidate's name
        string winner_name = candidates[i].name; 
// if there is a clear winner who wins more than half of the votes, we will print out the name of that candidate
        if (candidates[i].votes > voter_count / 2) 
        {
// exite the function with the name when there is a clear winner 
            printf("%s\n", winner_name);
            return true; 
        }
    }
// else exit the function without a winner 
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
// TODO
// set the minimal votes to the voter_counter
    int min_votes = voter_count; 
    
    for (int i = 0; i < candidate_count; i++)
    {
// candiates who is not eliminated and candiates who's votes less more equal to minimal votes 
        if (candidates[i].eliminated == false && candidates[i].votes <= min_votes)
        {
// update the canidates votes to the current minimal votes 
            min_votes = candidates[i].votes;
        }
    }
// have this function return the minimal votes so it can be used elsewhere
    return min_votes;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min_votes)
{
    // TODO
    
// iterate through all the candidates 
    for (int i = 0; i < candidate_count; i++)
    {
// candidates who are not eliminated and not equal to the minimal votes would mean that 
// there are the votes are not evenly shared among the candidates 
        if (candidates[i].eliminated == false && candidates[i].votes != min_votes)
        {
// exit the function when there is no tie
            return false; 
        }
    }
// exit this function when there is a tie 
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min_votes)
{
    // TODO
 
// iterate through all the candidates who's eliminated == false
// check is the votes they have is equal to the min_votes; 
// if it is true, change eliminated = true; which is assign the value to it 

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false && candidates[i].votes == min_votes) 
        {
            candidates[i].eliminated = true; 
        }
    }
}