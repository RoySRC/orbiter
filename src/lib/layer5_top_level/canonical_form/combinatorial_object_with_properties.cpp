/*
 * combinatorial_object_with_properties.cpp
 *
 *  Created on: Dec 8, 2021
 *      Author: betten
 */




#include "orbiter.h"

using namespace std;

namespace orbiter {
namespace layer5_applications {
namespace canonical_form {


combinatorial_object_with_properties::combinatorial_object_with_properties()
{
	Any_Combo = NULL;

	//std::string label;

	NO = NULL;

	f_projective_space = false;
	PA = NULL;

	SG = NULL;

	A_perm = NULL;

	f_has_TDO = false;
	TDO = NULL;

	GA_on_CO = NULL;

	//Flags = NULL;
	//Anti_Flags = NULL;

}

combinatorial_object_with_properties::~combinatorial_object_with_properties()
{

	if (TDO) {
		FREE_OBJECT(TDO);
	}
	if (GA_on_CO) {
		FREE_OBJECT(GA_on_CO);
	}
#if 0
	if (Flags) {
		FREE_OBJECT(Flags);
	}
	if (Anti_Flags) {
		FREE_OBJECT(Anti_Flags);
	}
#endif
}


void combinatorial_object_with_properties::init(
		canonical_form_classification::any_combinatorial_object *Any_Combo,
		l1_interfaces::nauty_output *NO,
		int f_projective_space,
		projective_geometry::projective_space_with_action *PA,
		int max_TDO_depth,
		std::string &label,
		int verbose_level)
// called from classification_of_combinatorial_objects::init_after_nauty
{
	int f_v = (verbose_level >= 1);

	if (f_v) {
		cout << "combinatorial_object_with_properties::init" << endl;
	}

	combinatorial_object_with_properties::Any_Combo = Any_Combo;
	combinatorial_object_with_properties::NO = NO;
	combinatorial_object_with_properties::f_projective_space = f_projective_space;
	combinatorial_object_with_properties::PA = PA;
	combinatorial_object_with_properties::label.assign(label);

	actions::action_global Action_global;

	if (f_v) {
		cout << "combinatorial_object_with_properties::init "
				"before Action_global.automorphism_group_as_permutation_group" << endl;
	}
	Action_global.automorphism_group_as_permutation_group(
					NO,
					A_perm,
					verbose_level - 2);

	if (f_v) {
		cout << "combinatorial_object_with_properties::init "
				"after Action_global.automorphism_group_as_permutation_group" << endl;
	}

	if (false) {
		cout << "combinatorial_object_with_properties::init "
				"A_perm:" << endl;

		A_perm->Strong_gens->print_generators_in_latex_individually(cout, verbose_level - 1);
		A_perm->Strong_gens->print_generators_in_source_code(verbose_level - 1);
		A_perm->print_base();
	}

	if (f_projective_space) {
		if (f_v) {
			cout << "combinatorial_object_with_properties::init "
					"before lift_generators_to_matrix_group" << endl;
		}

		lift_generators_to_matrix_group(verbose_level - 2);

		if (f_v) {
			cout << "combinatorial_object_with_properties::init "
					"after lift_generators_to_matrix_group" << endl;
		}
	}


	GA_on_CO = NEW_OBJECT(combinatorics_with_groups::group_action_on_combinatorial_object);


	if (f_v) {
		cout << "combinatorial_object_with_properties::init "
				"before GA_on_CO->init" << endl;
	}
	GA_on_CO->init(
			label,
			label,
			Any_Combo,
			A_perm,
			verbose_level);
	if (f_v) {
		cout << "combinatorial_object_with_properties::init "
				"after GA_on_CO->init" << endl;
	}


#if 0
	if (f_v) {
		cout << "combinatorial_object_with_properties::init "
				"before compute_flag_orbits" << endl;
	}
	compute_flag_orbits(verbose_level - 2);
	if (f_v) {
		cout << "combinatorial_object_with_properties::init "
				"after compute_flag_orbits" << endl;
	}
#endif

	if (f_v) {
		cout << "combinatorial_object_with_properties::init "
				"before compute_TDO" << endl;
	}
	compute_TDO(max_TDO_depth, verbose_level - 2);
	if (f_v) {
		cout << "combinatorial_object_with_properties::init "
				"after compute_TDO" << endl;
	}

	if (f_v) {
		cout << "combinatorial_object_with_properties::init done" << endl;
	}
}


void combinatorial_object_with_properties::lift_generators_to_matrix_group(
		int verbose_level)
{
	int f_v = (verbose_level >= 1);

	if (f_v) {
		cout << "combinatorial_object_with_properties::lift_generators_to_matrix_group" << endl;
	}
	actions::action *A_perm;

	actions::action_global Action_global;

	if (f_v) {
		cout << "combinatorial_object_with_properties::lift_generators_to_matrix_group "
				"before Action_global.reverse_engineer_linear_group_from_permutation_group" << endl;
	}

	Action_global.reverse_engineer_linear_group_from_permutation_group(
			PA->A /* A_linear */,
			PA->P,
			SG,
			A_perm,
			NO,
			verbose_level);

	if (f_v) {
		cout << "combinatorial_object_with_properties::lift_generators_to_matrix_group "
				"after Action_global.reverse_engineer_linear_group_from_permutation_group" << endl;
	}


	FREE_OBJECT(A_perm);

	if (f_v) {
		cout << "combinatorial_object_with_properties::lift_generators_to_matrix_group done" << endl;
	}
}

void combinatorial_object_with_properties::init_object_in_projective_space(
		canonical_form_classification::any_combinatorial_object *Any_Combo,
		l1_interfaces::nauty_output *NO,
		projective_geometry::projective_space_with_action *PA,
		std::string &label,
		int verbose_level)
{
	int f_v = (verbose_level >= 1);

	if (f_v) {
		cout << "combinatorial_object_with_properties::init_object_in_projective_space" << endl;
	}

	combinatorial_object_with_properties::Any_Combo = Any_Combo;
	combinatorial_object_with_properties::NO = NO;
	combinatorial_object_with_properties::label.assign(label);


	actions::action_global Action_global;
	actions::action *A_linear;

	A_linear = PA->A;

	if (f_v) {
		cout << "combinatorial_object_with_properties::init_object_in_projective_space "
				"before Action_global.reverse_engineer_linear_group_from_permutation_group" << endl;
	}
	Action_global.reverse_engineer_linear_group_from_permutation_group(
			A_linear,
			PA->P,
			SG,
			A_perm,
			NO,
			verbose_level);
	if (f_v) {
		cout << "combinatorial_object_with_properties::init_object_in_projective_space "
				"after Action_global.reverse_engineer_linear_group_from_permutation_group" << endl;
	}


	if (f_v) {
		cout << "combinatorial_object_with_properties::init_object_in_projective_space done" << endl;
	}

}

void combinatorial_object_with_properties::latex_report(
		std::ostream &ost,
		canonical_form_classification::objects_report_options
			*Report_options,
		int verbose_level)
{
	int f_v = (verbose_level >= 1);

	if (f_v) {
		cout << "combinatorial_object_with_properties::latex_report" << endl;
	}

	ost << "\\subsection*{object\\_with\\_properties::latex\\_report Automorphism Group as Permutation Group}" << endl;

	{
		ring_theory::longinteger_object go;

		A_perm->Strong_gens->group_order(go);

		ost << "Automorphism group has order: " << go << "\\\\" << endl;
	}

	ost << "Generators for the automorphism group: \\\\" << endl;
	if (A_perm->degree < 100) {
		A_perm->Strong_gens->print_generators_in_latex_individually(ost, verbose_level - 1);

		ost << "\\begin{verbatim}" << endl;
		A_perm->Strong_gens->print_generators_gap(ost, verbose_level - 1);
		ost << "\\end{verbatim}" << endl;

	}
	else {
		ost << "permutation degree is too large to print. \\\\" << endl;

	}

	if (f_projective_space) {

		ost << "\\subsection*{object\\_with\\_properties::latex\\_report Automorphism Group in Projective Space}" << endl;

		{
			ring_theory::longinteger_object go;

			SG->group_order(go);

			ost << "Automorphism group has order: " << go << "\\\\" << endl;
		}


		ost << "Generators for the automorphism group as matrix group: \\\\" << endl;

		if (f_v) {
			cout << "combinatorial_object_with_properties::latex_report "
					"before SG->print_generators_in_latex_individually" << endl;
		}
		SG->print_generators_in_latex_individually(ost, verbose_level - 1);
		if (f_v) {
			cout << "combinatorial_object_with_properties::latex_report "
					"after SG->print_generators_in_latex_individually" << endl;
		}
	}


	if (Report_options->f_export_group_orbiter) {

		if (f_v) {
			cout << "combinatorial_object_with_properties::latex_report "
					"f_export_group_orbiter" << endl;
		}

		std::string fname;
		std::string label_txt;
		std::string label_tex;


		fname = label + "_aut.makefile";
		label_txt = label + "_aut";
		label_tex = label + "\\_aut";

		if (f_v) {
			cout << "combinatorial_object_with_properties::latex_report "
					"before A_perm->Strong_gens->export_to_orbiter_as_bsgs" << endl;
		}
		A_perm->Strong_gens->export_to_orbiter_as_bsgs(
				A_perm,
				fname, label, label_tex,
				verbose_level);
		if (f_v) {
			cout << "combinatorial_object_with_properties::latex_report "
					"after A_perm->Strong_gens->export_to_orbiter_as_bsgs" << endl;
		}
	}

	if (Report_options->f_export_group_GAP) {

		if (f_v) {
			cout << "combinatorial_object_with_properties::latex_report "
					"f_export_group_GAP" << endl;
		}

		std::string fname;


		fname = label + "_aut.gap";


		interfaces::l3_interface_gap GAP;

		if (f_v) {
			cout << "combinatorial_object_with_properties::latex_report "
					"before GAP.export_permutation_group_to_GAP" << endl;
		}

		GAP.export_permutation_group_to_GAP(
				fname,
				A_perm,
				A_perm->Strong_gens,
				verbose_level);

		if (f_v) {
			cout << "object_with_properties::latex_report "
					"after GAP.export_permutation_group_to_GAP" << endl;
		}
	}



#if 1
	groups::schreier *Sch;


	if (f_v) {
		cout << "combinatorial_object_with_properties::latex_report "
				"before compute_all_point_orbits_schreier" << endl;
	}
	Sch = A_perm->Strong_gens->compute_all_point_orbits_schreier(A_perm,
			verbose_level);
	if (f_v) {
		cout << "combinatorial_object_with_properties::latex_report "
				"after compute_all_point_orbits_schreier" << endl;
	}
#endif


	if (Report_options->f_export_flag_orbits) {

		if (f_v) {
			cout << "combinatorial_object_with_properties::latex_report "
					"f_export_flag_orbits" << endl;
		}

		ost << "\\subsection*{object\\_with\\_properties::latex\\_report Flag Orbits}" << endl;

		if (f_v) {
			cout << "combinatorial_object_with_properties::latex_report "
					"before GA_on_CO->export_INP_with_flag_orbits" << endl;
		}
		GA_on_CO->export_INP_with_flag_orbits(
				ost,
				verbose_level);
		if (f_v) {
			cout << "combinatorial_object_with_properties::latex_report "
					"after GA_on_CO->export_INP_with_flag_orbits" << endl;
		}

		if (f_v) {
			cout << "combinatorial_object_with_properties::latex_report "
					"before GA_on_CO->export_TDA_with_flag_orbits" << endl;
		}
		GA_on_CO->export_TDA_with_flag_orbits(
				ost,
				verbose_level);
		if (f_v) {
			cout << "combinatorial_object_with_properties::latex_report "
					"after GA_on_CO->export_TDA_with_flag_orbits" << endl;
		}
		if (f_v) {
			cout << "combinatorial_object_with_properties::latex_report "
					"f_export_flag_orbits done" << endl;
		}
	}

	if (Report_options->f_show_TDO) {

		if (f_v) {
			cout << "combinatorial_object_with_properties::latex_report "
					"f_show_TDO" << endl;
		}
		ost << "\\subsection*{object\\_with\\_properties::latex\\_report TDO}" << endl;

		ost << "Decomposition by combinatorial refinement (TDO):\\\\" << endl;

		if (f_v) {
			cout << "combinatorial_object_with_properties::latex_report "
					"before print_TDO" << endl;
		}
		print_TDO(ost, Report_options, verbose_level);
		if (f_v) {
			cout << "combinatorial_object_with_properties::latex_report "
					"after print_TDO" << endl;
		}
		if (f_v) {
			cout << "combinatorial_object_with_properties::latex_report "
					"f_show_TDO done" << endl;
		}
	}

	if (Report_options->f_show_TDA) {

		if (f_v) {
			cout << "combinatorial_object_with_properties::latex_report "
					"f_show_TDA" << endl;
		}
		ost << "\\subsection*{object\\_with\\_properties::latex\\_report TDA}" << endl;

		{
			ring_theory::longinteger_object go;

			A_perm->Strong_gens->group_order(go);

			ost << "Automorphism group has order: " << go << "\\\\" << endl;
		}

		ost << "Decomposition by automorphism group:\\\\" << endl;

		if (f_v) {
			cout << "combinatorial_object_with_properties::latex_report "
					"before GA_on_CO->print_schemes" << endl;
		}
		GA_on_CO->print_schemes(ost, Report_options, verbose_level);
		if (f_v) {
			cout << "combinatorial_object_with_properties::latex_report "
					"after GA_on_CO->print_schemes" << endl;
		}

#if 0
		if (f_v) {
			cout << "combinatorial_object_with_properties::latex_report "
					"before Sch->print_TDA" << endl;
		}
		Sch->print_TDA(ost, OwCF, Report_options, verbose_level);
		if (f_v) {
			cout << "object_with_properties::latex_report "
					"after Sch->print_TDA" << endl;
		}
#endif

		if (f_v) {
			cout << "combinatorial_object_with_properties::latex_report "
					"f_show_TDA done" << endl;
		}


	}
	if (Report_options->f_export_labels) {

		ost << "\\subsection*{object\\_with\\_properties::latex\\_report Labels}" << endl;

		canonical_form_classification::encoded_combinatorial_object *Enc;

		Any_Combo->encode_incma(Enc, verbose_level);

		//latex_TDA(ost, Enc, verbose_level);
		//ost << "\\\\" << endl;

		int *point_labels;
		int *block_labels;

		Enc->compute_labels(
				Sch->nb_orbits, Sch->orbit_first, Sch->orbit_len, Sch->orbit,
				point_labels, block_labels,
				verbose_level);

		orbiter_kernel_system::file_io Fio;

		string fname;

		fname = "point_labels.csv";
		Fio.Csv_file_support->int_matrix_write_csv(
				fname, point_labels, Enc->nb_rows, 1);

		cout << "combinatorial_object_with_properties::latex_report "
				"Written file " << fname << " of size "
				<< Fio.file_size(fname) << endl;

		fname = "block_labels.csv";
		Fio.Csv_file_support->int_matrix_write_csv(
				fname, block_labels, Enc->nb_cols, 1);

		cout << "combinatorial_object_with_properties::latex_report "
				"Written file " << fname << " of size "
				<< Fio.file_size(fname) << endl;

		FREE_int(point_labels);
		FREE_int(block_labels);

		FREE_OBJECT(Enc);
	}

	ost << "\\subsection*{object\\_with\\_properties::latex\\_report Canonical labeling}" << endl;

	ost << "Canonical labeling:\\\\" << endl;
	canonical_form_classification::encoded_combinatorial_object *Enc;
	canonical_form_classification::encoded_combinatorial_object *Enc2;

	if (f_v) {
		cout << "combinatorial_object_with_properties::latex_report "
				"before Any_Combo->encode_incma" << endl;
	}
	Any_Combo->encode_incma(Enc, verbose_level);
	if (f_v) {
		cout << "combinatorial_object_with_properties::latex_report "
				"after Any_Combo->encode_incma" << endl;
	}


	Enc2 = NEW_OBJECT(canonical_form_classification::encoded_combinatorial_object);

	Enc2->init_canonical_form(Enc, NO, verbose_level);



	int canonical_row;
	int canonical_orbit;

	canonical_row = NO->canonical_labeling[Enc->nb_rows - 1];

	canonical_orbit = Sch->orbit_number(canonical_row);

	ost << "canonical row = " << canonical_row << "\\\\" << endl;
	ost << "canonical orbit number = " << canonical_orbit << "\\\\" << endl;

	Enc2->latex_set_system_by_rows(ost, verbose_level);

	FREE_OBJECT(Enc2);

	if (Report_options->f_show_incidence_matrices) {

		ost << "\\subsection*{object\\_with\\_properties::latex\\_report Incidence Matrices}" << endl;

		if (f_v) {
			cout << "combinatorial_object_with_properties::latex_report "
					"f_show_incidence_matrices" << endl;
		}

		int v = Enc->nb_rows;
		int b = Enc->nb_cols;

		std::string *point_labels;
		std::string *block_labels;


		point_labels = new string [v];
		block_labels = new string [b];

		int i, j, a;

		for (i = 0; i < v; i++) {

			a = NO->canonical_labeling[i];
			if (Sch->orbit_number(a) == canonical_orbit) {
				point_labels[i] = "*" + std::to_string(a);
			}
			else {
				point_labels[i] = std::to_string(a);
			}
		}
		for (j = 0; j < b; j++) {
			block_labels[j] = std::to_string(NO->canonical_labeling[v + j]);
		}

		Enc->latex_canonical_form_with_labels(
				ost, NO,
				point_labels,
				block_labels,
				verbose_level);

		delete [] point_labels;
		delete [] block_labels;

		FREE_OBJECT(Enc);
	}

	GA_on_CO->report_flag_orbits(
			ost, verbose_level);



	if (Report_options->f_lex_least) {

		ost << "\\subsection*{object\\_with\\_properties::latex\\_report Lex Least Form}" << endl;

		if (f_v) {
			cout << "combinatorial_object_with_properties::latex_report f_lex_least" << endl;
		}
		geometry_builder::geometry_builder *GB;

		GB = Get_geometry_builder(Report_options->lex_least_geometry_builder);


		int idx;
		int f_found;
		l1_interfaces::nauty_output *NO;
		data_structures::bitvector *Canonical_form;


		if (f_v) {
			cout << "combinatorial_object_with_properties::latex_report "
					"before find_object, "
					"OwCF->v=" << Any_Combo->v << endl;
		}

		GB->gg->inc->iso_type_at_line[Any_Combo->v - 1]->Canonical_forms->find_object(
				Any_Combo,
				f_found, idx,
				NO,
				Canonical_form,
				verbose_level);

		if (f_v) {
			cout << "combinatorial_object_with_properties::latex_report "
					"after find_object" << endl;
		}

		// if f_found is true, B[idx] agrees with the given object


		if (!f_found) {
			cout << "combinatorial_object_with_properties::latex_report "
					"cannot find object in geometry_builder" << endl;
			exit(1);
		}

		canonical_form_classification::any_combinatorial_object *Any_Combo2 =
				(canonical_form_classification::any_combinatorial_object *)
				GB->gg->inc->iso_type_at_line[Any_Combo->v - 1]->Canonical_forms->Objects[idx];

		if (f_v) {
			cout << "combinatorial_object_with_properties::latex_report "
					"before FREE_OBJECT(NO)" << endl;
		}
		FREE_OBJECT(NO);
		if (f_v) {
			cout << "combinatorial_object_with_properties::latex_report "
					"after FREE_OBJECT(NO)" << endl;
		}
		FREE_OBJECT(Canonical_form);
		if (f_v) {
			cout << "combinatorial_object_with_properties::latex_report "
					"after FREE_OBJECT(Canonical_form)" << endl;
		}

		ost << "Is isomorphic to object " << idx << " in the list:\\\\" << endl;
		ost << "Lex-least form is:\\\\" << endl;

		Any_Combo2->print_tex_detailed(
				ost,
				Report_options,
				verbose_level);
	}


	if (f_v) {
		cout << "combinatorial_object_with_properties::latex_report done" << endl;
	}

}

void combinatorial_object_with_properties::compute_TDO(
		int max_TDO_depth, int verbose_level)
{
	int f_v = (verbose_level >= 1);

	if (f_v) {
		cout << "combinatorial_object_with_properties::compute_TDO" << endl;
	}
	canonical_form_classification::encoded_combinatorial_object *Enc;

	Any_Combo->encode_incma(Enc, verbose_level);



	TDO = NEW_OBJECT(combinatorics::tdo_scheme_compute);

	if (f_v) {
		cout << "combinatorial_object_with_properties::compute_TDO "
				"before TDO->init" << endl;
	}
	TDO->init(Enc, max_TDO_depth, verbose_level);
	if (f_v) {
		cout << "combinatorial_object_with_properties::compute_TDO "
				"after TDO->init" << endl;
	}
	f_has_TDO = true;


	//latex_TDA(ost, Enc, verbose_level);

	FREE_OBJECT(Enc);
	if (f_v) {
		cout << "combinatorial_object_with_properties::compute_TDO done" << endl;
	}

}

void combinatorial_object_with_properties::print_TDO(
		std::ostream &ost,
		canonical_form_classification::objects_report_options
			*Report_options,
		int verbose_level)
{

	if (f_has_TDO) {
		TDO->print_schemes(ost, Report_options, verbose_level);
	}
	else {
		cout << "combinatorial_object_with_properties::print_TDO "
				"TDO has not yet been computed" << endl;
	}

}



}}}