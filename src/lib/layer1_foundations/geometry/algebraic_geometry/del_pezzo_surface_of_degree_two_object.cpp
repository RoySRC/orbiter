/*
 * del_pezzo_surface_of_degree_two_object.cpp
 *
 *  Created on: Feb 25, 2021
 *      Author: betten
 */

#include "foundations.h"


using namespace std;


namespace orbiter {
namespace layer1_foundations {
namespace geometry {
namespace algebraic_geometry {


del_pezzo_surface_of_degree_two_object::del_pezzo_surface_of_degree_two_object()
{
	Record_birth();
	Dom = NULL;

	RHS = NULL;
	Subtrees = NULL;
	Coefficient_vector = NULL;

	pal = NULL;

}

del_pezzo_surface_of_degree_two_object::~del_pezzo_surface_of_degree_two_object()
{
	Record_death();
	if (pal) {
		FREE_OBJECT(pal);
	}
}

void del_pezzo_surface_of_degree_two_object::init(
		del_pezzo_surface_of_degree_two_domain *Dom,
		algebra::expression_parser::formula *RHS,
		algebra::expression_parser::syntax_tree_node **Subtrees,
		int *Coefficient_vector,
		int verbose_level)
{
	int f_v = (verbose_level >= 1);

	if (f_v) {
		cout << "del_pezzo_surface_of_degree_two_object::init" << endl;
	}
	del_pezzo_surface_of_degree_two_object::Dom = Dom;
	del_pezzo_surface_of_degree_two_object::RHS = RHS;
	del_pezzo_surface_of_degree_two_object::Subtrees = Subtrees;
	del_pezzo_surface_of_degree_two_object::Coefficient_vector = Coefficient_vector;

	if (f_v) {
		cout << "del_pezzo_surface_of_degree_two_object::init done" << endl;
	}
}

void del_pezzo_surface_of_degree_two_object::enumerate_points_and_lines(
		int verbose_level)
{
	int f_v = (verbose_level >= 1);

	if (f_v) {
		cout << "del_pezzo_surface_of_degree_two_object::enumerate_points_and_lines" << endl;
	}

	vector<long int> Points;

	if (f_v) {
		cout << "del_pezzo_surface_of_degree_two_object::enumerate_points_and_lines "
				"before Dom->enumerate_points" << endl;
	}
	Dom->enumerate_points(Coefficient_vector,
		Points,
		0 /*verbose_level - 1*/);
	if (f_v) {
		cout << "del_pezzo_surface_of_degree_two_object::enumerate_points_and_lines "
				"after Dom->enumerate_points" << endl;
	}
	if (f_v) {
		cout << "del_pezzo_surface_of_degree_two_object::enumerate_points_and_lines "
				"The object has " << Points.size() << " points" << endl;
	}


	pal = NEW_OBJECT(geometry::other_geometry::points_and_lines);

	if (f_v) {
		cout << "del_pezzo_surface_of_degree_two_object::enumerate_points_and_lines "
				"before pal->init" << endl;
	}
	pal->init(Dom->P3, Points, verbose_level);
	if (f_v) {
		cout << "del_pezzo_surface_of_degree_two_object::enumerate_points_and_lines "
				"after pal->init" << endl;
	}



	if (f_v) {
		cout << "del_pezzo_surface_of_degree_two_object::enumerate_points_and_lines done" << endl;
	}
}

void del_pezzo_surface_of_degree_two_object::create_latex_report(
		std::string &label,
		std::string &label_tex, int verbose_level)
{
	int f_v = (verbose_level >= 1);

	if (f_v) {
		cout << "del_pezzo_surface_of_degree_two_object::create_latex_report" << endl;
	}

	{



		string fname;
		string author;
		string title;
		string extra_praeamble;

		fname = label + "_report.tex";

		title = "Del Pezzo Surface " + label_tex;





		{
			ofstream ost(fname);
			other::l1_interfaces::latex_interface L;

			L.head(ost,
					false /* f_book*/,
					true /* f_title */,
					title, author,
					false /* f_toc */,
					false /* f_landscape */,
					true /* f_12pt */,
					true /* f_enlarged_page */,
					true /* f_pagenumbers */,
					extra_praeamble /* extra_praeamble */);


			if (f_v) {
				cout << "del_pezzo_surface_of_degree_two_object::create_latex_report "
						"before report_properties" << endl;
			}
			report_properties(ost, verbose_level);
			if (f_v) {
				cout << "del_pezzo_surface_of_degree_two_object::create_latex_report "
						"after report_properties" << endl;
			}


			L.foot(ost);

		}
		other::orbiter_kernel_system::file_io Fio;

		cout << "written file " << fname << " of size "
				<< Fio.file_size(fname) << endl;
	}
	if (f_v) {
		cout << "del_pezzo_surface_of_degree_two_object::create_latex_report done" << endl;
	}
}

void del_pezzo_surface_of_degree_two_object::report_properties(
		std::ostream &ost, int verbose_level)
{
	int f_v = (verbose_level >= 1);

	if (f_v) {
		cout << "del_pezzo_surface_of_degree_two_object::report_properties" << endl;
	}

	if (f_v) {
		cout << "del_pezzo_surface_of_degree_two_object::report_properties "
				"before print_equation" << endl;
	}
	print_equation(ost);

#if 0
	if (f_v) {
		cout << "del_pezzo_surface_of_degree_two_object::report_properties "
				"before print_general" << endl;
	}
	print_general(ost);
#endif


	if (f_v) {
		cout << "del_pezzo_surface_of_degree_two_object::report_properties "
				"before print_lines" << endl;
	}
	pal->print_all_lines(ost);

	if (f_v) {
		cout << "del_pezzo_surface_of_degree_two_object::report_properties "
				"before print_points" << endl;
	}
	print_points(ost);

#if 0
	if (f_v) {
		cout << "del_pezzo_surface_of_degree_two_object::report_properties "
				"print_tritangent_planes" << endl;
	}
	print_tritangent_planes(ost);


	if (f_v) {
		cout << "del_pezzo_surface_of_degree_two_object::report_properties "
				"before print_Steiner_and_Eckardt" << endl;
	}
	print_Steiner_and_Eckardt(ost);

	//SOA->SO->print_planes_in_trihedral_pairs(fp);

#if 0
	if (f_v) {
		cout << "del_pezzo_surface_of_degree_two_object::report_properties "
				"before print_generalized_quadrangle" << endl;
	}
	print_generalized_quadrangle(ost);
#endif

	if (f_v) {
		cout << "surface_object_properties::report_properties "
				"before print_line_intersection_graph" << endl;
	}
	print_line_intersection_graph(ost);
#endif

	if (f_v) {
		cout << "del_pezzo_surface_of_degree_two_object::report_properties done" << endl;
	}
}

void del_pezzo_surface_of_degree_two_object::print_equation(
		std::ostream &ost)
{
	ost << "\\subsection*{The equation}" << endl;
	ost << "The equation of the surface ";
	ost << " is :" << endl;

	Dom->print_equation_with_line_breaks_tex(ost, Coefficient_vector);

	Int_vec_print(ost, Coefficient_vector, 15);
	ost << "\\\\" << endl;

	long int rk;

	Dom->F->Projective_space_basic->PG_element_rank_modified_lint(
			Coefficient_vector, 1, 15, rk);
	ost << "The point rank of the equation over GF$("
			<< Dom->F->q << ")$ is " << rk << "\\\\" << endl;

	//ost << "Number of points on the surface " << SO->nb_pts << "\\\\" << endl;


}

void del_pezzo_surface_of_degree_two_object::print_points(
		std::ostream &ost)
{
	ost << "\\subsection*{All Points on surface}" << endl;

	cout << "surface_object_properties::print_points before print_points_on_surface" << endl;
	//print_points_on_surface(ost);
	pal->print_all_points(ost);

#if 0
	ost << "\\subsubsection*{Eckardt Points}" << endl;
	cout << "surface_object_properties::print_points before print_Eckardt_points" << endl;
	print_Eckardt_points(ost);

	ost << "\\subsubsection*{Singular Points}" << endl;
	cout << "surface_object_properties::print_points before print_singular_points" << endl;
	print_singular_points(ost);

	ost << "\\subsubsection*{Double Points}" << endl;
	cout << "surface_object_properties::print_points before print_double_points" << endl;
	print_double_points(ost);

	ost << "\\subsubsection*{Points on lines}" << endl;
	cout << "surface_object_properties::print_points before print_points_on_lines" << endl;
	print_points_on_lines(ost);

	ost << "\\subsubsection*{Points on surface but on no line}" << endl;
	cout << "surface_object_properties::print_points before print_points_on_surface_but_not_on_a_line" << endl;
	print_points_on_surface_but_not_on_a_line(ost);

#if 0
	ost << "\\clearpage" << endl;
	ost << "\\section*{Lines through points}" << endl;
	lines_on_point->print_table_tex(ost);
#endif
#endif

}





}}}}


