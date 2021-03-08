/*
 * program for baseball or softball on-base percentage, by John C. Lusth, 2014
 * 
 * this program may be freely distributed and modified, as long as:
 * 
 * a) the authorship of any modifications is added
 *
 * b) the reason for modification is added
 *
 * c) the comments are updated to reflect modifications
 *
 * d) the original authorship and that of any previous modifiers is preserved.
 *
 *
 * MODIFICATION
 * Adapted by Joshua Neely in 2021 for the purpose of self study on an old c course.
 */

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <math.h>

// function prototypes

void getData(int *, int *, int *, int *, int *, int *);
void displayData(int, int, int, int, int, int);
void displayRating(double);
double computeRating(int, int, int, int, int, int);
char* pluralize(int, char*, char*);

int
main(int argc, char **argv)
    {
    int goals, shots, corners, assists, passes, touches;
    double rating;
    
    //get the statistics from the user
    //pass in addresses so getDat can set these variables
    getData(&goals, &shots, &corners, &assists, &passes, &touches);

    //compute the rating
    rating = computeRating(goals, shots, corners, assists, passes, touches);

    //display the statistics
    displayData(goals, shots, corners, assists, passes, touches);

    //display the results
    displayRating(rating);

    return 0;
    }

void
getData(int *goals, int *shots, int *corners, int *assists, int *passes, int *touches)
    {
    printf("Enter number of goals: ");
    scanf(" %d", goals);

    printf("Enter number of shots: ");
    scanf(" %d", shots);

    printf("Enter number of effective corner kicks: ");
    scanf(" %d", corners);

    printf("Enter number of primary assists: ");
    scanf(" %d", assists);

    printf("Enter number of effective passes: ");
    scanf(" %d", passes);

    printf("Enter number of touches: ");
    scanf(" %d", touches);

    return;
    }

double
computeRating(int goals, int shots, int corners, int assists, int passes, int touches)
    {
    int numerator = (5 * goals) + (4 * shots) + (3 * corners) + (2 * assists) + passes;
    return numerator / (double) touches;
    }

char*
pluralize(int count, char* singleForm, char* pluralForm)
    {
        return (count == 1) ? singleForm : pluralForm;
    }

void
displayData(int goals, int shots, int corners, int assists, int passes, int touches)
    {
    printf("\n");
    printf("%d %s\n", goals, pluralize(goals, "goal", "goals"));
    printf("%d %s\n", shots, pluralize(shots, "shot", "shots"));
    printf("%d %s\n", corners, pluralize(corners, "corner", "corners"));
    printf("%d %s\n", assists, pluralize(assists, "assist", "assists"));
    printf("%d %s\n", passes, pluralize(passes, "pass", "passes"));
    printf("%d %s\n", touches, pluralize(touches, "touch", "touches"));
    return;
    }

void displayRating(double rating)
    {
    printf("\nFor these statistics, the offensive production ratiing is %+.3f\n", rating);
    }
