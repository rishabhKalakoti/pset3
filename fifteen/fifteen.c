/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int dimension;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    dimension = atoi(argv[1]);
    if (dimension < DIM_MIN || dimension > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < dimension; i++)
        {
            for (int j = 0; j < dimension; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < dimension - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("WoN!!!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    // TODO
    int i, j;
    int num = dimension * dimension - 1;
    for (i = 0; i < dimension; i++)
    {
        for (j = 0; j < dimension; j++)
        {
            board[i][j] = num;
            num--;
        }
    }
    if (dimension % 2 == 0)
    {
        board[dimension - 1][dimension - 3] = 1;
        board[dimension - 1][dimension - 2] = 2;
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // TODO
    int i, j;
    for (i = 0; i < dimension; i++)
    {
        for ( j = 0; j < dimension; j++)
        {
            printf("%3d", board[i][j]);
        }
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    // TODO
    int i, j;
    int x, y;
    int xNew, yNew;
    // find coords of tile
    for (i = 0; i < dimension; i++)
    {
        for (j = 0; j < dimension; j++)
        {
            if (board[i][j] == tile)
            {
                x = i;
                y = j;
            }
            if (board[i][j] == 0)
            {
                xNew = i;
                yNew = j;
            }
        }
    }
    // check move validity
    if ( !(((xNew - x == 1 || xNew - x == -1) && yNew == y) || 
    ((yNew - y == 1 || yNew - y == -1) && xNew == x)))
    {
        return false;
    }
    // swap the numbers
    board[xNew][yNew] = tile;
    board[x][y] = 0;
    
    return true;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    // TODO
    int i, j;
    int temp = board[0][0];
    for (i = 0; i < dimension; i++)
    {
        for (j = 0; j < dimension; j++)
        {
            if (temp != board[0][0])
            {
                if (temp > board[i][j] && 
                !(i == dimension - 1 && 
                j == dimension - 1))
                {
                    return false;
                }
                
            }
            temp = board[i][j];
        }
    }
    return true;
}