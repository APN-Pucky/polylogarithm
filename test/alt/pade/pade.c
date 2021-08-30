#include <math.h>

/**
 * @brief Clausen function \f$\mathrm{Cl}_2(\theta) = \mathrm{Im}(\mathrm{Li}_2(e^{i\theta}))\f$
 * @param x real angle
 * @return \f$\mathrm{Cl}_2(\theta)\f$
 * @author Alexander Voigt
 * @note Implementation as economized Padé approximation.
 */
double clausen_2_pade(double x)
{
   const double PI = 3.14159265358979324;
   const double PI2 = 2*PI, PIH = PI/2, PI28 = PI*PI/8;
   double sgn = 1;

   if (x < 0) {
      x = -x;
      sgn = -1;
   }

   if (x >= PI2) {
      x = fmod(x, PI2);
   }

   if (x > PI) {
      const double p0 = 6.28125;
      const double p1 = 0.0019353071795864769253;
      x = (p0 - x) + p1;
      sgn = -sgn;
   }

   if (x == 0 || x == PI) {
      return 0;
   }

   double h = 0;

   if (x < PIH) {
      const double P[] = {
         2.7951565822419270e-02, -8.8865360514541522e-04,
         6.8282348222485902e-06, -7.5276232403566808e-09
      };
      const double Q[] = {
         1.0000000000000000e+00, -3.6904397961160525e-02,
         3.7342870576106476e-04, -8.7460760866531179e-07
      };
      const double y = x*x;
      const double z = y - PI28;
      const double z2 = z*z;
      const double p = P[0] + z * P[1] + z2 * (P[2] + z * P[3]);
      const double q = Q[0] + z * Q[1] + z2 * (Q[2] + z * Q[3]);

      h = x*(1 - log(x) + y*p/q/2);
   } else {
      const double P[] = {
         6.4005702446195512e-01, -2.0641655351338783e-01,
         2.4175305223497718e-02, -1.2355955287855728e-03,
         2.5649833551291124e-05, -1.4783829128773320e-07
      };
      const double Q[] = {
         1.0000000000000000e+00, -2.5299102015666356e-01,
         2.2148751048467057e-02, -7.8183920462457496e-04,
         9.5432542196310670e-06, -1.8184302880448247e-08
      };
      const double y = PI - x;
      const double z = y*y - PI28;
      const double z2 = z*z;
      const double z4 = z2*z2;
      const double p = P[0] + z * P[1] + z2 * (P[2] + z * P[3]) +
         z4 * (P[4] + z * P[5]);
      const double q = Q[0] + z * Q[1] + z2 * (Q[2] + z * Q[3]) +
         z4 * (Q[4] + z * Q[5]);

      h = y*p/q;
   }

   return sgn*h;
}
