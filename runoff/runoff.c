#include <cs50.h>
#include <stdio.h>
#include<string.h>

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
} candidate;

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
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Sample input
    // argc = 4;
    // argv[1] = "alice";
    // argv[2] = "bob";
    // argv[3] = "charlie";


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
bool vote(int voter, int rank, string name)
{

    for(int j = 0; j < candidate_count; j++)
    {
        if(strcmp(candidates[j].name, name) == 0)
        {
            // printf("Voter's candidate found!\n");
            preferences[voter][rank] = j;
            return true;
        }
    }


    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    int top_choice = 0;

    for(int v = 0; v < voter_count; v++)
    {
        for(int c = 0; c < candidate_count; c++)
        {
            if(candidates[preferences[v][c]].eliminated == false)
            {
                top_choice = preferences[v][c];
                candidates[top_choice].votes ++;
                break;
            }
        }
    }

    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    int half_votes = voter_count / 2;


    for(int i = 0; i < candidate_count; i++)
    {
        if(candidates[i].votes <= half_votes)
        {
            continue;
        }
        else
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int minimum_vote = 0;


    for(int i = 0; i < candidate_count; i++)
    {

        if(candidates[i].votes >= minimum_vote && candidates[i].eliminated == true)
        {
            continue;
        }
        else if(candidates[i].eliminated == false)
        {
            minimum_vote = candidates[i].votes;
        }

    }

    if(minimum_vote != 0)
        return minimum_vote;

    return 0;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{

    /*
        - Find the first candidate
            - Determine whether it is in or out
                - If in
                    - Then save its count
                - If out
                    - Ignore
        - Make a loop and compare the values with saved count
            - Make sure to ignore the values which are eliminated
    */



    int comparison = min;

    // First non-eliminated candidate
    for(int i = 0; i < candidate_count; i++)
    {
        if(candidates[i].eliminated == false)
        {
            comparison = candidates[i].votes;
            break;
        }
        else
        {
            continue;
        }
    }

    // Comparison loop
    for(int j = 0; j < candidate_count; j++)
    {
        if(candidates[j].eliminated == false)
        {
            if(comparison == candidates[j].votes)
            {
                continue;
            }
            else
            {
                return false;
            }
        }
        else
        {
            continue;
        }
    }


    return true;



















    // int vote = 0;
    // bool same = false;

    // for(int i = 0; i < candidate_count; i++)
    // {
    //     if(candidates[i].eliminated == true)
    //     {
    //         continue;
    //     }
    //     else if (candidates[i].eliminated == false)
    //     {
    //         for(int j = 0; j < candidate_count; j++)
    //         {
    //             if(candidates[i].votes == candidates[j].votes)
    //             {
    //                 printf("Match found!\n");
    //                 same = true;
    //             }
    //             else
    //             {
    //                 printf("misMatch found!\n");
    //                 same = false;
    //             }
    //         }
    //     }
    // }

    // printf("Final Output: %i\n", same);
    // if (same)
    // {
    //     return true;
    // }
    // else
    // {
    //     return false;
    // }


}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for(int o = 0; o < candidate_count; o++)
    {
        if(candidates[o].votes == min)
        {
            candidates[o].eliminated = true;
        }
    }

    return;
}
