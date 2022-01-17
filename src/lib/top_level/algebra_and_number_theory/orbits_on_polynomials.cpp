/*
 * orbits_on_polynomials.cpp
 *
 *  Created on: Nov 28, 2020
 *      Author: betten
 */






#include "orbiter.h"

using namespace std;

namespace orbiter {
namespace top_level {


orbits_on_polynomials::orbits_on_polynomials()
{
	LG = NULL;
	degree_of_poly = 0;

	F = NULL;
	A = NULL;
	n = 0;
	// go;
	HPD = NULL;
	A2 = NULL;
	Elt1 = Elt2 = Elt3 = NULL;
	Sch = NULL;
	// full_go
	//fname_base
	//fname_csv
	//fname_report
	T = NULL;
	Nb_pts = NULL;

}

orbits_on_polynomials::~orbits_on_polynomials()
{
}

void orbits_on_polynomials::init(
		linear_group *LG,
		int degree_of_poly,
		int f_recognize, std::string &recognize_text,
		int verbose_level)
{
	int f_v = (verbose_level >= 1);

	if (f_v) {
		cout << "orbits_on_polynomials::init" << endl;
	}

	orbits_on_polynomials::LG = LG;
	orbits_on_polynomials::degree_of_poly = degree_of_poly;



	A = LG->A_linear;
	F = A->matrix_group_finite_field();
	A->group_order(go);

	n = A->matrix_group_dimension();

	if (f_v) {
		cout << "n = " << n << endl;
	}

	if (f_v) {
		cout << "strong generators:" << endl;
		//A->Strong_gens->print_generators();
		A->Strong_gens->print_generators_tex();
	}

	HPD = NEW_OBJECT(homogeneous_polynomial_domain);


	monomial_ordering_type Monomial_ordering_type = t_PART;


	HPD->init(F, n /* nb_var */, degree_of_poly,
			TRUE /* f_init_incidence_structure */,
			Monomial_ordering_type,
			verbose_level - 2);

	A2 = NEW_OBJECT(action);
	A2->induced_action_on_homogeneous_polynomials(A,
		HPD,
		FALSE /* f_induce_action */, NULL,
		verbose_level - 2);

	if (f_v) {
		cout << "created action A2" << endl;
		A2->print_info();
	}


	Elt1 = NEW_int(A->elt_size_in_int);
	Elt2 = NEW_int(A->elt_size_in_int);
	Elt3 = NEW_int(A->elt_size_in_int);


	char str[1000];

	sprintf(str, "poly_orbits_d%d_n%d_q%d", degree_of_poly, n - 1, F->q);
	fname_base.assign(str);
	fname_csv.assign(fname_base);
	fname_csv.append(".csv");


	//Sch = new schreier;
	//A2->all_point_orbits(*Sch, verbose_level);


	if (f_v) {
		cout << "orbits_on_polynomials::init "
				"before A->Strong_gens->orbits_on_points_schreier" << endl;
	}


	Sch = A->Strong_gens->orbits_on_points_schreier(A2, verbose_level - 2);

	if (f_v) {
		cout << "orbits_on_polynomials::init "
				"after A->Strong_gens->orbits_on_points_schreier" << endl;
	}



	if (f_v) {
		cout << "orbits_on_polynomials::init "
				"before Sch->write_orbit_summary" << endl;
	}
	Sch->write_orbit_summary(fname_csv,
			A /*default_action*/,
			go,
			verbose_level);
	if (f_v) {
		cout << "orbits_on_polynomials::init "
				"after Sch->write_orbit_summary" << endl;
	}



	A->group_order(full_go);
	T = NEW_OBJECT(orbit_transversal);

	if (f_v) {
		cout << "orbits_on_polynomials::init before T->init_from_schreier" << endl;
	}

	T->init_from_schreier(
			Sch,
			A,
			full_go,
			verbose_level);

	if (f_v) {
		cout << "orbits_on_polynomials::init after T->init_from_schreier" << endl;
	}



	Sch->print_orbit_reps(cout);


	if (f_v) {
		cout << "orbits_on_polynomials::init "
				"before compute_points" << endl;
	}
	compute_points(verbose_level);
	if (f_v) {
		cout << "orbits_on_polynomials::init "
				"after compute_points" << endl;
	}



	if (f_recognize) {
		long int *Rank;
		int len;
		int i;

		int *Idx;


		cout << "orbits_on_polynomials::init recognition:" << endl;
		Orbiter->Lint_vec->scan(recognize_text, Rank, len);

		Idx = NEW_int(len);

		for (i = 0; i < len; i++) {
			//cout << "recognizing object " << i << " / " << len << " which is " << Rank[i] << endl;
			int orbit_idx;
			orbit_idx = Sch->orbit_number(Rank[i]);
			Idx[i] = orbit_idx;
			cout << "recognizing object " << i << " / " << len << ", point "
					<< Rank[i] << " lies in orbit " << orbit_idx << endl;
		}
		file_io Fio;
		std::string fname;

		fname.assign(fname_base);
		fname.append("_recognition.csv");

		Fio.int_vec_write_csv(Idx, len, fname, "Idx");

		FREE_lint(Rank);

	}




	FREE_int(Elt1);
	FREE_int(Elt2);
	FREE_int(Elt3);



	if (f_v) {
		cout << "orbits_on_polynomials::init done" << endl;
	}
}

void orbits_on_polynomials::compute_points(int verbose_level)
{
	int *coeff;
	int i;

	coeff = NEW_int(HPD->get_nb_monomials());
	Nb_pts = NEW_int(T->nb_orbits);


	for (i = 0; i < T->nb_orbits; i++) {

		longinteger_object go;
		T->Reps[i].Strong_gens->group_order(go);

		cout << i << " : ";
		Orbiter->Lint_vec->print(cout, T->Reps[i].data, T->Reps[i].sz);
		cout << " : ";
		cout << go;

		cout << " : ";

		HPD->unrank_coeff_vector(coeff, T->Reps[i].data[0]);

		std::vector<long int> Pts;

		HPD->enumerate_points(coeff, Pts, verbose_level);

		Points.push_back(Pts);
		Nb_pts[i] = Pts.size();
	}
	FREE_int(coeff);

}

void orbits_on_polynomials::report(int verbose_level)
{
	int f_v = (verbose_level >= 1);

	if (f_v) {
		cout << "orbits_on_polynomials::report" << endl;
	}
	cout << "orbit reps:" << endl;

	char title[1000];
	char author[1000];
	char str[1000];

	sprintf(str, "poly_orbits_d%d_n%d_q%d.tex", degree_of_poly, n - 1, F->q);
	fname_report.assign(str);

	sprintf(title, "Varieties of degree %d in PG(%d,%d)", degree_of_poly, n - 1, F->q);
	sprintf(author, "Orbiter");
	{
		ofstream ost(fname_report);
		latex_interface L;

		L.head(ost,
				FALSE /* f_book*/,
				TRUE /* f_title */,
				title, author,
				FALSE /* f_toc */,
				FALSE /* f_landscape */,
				TRUE /* f_12pt */,
				TRUE /* f_enlarged_page */,
				TRUE /* f_pagenumbers */,
				NULL /* extra_praeamble */);

		ost << "\\small" << endl;
		ost << "\\arraycolsep=2pt" << endl;
		ost << "\\parindent=0pt" << endl;
		ost << "$q = " << F->q << "$\\\\" << endl;
		ost << "$n = " << n - 1 << "$\\\\" << endl;
		ost << "degree of poly $ = " << degree_of_poly << "$\\\\" << endl;

		ost << "\\clearpage" << endl << endl;


		// summary table:

		ost << "\\section{The Varieties of degree $" << degree_of_poly
				<< "$ in $PG(" << n - 1 << ", " << F->q << ")$, summary}" << endl;

#if 0
		T->print_table_latex(
				f,
				TRUE /* f_has_callback */,
				polynomial_orbits_callback_print_function2,
				HPD /* callback_data */,
				TRUE /* f_has_callback */,
				polynomial_orbits_callback_print_function,
				HPD /* callback_data */,
				verbose_level);
#else
		int *coeff;
		int i;

		coeff = NEW_int(HPD->get_nb_monomials());
		//Nb_pts = NEW_int(T->nb_orbits);


		// compute the group of the surface:
		projective_space_with_action *PA;
		int f_semilinear;
		number_theory_domain NT;

		if (NT.is_prime(F->q)) {
			f_semilinear = FALSE;
		}
		else {
			f_semilinear = TRUE;
		}

		PA = NEW_OBJECT(projective_space_with_action);

		if (f_v) {
			cout << "group_theoretic_activity::do_cubic_surface_properties before PA->init" << endl;
		}
		PA->init(
			F, n - 1 /*n*/, f_semilinear,
			TRUE /* f_init_incidence_structure */,
			verbose_level);
		if (f_v) {
			cout << "group_theoretic_activity::do_cubic_surface_properties after PA->init" << endl;
		}






		tally T_nb_pts;
		int h, j, f, l, a;

		T_nb_pts.init(Nb_pts, T->nb_orbits, FALSE, 0);

		for (h = T_nb_pts.nb_types - 1; h >= 0; h--) {

			f = T_nb_pts.type_first[h];
			l = T_nb_pts.type_len[h];
			a = T_nb_pts.data_sorted[f];

			ost << "\\subsection{Objects with " << a << " Points}" << endl;

			ost << "There are " << l << " objects with " << a << " Points: \\\\" << endl;

			int *Idx;
			int len;

			T_nb_pts.get_class_by_value(Idx, len, a, 0 /*verbose_level*/);


			data_structures::sorting Sorting;

			Sorting.int_vec_heapsort(Idx, l);

			ost << "orbit : rep : go : poly : Pts\\\\" << endl;
			for (j = 0; j < l; j++) {

				//i = T_nb_pts.sorting_perm_inv[f + j];

				i = Idx[j];

				longinteger_object go;
				T->Reps[i].Strong_gens->group_order(go);

				ost << i << " : ";
				Orbiter->Lint_vec->print(ost, T->Reps[i].data, T->Reps[i].sz);
				ost << " : ";
				ost << go;

				ost << " : ";

				HPD->unrank_coeff_vector(coeff, T->Reps[i].data[0]);

				int nb_pts;

				nb_pts = Nb_pts[i];

				//ost << nb_pts;
				//ost << " : ";

				ost << T->Reps[i].data[0] << "=$";
				HPD->print_equation_tex(ost, coeff);
				//int_vec_print(f, coeff, HPD->get_nb_monomials());
				//cout << " = ";
				//HPD->print_equation_str(ost, coeff);

				//f << " & ";
				//Reps[i].Strong_gens->print_generators_tex(f);
				ost << "$";

				ost << " : ";

				int u;
				long int *set;
				strong_generators *Sg;

				set = NEW_lint(nb_pts);
				for (u = 0; u < nb_pts; u++) {
					set[u] = Points[i][u];
				}

				for (u = 0; u < nb_pts; u++) {
					ost << set[u];
					if (u < nb_pts - 1) {
						ost << ",";
					}
				}

				PA->compute_group_of_set(set, nb_pts,
						Sg,
						verbose_level);

				ost << " : go=";
				longinteger_object go1;
				Sg->group_order(go1);
				ost << go1;
				ost << "\\\\" << endl;

				FREE_lint(set);
			}

			FREE_int(Idx);

		}
		FREE_OBJECT(PA);

#endif

		FREE_int(coeff);



		L.foot(ost);

	}
	file_io Fio;

	cout << "Written file " << fname_report << " of size " << Fio.file_size(fname_report) << endl;
	if (f_v) {
		cout << "orbits_on_polynomials::report done" << endl;
	}

}

void orbits_on_polynomials::report_detailed_list(std::ostream &ost,
		int verbose_level)
{
	int f_v = (verbose_level >= 1);

	if (f_v) {
		cout << "orbits_on_polynomials::report_detailed_list" << endl;
	}
	// detailed listing:



	tally T1;

	T1.init(Nb_pts, T->nb_orbits, FALSE, 0);
	ost << "Distribution of the number of points: $";
	T1.print_naked_tex(ost, TRUE);
	ost << "$\\\\" << endl;

	ost << "\\section{The Varieties of degree $" << degree_of_poly
			<< "$ in $PG(" << n - 1 << ", " << F->q << ")$, "
					"detailed listing}" << endl;
	{
		int fst, l, a, r;
		longinteger_object go, go1;
		longinteger_domain D;
		int *coeff;
		int *line_type;
		long int *Pts;
		int nb_pts;
		int *Kernel;
		int *v;
		int i;
		//int h, pt, orbit_idx;

		A->group_order(go);
		Pts = NEW_lint(HPD->get_P()->N_points);
		coeff = NEW_int(HPD->get_nb_monomials());
		line_type = NEW_int(HPD->get_P()->N_lines);
		Kernel = NEW_int(HPD->get_nb_monomials() * HPD->get_nb_monomials());
		v = NEW_int(n);

		for (i = 0; i < Sch->nb_orbits; i++) {
			ost << "\\subsection*{Orbit " << i << " / "
					<< Sch->nb_orbits << "}" << endl;
			fst = Sch->orbit_first[i];
			l = Sch->orbit_len[i];

			D.integral_division_by_int(go, l, go1, r);
			a = Sch->orbit[fst];
			HPD->unrank_coeff_vector(coeff, a);


			vector<long int> Points;

			HPD->enumerate_points(coeff, Points, verbose_level);

			nb_pts = Points.size();
			Pts = NEW_lint(nb_pts);
			for (int u = 0; u < nb_pts; u++) {
				Pts[u] = Points[u];
			}

			ost << "stab order " << go1 << "\\\\" << endl;
			ost << "orbit length = " << l << "\\\\" << endl;
			ost << "orbit rep = " << a << "\\\\" << endl;
			ost << "number of points = " << nb_pts << "\\\\" << endl;

			ost << "$";
			Orbiter->Int_vec->print(ost, coeff, HPD->get_nb_monomials());
			ost << " = ";
			HPD->print_equation(ost, coeff);
			ost << "$\\\\" << endl;


			cout << "We found " << nb_pts << " points in the variety" << endl;
			cout << "They are : ";
			Orbiter->Lint_vec->print(cout, Pts, nb_pts);
			cout << endl;
			HPD->get_P()->print_set_numerical(cout, Pts, nb_pts);

			F->display_table_of_projective_points(
					ost, Pts, nb_pts, n);

			HPD->get_P()->line_intersection_type(Pts, nb_pts,
					line_type, 0 /* verbose_level */);

			ost << "The line type is: ";

			stringstream sstr;
			Orbiter->Int_vec->print_classified_str(sstr,
					line_type, HPD->get_P()->N_lines, TRUE /* f_backwards*/);
			string s = sstr.str();
			ost << "$" << s << "$\\\\" << endl;
			//int_vec_print_classified(line_type, HPD->P->N_lines);
			//cout << "after int_vec_print_classified" << endl;

			ost << "The stabilizer is generated by:" << endl;
			T->Reps[i].Strong_gens->print_generators_tex(ost);
		} // next i

		FREE_lint(Pts);
		FREE_int(coeff);
		FREE_int(line_type);
		FREE_int(Kernel);
		FREE_int(v);
		}

	if (f_v) {
		cout << "orbits_on_polynomials::report_detailed_list done" << endl;
	}
}

}}
