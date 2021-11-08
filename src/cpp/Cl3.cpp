// ====================================================================
// This file is part of Polylogarithm.
//
// Polylogarithm is licenced under the MIT License.
// ====================================================================

#include "Cl3.hpp"
#include <cmath>

namespace polylogarithm {

/**
 * @brief Clausen function \f$\mathrm{Cl}_3(\theta) = \mathrm{Re}(\mathrm{Li}_3(e^{i\theta}))\f$
 * @param x real angle
 * @return \f$\mathrm{Cl}_3(\theta)\f$
 * @author Alexander Voigt
 * @note Implementation as economized Padé approximation.
 */
double Cl3(double x) noexcept
{
   const double PI = 3.14159265358979324;
   const double PI2 = 2*PI, PIH = PI/2, PI28 = PI*PI/8;
   const double zeta3 = 1.2020569031595943;

   if (x < 0) {
      x = -x;
   }

   if (x >= PI2) {
      x = std::fmod(x, PI2);
   }

   if (x > PI) {
      const double p0 = 6.28125;
      const double p1 = 0.0019353071795864769253;
      x = (p0 - x) + p1;
   }

   if (x == 0) {
      return zeta3;
   }

   double h = 0;

   if (x < PIH) {
      const double P[] = {
         -7.5430148591242361e-01,  1.6121940167854339e-02,
         -3.7484056212140535e-05, -2.5191292110169198e-07
      };
      const double Q[] = {
         1.0000000000000000e+00, -2.6015033560727570e-02,
         1.5460630299236049e-04, -1.0987530650923219e-07
      };
      const double y = x*x;
      const double z = y - PI28;
      const double z2 = z*z;
      const double p = P[0] + z * P[1] + z2 * (P[2] + z * P[3]);
      const double q = Q[0] + z * Q[1] + z2 * (Q[2] + z * Q[3]);
      h = zeta3 + y*(p/q + std::log(x)/2);
   } else {
      const double P[] = {
         -4.9017024647634973e-01, 4.1559155224660940e-01,
         -7.9425531417806701e-02, 5.9420152260602943e-03,
         -1.8302227163540190e-04, 1.8027408929418533e-06
      };
      const double Q[] = {
         1.0000000000000000e+00, -1.9495887541644712e-01,
         1.2059410236484074e-02, -2.5235889467301620e-04,
         1.0199322763377861e-06,  1.9612106499469264e-09
      };
      const double y = PI - x;
      const double z = y*y - PI28;
      const double z2 = z*z;
      const double z4 = z2*z2;
      const double p = P[0] + z * P[1] + z2 * (P[2] + z * P[3]) +
         z4 * (P[4] + z * P[5]);
      const double q = Q[0] + z * Q[1] + z2 * (Q[2] + z * Q[3]) +
         z4 * (Q[4] + z * Q[5]);
      h = p/q;
   }

   return h;
}

/**
 * @brief Clausen function \f$\mathrm{Cl}_3(\theta) = \mathrm{Re}(\mathrm{Li}_3(e^{i\theta}))\f$ with long double precision
 * @param x real angle
 * @return \f$\mathrm{Cl}_3(\theta)\f$
 * @author Alexander Voigt
 * @note Implementation as economized Padé approximation.
 */
long double Cl3(long double x) noexcept
{
   const long double PI = 3.14159265358979323846264338327950288L;
   const long double PI2 = 2*PI, PIH = PI/2, PI28 = PI*PI/8;
   const long double zeta3 = 1.2020569031595942853997381615114499908L;

   if (x < 0) {
      x = -x;
   }

   if (x >= PI2) {
      x = std::fmod(x, PI2);
   }

   if (x > PI) {
      const long double p0 = 6.28125L;
      const long double p1 = 0.0019353071795864769252867665590057683943L;
      x = (p0 - x) + p1;
   }

   if (x == 0) {
      return zeta3;
   }

   long double h = 0;

   if (x < PIH) {
      const long double P[] = {
         -7.543014859124236086513359303676733979191e-01L,
          6.402301836868117230156416581268033099875e-02L,
         -2.127896098530218208963041584986434591351e-03L,
          3.463165731182357705183279540808782152120e-05L,
         -2.754862729116033380287404534774919686497e-07L,
          8.052538909862304289974104174276673516832e-10L,
          1.346114649676610056675054469405688579693e-12L,
         -9.624573206929882592200009480606020302094e-15L,
          8.275206821858140239162250779757575466957e-18L
      };
      const long double Q[] = {
          1.000000000000000000000000000000000000000e+00L,
         -8.951892304715004068142060061380434166813e-02L,
          3.220693717342225233144437822487371940443e-03L,
         -5.958192714621426181787114562889325229941e-05L,
          6.014846196895560469030445734629791881016e-07L,
         -3.236076181461994705051496031602571907271e-09L,
          8.340438662048507021623726184074556662658e-12L,
         -7.892956808623089379250167198187183753861e-15L,
          1.129224149808716947279552120998699589829e-18L
      };
      const long double y = x*x;
      const long double z = y - PI28;
      const long double z2 = z*z;
      const long double z4 = z2*z2;
      const long double z8 = z4*z4;
      // @todo(alex) add one more term:
      const long double p = P[0] + z * P[1] + z2 * (P[2] + z * P[3]) +
         z4 * (P[4] + z * P[5] + z2 * (P[6] + z * P[7])) + z8 * P[8];
      const long double q = Q[0] + z * Q[1] + z2 * (Q[2] + z * Q[3]) +
         z4 * (Q[4] + z * Q[5] + z2 * (Q[6] + z * Q[7])) + z8 * Q[8];
      h = zeta3 + y*(p/q + std::log(x)/2);
   } else {
      const long double P[] = {
         -4.901702464763497295023867883920487195585e-01L,
          1.383627100551763417738051599449773818178e+00L,
         -1.844002682148364621305380083013461847933e+00L,
          1.563880808732850065996446127297492925273e+00L,
         -9.527454451278452672142805742734474223237e-01L,
          4.444304509117015442253289733308961077770e-01L,
         -1.647875030685306314220378800538115071507e-01L,
          4.967825071601030726970818647842992410835e-02L,
         -1.233860796084952133261104412894436518532e-02L,
          2.541279038266908987516674931803683131910e-03L,
         -4.345955367166196341753615932772484893528e-04L,
          6.151865219319515057283373610462827653393e-05L,
         -7.156818018509654192384040775515653410043e-06L,
          6.767889054848634496309672687089961659404e-07L,
         -5.125309226510821380097226378219650957199e-08L,
          3.048859537856972635577813264215347682070e-09L,
         -1.389976271585941361238252210621219258086e-10L,
          4.704164267289991379740337499442804533393e-12L,
         -1.132342670092216676813702977101988168170e-13L,
          1.824345098049373687569378456747139377638e-15L,
         -1.791641454777807114948357142007867857930e-17L,
          9.108765355959209109895175829397816299966e-20L,
         -1.660401736402055166724718838052384514483e-22L
      };
      const long double Q[] = {
          1.000000000000000000000000000000000000000e+00L,
         -2.169855465456334109398757427681231252557e+00L,
          2.322591192513290976964726281913672818074e+00L,
         -1.625275527588871360012554245669893880287e+00L,
          8.307827568524387115453112563337808771609e-01L,
         -3.283520342971423622595752570043633453066e-01L,
          1.036112385177655663181226022787541960128e-01L,
         -2.658049675854302301943410969110308213449e-02L,
          5.594232916811019674312451829387056772971e-03L,
         -9.682117420514440669170644446720530951119e-04L,
          1.373775076479943342597652514135717056402e-04L,
         -1.585377827830451443222728940538258932617e-05L,
          1.469487119911154060364041910223012615302e-06L,
         -1.075235400618754592467376790070172663512e-07L,
          6.072406717259994215240055677751661462408e-09L,
         -2.571318839166908430254322849495115672150e-10L,
          7.860204435599274911316716981969539571217e-12L,
         -1.647194263529074575838983448164465153777e-13L,
          2.194513208755261829948257460166939183883e-15L,
         -1.645669178927884807010050119309005828655e-17L,
          5.496854459511181731052565995680338061501e-20L,
         -4.060391001681163801807157030538815464753e-23L,
         -1.500455700173452211389785169624351996026e-26L
      };
      const long double y = PI - x;
      const long double z = y*y - PI28;
      const long double z2 = z*z;
      const long double z4 = z2*z2;
      const long double z8 = z4*z4;
      const long double z16 = z8*z8;
      const long double p = P[0] + z*P[1] + z2*(P[2] + z*P[3]) +
         z4*(P[4] + z*P[5] + z2*(P[6] + z*P[7])) +
         z8*(P[8] + z*P[9] + z2*(P[10] + z*P[11]) +
             z4*(P[12] + z*P[13] + z2*(P[14] + z*P[15]))) +
         z16*(P[16] + z*P[17] + z2*(P[18] + z*P[19]) +
              z4*(P[20] + z*P[21] + z2*P[22]));
      const long double q = Q[0] + z*Q[1] + z2*(Q[2] + z*Q[3]) +
         z4*(Q[4] + z*Q[5] + z2*(Q[6] + z*Q[7])) +
         z8*(Q[8] + z*Q[9] + z2*(Q[10] + z*Q[11]) +
             z4*(Q[12] + z*Q[13] + z2*(Q[14] + z*Q[15]))) +
         z16*(Q[16] + z*Q[17] + z2*(Q[18] + z*Q[19]) +
              z4*(Q[20] + z*Q[21] + z2*Q[22]));
      h = p/q;
   }

   return h;
}

} // namespace polylogarithm
