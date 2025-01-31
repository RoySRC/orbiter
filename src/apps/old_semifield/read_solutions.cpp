/*
 * read_solutions.cpp
 *
 *  Created on: Oct 26, 2024
 *      Author: betten
 */




// read_solutions.cpp
//
// Anton Betten
// March 4, 2018
//
//
//

#include "orbiter.h"

using namespace std;


using namespace orbiter;
using namespace orbiter::top_level;


#define MY_BUFSIZE ONE_MILLION

int main(int argc, const char **argv)
{
	int i, j;
	int verbose_level = 0;
	int f_file_mask_data = FALSE;
	const char *file_mask_data = NULL;
	int f_file_mask_success = FALSE;
	const char *file_mask_success = NULL;
	int f_N = FALSE;
	int N = 0;
	int f_nb_cases = FALSE;
	int nb_cases = 0;
	int f_data_set_size = FALSE;
	int data_set_size = 0;
	int f_data_offset = FALSE;
	int data_offset = 0;
	int f_save = FALSE;
	const char *save_prefix = NULL;
	int f_order = FALSE;
	int order = 0;
	int f_dim_over_kernel;
	int dim_over_kernel = 0;
	int f_poly = FALSE;
	const char *poly = NULL;

	cout << argv[0] << endl;
	for (i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-v") == 0) {
			verbose_level = atoi(argv[++i]);
			cout << "-v " << verbose_level << endl;
			}
		else if (strcmp(argv[i], "-poly") == 0) {
			f_poly = TRUE;
			poly = argv[++i];
			cout << "-poly " << poly << endl;
			}
		else if (strcmp(argv[i], "-order") == 0) {
			f_order = TRUE;
			order = atoi(argv[++i]);
			cout << "-order " << order << endl;
			}
		else if (strcmp(argv[i], "-dim_over_kernel") == 0) {
			f_dim_over_kernel = TRUE;
			dim_over_kernel = atoi(argv[++i]);
			cout << "-dim_over_kernel " << dim_over_kernel << endl;
			}
		else if (strcmp(argv[i], "-file_mask_data") == 0) {
			f_file_mask_data = TRUE;
			file_mask_data = argv[++i];
			cout << "-file_mask_data " << file_mask_data << endl;
			}
		else if (strcmp(argv[i], "-file_mask_success") == 0) {
			f_file_mask_success = TRUE;
			file_mask_success = argv[++i];
			cout << "-file_mask_success " << file_mask_success << endl;
			}
		else if (strcmp(argv[i], "-N") == 0) {
			f_N = TRUE;
			N = atoi(argv[++i]);
			cout << "-N " << N << endl;
			}
		else if (strcmp(argv[i], "-nb_cases") == 0) {
			f_nb_cases = TRUE;
			nb_cases = atoi(argv[++i]);
			cout << "-nb_cases " << nb_cases << endl;
			}
		else if (strcmp(argv[i], "-data_set_size") == 0) {
			f_data_set_size = TRUE;
			data_set_size = atoi(argv[++i]);
			cout << "-data_set_size " << data_set_size << endl;
			}
		else if (strcmp(argv[i], "-data_offset") == 0) {
			f_data_offset = TRUE;
			data_offset = atoi(argv[++i]);
			cout << "-data_offset " << data_offset << endl;
			}
		else if (strcmp(argv[i], "-save") == 0) {
			f_save = TRUE;
			save_prefix = argv[++i];
			cout << "-save " << save_prefix << endl;
			}
		}
	if (!f_file_mask_data) {
		cout << "please use -file_mask_data <file_mask>" << endl;
		exit(1);
		}
	if (!f_file_mask_success) {
		cout << "please use -file_mask_success <file_mask>" << endl;
		exit(1);
		}
	if (!f_N) {
		cout << "please use -N <N>" << endl;
		exit(1);
		}
	if (!f_nb_cases) {
		cout << "please use -nb_cases <nb_cases>" << endl;
		exit(1);
		}
	if (!f_data_set_size) {
		cout << "please use -data_set_size <data_set_size>" << endl;
		exit(1);
		}



	if (!f_order) {
		cout << "please use option -order <order>" << endl;
		exit(1);
		}

	int p, e, e1, n, k, q, k2;
	number_theory_domain NT;

	NT.factor_prime_power(order, p, e);
	cout << "order = " << order << " = " << p << "^" << e << endl;

	if (f_dim_over_kernel) {
		if (e % dim_over_kernel) {
			cout << "dim_over_kernel does not divide e" << endl;
			exit(1);
			}
		e1 = e / dim_over_kernel;
		n = 2 * dim_over_kernel;
		k = dim_over_kernel;
		q = NT.i_power_j(p, e1);
		cout << "order=" << order << " n=" << n
			<< " k=" << k << " q=" << q << endl;
		}
	else {
		n = 2 * e;
		k = e;
		q = p;
		cout << "order=" << order << " n=" << n
			<< " k=" << k << " q=" << q << endl;
		}
	k2 = k * k;


	{
	finite_field *F;
	semifield_classify *SC;

	F = NEW_OBJECT(finite_field);
	F->init_override_polynomial(q, poly, 0 /* verbose_level */);

	SC = NEW_OBJECT(semifield_classify);
	cout << "before SC->init" << endl;
	SC->init(argc, argv, order, n, k, F,
			4 /* MINIMUM(verbose_level - 1, 2) */);
	cout << "after SC->init" << endl;






	int nb_missing = 0;
	int *Missing = NULL;
	int nb_existing = 0;
	int *Existing = NULL;
	char fname[1000];
	int nb_false = 0;
	file_io Fio;


	Missing = NEW_int(N);
	Existing = NEW_int(N);

	for (i = 0; i < N; i++) {
		sprintf(fname, file_mask_success, i);
		if (Fio.file_size(fname) <= 0) {
			Missing[nb_missing] = i;
			nb_missing++;
			}
		else {
			Existing[nb_existing] = i;
			nb_existing++;
			}
		}

	cout << "There are " << nb_missing << " missing files" << endl;
	cout << "There are " << nb_existing << " existing files" << endl;

	int h, e, l, o, k;
	long int a;
	int *f_solution_read = NULL;
	int *solution_first = NULL;
	int *nb_solutions = NULL;
	int nb_data_sets_allocated = 0;
	int nb_data_sets_used = 0;
	long int *Data_sets = NULL;

	f_solution_read = NEW_int(nb_cases);
	nb_solutions = NEW_int(nb_cases);
	solution_first = NEW_int(nb_cases);
	int_vec_zero(nb_solutions, nb_cases);
	int_vec_zero(solution_first, nb_cases);
	for (i = 0; i < nb_cases; i++) {
		f_solution_read[i] = FALSE;
		nb_solutions[i] = 0;
		}

	nb_data_sets_allocated = 1024;
	nb_data_sets_used = 0;
	Data_sets = NEW_lint(nb_data_sets_allocated * data_set_size);


	char *p_buf;
	char buf[MY_BUFSIZE];


	for (h = 0; h < nb_existing; h++) {
		e = Existing[h];

		sprintf(fname, file_mask_data, e);

		cout << "Working on file " << h << " / " << nb_existing
				<< " which is case " << e << endl;

			{
			ifstream fp(fname);

			while (TRUE) {

				if (fp.eof()) {
					break;
					}

				{
				string S;
				getline(fp, S);
				l = S.length();
				//cout << "read line of length " << l << " : " << S << endl;
				for (j = 0; j < l; j++) {
					buf[j] = S[j];
					}
				buf[l] = 0;
				}

				if (strncmp(buf, "start orbit", 11) == 0) {
					sscanf(buf + 12, "%d", &o);
					//cout << "Reading solutions for orbit " << o << endl;

					if (o >= nb_cases) {
						cout << "o >= nb_cases" << endl;
						exit(1);
						}
					nb_solutions[o] = 0;
					solution_first[o] = nb_data_sets_used;

					while (TRUE) {

						if (fp.eof()) {
							cout << "unexpected eof" << endl;
							exit(1);
							}
						{
						string S;
						getline(fp, S);
						l = S.length();
						//cout << "read line of length " << l << " : " << S << endl;
						for (j = 0; j < l; j++) {
							buf[j] = S[j];
							}
						buf[l] = 0;
						}

						if (strncmp(buf, "finish orbit", 12) == 0) {
							//cout << "Reading solutions for orbit "
							//<< o << " completed" << endl;
							f_solution_read[o] = TRUE;
							break;
							}
						else if (strncmp(buf, "SOL", 3) == 0) {

							p_buf = buf + 3;

							if (nb_data_sets_used == nb_data_sets_allocated) {
								int alloc_new;
								long int *Data_new;

								alloc_new = 2 * nb_data_sets_allocated;
								Data_new = NEW_lint(alloc_new * data_set_size);
								lint_vec_copy(Data_sets, Data_new,
										nb_data_sets_used * data_set_size);

								FREE_lint(Data_sets);
								Data_sets = Data_new;
								nb_data_sets_allocated = alloc_new;
								}
							for (k = 0; k < data_set_size; k++) {
								s_scan_lint(&p_buf, &a);
								Data_sets[nb_data_sets_used * data_set_size + k] = a;
								}

							if (!SC->test_partial_semifield_numerical_data(
									Data_sets + nb_data_sets_used * data_set_size + data_offset,
									data_set_size - data_offset, verbose_level)) {
								cout << "the solution fails the semifield test" << endl;
								nb_false++;
								//exit(1);
							}
							else {
								nb_data_sets_used++;
								nb_solutions[o]++;
							}
							}
						} // while

					}
				else {
					cout << "unexpected input line: " << buf << endl;
					break;
					}
				} // while

			}

		}

	cout << "done reading solutions, we found " << nb_data_sets_used
			<< " solutions" << endl;
	cout << "nb_false=" << nb_false << endl;
	long int *Data_sorted;
	int *FstLen;
	int *ExistingFstLen;
	int nb_existing_cases = 0;
	int c;

	Data_sorted = NEW_lint(nb_data_sets_used * data_set_size);
	h = 0;
	for (o = 0; o < nb_cases; o++) {
		if (f_solution_read[o]) {
			lint_vec_copy(
					Data_sets + solution_first[o] * data_set_size,
					Data_sorted + h * data_set_size,
					nb_solutions[o] * data_set_size);
			solution_first[o] = h;
			h += nb_solutions[o];
			if (nb_solutions[o]) {
				nb_existing_cases++;
			}
		}
	}
	cout << "nb_existing_cases=" << nb_existing_cases << endl;
	if (h != nb_data_sets_used) {
		cout << "warning: h != nb_data_sets_used" << endl;
		}
	nb_data_sets_used = h;
	FstLen = NEW_int(nb_cases * 2);
	ExistingFstLen = NEW_int(nb_existing_cases * 3);
	c = 0;
	for (o = 0; o < nb_cases; o++) {
		FstLen[2 * o + 0] = solution_first[o];
		FstLen[2 * o + 1] = nb_solutions[o];
		if (nb_solutions[o]) {
			ExistingFstLen[3 * c + 0] = o;
			ExistingFstLen[3 * c + 1] = solution_first[o];
			ExistingFstLen[3 * c + 2] = nb_solutions[o];
			c++;
		}
	}
	cout << "There are " << nb_missing << " missing files" << endl;
	cout << "They are:";
	int_vec_print(cout, Missing, nb_missing);
	cout << endl;

	int nb_missing_cases;
	int *Missing_cases;

	nb_missing_cases = 0;
	for (o = 0; o < nb_cases; o++) {
		if (!f_solution_read[o]) {
			nb_missing_cases++;
			}
		}
	Missing_cases = NEW_int(nb_missing_cases);
	h = 0;
	for (o = 0; o < nb_cases; o++) {
		if (!f_solution_read[o]) {
			Missing_cases[h++] = o;
			}
		}
	cout << "There are " << nb_missing_cases << " missing cases" << endl;
	cout << "They are:";
	int_vec_print(cout, Missing_cases, nb_missing_cases);
	cout << endl;


	if (f_save) {
		char fname_FstLen[1000];

		sprintf(fname_FstLen, "%s_FstLen.csv", save_prefix);
		Fio.int_matrix_write_csv(fname_FstLen, FstLen, nb_cases, 2);

		cout << "Written file " << fname_FstLen << " of size "
				<< Fio.file_size(fname_FstLen) << endl;

		char fname_Data[1000];

		sprintf(fname_Data, "%s_Data.csv", save_prefix);
		Fio.lint_matrix_write_csv(fname_Data, Data_sorted,
				nb_data_sets_used, data_set_size);

		cout << "Written file " << fname_Data << " of size "
				<< Fio.file_size(fname_Data) << endl;
		char fname_existing[1000];

		sprintf(fname_existing, "%s_Existing.csv", save_prefix);
		Fio.int_matrix_write_csv(fname_existing,
				ExistingFstLen,
				nb_existing_cases, 3);

		cout << "Written file " << fname_existing << " of size "
				<< Fio.file_size(fname_existing) << endl;
		}


	cout << "before freeing SC" << endl;
	FREE_OBJECT(SC);
	cout << "before freeing F" << endl;
	FREE_OBJECT(F);
	cout << "before leaving scope" << endl;
	}
	cout << "after leaving scope" << endl;

}

