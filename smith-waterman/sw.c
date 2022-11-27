#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define S_LEN 512
#define N 1000

double get_time() // function to get the time of day in seconds
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec + tv.tv_usec * 1e-6;
}

int max4(int n1, int n2, int n3, int n4)
{
	int tmp1, tmp2;
	tmp1 = n1 > n2 ? n1 : n2;
	tmp2 = n3 > n4 ? n3 : n4;
	tmp1 = tmp1 > tmp2 ? tmp1 : tmp2;
	return tmp1;
}

void backtrace(char *simple_rev_cigar, char **dir_mat, int i, int j, int max_cigar_len)
{
	int n;
	for (n = 0; n < max_cigar_len && dir_mat[i][j] != 0; n++)
	{
		int dir = dir_mat[i][j];
		if (dir == 1 || dir == 2)
		{
			i--;
			j--;
		}
		else if (dir == 3)
			i--;
		else if (dir == 4)
			j--;

		simple_rev_cigar[n] = dir;
	}
}

int main(int argc, char *argv[])
{
	srand(time(NULL));

	char alphabet[5] = {'A', 'C', 'G', 'T', 'N'};

	int ins = -2, del = -2, match = 1, mismatch = -1; // penalties

	char **query = (char **)malloc(N * sizeof(char *));
	for (int i = 0; i < N; i++)
		query[i] = (char *)malloc(S_LEN * sizeof(char));

	char **reference = (char **)malloc(N * sizeof(char *));
	for (int i = 0; i < N; i++)
		reference[i] = (char *)malloc(S_LEN * sizeof(char));

	int **sc_mat = (int **)malloc((S_LEN + 1) * sizeof(int *));
	for (int i = 0; i < (S_LEN + 1); i++)
		sc_mat[i] = (int *)malloc((S_LEN + 1) * sizeof(int));
	char **dir_mat = (char **)malloc((S_LEN + 1) * sizeof(char *));
	for (int i = 0; i < (S_LEN + 1); i++)
		dir_mat[i] = (char *)malloc((S_LEN + 1) * sizeof(char));

	int *res = (int *)malloc(N * sizeof(int));
	char **simple_rev_cigar = (char **)malloc(N * sizeof(char *));
	for (int i = 0; i < N; i++)
		simple_rev_cigar[i] = (char *)malloc(S_LEN * 2 * sizeof(char));


	// randomly generate sequences
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < S_LEN; j++)
		{
			query[i][j] = alphabet[rand() % 5];
			reference[i][j] = alphabet[rand() % 5];
		}
	}

	double start_cpu = get_time();

	for (int n = 0; n < N; n++)
	{
		int max = ins; // in sw all scores of the alignment are >= 0, so this will be for sure changed
		int maxi, maxj;
		// initialize the scoring matrix and direction matrix to 0
		for (int i = 0; i < S_LEN + 1; i++)
		{
			for (int j = 0; j < S_LEN + 1; j++)
			{
				sc_mat[i][j] = 0;
				dir_mat[i][j] = 0;
			}
		}
		// compute the alignment
		for (int i = 1; i < S_LEN; i++)
		{
			for (int j = 1; j < S_LEN; j++)
			{
				// compare the sequences characters
				int comparison = (query[n][i - 1] == reference[n][j - 1]) ? match : mismatch;
				// compute the cell knowing the comparison result
				int tmp = max4(sc_mat[i - 1][j - 1] + comparison, sc_mat[i - 1][j] + del, sc_mat[i][j - 1] + ins, 0);
				char dir;

				if (tmp == (sc_mat[i - 1][j - 1] + comparison))
					dir = comparison == match ? 1 : 2;
				else if (tmp == (sc_mat[i - 1][j] + del))
					dir = 3;
				else if (tmp == (sc_mat[i][j - 1] + ins))
					dir = 4;
				else
					dir = 0;

				dir_mat[i][j] = dir;
				sc_mat[i][j] = tmp;

				if (tmp > max)
				{
					max = tmp;
					maxi = i;
					maxj = j;
				}
			}
		}
		res[n] = sc_mat[maxi][maxj];
		backtrace(simple_rev_cigar[n], dir_mat, maxi, maxj, S_LEN * 2);
	}

	double end_cpu = get_time();

	printf("SW Time CPU: %.10lf\n", end_cpu - start_cpu);

	return 0;
}