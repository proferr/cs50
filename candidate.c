#include <stdio.h>
#include <cs50.h>

typedef struct
{
    string name;
    int votes;
}
candidate;

int main(void)
{

    const int total_candidates = 3;
    candidate president[total_candidates];

    president[0].name = "Guilherme";
    president[0].votes = 15;

    president[1].name = "Ana";
    president[1].votes = 22;

    president[2].name = "Tallis";
    president[2].votes = 13;

    string candidate_winner = "";
    int highest_votes = 0;
    for (int i = 0; i < total_candidates; i++)
    {
        if(highest_votes < president[i].votes)
        {
            highest_votes = president[i].votes;
            candidate_winner = president[i].name;
        }
    }
    printf("Candidate Winner: %s \n", candidate_winner);
    printf("Total votes: %i \n", highest_votes);
}
