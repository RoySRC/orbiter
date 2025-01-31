// hjelmslev.cpp
//
// Anton Betten
//
//
// June 22, 2010
//
//
// 
//
//

#include "foundations.h"

using namespace std;


namespace orbiter {
namespace layer1_foundations {
namespace geometry {
namespace other_geometry {


hjelmslev::hjelmslev()
{
	Record_birth();
	n = k = q = 0;
	n_choose_k_p = 0;
	R = NULL;
	G = NULL;
	v = NULL;
	Mtx = NULL;
	base_cols = NULL;
}


hjelmslev::~hjelmslev()
{
	Record_death();
	if (G) {
		FREE_OBJECT(G);
		}
	if (Mtx) {
		FREE_int(Mtx);
		}
	if (base_cols) {
		FREE_int(base_cols);
		}
	if (v) {
		FREE_int(v);
		}
}

void hjelmslev::init(
		algebra::ring_theory::finite_ring *R,
		int n, int k, int verbose_level)
{
	int f_v = (verbose_level >= 1);
	combinatorics::other_combinatorics::combinatorics_domain Combi;

	if (f_v) {
		cout << "hjelmslev::init n=" << n << " k=" << k
				<< " q=" << R->q << endl;
		}
	hjelmslev::R = R;
	hjelmslev::n = n;
	hjelmslev::k = k;
	n_choose_k_p = Combi.generalized_binomial(n, k, R->get_p());
	if (f_v) {
		cout << "hjelmslev::init n_choose_k_p = "
				<< n_choose_k_p << endl;
		}
	G = NEW_OBJECT(projective_geometry::grassmann);
	G->init(n, k, R->get_Fp(), verbose_level);
	Mtx = NEW_int(k * n);
	base_cols = NEW_int(n);
	v = NEW_int(k * (n - k));
}

long int hjelmslev::number_of_submodules()
{
	algebra::number_theory::number_theory_domain NT;
	return n_choose_k_p * NT.i_power_j_lint(R->get_p(), (R->get_e() - 1) * k * (n - k));
}

void hjelmslev::unrank_lint(
		int *M, long int rk, int verbose_level)
{
	int f_v = (verbose_level >= 1);
	int f_vv = (verbose_level >= 2);
	long int a, b, c, i, j, h;
	geometry_global Gg;
	
	if (f_v) {
		cout << "hjelmslev::unrank_lint " << rk << endl;
		cout << "verbose_level=" << verbose_level << endl;
	}
	if (k == 0) {
		return;
	}
	a = rk % n_choose_k_p;
	b = (rk - a) / n_choose_k_p;
	if (f_vv) {
		cout << "rk=" << rk << " a=" << a << " b=" << b << endl;
	}
	G->unrank_lint(a, 0);
	Gg.AG_element_unrank(R->get_e(), v, 1, k * (n - k), b);
	if (f_vv) {
		Int_vec_print_integer_matrix_width(cout, G->M, k, n, n, 5);
		Int_vec_print(cout, v, k * (n - k));
		cout << endl;
	}
	for (i = 0; i < k * n; i++) {
		Mtx[i] = G->M[i];
	}
	for (j = 0; j < n - k; j++) {
		h = G->base_cols[k + j];
		for (i = 0; i < k; i++) {
			c = v[i * (n - k) + j];
			Mtx[i * n + h] += c * R->get_p();
		}
	}
	for (i = 0; i < k * n; i++) {
		M[i] = Mtx[i];
	}
}

long int hjelmslev::rank_lint(
		int *M, int verbose_level)
{
	int f_v = (verbose_level >= 1);
	int f_vv = (verbose_level >= 2);
	long int c, i, j, h, rk_mtx;
	long int a, b, rk;
	int f_special = false;
	int f_complete = true;
	geometry_global Gg;
	
	if (f_v) {
		cout << "hjelmslev::rank_lint " << endl;
		Int_vec_print_integer_matrix_width(cout, M, k, n, n, 5);
		cout << "verbose_level=" << verbose_level << endl;
		}
	for (i = 0; i < k * n; i++) {
		Mtx[i] = M[i];
		}
	rk_mtx = R->Gauss_int(Mtx,
			f_special, f_complete,
			base_cols, false, NULL, k, n, n, 0);
	if (f_v) {
		cout << "hjelmslev::rank_lint after Gauss, "
				"rk_mtx=" << rk_mtx << endl;
		Int_vec_print_integer_matrix_width(cout, Mtx, k, n, n, 5);
		cout << "base_cols=";
		Int_vec_print(cout, base_cols, rk_mtx);
		cout << endl;
		}
	other::orbiter_kernel_system::Orbiter->Int_vec->complement(base_cols, n, k);
	if (rk_mtx != k) {
		cout << "hjelmslev::rank_lint fatal: rk_mtx != k" << endl;
		exit(1);
		}
	if (f_v) {
		cout << "complement:";
		Int_vec_print(cout, base_cols + k, n - k);
		cout << endl;
		}
	for (j = 0; j < n - k; j++) {
		h = G->base_cols[k + j];
		for (i = 0; i < k; i++) {
			c = Mtx[i * n + h] / R->get_p();
			v[i * (n - k) + j] = c;
			Mtx[i * n + h] -= c * R->get_p();
			}
		}
	
	for (i = 0; i < k * n; i++) {
		G->M[i] = Mtx[i];
		}
	if (f_vv) {
		Int_vec_print(cout, v, k * (n - k));
		cout << endl;
		}
	b = Gg.AG_element_rank(R->get_e(), v, 1, k * (n - k));
	a = G->rank_lint(0);
	rk = b * n_choose_k_p + a;
	if (f_v) {
		cout << "hjelmslev::rank_lint rk=" << rk
				<< " a=" << a << " b=" << b << endl;
	}
	return rk;
}

}}}}


