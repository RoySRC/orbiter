// combinatorics.h
//
// Anton Betten
//
// moved here from galois.h: July 27, 2018
// started as orbiter:  October 23, 2002
// 2nd version started:  December 7, 2003
// galois started:  August 12, 2005



#ifndef ORBITER_SRC_LIB_FOUNDATIONS_COMBINATORICS_COMBINATORICS_H_
#define ORBITER_SRC_LIB_FOUNDATIONS_COMBINATORICS_COMBINATORICS_H_



namespace orbiter {
namespace layer1_foundations {
namespace combinatorics {


// #############################################################################
// apn_functions.cpp
// #############################################################################

//! boolean functions

class apn_functions {

public:

	field_theory::finite_field *F;

	apn_functions();
	~apn_functions();
	void init(
			field_theory::finite_field *F,
			int verbose_level);
	void search_APN(
			int delta_max, int verbose_level);
	void search_APN_recursion(
			int *f, int depth, int f_normalize,
			int &delta_max, int &nb_times,
			std::vector<std::vector<int> > &Solutions,
			int *A_matrix, int *B_matrix,
			int *Count_ab, int *nb_times_ab,
			int verbose_level);
	int search_APN_perform_checks(
			int *f, int depth,
			int delta_max,
			int *A_matrix, int *B_matrix, int *Count_ab,
			int verbose_level);
	void search_APN_undo_checks(
			int *f, int depth,
			int delta_max,
			int *A_matrix, int *B_matrix, int *Count_ab,
			int verbose_level);
	int perform_single_check(
			int *f, int depth, int i, int delta_max,
			int *A_matrix, int *B_matrix, int *Count_ab,
			int verbose_level);
	void undo_single_check(
			int *f, int depth, int i, int delta_max,
			int *A_matrix, int *B_matrix, int *Count_ab,
			int verbose_level);
	void search_APN_old(
			int verbose_level);
	void search_APN_recursion_old(
			int *f, int depth, int f_normalize,
			int &delta_min, int &nb_times,
			std::vector<std::vector<int> > &Solutions,
			int *nb_times_ab,
			int verbose_level);
	int differential_uniformity(
			int *f, int *nb_times_ab, int verbose_level);
	int differential_uniformity_with_fibre(
			int *f, int *nb_times_ab, int *&Fibre,
			int verbose_level);

};



// #############################################################################
// boolean_function_domain.cpp
// #############################################################################

//! boolean functions

class boolean_function_domain {

public:
	int n;
	int n2; // n / 2
	int Q; // 2^n
	int bent; // 2^{n/2}
	int near_bent; // 2^{(n+1)/2}
	//int NN;
	ring_theory::longinteger_object *NN; // 2^Q
	int N; // size of PG(n,2)

	field_theory::finite_field *Fq; // the field F2
	//finite_field *FQ; // the field of order 2^n

	ring_theory::homogeneous_polynomial_domain *Poly;
		// Poly[i] = polynomial of degree i in n + 1 variables.
		// i = 1,..,n
	int **A_poly; // [1..n][Poly[i].get_nb_monomials()]
	int **B_poly; // [1..n][Poly[i].get_nb_monomials()]
	int *Kernel;
	int dim_kernel;


	long int *affine_points; // [Q]
		// affine_points[i] = PG_rank of affine point[i]



	int *v; // [n]
	int *v1; // [n + 1]
	int *w; // [n]
	int *f; // [Q]
	int *f2; // [Q]
	int *F; // [Q]
	int *T; // [Q]
	int *W; // [Q * Q] = Walsh matrix
	int *f_proj;
	int *f_proj2;



	boolean_function_domain();
	~boolean_function_domain();
	void init(
			field_theory::finite_field *F2, int n,
			int verbose_level);
	void setup_polynomial_rings(
			int verbose_level);
	void compute_polynomial_representation(
			int *func, int *coeff, int verbose_level);
	void evaluate_projectively(
			int *coeff, int *f);
	void evaluate(
			int *coeff, int *f);
	void raise(
			int *in, int *out);
	void apply_Walsh_transform(
			int *in, int *out);
	int is_bent(
			int *T);
	int is_near_bent(
			int *T);
};




// #############################################################################
// brick_domain.cpp
// #############################################################################

//! a problem of Neil Sloane

class brick_domain {

public:
	field_theory::finite_field *F;
	int q;
	int nb_bricks;

	brick_domain();
	~brick_domain();
	void init(
			field_theory::finite_field *F, int verbose_level);
	void unrank(
			int rk, int &f_vertical,
		int &x0, int &y0, int verbose_level);
	int rank(
			int f_vertical, int x0, int y0, int verbose_level);
	void unrank_coordinates(
			int rk,
		int &x1, int &y1, int &x2, int &y2, 
		int verbose_level);
	int rank_coordinates(
			int x1, int y1, int x2, int y2,
		int verbose_level);
};








// #############################################################################
// combinatorics_domain.cpp
// #############################################################################

//! a collection of combinatorial functions

class combinatorics_domain {

public:

	permutations *Permutations;


	combinatorics_domain();
	~combinatorics_domain();
	int int_factorial(
			int a);
	int Kung_mue_i(
			int *part, int i, int m);
	void partition_dual(
			int *part, int *dual_part, int n,
			int verbose_level);
	void make_all_partitions_of_n(
			int n, int *&Table, int &nb, int verbose_level);
	int count_all_partitions_of_n(
			int n);
	int partition_first(
			int *v, int n);
	int partition_next(
			int *v, int n);
	void partition_print(
			std::ostream &ost, int *v, int n);
	int int_vec_is_regular_word(
			int *v, int len, int q);
		// Returns true if the word v of length len is regular, i.~e.
		// lies in an orbit of length $len$ under the action of the cyclic group
		// $C_{len}$ acting on the coordinates.
		// Lueneburg~\cite{Lueneburg87a} p. 118.
		// v is a vector over $\{0, 1, \ldots , q-1\}$
	int int_vec_first_regular_word(
			int *v, int len, int q);
	int int_vec_next_regular_word(
			int *v, int len, int q);
	void int_vec_splice(
			int *v, int *w, int len, int p);
	int is_subset_of(
			int *A, int sz_A, int *B, int sz_B);
	int set_find(
			int *elts, int size, int a);
	void set_complement(
			int *subset, int subset_size, int *complement,
		int &size_complement, int universal_set_size);
	void set_complement_lint(
			long int *subset, int subset_size, long int *complement,
		int &size_complement, int universal_set_size);
	void set_complement_safe(
			int *subset, int subset_size, int *complement,
		int &size_complement, int universal_set_size);
	// subset does not need to be in increasing order
	void set_add_elements(
			int *elts, int &size,
		int *elts_to_add, int nb_elts_to_add);
	void set_add_element(
			int *elts, int &size, int a);
	void set_delete_elements(
			int *elts, int &size,
		int *elts_to_delete, int nb_elts_to_delete);
	void set_delete_element(
			int *elts, int &size, int a);
	int compare_lexicographically(
			int a_len, long int *a, int b_len, long int *b);
	long int int_n_choose_k(
			int n, int k);
	void make_t_k_incidence_matrix(
			int v, int t, int k, int &m, int &n, int *&M,
		int verbose_level);
	void print_k_subsets_by_rank(
			std::ostream &ost, int v, int k);
	int f_is_subset_of(
			int v, int t, int k,
			int rk_t_subset, int rk_k_subset);
	int rank_subset(
			int *set, int sz, int n);
	void rank_subset_recursion(
			int *set, int sz, int n, int a0, int &r);
	void unrank_subset(
			int *set, int &sz, int n, int r);
	void unrank_subset_recursion(
			int *set, int &sz, int n, int a0, int &r);
	int rank_k_subset(
			int *set, int n, int k);
	void unrank_k_subset(
			int rk, int *set, int n, int k);
	void unrank_k_subset_and_complement(
			int rk, int *set, int n, int k);
	int first_k_subset(
			int *set, int n, int k);
	int next_k_subset(
			int *set, int n, int k);
	int next_k_subset_at_level(
			int *set, int n, int k, int backtrack_level);
	void rank_k_subsets(
			int *Mtx, int nb_rows, int n, int k, int *&Ranks,
			int verbose_level);
	void rank_k_subsets_and_sort(
			int *Mtx, int nb_rows, int n, int k, int *&Ranks,
			int verbose_level);
	void subset_permute_up_front(
			int n, int k, int *set, int *k_subset_idx,
		int *permuted_set);
	int ordered_pair_rank(
			int i, int j, int n);
	void ordered_pair_unrank(
			int rk, int &i, int &j, int n);
	void set_partition_4_into_2_unrank(
			int rk, int *v);
	int set_partition_4_into_2_rank(
			int *v);
	int unordered_triple_pair_rank(
			int i, int j, int k, int l, int m, int n);
	void unordered_triple_pair_unrank(
			int rk, int &i, int &j, int &k,
		int &l, int &m, int &n);
	long int ij2k_lint(
			long int i, long int j, long int n);
	void k2ij_lint(
			long int k, long int & i, long int & j, long int n);
	int ij2k(
			int i, int j, int n);
	void k2ij(
			int k, int & i, int & j, int n);
	int ijk2h(
			int i, int j, int k, int n);
	void h2ijk(
			int h, int &i, int &j, int &k, int n);
	int disjoint_binary_representation(
			int u, int v);
	int hall_test(
			int *A, int n, int kmax, int *memo, int verbose_level);
	int philip_hall_test(
			int *A, int n, int k, int *memo, int verbose_level);
	int philip_hall_test_dual(
			int *A, int n, int k, int *memo, int verbose_level);
	void print_01_matrix_with_stars(
			std::ostream &ost, int *A, int m, int n);
	void print_int_matrix(
			std::ostream &ost, int *A, int m, int n);
	int create_roots_H4(
			field_theory::finite_field *F, int *roots);
	long int generalized_binomial(
			int n, int k, int q);
	void print_tableau(
			int *Tableau, int l1, int l2,
		int *row_parts, int *col_parts);
	int ijk_rank(
			int i, int j, int k, int n);
	void ijk_unrank(
			int &i, int &j, int &k, int n, int rk);
	long int largest_binomial2_below(
			int a2);
	long int largest_binomial3_below(
			int a3);
	long int binomial2(
			int a);
	long int binomial3(
			int a);
	int minus_one_if_positive(
			int i);
	void make_partitions(
			int n, int *Part, int cnt);
	int count_partitions(
			int n);
	int next_partition(
			int n, int *part);
	long int binomial_lint(
			int n, int k);
	void binomial(
			ring_theory::longinteger_object &a,
			int n, int k, int verbose_level);
	void binomial_with_table(
			ring_theory::longinteger_object &a,
			int n, int k);
	void size_of_conjugacy_class_in_sym_n(
			ring_theory::longinteger_object &a, int n, int *part);
	void q_binomial_with_table(
			ring_theory::longinteger_object &a,
		int n, int k, int q, int verbose_level);
	void q_binomial(
			ring_theory::longinteger_object &a,
		int n, int k, int q, int verbose_level);
	void q_binomial_no_table(
			ring_theory::longinteger_object &a,
		int n, int k, int q, int verbose_level);
	void krawtchouk_with_table(
			ring_theory::longinteger_object &a,
		int n, int q, int k, int x);
	void krawtchouk(
			ring_theory::longinteger_object &a,
			int n, int q, int k, int x);
	void do_tdo_refinement(
			tdo_refinement_description *Descr, int verbose_level);
	void do_tdo_print(
			std::string &fname, int verbose_level);
	void make_elementary_symmetric_functions(
			int n, int k_max, int verbose_level);
	void Dedekind_numbers(
			int n_min, int n_max, int q_min, int q_max,
			int verbose_level);
	void convert_stack_to_tdo(
			std::string &stack_fname, int verbose_level);
	void do_parameters_maximal_arc(
			int q, int r, int verbose_level);
	void do_parameters_arc(
			int q, int s, int r, int verbose_level);
	void do_read_poset_file(
			std::string &fname,
			int f_grouping, double x_stretch, int verbose_level);
	// creates a layered graph file from a text file
	// which was created by DISCRETA/sgls2.cpp
	void do_make_tree_of_all_k_subsets(
			int n, int k, int verbose_level);
	void create_random_permutation(
			int deg,
			std::string &fname_csv, int verbose_level);
	void create_random_k_subsets(
			int n, int k, int nb,
			std::string &fname_csv, int verbose_level);
	void compute_incidence_matrix(
			int v, int b, int k, long int *Blocks_coded,
			int *&M, int verbose_level);
	void compute_incidence_matrix_from_blocks(
			int v, int b, int k, int *Blocks,
			int *&M, int verbose_level);
	void compute_incidence_matrix_from_blocks_lint(
			int v, int b, int k, long int *Blocks,
			int *&M, int verbose_level);
	void compute_incidence_matrix_from_sets(
			int v, int b, long int *Sets_coded,
			int *&M,
			int verbose_level);
	void compute_blocks_from_coding(
			int v, int b, int k, long int *Blocks_coded,
			int *&Blocks, int verbose_level);
	void compute_blocks_from_incma(
			int v, int b, int k, int *incma,
			int *&Blocks, int verbose_level);
	void refine_the_partition(
			int v, int k, int b, long int *Blocks_coded,
			int &b_reduced,
			int verbose_level);
	void compute_TDO_decomposition_of_projective_space_old(
			std::string &fname_base,
			geometry::projective_geometry::projective_space *P,
			long int *points, int nb_points,
			long int *lines, int nb_lines,
			std::vector<std::string> &file_names,
			int verbose_level);
	// called from quartic_curve_from_surface::TDO_decomposition
	combinatorics::decomposition_scheme *compute_TDO_decomposition_of_projective_space(
			geometry::projective_geometry::projective_space *P,
			long int *points, int nb_points,
			long int *lines, int nb_lines,
			int verbose_level);
	// returns NULL if the space is too large
	void create_incidence_matrix_of_graph(
			int *Adj, int n,
			int *&M, int &nb_rows, int &nb_cols,
			int verbose_level);
	void free_global_data();
	void free_tab_q_binomials();
	void create_wreath_product_design(
			int n, int k,
			long int *&Blocks, long int &nb_blocks,
			int verbose_level);
	void create_linear_space_from_latin_square(
			int *Mtx, int s,
			int &v, int &k,
			long int *&Blocks, long int &nb_blocks,
			int verbose_level);
	void report_large_set(
			std::ostream &ost, long int *coding, int nb_designs,
			int design_v, int design_k, int design_sz, int verbose_level);
	void report_large_set_compact(
			std::ostream &ost, long int *coding, int nb_designs,
			int design_v, int design_k, int design_sz, int verbose_level);

};





// #############################################################################
// decomposition_scheme.cpp
// #############################################################################


//! a decomposition scheme of an incidence structure


class decomposition_scheme {

public:

	decomposition *Decomposition;

	row_and_col_partition *RC;

	int f_has_row_scheme;
	int *row_scheme;
	int f_has_col_scheme;
	int *col_scheme;

	data_structures::set_of_sets *SoS_points;
	data_structures::set_of_sets *SoS_lines;

	decomposition_scheme();
	~decomposition_scheme();
	void init_row_and_col_schemes(
			decomposition *Decomposition,
			int verbose_level);
	// called from combinatorics_domain::compute_TDO_decomposition_of_projective_space
	void get_classes(
			int verbose_level);
	void init_row_scheme(
			decomposition *Decomposition,
			int verbose_level);
	void init_col_scheme(
			decomposition *Decomposition,
			int verbose_level);
	void get_row_scheme(
			int verbose_level);
	void get_col_scheme(
			int verbose_level);
	void print_row_decomposition_tex(
		std::ostream &ost,
		int f_enter_math, int f_print_subscripts,
		int verbose_level);
	void print_column_decomposition_tex(
		std::ostream &ost,
		int f_enter_math, int f_print_subscripts,
		int verbose_level);
	void print_decomposition_scheme_tex(
			std::ostream &ost,
		int *scheme);
	void print_tactical_decomposition_scheme_tex(
			std::ostream &ost,
		int f_print_subscripts);
	void print_tactical_decomposition_scheme_tex_internal(
		std::ostream &ost, int f_enter_math_mode,
		int f_print_subscripts);
	void print_row_tactical_decomposition_scheme_tex(
		std::ostream &ost, int f_enter_math_mode,
		int f_print_subscripts);
	void print_column_tactical_decomposition_scheme_tex(
		std::ostream &ost, int f_enter_math_mode,
		int f_print_subscripts);
	void print_non_tactical_decomposition_scheme_tex(
		std::ostream &ost, int f_enter_math_mode,
		int f_print_subscripts);
	void stringify_row_scheme(
			std::string *&Table, int f_print_subscripts);
		// Table[(nb_row_classes + 1) * (nb_col_classes + 1)]
	void stringify_col_scheme(
			std::string *&Table, int f_print_subscripts);
		// Table[(nb_row_classes + 1) * (nb_col_classes + 1)]
	void write_csv(
			std::string &fname_row, std::string &fname_col,
			std::string &fname_row_classes, std::string &fname_col_classes,
			int verbose_level);
	void report_latex_with_external_files(
			std::ostream &ost,
			std::string &label_scheme,
			std::string &label_txt,
			int upper_bound_on_size_for_printing,
			int verbose_level);
	void report_classes_with_external_files(
			std::ostream &ost,
			std::string &label_scheme,
			std::string &label_txt,
			int verbose_level);
	void export_csv(
			std::string &label_scheme,
			std::string &label_txt,
			int verbose_level);

};


// #############################################################################
// decomposition.cpp
// #############################################################################


//! decomposition of an incidence matrix


class decomposition {

public:

	int nb_points;
	int nb_blocks;
	int N;
	int *Incma;

	geometry::other_geometry::incidence_structure *Inc;
	data_structures::partitionstack *Stack;

	int f_has_decomposition;
	decomposition_scheme *Scheme;


	decomposition();
	~decomposition();
	void init_incidence_structure(
			geometry::other_geometry::incidence_structure *Inc,
			int verbose_level);
	// called from
	// decomposition::init_decomposition_of_projective_space
	// combinatorics_domain::refine_the_partition
	// combinatorics_domain::compute_TDO_decomposition_of_projective_space_old
	// set_of_sets::get_eckardt_points
	// combinatorics_with_action::report_TDO_and_TDA
	// combinatorics_with_action::report_TDA
	// group_action_on_combinatorial_object::init
	// design_activity::do_tactical_decomposition
	void init_inc_and_stack(
			geometry::other_geometry::incidence_structure *Inc,
			data_structures::partitionstack *Stack,
		int verbose_level);
	void init_decomposition_of_projective_space(
			geometry::projective_geometry::projective_space *P,
			long int *points, int nb_points,
			long int *lines, int nb_lines,
			int verbose_level);
	void init_incidence_matrix(
			int m, int n, int *M,
		int verbose_level);
		// copies the incidence matrix
	void compute_TDO_deep(
			int verbose_level);
	void compute_the_decomposition(
			int verbose_level);
	void setup_default_partition(
			int verbose_level);
	void compute_TDO_old(
			int max_depth, int verbose_level);
	void get_row_scheme(
			int verbose_level);
	void get_col_scheme(
			int verbose_level);
	void compute_TDO_safe(
		int depth, int verbose_level);
	void compute_TDO_safe_and_write_files(
		int depth,
		std::string &fname_base,
		std::vector<std::string> &file_names,
		int verbose_level);
	int refine_column_partition_safe(
			int verbose_level);
	int refine_row_partition_safe(
			int verbose_level);
	void get_and_print_row_decomposition_scheme(
		int f_list_incidences,
		int f_local_coordinates, int verbose_level);
	void get_and_print_col_decomposition_scheme(
		int f_list_incidences,
		int f_local_coordinates, int verbose_level);
	void get_permuted_incidence_matrix(
			row_and_col_partition *RC,
		int *&incma, int verbose_level);
	void latex(
			std::ostream &ost,
			graphics::draw_incidence_structure_description *Draw_options,
			row_and_col_partition *RC,
			int verbose_level);
	void get_row_decomposition_scheme(
			row_and_col_partition *RC,
		int *row_scheme, int verbose_level);
	void get_row_decomposition_scheme_if_possible(
			row_and_col_partition *RC,
		int *row_scheme, int verbose_level);
	void get_col_decomposition_scheme(
			row_and_col_partition *RC,
		int *col_scheme, int verbose_level);
	void row_scheme_to_col_scheme(
			row_and_col_partition *RC,
		int *row_scheme, int *col_scheme,
		int verbose_level);
	void print_row_tactical_decomposition_scheme_incidences_tex(
		std::ostream &ost, int f_enter_math_mode,
		row_and_col_partition *RC,
		int f_local_coordinates, int verbose_level);
	void print_col_tactical_decomposition_scheme_incidences_tex(
		std::ostream &ost, int f_enter_math_mode,
		row_and_col_partition *RC,
		int f_local_coordinates, int verbose_level);
	void get_incidences_by_row_scheme(
			row_and_col_partition *RC,
		int row_class_idx, int col_class_idx,
		int rij, int *&incidences, int verbose_level);
	void get_incidences_by_col_scheme(
			row_and_col_partition *RC,
		int row_class_idx, int col_class_idx,
		int kij, int *&incidences, int verbose_level);
	void get_and_print_decomposition_schemes();
	void get_and_print_row_tactical_decomposition_scheme_tex(
		std::ostream &ost,
		int f_enter_math, int f_print_subscripts);
	void get_and_print_column_tactical_decomposition_scheme_tex(
		std::ostream &ost,
		int f_enter_math, int f_print_subscripts);
	void print_partitioned(
		std::ostream &ost,
		int f_labeled);
	void print_column_labels(
		std::ostream &ost,
		int *col_classes, int nb_col_classes, int width);
	void print_hline(
		std::ostream &ost,
		row_and_col_partition *RC,
		int width, int f_labeled);
	void print_line(
		std::ostream &ost,
		row_and_col_partition *RC,
		int row_cell, int i,
		int width, int f_labeled);
	void stringify_decomposition(
			row_and_col_partition *RC,
			std::string *&T,
			int *the_scheme,
			int f_print_subscripts);
	void prepare_col_labels(
			row_and_col_partition *RC,
			std::vector<std::string> &col_labels, int f_print_subscripts);
	void prepare_row_labels(
			row_and_col_partition *RC,
			std::vector<std::string> &row_labels, int f_print_subscripts);
	void prepare_matrix(
			row_and_col_partition *RC,
			std::vector<std::string> &matrix_labels,
			int *the_scheme);
	void print_row_tactical_decomposition_scheme_tex(
		std::ostream &ost, int f_enter_math_mode,
		row_and_col_partition *RC,
		int *row_scheme, int f_print_subscripts);
	void print_column_tactical_decomposition_scheme_tex(
		std::ostream &ost, int f_enter_math_mode,
		row_and_col_partition *RC,
		int *col_scheme, int f_print_subscripts);
	void compute_TDO(
			int verbose_level);
	void get_and_report_classes(
			std::ostream &ost,
			int verbose_level);
	void print_schemes(
			std::ostream &ost,
			graphics::draw_incidence_structure_description *Draw_options,
			canonical_form_classification::objects_report_options
				*Report_options,
			int verbose_level);

};




// #############################################################################
// domino_assignment.cpp:
// #############################################################################

// the dimensions are (<D>+1) * <s>   x <D>*<s>
// so, for D=7 we would get
// s=4:   32x28
// s=5:   40x35

//! compute a domino portrait using an optimization algorithm

class domino_assignment {
public:
	int D;
	int s;
	int size_dom;
	int tot_dom;

	int M; // number of rows  = (D + 1) * s
	int N; // number of columns = D * s

	int *ij_posi; // [M * N * 2];
		// ij_posi[(i * N + j) * 2 + 0] = i
		// ij_posi[(i * N + j) * 2 + 1] = j

	int *assi; // [tot_dom * 5];
		// 0: m
		// 1: n
		// 2: o = orientation
		// 3: i
		// 4: j
		// where (i,j) is the place of the top or left half of the domino

	int *broken_dom; // [M * N]
		// broken_dom[i * n + j] is the index in the assi array
		// of the domino piece covering the place (i,j)
	int *matching; // [M * N]
		// matching[i * N + j] tells the direction
		// of the second half of the domino
	int *A; // [M * N], the domino matrix
	int *mphoto; // [M * N], the photo matrix

	int *North; // [M * N]
	int *South; // [M * N]
	int *West; // [M * N]
	int *East; // [M * N]

	int brake_cnt;
	int *brake; // [tot_dom], used as [brake_cnt]

	int nb_changes;

	std::vector<domino_change> Changes;


	domino_assignment();
	~domino_assignment();
	void stage0(
			int verbose_level);
	void stage1(
			int verbose_level);
	void stage2(
			int verbose_level);
	void initialize_assignment(
			int D, int s, int verbose_level);
	void init_matching(
			int verbose_level);
	int cost_function();
	int compute_cost_of_one_piece(
			int idx);
	int compute_cost_of_one_piece_directly(
			int m, int n, int o, int i, int j);
	int my_distance(
			int a, int b);
	void compute_domino_matrix(
			int depth);
	void move(
			domino_assignment *To);
	void draw_domino_matrix(
			std::string &fname,
			int depth,
			int f_has_cost, int cost,
			graphics::layered_graph_draw_options *Draw_options,
			int verbose_level);
	void draw_domino_matrix2(
			std::string &fname,
			int f_has_cost, int cost,
		int f_frame, int f_grid, int f_B, int *B,
		int f_numbers, int f_gray,
		graphics::layered_graph_draw_options *Draw_options,
		int verbose_level);
	void read_photo(
			std::string &photo_fname, int verbose_level);
	void scale_photo(
			double *dphoto, int verbose_level);
	void do_flip_recorded(
			int f2, int verbose_level);
	void do_flip(
			int f2, int verbose_level);
	void flip_each(
			int verbose_level);
	void flip_randomized(
			int verbose_level);
	void do_swap_recorded(
			int s1, int s2, int verbose_level);
	void do_swap(
			int s1, int s2, int verbose_level);
	int do_flipswap(
			int f2);
	void swap_randomized(
			int verbose_level);
	void swap_each(
			int verbose_level);
	void do_horizontal_rotate(
			int ro, int verbose_level);
	void do_vertical_rotate(
			int ro, int verbose_level);
	int modify_matching(
			int idx_first_broken,
			int ass_m, int ass_n,
			int ass_o, int ass_i, int ass_j,
			int verbose_level);
	void follow_the_matching(
			int l, int *used, int *reached,
			int *list, int *length, int *prec,
			int verbose_level);
	int find_match(
			int l,
		int *reached1, int *list1, int *length1, int *prec1,
		int *reached2, int *list2, int *length2, int *prec2,
		int verbose_level);
	int breadth_search(
			int l, int *used, int *reached,
			int *list, int *length, int *prec,
			int verbose_level);
	void rotate_once(
			int ro, int verbose_level);
	void rotate_randomized(
			int verbose_level);
	void do_horizontal_shift(
			int ro, int verbose_level);
	void do_vertical_shift(
			int ro, int verbose_level);
	void shift_once(
			int ro, int verbose_level);
	void shift_once_randomized(
			int verbose_level);
	void shift_randomized(
			int verbose_level);
	void flip_after_shift(
			int verbose_level);
	void print_matching(
			std::ostream &ost);
	void print(
			std::ostream &ost);
	void prepare_latex(
			std::string &photo_label, int verbose_level);
	void record_flip(
			int idx, int verbose_level);
	void record_swap(
			int s1, int s2, int verbose_level);
	void record_matching(
			int verbose_level);
	void drop_changes_to(
			int nb_changes_to_drop_to, int verbose_level);
	void classify_changes_by_type(
			int verbose_level);
	void get_cost_function(
			int *&Cost, int &len, int verbose_level);
};

// #############################################################################
// domino_change.cpp:
// #############################################################################


//! utility class for the domino portrait algorithm

class domino_change {
public:
	int type_of_change;
	int cost_after_change;

	domino_change();
	~domino_change();
	void init(
			domino_assignment *DA,
			int type_of_change, int verbose_level);
};







// #############################################################################
// geo_parameter.cpp
// #############################################################################


#define MODE_UNDEFINED 0
#define MODE_SINGLE 1
#define MODE_STACK 2

#define UNKNOWNTYPE 0
#define POINTTACTICAL 1
#define BLOCKTACTICAL 2
#define POINTANDBLOCKTACTICAL 3

#define FUSE_TYPE_NONE 0
#define FUSE_TYPE_SIMPLE 1
#define FUSE_TYPE_DOUBLE 2
//#define FUSE_TYPE_MULTI 3
//#define FUSE_TYPE_TDO 4

//! decomposition stack of a linear space or incidence geometry



class geo_parameter {
public:
	int decomposition_type;
	int fuse_type;
	int v, b;

	int mode;
	std::string label;

	// for MODE_SINGLE
	int nb_V, nb_B;
	int *V, *B;
	int *scheme;
	int *fuse;

	// for MODE_STACK
	int nb_parts, nb_entries;

	int *part;
	int *entries;
	int part_nb_alloc;
	int entries_nb_alloc;


	int lambda_level;
	int row_level, col_level;
	int extra_row_level, extra_col_level;

	geo_parameter();
	~geo_parameter();
	void append_to_part(
			int a);
	void append_to_entries(
			int a1, int a2, int a3, int a4);
	void write(
			std::ofstream &aStream, std::string &label);
	void write_mode_single(
			std::ofstream &aStream,
			std::string &label);
	void write_mode_stack(
			std::ofstream &aStream,
			std::string &label);
	void convert_single_to_stack(
			int verbose_level);
	int partition_number_row(
			int row_idx);
	int partition_number_col(
			int col_idx);
	int input(
			std::ifstream &aStream);
	int input_mode_single(
			std::ifstream &aStream);
	int input_mode_stack(
			std::ifstream &aStream, int verbose_level);
	void init_tdo_scheme(
			tdo_scheme_synthetic &G, int verbose_level);
	void print_schemes(
			tdo_scheme_synthetic &G);
	void print_schemes_tex(
			tdo_scheme_synthetic &G);
	void print_scheme_tex(
			std::ostream &ost,
			tdo_scheme_synthetic &G, int h);
	void print_C_source();
	void convert_single_to_stack_fuse_simple_pt(
			int verbose_level);
	void convert_single_to_stack_fuse_simple_bt(
			int verbose_level);
	void convert_single_to_stack_fuse_double_pt(
			int verbose_level);
	void cut_off_two_lines(
			geo_parameter &GP2,
		int *&part_relabel, int *&part_length,
		int verbose_level);
	void cut_off(
			geo_parameter &GP2, int w,
		int *&part_relabel, int *&part_length,
		int verbose_level);
	void copy(
			geo_parameter &GP2);
	void print_schemes();
	int tdo_scheme_get_row_class_length_fused(
			tdo_scheme_synthetic &G,
			int h, int class_first, int class_len);
	int tdo_scheme_get_col_class_length_fused(
			tdo_scheme_synthetic &G,
			int h, int class_first, int class_len);
};



// #############################################################################
// pentomino_puzzle.cpp
// #############################################################################


#define NB_PIECES 18



//! generate all solutions of the pentomino puzzle


class pentomino_puzzle {

	public:
	int *S[NB_PIECES];
	int S_length[NB_PIECES];
	int *O[NB_PIECES];
	int O_length[NB_PIECES];
	int *T[NB_PIECES];
	int T_length[NB_PIECES];
	int *R[NB_PIECES];
	int R_length[NB_PIECES];
	int Rotate[4 * 25];
	int Rotate6[4 * 36];
	int var_start[NB_PIECES + 1];
	int var_length[NB_PIECES + 1];


	void main(
			int verbose_level);
	int has_interlocking_Ps(
			long int *set);
	int has_interlocking_Pprime(
			long int *set);
	int has_interlocking_Ls(
			long int *set);
	int test_if_interlocking_Ps(
			int a1, int a2);
	int has_interlocking_Lprime(
			long int *set);
	int test_if_interlocking_Ls(
			int a1, int a2);
	int number_of_pieces_of_type(
			int t, long int *set);
	int does_it_contain_an_I(
			long int *set);
	void decode_assembly(
			long int *set);
	// input set[5]
	void decode_piece(
			int j, int &h, int &r, int &t);
	// h is the kind of piece
	// r is the rotation index
	// t is the translation index
	// to get the actual rotation and translation, use
	// R[h][r] and T[h][t].
	int code_piece(
			int h, int r, int t);
	void draw_it(
			std::ostream &ost, long int *sol);
	void compute_image_function(
			data_structures::set_of_sets *S,
			int elt_idx,
			int gen_idx, int &idx_of_image, int verbose_level);
	void turn_piece(
			int &h, int &r, int &t, int verbose_level);
	void flip_piece(
			int &h, int &r, int &t, int verbose_level);
	void setup_pieces();
	void setup_rotate();
	void setup_var_start();
	void make_coefficient_matrix(
			solvers::diophant *D);

};


// #############################################################################
// permutations.cpp
// #############################################################################


//! permutations given in vector form


class permutations {

public:

	permutations();
	~permutations();
	void random_permutation(
			int *random_permutation, long int n);
	void perm_move(
			int *from, int *to, long int n);
	void perm_identity(
			int *a, long int n);
	int perm_is_identity(
			int *a, long int n);
	void perm_elementary_transposition(
			int *a, long int n, int f);
	void perm_cycle(
			int *perm, long int n);
	void perm_mult(
			int *a, int *b, int *c, long int n);
	void perm_conjugate(
			int *a, int *b, int *c, long int n);
	// c := a^b = b^-1 * a * b
	void perm_inverse(
			int *a, int *b, long int n);
	// b := a^-1
	void perm_raise(
			int *a, int *b, int e, long int n);
	// b := a^e (e >= 0)
	void perm_direct_product(
			long int n1, long int n2,
			int *perm1, int *perm2, int *perm3);
	void perm_print_list(
			std::ostream &ost, int *a, int n);
	void perm_print_list_offset(
			std::ostream &ost, int *a, int n, int offset);
	void perm_print_product_action(
			std::ostream &ost, int *a, int m_plus_n, int m,
		int offset, int f_cycle_length);
	void perm_print(
			std::ostream &ost, int *a, int n);
	void perm_print_with_point_labels(
			std::ostream &ost,
			int *a, int n,
			std::string *Point_labels, void *data);
	void perm_print_with_cycle_length(
			std::ostream &ost, int *a, int n);
	void perm_print_counting_from_one(
			std::ostream &ost, int *a, int n);
	void perm_print_offset(
			std::ostream &ost,
		int *a, int n,
		int offset,
		int f_print_cycles_of_length_one,
		int f_cycle_length,
		int f_max_cycle_length,
		int max_cycle_length,
		int f_orbit_structure,
		std::string *Point_labels, void *data);
	void perm_cycle_type(
			int *perm, long int degree, int *cycles, int &nb_cycles);
	int perm_order(
			int *a, long int n);
	int perm_signum(
			int *perm, long int n);
	int is_permutation(
			int *perm, long int n);
	int is_permutation_lint(
			long int *perm, long int n);
	void first_lehmercode(
			int n, int *v);
	int next_lehmercode(
			int n, int *v);
	int sign_based_on_lehmercode(
			int n, int *v);
	void lehmercode_to_permutation(
			int n, int *code, int *perm);

};


// #############################################################################
// polynomial_function_domain.cpp
// #############################################################################

//! polynomial expressions for functions from a finite field to itself

class polynomial_function_domain {

public:
	field_theory::finite_field *Fq; // the field Fq
	int q;

	int n;
	int max_degree; // n * (q - 1)

	int Q; // q^n = number of inputs to the function.

	ring_theory::homogeneous_polynomial_domain *Poly;
		// Poly[i] = polynomial of degree i in n + 1 variables.
		// i = 1,..,max_degree
	int **A_poly; // [1..max_degree][Poly[i].get_nb_monomials()]
	int **B_poly; // [1..max_degree][Poly[i].get_nb_monomials()]
	int **C_poly; // [1..max_degree][Poly[i].get_nb_monomials()]
	int *Kernel;
	int dim_kernel;


	long int *affine_points; // [Q]
		// affine_points[i] = PG_rank of affine point[i]



	int *v; // [n]
	int *v1; // [n + 1]
	int *w; // [n]
	int *f; // [Q]
	int *f2; // [Q]


	polynomial_function_domain();
	~polynomial_function_domain();
	void init(
			field_theory::finite_field *Fq,
			int n, int verbose_level);
	void setup_polynomial_rings(
			int verbose_level);
	void compute_polynomial_representation(
			int *func, int *coeff, int verbose_level);
	void evaluate_projectively(
			int *coeff, int *f);
	void evaluate(
			int *coeff, int *f);
	void raise(
			int *in, int *out);
	void multiply_i_times_j(
			int i, int j,
			int *A_eqn, int *B_eqn, int *C_eqn,
		int verbose_level);
	void algebraic_normal_form(
			int *func, int len,
			int *&coeff, int &nb_coeff,
			int verbose_level);
};





// #############################################################################
// row_and_col_partition.cpp
// #############################################################################


//! the partition associated with a decomposition of an incidence matrix


class row_and_col_partition {

public:

	data_structures::partitionstack *Stack;

	int *row_classes;
	int *row_class_idx;
	int nb_row_classes;

	int *col_classes;
	int *col_class_idx;
	int nb_col_classes;

	row_and_col_partition();
	~row_and_col_partition();
	void init_from_partitionstack(
			data_structures::partitionstack *Stack,
			int verbose_level);
	void print_classes_of_decomposition_tex(
			std::ostream &ost);
	void print_decomposition_scheme(
			std::ostream &ost,
		int *scheme);
	void print_row_tactical_decomposition_scheme_tex(
			std::ostream &ost, int f_enter_math_mode,
		int *row_scheme, int f_print_subscripts);
	void print_column_tactical_decomposition_scheme_tex(
			std::ostream &ost, int f_enter_math_mode,
		int *col_scheme, int f_print_subscripts);


};




// #############################################################################
// tdo_data.cpp TDO parameter refinement
// #############################################################################

//! a utility class related to the class tdo_scheme

class tdo_data {
public:
	int *types_first;
	int *types_len;
	int *only_one_type;
	int nb_only_one_type;
	int *multiple_types;
	int nb_multiple_types;
	int *types_first2;
	solvers::diophant *D1;
	solvers::diophant *D2;

	tdo_data();
	~tdo_data();
	void free();
	void allocate(
			int R);
	int solve_first_system(
			int verbose_level,
		int *&line_types, int &nb_line_types,
		int &line_types_allocated);
	void solve_second_system_omit(
			int verbose_level,
		int *classes_len,
		int *&line_types, int &nb_line_types,
		int *&distributions, int &nb_distributions,
		int omit);
	void solve_second_system_with_help(
			int verbose_level,
		int f_use_mckay_solver, int f_once,
		int *classes_len, int f_scale, int scaling,
		int *&line_types, int &nb_line_types,
		int *&distributions, int &nb_distributions,
		int cnt_second_system, solution_file_data *Sol);
	void solve_second_system_from_file(
			int verbose_level,
		int *classes_len, int f_scale, int scaling,
		int *&line_types, int &nb_line_types,
		int *&distributions, int &nb_distributions,
		std::string &solution_file_name);
	void solve_second_system(
			int verbose_level,
		int f_use_mckay_solver, int f_once,
		int *classes_len, int f_scale, int scaling,
		int *&line_types, int &nb_line_types,
		int *&distributions, int &nb_distributions);
};

// #############################################################################
// tdo_refinement_description.cpp
// #############################################################################



//! input data for the parameter refinement of a linear space

class tdo_refinement_description {
	public:

	int f_lambda3;
	int lambda3, block_size;
	int f_scale;
	int scaling;
	int f_range;
	int range_first, range_len;
	int f_select;
	std::string select_label;
	int f_omit1;
	int omit1;
	int f_omit2;
	int omit2;
	int f_D1_upper_bound_x0;
	int D1_upper_bound_x0;
	int f_reverse;
	int f_reverse_inverse;
	int f_use_packing_numbers;
	int f_dual_is_linear_space;
	int f_do_the_geometric_test;
	int f_once;
	int f_use_mckay_solver;
	int f_input_file;
	std::string fname_in;

	solution_file_data *Sol;

	tdo_refinement_description();
	~tdo_refinement_description();
	int read_arguments(
			int argc, std::string *argv, int verbose_level);
	void print();

};


// #############################################################################
// tdo_refinement.cpp
// #############################################################################



//! refinement of the parameters of a linear space

class tdo_refinement {
	public:

	int t0;
	int cnt;

	tdo_refinement_description *Descr;

	std::string fname;
	std::string fname_out;



	geo_parameter GP;

	geo_parameter GP2;



	int f_doit;
	int nb_written, nb_written_tactical, nb_tactical;
	int cnt_second_system;

	tdo_refinement();
	~tdo_refinement();
	void init(
			tdo_refinement_description *Descr,
			int verbose_level);
	void main_loop(
			int verbose_level);
	void do_it(
			std::ofstream &g, int verbose_level);
	void do_row_refinement(
			std::ofstream &g,
			tdo_scheme_synthetic &G,
			data_structures::partitionstack &P,
			int verbose_level);
	void do_col_refinement(
			std::ofstream &g,
			tdo_scheme_synthetic &G,
			data_structures::partitionstack &P,
			int verbose_level);
	void do_all_row_refinements(
			std::string &label_in, std::ofstream &g,
			tdo_scheme_synthetic &G,
		int *point_types, int nb_point_types, int point_type_len,
		int *distributions, int nb_distributions, int &nb_tactical,
		int verbose_level);
	void do_all_column_refinements(
			std::string &label_in, std::ofstream &g,
			tdo_scheme_synthetic &G,
		int *line_types, int nb_line_types, int line_type_len,
		int *distributions, int nb_distributions, int &nb_tactical,
		int verbose_level);
	int do_row_refinement(
			int t,
			std::string &label_in,
			std::ofstream &g,
			tdo_scheme_synthetic &G,
		int *point_types, int nb_point_types, int point_type_len,
		int *distributions, int nb_distributions,
		int verbose_level);
		// returns true or false depending on whether the
		// refinement gave a tactical decomposition
	int do_column_refinement(
			int t, std::string &label_in,
			std::ofstream &g,
			tdo_scheme_synthetic &G,
		int *line_types, int nb_line_types, int line_type_len,
		int *distributions, int nb_distributions,
		int verbose_level);
		// returns true or false depending on whether the
		// refinement gave a tactical decomposition
};



// #############################################################################
// tdo_scheme_compute.cpp
// #############################################################################

//! tactical decomposition of an incidence structure obtained by refinement

class tdo_scheme_compute {

public:

	canonical_form_classification::encoded_combinatorial_object *Enc;
	decomposition *Decomp;

	int f_TDA;
	int nb_orbits;
	int *orbit_first;
	int *orbit_len;
	int *orbit;

	tdo_scheme_compute();
	~tdo_scheme_compute();
	void init(
			canonical_form_classification::encoded_combinatorial_object *Enc,
			int max_depth,
			int verbose_level);
	// used by combinatorial_object_with_properties::compute_TDO
	void init_TDA(
			canonical_form_classification::encoded_combinatorial_object *Enc,
			int nb_orbits, int *orbit_first, int *orbit_len, int *orbit,
			int verbose_level);
	void print_schemes(
			std::ostream &ost,
			graphics::draw_incidence_structure_description *Draw_options,
			canonical_form_classification::objects_report_options
				*Report_options,
			int verbose_level);

};


// #############################################################################
// tdo_scheme_synthetic.cpp
// #############################################################################



#define NUMBER_OF_SCHEMES 5
#define ROW_SCHEME 0
#define COL_SCHEME 1
#define LAMBDA_SCHEME 2
#define EXTRA_ROW_SCHEME 3
#define EXTRA_COL_SCHEME 4


//! internal class related to class tdo_data


struct solution_file_data {
	int nb_solution_files;
	std::vector<int> system_no;
	std::vector<std::string> solution_file;
};

//! canonical tactical decomposition of an incidence structure

class tdo_scheme_synthetic {

public:

	// the following is needed by the TDO process:
	// allocated in init_partition_stack
	// freed in exit_partition_stack

	//partition_backtrack PB;

	data_structures::partitionstack *P;

	int part_length;
	int *part;
	int nb_entries;
	int *entries;
	int row_level;
	int col_level;
	int lambda_level;
	int extra_row_level;
	int extra_col_level;

	int mn; // m + n
	int m; // # of rows
	int n; // # of columns

	int level[NUMBER_OF_SCHEMES];
	int *row_classes[NUMBER_OF_SCHEMES], nb_row_classes[NUMBER_OF_SCHEMES];
	int *col_classes[NUMBER_OF_SCHEMES], nb_col_classes[NUMBER_OF_SCHEMES];
	int *row_class_index[NUMBER_OF_SCHEMES];
	int *col_class_index[NUMBER_OF_SCHEMES];
	int *row_classes_first[NUMBER_OF_SCHEMES];
	int *row_classes_len[NUMBER_OF_SCHEMES];
	int *row_class_no[NUMBER_OF_SCHEMES];
	int *col_classes_first[NUMBER_OF_SCHEMES];
	int *col_classes_len[NUMBER_OF_SCHEMES];
	int *col_class_no[NUMBER_OF_SCHEMES];

	int *the_row_scheme;
	int *the_col_scheme;
	int *the_extra_row_scheme;
	int *the_extra_col_scheme;
	int *the_row_scheme_cur; // [m * nb_col_classes[ROW_SCHEME]]
	int *the_col_scheme_cur; // [n * nb_row_classes[COL_SCHEME]]
	int *the_extra_row_scheme_cur; // [m * nb_col_classes[EXTRA_ROW_SCHEME]]
	int *the_extra_col_scheme_cur; // [n * nb_row_classes[EXTRA_COL_SCHEME]]

	// end of TDO process data

	tdo_scheme_synthetic();
	~tdo_scheme_synthetic();

	void init_part_and_entries(
			int *part, int *entries, int verbose_level);
	void init_part_and_entries_int(
			int *part, int *entries, int verbose_level);
	void init_TDO(
			int *Part, int *Entries,
		int Row_level, int Col_level,
		int Extra_row_level, int Extra_col_level,
		int Lambda_level, int verbose_level);
	void exit_TDO();
	void init_partition_stack(
			int verbose_level);
	void exit_partition_stack();
	void get_partition(
			int h, int l, int verbose_level);
	void free_partition(
			int h);
	void complete_partition_info(
			int h, int verbose_level);
	void get_row_or_col_scheme(
			int h, int l, int verbose_level);
	void get_column_split_partition(
			int verbose_level,
			data_structures::partitionstack &P);
	void get_row_split_partition(
			int verbose_level,
			data_structures::partitionstack &P);
	void print_all_schemes();
	void print_scheme(
			int h, int verbose_level);
	void print_scheme_tex(
			std::ostream &ost, int h);
	void print_scheme_tex_fancy(
			std::ostream &ost,
			int h, int f_label, std::string &label);
	void compute_whether_first_inc_must_be_moved(
			int *f_first_inc_must_be_moved, int verbose_level);
	int count_nb_inc_from_row_scheme(
			int verbose_level);
	int count_nb_inc_from_extra_row_scheme(
			int verbose_level);


	int geometric_test_for_row_scheme(
			data_structures::partitionstack &P,
		int *point_types, int nb_point_types, int point_type_len,
		int *distributions, int nb_distributions,
		int f_omit1, int omit1, int verbose_level);
	int geometric_test_for_row_scheme_level_s(
			data_structures::partitionstack &P, int s,
		int *point_types, int nb_point_types, int point_type_len,
		int *distribution,
		int *non_zero_blocks, int nb_non_zero_blocks,
		int f_omit1, int omit1,
		int verbose_level);


	int refine_rows(
			int verbose_level,
		int f_use_mckay, int f_once,
		data_structures::partitionstack &P,
		int *&point_types, int &nb_point_types, int &point_type_len,
		int *&distributions, int &nb_distributions,
		int &cnt_second_system, solution_file_data *Sol,
		int f_omit1, int omit1, int f_omit2, int omit2,
		int f_use_packing_numbers,
		int f_dual_is_linear_space,
		int f_do_the_geometric_test);
	int refine_rows_easy(
			int verbose_level,
		int *&point_types, int &nb_point_types, int &point_type_len,
		int *&distributions, int &nb_distributions,
		int &cnt_second_system);
	int refine_rows_hard(
			data_structures::partitionstack &P,
			int verbose_level,
		int f_use_mckay, int f_once,
		int *&point_types, int &nb_point_types, int &point_type_len,
		int *&distributions, int &nb_distributions,
		int &cnt_second_system,
		int f_omit1, int omit1, int f_omit, int omit,
		int f_use_packing_numbers, int f_dual_is_linear_space);
	void row_refinement_L1_L2(
			data_structures::partitionstack &P,
			int f_omit, int omit,
		int &L1, int &L2, int verbose_level);
	int tdo_rows_setup_first_system(
			int verbose_level,
		tdo_data &T, int r,
		data_structures::partitionstack &P,
		int f_omit, int omit,
		int *&point_types, int &nb_point_types);
	int tdo_rows_setup_second_system(
			int verbose_level,
		tdo_data &T,
		data_structures::partitionstack &P,
		int f_omit, int omit,
		int f_use_packing_numbers,
		int f_dual_is_linear_space,
		int *&point_types, int &nb_point_types);
	int tdo_rows_setup_second_system_eqns_joining(
			int verbose_level,
		tdo_data &T,
		data_structures::partitionstack &P,
		int f_omit, int omit, int f_dual_is_linear_space,
		int *point_types, int nb_point_types,
		int eqn_offset);
	int tdo_rows_setup_second_system_eqns_counting(
			int verbose_level,
		tdo_data &T,
		data_structures::partitionstack &P,
		int f_omit, int omit,
		int *point_types, int nb_point_types,
		int eqn_offset);
	int tdo_rows_setup_second_system_eqns_packing(
			int verbose_level,
		tdo_data &T,
		data_structures::partitionstack &P,
		int f_omit, int omit,
		int *point_types, int nb_point_types,
		int eqn_start, int &nb_eqns_used);

	int refine_columns(
			int verbose_level, int f_once,
			data_structures::partitionstack &P,
		int *&line_types, int &nb_line_types, int &line_type_len,
		int *&distributions, int &nb_distributions,
		int &cnt_second_system, solution_file_data *Sol,
		int f_omit1, int omit1, int f_omit, int omit,
		int f_D1_upper_bound_x0, int D1_upper_bound_x0,
		int f_use_mckay_solver,
		int f_use_packing_numbers);
	int refine_cols_hard(
			data_structures::partitionstack &P,
		int verbose_level, int f_once,
		int *&line_types, int &nb_line_types, int &line_type_len,
		int *&distributions, int &nb_distributions,
		int &cnt_second_system, solution_file_data *Sol,
		int f_omit1, int omit1, int f_omit, int omit,
		int f_D1_upper_bound_x0, int D1_upper_bound_x0,
		int f_use_mckay_solver,
		int f_use_packing_numbers);
	void column_refinement_L1_L2(
			data_structures::partitionstack &P,
		int f_omit, int omit,
		int &L1, int &L2, int verbose_level);
	int tdo_columns_setup_first_system(
			int verbose_level,
		tdo_data &T, int r,
		data_structures::partitionstack &P,
		int f_omit, int omit,
		int *&line_types, int &nb_line_types);
	int tdo_columns_setup_second_system(
			int verbose_level,
		tdo_data &T,
		data_structures::partitionstack &P,
		int f_omit, int omit,
		int f_use_packing_numbers,
		int *&line_types, int &nb_line_types);
	int tdo_columns_setup_second_system_eqns_joining(
			int verbose_level,
		tdo_data &T,
		data_structures::partitionstack &P,
		int f_omit, int omit,
		int *line_types, int nb_line_types,
		int eqn_start);
	void tdo_columns_setup_second_system_eqns_counting(
			int verbose_level,
		tdo_data &T,
		data_structures::partitionstack &P,
		int f_omit, int omit,
		int *line_types, int nb_line_types,
		int eqn_start);
	int tdo_columns_setup_second_system_eqns_upper_bound(
			int verbose_level,
		tdo_data &T,
		data_structures::partitionstack &P,
		int f_omit, int omit,
		int *line_types, int nb_line_types,
		int eqn_start, int &nb_eqns_used);


	int td3_refine_rows(
			int verbose_level, int f_once,
		int lambda3, int block_size,
		int *&point_types, int &nb_point_types, int &point_type_len,
		int *&distributions, int &nb_distributions);
	int td3_rows_setup_first_system(
			int verbose_level,
		int lambda3, int block_size, int lambda2,
		tdo_data &T, int r,
		data_structures::partitionstack &P,
		int &nb_vars,int &nb_eqns,
		int *&point_types, int &nb_point_types);
	int td3_rows_setup_second_system(
			int verbose_level,
		int lambda3, int block_size, int lambda2,
		tdo_data &T,
		int nb_vars, int &Nb_vars, int &Nb_eqns,
		int *&point_types, int &nb_point_types);
	int td3_rows_counting_flags(
			int verbose_level,
		int lambda3, int block_size, int lambda2, int &S,
		tdo_data &T,
		int nb_vars, int Nb_vars,
		int *&point_types, int &nb_point_types, int eqn_offset);
	int td3_refine_columns(
			int verbose_level, int f_once,
		int lambda3, int block_size,
		int f_scale, int scaling,
		int *&line_types, int &nb_line_types, int &line_type_len,
		int *&distributions, int &nb_distributions);
	int td3_columns_setup_first_system(
			int verbose_level,
		int lambda3, int block_size, int lambda2,
		tdo_data &T, int r,
		data_structures::partitionstack &P,
		int &nb_vars, int &nb_eqns,
		int *&line_types, int &nb_line_types);
	int td3_columns_setup_second_system(
			int verbose_level,
		int lambda3, int block_size, int lambda2, int f_scale, int scaling,
		tdo_data &T,
		int nb_vars, int &Nb_vars, int &Nb_eqns,
		int *&line_types, int &nb_line_types);
	int td3_columns_triples_same_class(
			int verbose_level,
		int lambda3, int block_size,
		tdo_data &T,
		int nb_vars, int Nb_vars,
		int *&line_types, int &nb_line_types, int eqn_offset);
	int td3_columns_pairs_same_class(
			int verbose_level,
		int lambda3, int block_size, int lambda2,
		tdo_data &T,
		int nb_vars, int Nb_vars,
		int *&line_types, int &nb_line_types, int eqn_offset);
	int td3_columns_counting_flags(
			int verbose_level,
		int lambda3, int block_size, int lambda2, int &S,
		tdo_data &T,
		int nb_vars, int Nb_vars,
		int *&line_types, int &nb_line_types, int eqn_offset);
	int td3_columns_lambda2_joining_pairs_from_different_classes(
		int verbose_level,
		int lambda3, int block_size, int lambda2,
		tdo_data &T,
		int nb_vars, int Nb_vars,
		int *&line_types, int &nb_line_types, int eqn_offset);
	int td3_columns_lambda3_joining_triples_2_1(
			int verbose_level,
		int lambda3, int block_size, int lambda2,
		tdo_data &T,
		int nb_vars, int Nb_vars,
		int *&line_types, int &nb_line_types, int eqn_offset);
	int td3_columns_lambda3_joining_triples_1_1_1(
			int verbose_level,
		int lambda3, int block_size, int lambda2,
		tdo_data &T,
		int nb_vars, int Nb_vars,
		int *&line_types, int &nb_line_types, int eqn_offset);


};







}}}



#endif /* ORBITER_SRC_LIB_FOUNDATIONS_COMBINATORICS_COMBINATORICS_H_ */




