// ====================================================================
// This file is part of Polylogarithm.
//
// Polylogarithm is licenced under the MIT License.
// ====================================================================

#include "Cl2.hpp"
#include <cmath>

namespace polylogarithm {

namespace {

   template <typename T, int N>
   T horner(T x, const T (&c)[N]) noexcept
   {
      T p = c[N - 1];
      for (int i = N - 2; i >= 0; --i) {
         p = p*x + c[i];
      }
      return p;
   }

} // anonymous namespace

/**
 * @brief Clausen function \f$\mathrm{Cl}_2(\theta) = \mathrm{Im}(\mathrm{Li}_2(e^{i\theta}))\f$
 * @param x real angle
 * @return \f$\mathrm{Cl}_2(\theta)\f$
 * @author Alexander Voigt
 * @note Implementation as economized Padé approximation.
 */
double Cl2(double x) noexcept
{
   const double PI = 3.14159265358979324;
   const double PI2 = 2*PI, PIH = PI/2, PI28 = PI*PI/8;
   double sgn = 1;

   if (x < 0) {
      x = -x;
      sgn = -1;
   }

   if (x >= PI2) {
      x = std::fmod(x, PI2);
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

      h = x*(1 - std::log(x) + y*p/q/2);
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

/**
 * @brief Clausen function \f$\mathrm{Cl}_2(\theta) = \mathrm{Im}(\mathrm{Li}_2(e^{i\theta}))\f$ with long double precision
 * @param x real angle
 * @return \f$\mathrm{Cl}_2(\theta)\f$
 * @author K.S. Kölbig
 * @note Implementation translated from CERNLIB DCLAUS function C326
 * and extended to long double precision by Alexander Voigt.
 *
 * Journal of Computational and Applied Mathematics 64 (1995) 295-297.
 */
long double Cl2(long double x) noexcept
{
   const long double PI = 3.14159265358979323846264338327950288L;
   const long double PI2 = 2*PI, PIH = PI/2, PI28 = PI*PI/8;
   long double sgn = 1;

   if (x < 0) {
      x = -x;
      sgn = -1;
   }

   if (x >= PI2) {
      x = std::fmod(x, PI2);
   }

   if (x > PI) {
      const long double p0 = 6.28125L;
      const long double p1 = 0.0019353071795864769252867665590057683943L;
      x = (p0 - x) + p1;
      sgn = -sgn;
   }

   if (x == 0 || x == PI) {
      return 0;
   }

   long double h = 0;

   if (x < PIH) {
      const long double P[] = {
         2.795156582241927046412081735910646612854e-02l,
        -2.704528039782130831727668760352473119745e-03l,
         1.058576547177802928762582430994046913011e-04l,
        -2.147507975446829791077479076828450780219e-06l,
         2.401415296681270093111305488326496124531e-08l,
        -1.450571790543608936928129678333156785370e-10l,
         4.280534901040925211965221454555516657749e-13l,
        -4.792802237226483806823208684186867186935e-16l,
         8.883657381852830471176782778999368430017e-20l
      };
      const long double Q[] = {
         1.l,
        -1.018694323414614410071369720193716012304e-01l,
         4.248408782245281612900840467370146443889e-03l,
        -9.337710301347963985908084056584187570954e-05l,
         1.159379163193822053103946363960603543601e-06l,
        -8.083352720393357000801675734774176899515e-09l,
         2.949313240431512997069808854213308209519e-11l,
        -4.742700419624204182400715964695278593777e-14l,
         2.158380636740175386190809152807629331877e-17l
      };
      const long double y = x*x;
      const long double z = y - PI28;
      const long double p = horner(z, P);
      const long double q = horner(z, Q);

      h = x*(1 - std::log(x) + y*p/q/2);
   } else {
      const long double P[] = {
         6.400570244619551220929428522356830562481e-01l,
        -4.651631624886004423703445967760673575997e-01l,
         1.487130845262105644024901814213146749895e-01l,
        -2.749665174801454303884783494225610407035e-02l,
         3.251522465413666561950482170352156048203e-03l,
        -2.567438381297475310848635518657180974512e-04l,
         1.372076105130164861564020074178493529151e-05l,
        -4.924179093673498700461153483531075799113e-07l,
         1.153267936031337440182387313169828395860e-08l,
        -1.667578310677508029208023423625588832295e-10l,
         1.348437292247918547169070120217729056878e-12l,
        -5.052245092698477071447850656280954693011e-15l,
         5.600638109466570497480415519182233229048e-18,
      };
      const long double Q[] = {
         1.l,
        -6.572465772185054284667746526549393897676e-01l,
         1.886234634096976582977630140163583172173e-01l,
        -3.103347567899737687117030083178445406132e-02l,
         3.230860399291224478336071920154030050234e-03l,
        -2.216546569335921728108984951507368387512e-04l,
         1.011949972138985643994631167412420906088e-05l,
        -3.033400935206767852937290458763547850384e-07l,
         5.748454611964843057644023468691231929690e-09l,
        -6.408350048413952604351408631173781906861e-11l,
         3.678584366662951864267349037579031493395e-13l,
        -8.240439699357036167611014086997683837396e-16l,
         3.041049046123062158788159773779755292771e-19l
      };
      const long double y = PI - x;
      const long double z = y*y - PI28;
      const long double p = horner(z, P);
      const long double q = horner(z, Q);

      h = y*p/q;
   }

   return sgn*h;
}

} // namespace polylogarithm
