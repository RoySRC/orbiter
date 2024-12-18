/*
 * classification_of_varieties.cpp
 *
 *  Created on: Oct 15, 2023
 *      Author: betten
 */





#if 0

#include "orbiter.h"

using namespace std;

namespace orbiter {
namespace layer5_applications {
namespace canonical_form {

#if 1

classification_of_varieties::classification_of_varieties()
{
	Classifier = NULL;

	// nauty:
		CB = NULL;
		canonical_labeling_len = 0;
		//alpha = NULL;
		//gamma = NULL;
		F_first_time = NULL;
		Iso_idx = NULL;
		Idx_canonical_form = NULL;
		Idx_equation = NULL;
		nb_iso_orbits = 0;
		Orbit_input_idx = NULL;

		Classification_table_nauty = NULL;

	// substructure classification:
#if 0
		SubC = NULL;


		//canonical_equation = NULL;
		//transporter_to_canonical_form = NULL;
		//longinteger_object go_eqn;

		CFS_table = NULL;
#endif

		Canonical_equation = NULL;

		Tally = NULL;

		transversal = NULL;
		frequency = NULL;
		nb_types = 0;

	// stuff common to both algorithms:

	Variety_table = NULL;

	Elt = NULL;
	eqn2 = NULL;
	Goi = NULL;



}

classification_of_varieties::~classification_of_varieties()
{
	if (F_first_time) {
		FREE_int(F_first_time);
	}
	if (Iso_idx) {
		FREE_int(Iso_idx);
	}
	if (Idx_canonical_form) {
		FREE_int(Idx_canonical_form);
	}
	if (Idx_equation) {
		FREE_int(Idx_equation);
	}
	if (Orbit_input_idx) {
		FREE_int(Orbit_input_idx);
	}

	if (Classification_table_nauty) {
		FREE_int(Classification_table_nauty);
	}

}

void classification_of_varieties::init(
		canonical_form_classifier *Classifier, int verbose_level)
{
	int f_v = (verbose_level >= 1);

	if (f_v) {
		cout << "classification_of_varieties::init " << endl;
	}
	if (f_v) {
		cout << "classification_of_varieties::init" << endl;
		cout << "classification_of_varieties::init "
				"nb_objects_to_test = " << Classifier->Input->nb_objects_to_test << endl;
	}

	classification_of_varieties::Classifier = Classifier;

	if (f_v) {
		cout << "classification_of_varieties::init "
				"nb_objects_to_test=" << Classifier->Input->nb_objects_to_test << endl;
	}


	Variety_table = (variety_compute_canonical_form **)
			NEW_pvoid(Classifier->Input->nb_objects_to_test);

	Elt = NEW_int(Classifier->Ring_with_action->PA->A->elt_size_in_int);
	eqn2 = NEW_int(Classifier->Ring_with_action->Poly_ring->get_nb_monomials());
	Goi = NEW_lint(Classifier->Input->nb_objects_to_test);


	if (Classifier->get_description()->f_algorithm_nauty) {


		if (f_v) {
			cout << "classification_of_varieties::init "
					"algorithm nauty" << endl;
		}

		// classification by nauty:

		F_first_time = NEW_int(Classifier->Input->nb_objects_to_test);
		Iso_idx = NEW_int(Classifier->Input->nb_objects_to_test);
		Idx_canonical_form = NEW_int(Classifier->Input->nb_objects_to_test);
		Idx_equation = NEW_int(Classifier->Input->nb_objects_to_test);
		Orbit_input_idx = NEW_int(Classifier->Input->nb_objects_to_test);
		nb_iso_orbits = 0;


		if (f_v) {
			cout << "classification_of_varieties::init "
					"before classify_nauty" << endl;
		}
		classify_nauty(verbose_level - 1);
		if (f_v) {
			cout << "classification_of_varieties::init "
					"after classify_nauty" << endl;
		}

		if (f_v) {
			cout << "classification_of_varieties::init "
					"before finalize_classification_by_nauty" << endl;
		}
		finalize_classification_by_nauty(verbose_level - 1);
		if (f_v) {
			cout << "classification_of_varieties::init "
					"after finalize_classification_by_nauty" << endl;
		}

	}
#if 0
	else if (Classifier->get_description()->f_algorithm_substructure) {


		if (f_v) {
			cout << "classification_of_varieties::init "
					"algorithm substructure" << endl;
		}

		cout << "classification_of_varieties::init "
				"algorithm substructure not available" << endl;
		exit(1);



#if 0
		Canonical_equation = NEW_int(Classifier->Input->nb_objects_to_test
				* Classifier->Ring_with_action->Poly_ring->get_nb_monomials());

		if (f_v) {
			cout << "classification_of_varieties::init "
					"before classify_with_substructure" << endl;
		}
		classify_with_substructure(
				verbose_level - 1);
		if (f_v) {
			cout << "classification_of_varieties::init "
					"after classify_with_substructure" << endl;
		}

		if (f_v) {
			cout << "classification_of_varieties::init "
					"before finalize_canonical_forms" << endl;
		}
		finalize_canonical_forms(
					verbose_level);
		if (f_v) {
			cout << "classification_of_varieties::init "
					"after finalize_canonical_forms" << endl;
		}
#endif

	}
#endif
	else {
		cout << "classification_of_varieties::init "
				"please select which algorithm to use" << endl;
		exit(1);
	}



#if 0
	if (f_v) {
		cout << "classification_of_varieties::init "
				"before generate_source_code" << endl;
	}

	generate_source_code(
			Descr->fname_base_out,
			verbose_level);

	if (f_v) {
		cout << "classification_of_varieties::init "
				"after generate_source_code" << endl;
	}
#endif

}



void classification_of_varieties::classify_nauty(
		int verbose_level)
{
	int f_v = (verbose_level >= 1);


	if (f_v) {
		cout << "classification_of_varieties::classify_nauty" << endl;
	}
	if (f_v) {
		cout << "classification_of_varieties::classify_nauty" << endl;
		cout << "classification_of_varieties::classify_nauty "
				"nb_objects_to_test = " << Classifier->Input->nb_objects_to_test << endl;
	}


	CB = NEW_OBJECT(canonical_form_classification::classify_bitvectors);




	if (f_v) {
		cout << "classification_of_varieties::classify_nauty "
				"before main_loop" << endl;
	}
	main_loop(verbose_level);
	if (f_v) {
		cout << "classification_of_varieties::classify_nauty "
				"after main_loop" << endl;
	}

	if (f_v) {
		cout << "classification_of_varieties::classify_nauty "
				"The number of graph theoretic canonical forms is "
				<< CB->nb_types << endl;
	}


}

#if 0
void classification_of_varieties::classify_with_substructure(
		int verbose_level)
{
	int f_v = (verbose_level >= 1);


	if (f_v) {
		cout << "classification_of_varieties::classify_with_substructure, "
				"Descr->substructure_size="
				<< Classifier->get_description()->substructure_size << endl;
	}




	SubC = NEW_OBJECT(set_stabilizer::substructure_classifier);

	if (f_v) {
		cout << "classification_of_varieties::classify_with_substructure "
				"before SubC->classify_substructures" << endl;
	}

	SubC->classify_substructures(
			Classifier->get_description()->fname_base_out,
			Classifier->Ring_with_action->PA->A,
			Classifier->Ring_with_action->PA->A,
			Classifier->Ring_with_action->PA->A->Strong_gens,
			Classifier->get_description()->substructure_size,
			verbose_level - 3);

	if (f_v) {
		cout << "classification_of_varieties::classify_with_substructure "
				"after SubC->classify_substructures" << endl;
		cout << "classification_of_varieties::classify_with_substructure "
				"We found " << SubC->nb_orbits
				<< " orbits at level "
				<< Classifier->get_description()->substructure_size << ":" << endl;
	}



	CFS_table = (canonical_form_substructure **)
			NEW_pvoid(Classifier->Input->nb_objects_to_test);



	if (f_v) {
		cout << "classification_of_varieties::classify_with_substructure "
				"before main_loop" << endl;
	}
	main_loop(verbose_level);
	if (f_v) {
		cout << "classification_of_varieties::classify_with_substructure "
				"after main_loop" << endl;
	}



	if (f_v) {
		cout << "classification_of_varieties::classify_with_substructure done" << endl;
	}

}
#endif

void classification_of_varieties::main_loop(
		int verbose_level)
{
	int f_v = (verbose_level >= 1);



	if (f_v) {
		cout << "classification_of_varieties::main_loop" << endl;
		cout << "classification_of_varieties::main_loop "
				"nb_objects_to_test = " << Classifier->Input->nb_objects_to_test << endl;
	}


	int input_counter;
	int nb_iso = 0;

	for (input_counter = 0; input_counter < Classifier->Input->nb_objects_to_test; input_counter++) {


		string fname_case_out;

		fname_case_out = Classifier->get_description()->fname_base_out + "_cnt" + std::to_string(input_counter);

		variety_compute_canonical_form *Variety;

		Variety = NEW_OBJECT(variety_compute_canonical_form);

		if (f_v) {
			cout << "classification_of_varieties::main_loop "
					"input_counter = " << input_counter << " / " << Classifier->Input->nb_objects_to_test
					<< " before Variety->init" << endl;
		}
		Variety->init(
				Classifier,
				Classifier->Ring_with_action,
				Classifier->Classification_of_varieties_nauty,
				fname_case_out,
				input_counter,
				Classifier->Input->Vo[input_counter],
				verbose_level - 2);



		if (f_v) {
			cout << "classification_of_varieties::main_loop "
					"input_counter = " << input_counter << " / " << Classifier->Input->nb_objects_to_test
					<< " after Variety->init" << endl;
		}

		Variety_table[input_counter] = Variety;


		if (Classifier->get_description()->f_algorithm_nauty) {

			if (f_v) {
				cout << "classification_of_varieties::main_loop "
						"input_counter = " << input_counter << " / " << Classifier->Input->nb_objects_to_test << endl;
			}

			if (Classifier->Input->skip_this_one(input_counter)) {
				if (f_v) {
					cout << "classification_of_varieties::main_loop "
							"skipping case input_counter = " << input_counter << endl;
				}
				//Variety_table[input_counter] = NULL;
				Iso_idx[input_counter] = -1;
				F_first_time[input_counter] = false;
				Goi[input_counter] = -1;
				//continue;
			}
			else {

				if (f_v) {
					cout << "classification_of_varieties::main_loop "
							"input_counter = " << input_counter << " / " << Classifier->Input->nb_objects_to_test
							<< " before Variety->compute_canonical_form_nauty_new" << endl;
				}
				Variety->compute_canonical_form_nauty_new(
						Classifier->get_description()->f_save_nauty_input_graphs,
						verbose_level);


				if (f_v) {
					cout << "classification_of_varieties::main_loop "
							"input_counter = " << input_counter << " / " << Classifier->Input->nb_objects_to_test
							<< " after Variety->compute_canonical_form_nauty_new" << endl;
				}

				Goi[input_counter] = Variety->Variety_stabilizer_compute->Stab_gens_variety->group_order_as_lint();

				if (Variety->Variety_stabilizer_compute->f_found_canonical_form
						&& Variety->Variety_stabilizer_compute->f_found_eqn) {

					F_first_time[input_counter] = false;

				}
				else if (Variety->Variety_stabilizer_compute->f_found_canonical_form
						&& !Variety->Variety_stabilizer_compute->f_found_eqn) {

					F_first_time[input_counter] = true;

				}
				else if (!Variety->Variety_stabilizer_compute->f_found_canonical_form) {

					F_first_time[input_counter] = true;

				}
				else {
					cout << "classification_of_varieties::main_loop illegal combination" << endl;
					exit(1);
				}

				Idx_canonical_form[input_counter] = Variety->Variety_stabilizer_compute->idx_canonical_form;
				Idx_equation[input_counter] = Variety->Variety_stabilizer_compute->idx_equation;

				if (F_first_time[input_counter]) {


					Iso_idx[input_counter] = nb_iso;

					int idx, i;


					for (i = 0; i < input_counter; i++) {
						idx = Idx_canonical_form[i];
						if (idx >= Variety->Variety_stabilizer_compute->idx_canonical_form) {
							Idx_canonical_form[i]++;
						}
					}

					Orbit_input_idx[nb_iso_orbits] = input_counter;
					nb_iso_orbits++;

					nb_iso++;

				}
				else {
					Iso_idx[input_counter] = Iso_idx[Idx_canonical_form[input_counter]];
				}
			}

		}
#if 0
		else if (Classifier->get_description()->f_algorithm_substructure) {

			if (f_v) {
				cout << "classification_of_varieties::main_loop "
						"input_counter = " << input_counter << " / " << Classifier->Input->nb_objects_to_test
						<< " before Variety->compute_canonical_form_substructure" << endl;
			}

			cout << "classification_of_varieties::main_loop algorithm_substructure is no longer supported" << endl;
			exit(1);

#if 0
			Variety->compute_canonical_form_substructure(
					verbose_level - 1);
#endif
			if (f_v) {
				cout << "classification_of_varieties::main_loop "
						"input_counter = " << input_counter << " / " << Classifier->Input->nb_objects_to_test
						<< " after Variety->compute_canonical_form_substructure" << endl;
			}

		}
#endif
		else {
			cout << "please select which algorithm to use" << endl;
			exit(1);
		}


		// Don't free Qco, because it is now stored in Variety_table[]
		//FREE_OBJECT(Qco);

	}

	if (f_v) {
		cout << "classification_of_varieties::main_loop done" << endl;
	}
}






void classification_of_varieties::report(
		poset_classification::poset_classification_report_options *Opt,
		int verbose_level)
{

	int f_v = (verbose_level >= 1);

	if (f_v) {
		cout << "classification_of_varieties::report" << endl;
	}

	string label;
	string fname;

	if (Opt->f_fname) {
		label.assign(Opt->fname);
	}
	else {
		label.assign("report");
	}


	fname = label;
	fname += "_orbits.tex";



	{
		ofstream ost(fname);
		l1_interfaces::latex_interface L;

		L.head_easy(ost);


		if (Classifier->get_description()->f_algorithm_nauty) {

			if (f_v) {
				cout << "classification_of_varieties::report "
						"before report_nauty" << endl;
			}

			report_nauty(ost, verbose_level);
			if (f_v) {
				cout << "classification_of_varieties::report "
						"after report_nauty" << endl;
			}

		}
#if 0
		else if (Classifier->get_description()->f_algorithm_substructure) {
			if (f_v) {
				cout << "classification_of_varieties::report "
						"before report_substructure" << endl;
			}

			cout << "classification_of_varieties::report "
					"report_substructure is not available" << endl;
			exit(1);

			//report_substructure(ost, verbose_level);
			if (f_v) {
				cout << "classification_of_varieties::report "
						"after report_substructure" << endl;
			}
		}
#endif

		L.foot(ost);
	}



	orbiter_kernel_system::file_io Fio;

	if (f_v) {
		cout << "Written file " << fname << " of size "
			<< Fio.file_size(fname) << endl;
	}


	{
		string fname_data;

		fname_data = label + "_canonical_form_data.csv";


		if (f_v) {
			cout << "classification_of_varieties::report "
					"before export_canonical_form_data" << endl;
		}
		export_canonical_form_data(
				fname_data, verbose_level);
		if (f_v) {
			cout << "classification_of_varieties::report "
					"after export_canonical_form_data" << endl;
		}

		if (f_v) {
			cout << "Written file " << fname_data << " of size "
					<< Fio.file_size(fname_data) << endl;
		}
	}
	if (f_v) {
		cout << "classification_of_varieties::report done" << endl;
	}

}

void classification_of_varieties::report_nauty(
		std::ostream &ost, int verbose_level)
{

	int f_v = (verbose_level >= 1);

	if (f_v) {
		cout << "classification_of_varieties::report_nauty" << endl;
	}


	int orbit_index;
	int nb_orbits;

	if (f_v) {
		cout << "classification_of_varieties::report_nauty" << endl;
	}


	nb_orbits = nb_iso_orbits;


	int idx;

	{


		ost << "Classification\\\\" << endl;
		ost << "$q=" << Classifier->Ring_with_action->PA->F->q << "$\\\\" << endl;
		ost << "Number of isomorphism classes: " << nb_orbits << "\\\\" << endl;


		std::vector<long int> Ago;

		for (orbit_index = 0;
				orbit_index < nb_orbits;
				orbit_index++) {
			idx = Orbit_input_idx[orbit_index];


			Ago.push_back(Goi[idx]);
		}

		data_structures::tally_lint T;

		T.init_vector_lint(
				Ago,
				false /* f_second */,
				0 /* verbose_level */);
		ost << "Automorphism group order statistic: " << endl;
		//ost << "$";
		T.print_file_tex(ost, true /* f_backwards */);
		ost << "\\\\" << endl;


		ost << endl;
		ost << "\\bigskip" << endl;
		ost << endl;


		if (f_v) {
			cout << "classification_of_varieties::report_nauty "
					"preparing reps" << endl;
		}
		ost << "The isomorphism classes are:\\\\" << endl;
		for (orbit_index = 0;
				orbit_index < nb_orbits;
				orbit_index++) {

			idx = Orbit_input_idx[orbit_index];

			//int *equation;

			if (f_v) {
				cout << "classification_of_varieties::report_nauty "
						"orbit_index = " << orbit_index << endl;
			}

			ost << "Isomorphism class " << orbit_index << " / " << nb_orbits << " is input " << idx << ":\\\\" << endl;
			ost << "Automorphism group order " << Goi[idx] << "\\\\" << endl;


			variety_object_with_action *Vo;
				// [nb_objects_to_test]

			Vo = Classifier->Input->Vo[idx];

			ost << "Number of points " << Vo->Variety_object->Point_sets->Set_size[0] << "\\\\" << endl;

			Vo->Variety_object->report_equations(ost);

			ost << "Points:\\\\" << endl;
			Classifier->Ring_with_action->PA->P->Reporting->print_set_of_points_easy(
					ost,
					Vo->Variety_object->Point_sets->Sets[0],
					Vo->Variety_object->Point_sets->Set_size[0]);

			Variety_table[idx]->Variety_stabilizer_compute->report(ost);


			ost << endl;
			ost << "\\bigskip" << endl;
			ost << endl;


			combinatorics_with_groups::combinatorics_with_action CombiA;
			int size_limit_for_printing = 50;
			groups::strong_generators *gens;

			gens = Variety_table[idx]->Variety_stabilizer_compute->Stab_gens_variety;


			if (f_v) {
				cout << "classification_of_varieties::report_nauty "
						"before CombiA.report_TDO_and_TDA_projective_space" << endl;
			}
			CombiA.report_TDO_and_TDA_projective_space(
					ost,
					Classifier->Ring_with_action->PA->P,
					Vo->Variety_object->Point_sets->Sets[0],
					Vo->Variety_object->Point_sets->Set_size[0],
					Classifier->Ring_with_action->PA->A,
					Classifier->Ring_with_action->PA->A_on_lines,
					gens, size_limit_for_printing,
					verbose_level);
			if (f_v) {
				cout << "classification_of_varieties::report_nauty "
						"after CombiA.report_TDO_and_TDA_projective_space" << endl;
			}


		}
	}
	if (f_v) {
		cout << "classification_of_varieties::report_nauty done" << endl;
	}
}


#if 0
void classification_of_varieties::report_substructure(
		std::ostream &ost, int verbose_level)
{

	int f_v = (verbose_level >= 1);

	if (f_v) {
		cout << "classification_of_varieties::report_substructure" << endl;
	}


	int orbit_index;
	//int i, j;

	int nb_orbits;
	int nb_monomials;

	//actions::action *A;
	//actions::action *A_on_lines;

	if (f_v) {
		cout << "classification_of_varieties::report_substructure" << endl;
	}


	nb_orbits = Tally->nb_types;
	nb_monomials = Classifier->Ring_with_action->Poly_ring->get_nb_monomials();


	//A = Descr->PA->A;
	//A_on_lines = Descr->PA->A_on_lines;


	int idx;

	{


		ost << "Classification\\\\" << endl;
		ost << "$q=" << Classifier->Ring_with_action->PA->F->q << "$\\\\" << endl;
		ost << "Number of isomorphism classes: " << nb_orbits << "\\\\" << endl;


		std::vector<long int> Ago;

		for (orbit_index = 0;
				orbit_index < nb_orbits;
				orbit_index++) {
			idx = Tally->sorting_perm_inv[Tally->type_first[orbit_index]];


			Ago.push_back(Goi[idx]);
		}

		data_structures::tally_lint T;

		T.init_vector_lint(
				Ago,
				false /* f_second */,
				0 /* verbose_level */);
		ost << "Automorphism group order statistic: " << endl;
		//ost << "$";
		T.print_file_tex(ost, true /* f_backwards */);
		ost << "\\\\" << endl;


		ost << endl;
		ost << "\\bigskip" << endl;
		ost << endl;


		if (f_v) {
			cout << "classification_of_varieties::report_substructure "
					"preparing reps" << endl;
		}
		ost << "The isomorphism classes are:\\\\" << endl;
		for (orbit_index = 0;
				orbit_index < nb_orbits;
				orbit_index++) {


			int *equation;

			if (f_v) {
				cout << "classification_of_varieties::report_substructure "
						"orbit_index = " << orbit_index << endl;
			}

			ost << "Isomorphism class " << orbit_index << " / " << nb_orbits << ":\\\\" << endl;


			idx = Tally->sorting_perm_inv[Tally->type_first[orbit_index]];



			if (Variety_table[idx]) {


				ost << "Number of rational points over "
						"$\\bbF_{" << Classifier->Ring_with_action->PA->F->q << "}$: ";
				ost << Variety_table[idx]->Vo->Variety_object->Point_sets->Set_size[0];
				ost << "\\\\" << endl;


				equation = Variety_table[idx]->canonical_equation;

				ost << "Canonical equation:" << endl;
				ost << "\\begin{eqnarray*}" << endl;

				//Poly_ring->print_equation_tex(ost, equation);

				Classifier->Ring_with_action->Poly_ring->print_equation_with_line_breaks_tex(
						ost, equation, 7, "\\\\");

				ost << "\\end{eqnarray*}" << endl;

				Int_vec_print(ost, equation, nb_monomials);
				ost << "\\\\" << endl;

			}
			else {
				ost << "Data not available.\\\\" << endl;

			}

			ring_theory::longinteger_object ago;

			//int idx;

			idx = Tally->sorting_perm_inv[Tally->type_first[orbit_index]];


			ago.create(Goi[idx]);

			ost << "Stabilizer order: ";

			ago.print_not_scientific(ost);
			ost << "\\\\" << endl;

			groups::strong_generators *gens;

			if (Variety_table[idx]) {
				gens = Variety_table[idx]->gens_stab_of_canonical_equation;

				ost << "The stabilizer: \\\\" << endl;
				gens->print_generators_tex(ost);
			}
			else {
				ost << "Data not available.\\\\" << endl;

			}




		}

	}


	if (f_v) {
		cout << "classification_of_varieties::report_substructure done" << endl;
	}
}
#endif

void classification_of_varieties::export_canonical_form_data(
		std::string &fname, int verbose_level)
{
	int f_v = (verbose_level >= 1);

	if (f_v) {
		cout << "classification_of_varieties::export_canonical_form_data" << endl;
	}

	int i;
	int nb_rows = Classifier->Input->nb_objects_to_test;
	int nb_cols_max = 50;


	string *Headers;

	Headers = new string[nb_cols_max];

	int c;
	int nb_cols;
	int idx_po, idx_so, idx_nb_pts; //, idx_sub = -1;
	c = 0;
	Headers[c++] = "Line";
	Headers[c++] = "CNT";
	if (Classifier->get_description()->f_label_po) {
		idx_po = c;
		Headers[c++] = "PO";
	}
	else {
		idx_po = -1;
	}
	if (Classifier->get_description()->f_label_so) {
		idx_so = c;
		Headers[c++] = "SO";
	}
	else {
		idx_so = -1;
	}
	idx_nb_pts = c;
	Headers[c++] = "nb_pts";



	int idx_eqn;


	if (Classifier->get_description()->f_algorithm_nauty) {
	}
#if 0
	else if (Classifier->get_description()->f_algorithm_substructure) {


		//idx_sub = c;
		Headers[c++] = "nb_sub_orbs";
		Headers[c++] = "frequencies";
		Headers[c++] = "nb_types";
		Headers[c++] = "selected_type";
		Headers[c++] = "selected_orbit";
		Headers[c++] = "selected_frequency";
		Headers[c++] = "go_min";
		Headers[c++] = "set_stabilizer_order";
		Headers[c++] = "reduced_set_size";
		Headers[c++] = "nb_interesting_subsets";
		Headers[c++] = "nb_interesting_subsets_reduced";
		Headers[c++] = "nb_interesting_subsets_rr";
		Headers[c++] = "nb_orbits";
		Headers[c++] = "nb_interesting_orbits";
		Headers[c++] = "nb_interesting_points";
		Headers[c++] = "orbit_length_under_set_stab";
	}
#endif

	idx_eqn = c;
	Headers[c++] = "stab_of_eqn";

	nb_cols = c;

	string *Table;

	Table = new string[nb_rows * nb_cols];

	for (i = 0; i < nb_rows; i++) {

		cout << "canonical_form_classifier::export_canonical_form_data "
				"i=" << i << " / " << Classifier->Input->nb_objects_to_test << endl;

		Table[i * nb_cols + 0] = std::to_string(i);


		if (Variety_table[i]) {

			Table[i * nb_cols + 1] = std::to_string(Variety_table[i]->Vo->cnt);
			if (idx_po >= 0) {
				Table[i * nb_cols + idx_po] = std::to_string(Variety_table[i]->Vo->po);
			}
			if (idx_so >= 0) {
				Table[i * nb_cols + idx_so] = std::to_string(Variety_table[i]->Vo->so);
			}
			Table[i * nb_cols + idx_nb_pts] = std::to_string(Variety_table[i]->Vo->Variety_object->Point_sets->Set_size[0]);

			if (Classifier->get_description()->f_algorithm_nauty) {

			}
#if 0
			else if (Classifier->get_description()->f_algorithm_substructure) {

				cout << "test 1" << endl;
#if 0
				if (CFS_table) {
					Table[i * nb_cols + idx_sub + 0] = std::to_string(SubC->nb_orbits);

					//cout << "i=" << i << " getting orbit_frequencies" << endl;


					string str;

					Int_vec_create_string_with_quotes(str, CFS_table[i]->SubSt->orbit_frequencies, SubC->nb_orbits);

					Table[i * nb_cols + idx_sub + 1] = str;

					//cout << "i=" << i << " getting orbit_frequencies part 3" << endl;


					cout << "test 2" << endl;
					Table[i * nb_cols + idx_sub + 2] = std::to_string(CFS_table[i]->SubSt->nb_types);
					Table[i * nb_cols + idx_sub + 3] = std::to_string(CFS_table[i]->SubSt->selected_type);
					Table[i * nb_cols + idx_sub + 4] = std::to_string(CFS_table[i]->SubSt->selected_orbit);
					Table[i * nb_cols + idx_sub + 5] = std::to_string(CFS_table[i]->SubSt->selected_frequency);
					Table[i * nb_cols + idx_sub + 6] = std::to_string(CFS_table[i]->SubSt->gens->group_order_as_lint());
					Table[i * nb_cols + idx_sub + 7] = std::to_string(CFS_table[i]->Gens_stabilizer_original_set->group_order_as_lint());
					Table[i * nb_cols + idx_sub + 8] = std::to_string(CFS_table[i]->CS->Stab_orbits->reduced_set_size);
					Table[i * nb_cols + idx_sub + 9] = std::to_string(CFS_table[i]->SubSt->nb_interesting_subsets);
					Table[i * nb_cols + idx_sub + 10] = std::to_string(CFS_table[i]->CS->Stab_orbits->nb_interesting_subsets_reduced);
					Table[i * nb_cols + idx_sub + 11] = std::to_string(CFS_table[i]->CS->nb_interesting_subsets_rr);
					Table[i * nb_cols + idx_sub + 12] = std::to_string(CFS_table[i]->CS->Stab_orbits->nb_orbits);
					Table[i * nb_cols + idx_sub + 13] = std::to_string(CFS_table[i]->CS->Stab_orbits->nb_interesting_orbits);
					Table[i * nb_cols + idx_sub + 14] = std::to_string(CFS_table[i]->CS->Stab_orbits->nb_interesting_points);
					Table[i * nb_cols + idx_sub + 15] = std::to_string(CFS_table[i]->Orb->used_length);
				}
#endif

			}
#endif



		}


		cout << "test 3" << endl;
		Table[i * nb_cols + idx_eqn] = std::to_string(Variety_table[i]->gens_stab_of_canonical_equation->group_order_as_lint());



	}
	if (f_v) {
		cout << "classification_of_varieties::export_canonical_form_data "
				"finished collecting Table" << endl;
	}

	int j;
	string headings;

	for (j = 0; j < nb_cols; j++) {
		headings += Headers[j];
		if (j < nb_cols - 1) {
			headings += ",";
		}
	}

	orbiter_kernel_system::file_io Fio;

	if (f_v) {
		cout << "classification_of_varieties::export_canonical_form_data "
				"before Fio.Csv_file_support->write_table_of_strings" << endl;
	}
	Fio.Csv_file_support->write_table_of_strings(
			fname,
			nb_rows, nb_cols, Table,
			headings,
			verbose_level);

	if (f_v) {
		cout << "classification_of_varieties::export_canonical_form_data "
				"after Fio.Csv_file_support->write_table_of_strings" << endl;
	}

	delete [] Table;
	delete [] Headers;

	if (f_v) {
		cout << "classification_of_varieties::export_canonical_form_data done" << endl;
	}

}

void classification_of_varieties::generate_source_code(
		std::string &fname_base,
		int verbose_level)
{
	int f_v = (verbose_level >= 1);
	int f_vv = (verbose_level >= 2);
	std::string fname;
	int orbit_index;
	int i;

	int nb_orbits;
	int nb_monomials;

	actions::action *A;
	//actions::action *A_on_lines;

	if (f_v) {
		cout << "classification_of_varieties::generate_source_code" << endl;
	}


#if 0
	if (!Descr->f_algorithm_substructure) {
		cout << "classification_of_varieties::generate_source_code skipping because "
				"we did not use substructure classification" << endl;
		return;
	}
#endif

	fname = fname_base + ".cpp";


	nb_orbits = Tally->nb_types;
	nb_monomials = Classifier->Ring_with_action->Poly_ring->get_nb_monomials();


	A = Classifier->Ring_with_action->PA->A;
	//A_on_lines = Classifier->PA->A_on_lines;

	{
		ofstream f(fname);

		f << "static int " << fname_base << "_nb_reps = "
				<< nb_orbits << ";" << endl;
		f << "static int " << fname_base << "_size = "
				<< nb_monomials << ";" << endl;



		if (f_v) {
			cout << "classification_of_varieties::generate_source_code "
					"preparing reps" << endl;
		}
		f << "// the equations:" << endl;
		f << "static int " << fname_base << "_reps[] = {" << endl;
		for (orbit_index = 0;
				orbit_index < nb_orbits;
				orbit_index++) {


			int *equation;

			if (f_v) {
				cout << "classification_of_varieties::generate_source_code "
						"orbit_index = " << orbit_index << endl;
			}

			int idx;

			idx = Tally->sorting_perm_inv[Tally->type_first[orbit_index]];


			//canonical_form_substructure *CFS = Variety_table[idx];


			if (Variety_table[idx]) {
				//equation = Classification_of_quartic_curves->Reps + orbit_index * Classification_of_quartic_curves->data_set_sz;
				equation = Variety_table[idx]->canonical_equation;

				f << "\t";
				for (i = 0; i < nb_monomials; i++) {
					f << equation[i];
					f << ", ";
				}
				f << endl;
			}
			else {
				f << "\t";
				for (i = 0; i < nb_monomials; i++) {
					f << 0;
					f << ", ";
				}
				f << "// problem" << endl;

			}

		}
		f << "};" << endl;



		if (f_v) {
			cout << "classification_of_varieties::generate_source_code "
					"preparing stab_order" << endl;
		}
		f << "// the stabilizer orders:" << endl;
		f << "static const char *" << fname_base << "_stab_order[] = {" << endl;
		for (orbit_index = 0;
				orbit_index < nb_orbits;
				orbit_index++) {

			ring_theory::longinteger_object ago;

			int idx;

			idx = Tally->sorting_perm_inv[Tally->type_first[orbit_index]];


			ago.create(Goi[idx]);

			f << "\t\"";

			ago.print_not_scientific(f);
			f << "\"," << endl;

		}
		f << "};" << endl;




#if 0
		if (f_v) {
			cout << "classification_of_varieties::generate_source_code "
					"preparing Bitangents" << endl;
		}
		f << "// the 28 bitangents:" << endl;
		f << "static long int " << fname_base << "_Bitangents[] = { " << endl;


		for (orbit_index = 0;
				orbit_index < nb_orbits;
				orbit_index++) {


			if (f_v) {
				cout << "classification_of_varieties::generate_source_code "
						"orbit_index = " << orbit_index << endl;
			}

			int idx;

			idx = Tally->sorting_perm_inv[Tally->type_first[orbit_index]];

			//canonical_form_substructure *CFS = Variety_table[idx];


			if (Variety_table[idx]) {
				long int *bitangents_orig;
				long int *bitangents_canonical;

				bitangents_orig = Variety_table[idx]->Qco->Quartic_curve_object->bitangents28;
				bitangents_canonical = NEW_lint(28);
				for (j = 0; j < 28; j++) {
					bitangents_canonical[j] =
							A_on_lines->Group_element->element_image_of(
									bitangents_orig[j],
							Variety_table[idx]->transporter_to_canonical_form,
							0 /* verbose_level */);
				}




				f << "\t";
				for (j = 0; j < 28; j++) {
					f << bitangents_canonical[j];
					f << ", ";
				}
				f << endl;
			}
			else {
				f << "\t";
				for (j = 0; j < 28; j++) {
					f << 0;
					f << ", ";
				}
				f << "// problem" << endl;

			}

		}
		f << "};" << endl;
#endif

		f << "static int " << fname_base << "_make_element_size = "
				<< A->make_element_size << ";" << endl;

		{
			int *stab_gens_first;
			int *stab_gens_len;
			int fst;



			stab_gens_first = NEW_int(nb_orbits);
			stab_gens_len = NEW_int(nb_orbits);
			fst = 0;
			for (orbit_index = 0;
					orbit_index < nb_orbits;
					orbit_index++) {


				groups::strong_generators *gens;

				int idx;

				idx = Tally->sorting_perm_inv[Tally->type_first[orbit_index]];

				//canonical_form_substructure *CFS = CFS_table[idx];
				//gens = CFS->Gens_stabilizer_canonical_form;
				if (Variety_table[idx]) {
					gens = Variety_table[idx]->gens_stab_of_canonical_equation;


					if (gens) {
						stab_gens_first[orbit_index] = fst;
						stab_gens_len[orbit_index] = gens->gens->len;
						fst += stab_gens_len[orbit_index];
					}
					else {
						cout << "classification_of_varieties::generate_source_code "
								"gens not available" << endl;
						stab_gens_first[orbit_index] = fst;
						stab_gens_len[orbit_index] = 0;
						fst += stab_gens_len[orbit_index];
					}
				}
				else {
					stab_gens_first[orbit_index] = fst;
					stab_gens_len[orbit_index] = 0;
					fst += 0;

				}
			}


			if (f_v) {
				cout << "classification_of_varieties::generate_source_code "
						"preparing stab_gens_fst" << endl;
			}
			f << "static int " << fname_base << "_stab_gens_fst[] = { " << endl << "\t";
			for (orbit_index = 0;
					orbit_index < nb_orbits;
					orbit_index++) {
				f << stab_gens_first[orbit_index];
				if (orbit_index < nb_orbits - 1) {
					f << ", ";
				}
				if (((orbit_index + 1) % 10) == 0) {
					f << endl << "\t";
				}
			}
			f << "};" << endl;

			if (f_v) {
				cout << "classification_of_varieties::generate_source_code "
						"preparing stab_gens_len" << endl;
			}
			f << "static int " << fname_base << "_stab_gens_len[] = { " << endl << "\t";
			for (orbit_index = 0;
					orbit_index < nb_orbits;
					orbit_index++) {
				f << stab_gens_len[orbit_index];
				if (orbit_index < nb_orbits - 1) {
					f << ", ";
				}
				if (((orbit_index + 1) % 10) == 0) {
					f << endl << "\t";
				}
			}
			f << "};" << endl;


			if (f_v) {
				cout << "classification_of_varieties::generate_source_code "
						"preparing stab_gens" << endl;
			}
			f << "static int " << fname_base << "_stab_gens[] = {" << endl;
			for (orbit_index = 0;
					orbit_index < nb_orbits;
					orbit_index++) {
				int j;

				for (j = 0; j < stab_gens_len[orbit_index]; j++) {
					if (f_vv) {
						cout << "classification_of_varieties::generate_source_code "
								"before extract_strong_generators_in_order "
								"generator " << j << " / "
								<< stab_gens_len[orbit_index] << endl;
					}
					f << "\t";

					groups::strong_generators *gens;

					int idx;

					idx = Tally->sorting_perm_inv[Tally->type_first[orbit_index]];

					//canonical_form_substructure *CFS = CFS_table[idx];
					//gens = CFS->Gens_stabilizer_canonical_form;
					if (Variety_table[idx]) {
						gens = Variety_table[idx]->gens_stab_of_canonical_equation;


						if (gens) {
							A->Group_element->element_print_for_make_element(
									gens->gens->ith(j), f);
							f << endl;
						}
						else {
							cout << "classification_of_varieties::generate_source_code "
									"gens are not available" << endl;
						}
					}
					else {
						f << "// problem" << endl;
					}
				}
			}
			f << "};" << endl;


			FREE_int(stab_gens_first);
			FREE_int(stab_gens_len);
		}
	}

	orbiter_kernel_system::file_io Fio;

	cout << "written file " << fname << " of size "
			<< Fio.file_size(fname.c_str()) << endl;
	if (f_v) {
		cout << "classification_of_varieties::generate_source_code done" << endl;
	}
}

void classification_of_varieties::write_classification_by_nauty_csv(
		std::string &fname_base,
		int verbose_level)
{
	int f_v = (verbose_level >= 1);
	std::string fname;


	if (f_v) {
		cout << "classification_of_varieties::write_classification_by_nauty_csv" << endl;
	}
	fname = fname_base + "_classification_by_nauty.csv";



	{
		ofstream ost(fname);


		string header;

		header = stringify_csv_header_line_nauty(verbose_level);
		ost << header << endl;

		int input_counter;

		for (input_counter = 0; input_counter < Classifier->Input->nb_objects_to_test; input_counter++) {

			if (f_v) {
				cout << "classification_of_varieties::write_classification_by_nauty_csv "
						"input_counter=" << input_counter << " / " << Classifier->Input->nb_objects_to_test << endl;
			}

			string line;

			line = Variety_table[input_counter]->stringify_csv_entry_one_line_nauty(
					input_counter, verbose_level);

			ost << input_counter << "," << line << endl;


		}
		ost << "END" << endl;
	}


	orbiter_kernel_system::file_io Fio;

	cout << "written file " << fname << " of size "
			<< Fio.file_size(fname) << endl;
	if (f_v) {
		cout << "classification_of_varieties::write_classification_by_nauty_csv done" << endl;
	}
}

void classification_of_varieties::write_canonical_forms_csv(
		std::string &fname_base,
		int verbose_level)
{
	int f_v = (verbose_level >= 1);
	std::string fname;
	int i;

	int nb_monomials;


	if (f_v) {
		cout << "classification_of_varieties::write_canonical_forms_csv" << endl;
	}
	fname = fname_base + "_canonical_form.csv";


	nb_monomials = Classifier->Ring_with_action->Poly_ring->get_nb_monomials();
	if (f_v) {
		cout << "classification_of_varieties::write_canonical_forms_csv "
				"nb_monomials = " << nb_monomials << endl;
	}



	{
		ofstream ost(fname);

		string header;

		header = stringify_csv_header(verbose_level);
		ost << header << endl;


		for (i = 0; i < Classifier->Input->nb_objects_to_test; i++) {

			if (f_v) {
				cout << "classification_of_varieties::write_canonical_forms_csv "
						"i=" << i << " / " << Classifier->Input->nb_objects_to_test << endl;
			}

			string line;

			line = Variety_table[i]->stringify_csv_entry_one_line_nauty_new(
					i, verbose_level);

			ost << i << "," << line << endl;

		}
		ost << "END" << endl;
	}


	orbiter_kernel_system::file_io Fio;

	cout << "written file " << fname << " of size "
			<< Fio.file_size(fname) << endl;
	if (f_v) {
		cout << "classification_of_varieties::write_canonical_forms_csv done" << endl;
	}
}



std::string classification_of_varieties::stringify_csv_header(
		int verbose_level)
{
	int f_v = (verbose_level >= 1);

	if (f_v) {
		cout << "canonical_form_of_variety::stringify_csv_header" << endl;
	}
	string header;

	header = "ROW,CNT,PO,SO,PO_GO,PO_INDEX,Iso,Eqn,Eqn2,NPts,Pts,Bitangents,"
			"Transporter,CanEqn,CanPts,CanLines,AutTl,AutGens,Ago";

	if (Classifier->has_description()) {
		if (Classifier->get_description()->carry_through.size()) {
			int i;

			for (i = 0; i < Classifier->get_description()->carry_through.size(); i++) {
				header += "," + Classifier->get_description()->carry_through[i];
			}
		}
	}
	return header;

}

std::string classification_of_varieties::stringify_csv_header_line_nauty(
		int verbose_level)
{
	int f_v = (verbose_level >= 1);

	if (f_v) {
		cout << "canonical_form_of_variety::stringify_csv_header_line_nauty" << endl;
	}

	std::string header;

	header = "ROW,CNT,PO,SO,PO_GO,PO_INDEX,Iso_idx,F_Fst,Idx_canonical,Idx_eqn,Eqn,Eqn2,NPts,Pts,Bitangents";

	if (Classifier->get_description()->carry_through.size()) {
		int i;

		for (i = 0; i < Classifier->get_description()->carry_through.size(); i++) {
			header += "," + Classifier->get_description()->carry_through[i];
		}
	}

	header += ",NO_N,NO_ago,NO_base_len,NO_aut_cnt,NO_base,NO_tl,NO_aut,NO_cl,NO_stats";
	header += ",nb_eqn,ago";

	return header;
}

void classification_of_varieties::finalize_classification_by_nauty(
		int verbose_level)
{
	int f_v = (verbose_level >= 1);


	if (f_v) {
		cout << "classification_of_varieties::finalize_classification_by_nauty" << endl;
	}


	if (f_v) {
		cout << "classification_of_varieties::finalize_classification_by_nauty "
				"before make_classification_table_nauty" << endl;
	}

	make_classification_table_nauty(
			Classification_table_nauty,
			verbose_level);

	if (f_v) {
		cout << "classification_of_varieties::finalize_classification_by_nauty "
				"after make_classification_table_nauty" << endl;
	}


	if (f_v) {
		cout << "classification_of_varieties::finalize_classification_by_nauty "
				"before write_classification_by_nauty_csv" << endl;
	}
	write_classification_by_nauty_csv(
			Classifier->get_description()->fname_base_out,
			verbose_level);
	if (f_v) {
		cout << "classification_of_varieties::finalize_classification_by_nauty "
				"after write_classification_by_nauty_csv" << endl;
	}


	if (f_v) {
		cout << "classification_of_varieties::finalize_classification_by_nauty done" << endl;
	}
}


void classification_of_varieties::finalize_canonical_forms(
		int verbose_level)
// this only works if we use the substructure algorithm.
// The Nauty based algorithm does not give us a canonical equation.
{
	int f_v = (verbose_level >= 1);


	if (f_v) {
		cout << "classification_of_varieties::finalize_canonical_forms" << endl;
	}

	int i, j;


	for (i = 0; i < Classifier->Input->nb_objects_to_test; i++) {
		Variety_table[i]->compute_canonical_object(verbose_level);
	}




	cout << "canonical forms of all input objects:" << endl;
	for (i = 0; i < Classifier->Input->nb_objects_to_test; i++) {
		cout << setw(2) << i << " : ";
		Int_vec_print(cout,
				Canonical_equation + i * Classifier->Ring_with_action->Poly_ring->get_nb_monomials(),
				Classifier->Ring_with_action->Poly_ring->get_nb_monomials());
		cout << " : " << Goi[i] << endl;
	}

	Tally = NEW_OBJECT(data_structures::tally_vector_data);

	Tally->init(Canonical_equation,
			Classifier->Input->nb_objects_to_test,
			Classifier->Ring_with_action->Poly_ring->get_nb_monomials(),
			verbose_level);


	Tally->get_transversal(
			transversal, frequency, nb_types, verbose_level);

	cout << "Number of orbits = " << Tally->nb_types << endl;

	cout << "Classification of input curves:" << endl;

	cout << "Input object : Iso type" << endl;
	for (i = 0; i < Classifier->Input->nb_objects_to_test; i++) {
		cout << setw(2) << i << " : " <<
				Tally->rep_idx[i] << endl;
	}

	cout << "Transversal of the isomorphism classes = orbit representatives:" << endl;
	Int_vec_print(cout, transversal, nb_types);
	cout << endl;

	//Classification_of_quartic_curves->print();

	for (i = 0; i < Tally->nb_types; i++) {

		//h = int_vec_hash(Reps + i * data_set_sz, data_set_sz);

		cout << i << " : " << Tally->Frequency[i] << " x ";
		Int_vec_print(cout,
				Tally->Reps + i * Tally->data_set_sz,
				Tally->data_set_sz);
		cout << " : ";
		j = Tally->sorting_perm_inv[Tally->type_first[i]];
		cout << Goi[j] << " : ";
		Int_vec_print(cout,
				Tally->sorting_perm_inv + Tally->type_first[i],
				Tally->Frequency[i]);
		cout << endl;
#if 0
		cout << "for elements ";
		int_vec_print(cout, sorting_perm_inv + type_first[i], Frequency[i]);
		cout << endl;
#endif
	}


	if (f_v) {
		cout << "classification_of_varieties::finalize_canonical_forms "
				"before write_canonical_forms_csv" << endl;
	}
	write_canonical_forms_csv(
			Classifier->get_description()->fname_base_out,
			verbose_level);
	if (f_v) {
		cout << "classification_of_varieties::finalize_canonical_forms "
				"after write_canonical_forms_csv" << endl;
	}

	if (f_v) {
		cout << "classification_of_varieties::finalize_canonical_forms done" << endl;
	}

}

void classification_of_varieties::make_classification_table_nauty(
		int *&T,
		int verbose_level)
{
	int f_v = (verbose_level >= 1);



	if (f_v) {
		cout << "classification_of_varieties::make_classification_table_nauty" << endl;
	}

	T = NEW_int(Classifier->Input->nb_objects_to_test * 4);

	int counter;

	for (counter = 0; counter < Classifier->Input->nb_objects_to_test; counter++) {
		T[counter * 4 + 0] = F_first_time[counter];
		T[counter * 4 + 1] = Iso_idx[counter];
		T[counter * 4 + 2] = Idx_canonical_form[counter];
		T[counter * 4 + 3] = Idx_equation[counter];
	}

	if (f_v) {
		cout << "classification_of_varieties::make_classification_table_nauty done" << endl;
	}

}

#endif




}}}
#endif

