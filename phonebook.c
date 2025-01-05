#include <cs50.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    string name;
    string number;
}
person;

int main(void)
{

    person people[3];

    people[0].name = "Fernando";
    people[0].number = "+55 41 9 9974-7630";

    people[1].name = "Joice";
    people[1].number = "+55 41 9 9612-6541";

    people[2].name = "Bruno";
    people[2].number = "+55 41 9 8882-8422";

    string name = get_string("Name: ");

    for (int i = 0; i < 3; i++)
    {
        if (strcmp(people[i].name, name) == 0)
        {
            printf("Found %s\n", people[i].number);
            return 0;
        }
    }
    printf("Not found\n");
    return 1;
}
