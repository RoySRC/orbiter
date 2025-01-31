// action_on_determinant.cpp
//
// Anton Betten
// January 16, 2009

#include "layer1_foundations/foundations.h"
#include "layer2_discreta/discreta.h"
#include "group_actions.h"


using namespace std;


namespace orbiter {
namespace layer3_group_actions {
namespace induced_actions {


action_on_determinant::action_on_determinant()
{
	Record_birth();
	M = NULL;
	f_projective = false;
	m = 0;
	q = 0;
	degree = 0;
}

action_on_determinant::~action_on_determinant()
{
	Record_death();
}


void action_on_determinant::init(
		actions::action &A,
		int f_projective, int m, int verbose_level)
{
	int f_v = (verbose_level >= 1);
	algebra::ring_theory::longinteger_object go;
	algebra::number_theory::number_theory_domain NT;
	
	if (f_v) {
		cout << "action_on_determinant::init" << endl;
		cout << "action_on_determinant::init f_projective=" << f_projective << endl;
		cout << "action_on_determinant::init m=" << m << endl;
	}
	action_on_determinant::f_projective = f_projective;
	action_on_determinant::m = m;
	if (A.type_G != matrix_group_t) {
		cout << "action_on_determinant::init action "
				"not of matrix group type" << endl;
		exit(1);
	}
	M = A.G.matrix_grp;
	q = M->GFq->q;
	if (f_projective) {
		degree = NT.gcd_lint(m, q - 1);
	}
	else {
		degree = q - 1;
	}
	if (f_v) {
		cout << "action_on_determinant::init "
				"degree=" << degree << endl;
	}
	
	if (f_v) {
		cout << "action_on_determinant::init "
				"field order is " << q << endl;
	}
}

long int action_on_determinant::compute_image(
		actions::action *A,
		int *Elt, long int i, int verbose_level)
{
	//verbose_level = 1;
	int f_v = (verbose_level >= 1);
	long int a, b, c, l = 0, j;
	
	if (f_v) {
		cout << "action_on_determinant::compute_image "
				"i = " << i << endl;
	}
	if (i < 0 || i >= degree) {
		cout << "action_on_determinant::compute_image "
				"i = " << i << " out of range" << endl;
		exit(1);
	}
	if (f_projective) {
		a = M->GFq->alpha_power(i);
	}
	else {
		a = i + 1;
	}
	if (f_v) {
		cout << "action_on_determinant::compute_image "
				"a = " << a << endl;
	}
	if (f_v) {
		cout << "action_on_determinant::compute_image "
				"M = " << endl;
		Int_matrix_print(Elt, M->n, M->n);
	}
	b = M->GFq->Linear_algebra->matrix_determinant(Elt, M->n, 0);
	if (f_v) {
		cout << "action_on_determinant::compute_image "
				"det = " << b << endl;
	}
	c = M->GFq->mult(a, b);
	if (f_v) {
		cout << "action_on_determinant::compute_image "
				"c = a * b = " << c << endl;
	}
	if (f_projective) {
		l = M->GFq->log_alpha(c);
		if (f_v) {
			cout << "action_on_determinant::compute_image "
					"f_projective, l = " << l << endl;
		}
		j = l % degree;
		if (f_v) {
			cout << "action_on_determinant::compute_image "
					"f_projective j = l % degree = " << j << endl;
		}
	}
	else {
		j = c - 1;
		if (f_v) {
			cout << "action_on_determinant::compute_image "
					"j = c - 1 = " << j << endl;
		}
	}
	if (f_v) {
		cout << "action_on_determinant::compute_image "
				"det = " << b << endl;
		cout << "action_on_determinant::compute_image "
				<< a << " * " << b << " = " << c << endl;
		if (f_projective) {
			cout << "action_on_determinant::compute_image f_projective, a = " << a
					<< " l = " << l << " c = " << c << endl;
		}
		cout << "action_on_determinant::compute_image "
				"image of " << i << " is " << j << endl;
	}
	return j;
}

}}}

