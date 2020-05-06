// ====================================================================
// This file is part of Polylogarithm.
//
// Polylogarithm is licenced under the GNU Lesser General Public
// License (GNU LGPL) version 3.
// ====================================================================

#include <complex.h>
#include <float.h>
#include <math.h>

/**
 * @brief Real dilogarithm \f$\mathrm{Li}_2(x)\f$
 * @param x real argument
 * @note Implementation translated by R.Brun from CERNLIB DILOG function C332
 * @return \f$\mathrm{Li}_2(x)\f$
 *
 * Implemented as a truncated series expansion in terms of Chebyshev
 * polynomials, see [Yudell L. Luke: Mathematical functions and their
 * approximations, Academic Press Inc., New York 1975, p.67].
 */
double li2(double x)
{
   const double PI  = 3.141592653589793;
   const double HF  = 0.5;
   const double PI2 = PI*PI;
   const double PI3 = PI2/3;
   const double PI6 = PI2/6;
   const double PI12 = PI2/12;
   const double C[20] = {  0.42996693560813697, 0.40975987533077106,
     -0.01858843665014592, 0.00145751084062268,-0.00014304184442340,
      0.00001588415541880,-0.00000190784959387, 0.00000024195180854,
     -0.00000003193341274, 0.00000000434545063,-0.00000000060578480,
      0.00000000008612098,-0.00000000001244332, 0.00000000000182256,
     -0.00000000000027007, 0.00000000000004042,-0.00000000000000610,
      0.00000000000000093,-0.00000000000000014, 0.00000000000000002};

   double T, H, Y, S, A, ALFA, B1, B2, B0;

   if (x == 1) {
       H = PI6;
   } else if (x == -1) {
       H = -PI12;
   } else {
       T = -x;
       if (T <= -2) {
           Y = -1/(1+T);
           S = 1;
           B1= log(-T);
           B2= log(1+1/T);
           A = -PI3+HF*(B1*B1-B2*B2);
       } else if (T < -1) {
           Y = -1-T;
           S = -1;
           A = log(-T);
           A = -PI6+A*(A+log(1+1/T));
       } else if (T <= -0.5) {
           Y = -(1+T)/T;
           S = 1;
           A = log(-T);
           A = -PI6+A*(-HF*A+log(1+T));
       } else if (T < 0) {
           Y = -T/(1+T);
           S = -1;
           B1= log(1+T);
           A = HF*B1*B1;
       } else if (T <= 1) {
           Y = T;
           S = 1;
           A = 0;
       } else {
           Y = 1/T;
           S = -1;
           B1= log(T);
           A = PI6+HF*B1*B1;
       }
       H    = Y+Y-1;
       ALFA = H+H;
       B1   = 0;
       B2   = 0;
       for (int i = 19; i >= 0; i--) {
          B0 = C[i] + ALFA*B1-B2;
          B2 = B1;
          B1 = B0;
       }
       H = -(S*(B0-H*B2)+A);
    }
    return H;
}


/**
 * @brief Complex dilogarithm \f$\mathrm{Li}_2(z)\f$
 * @param z complex argument
 * @note Implementation translated from SPheno to C++
 * @return \f$\mathrm{Li}_2(z)\f$
 */
static double _Complex cli2(const double _Complex z)
{
   const double PI = 3.141592653589793;

   // bf[1..N-1] are the even Bernoulli numbers / (2 n + 1)!
   // generated by: Table[BernoulliB[2 n]/(2 n + 1)!, {n, 1, 9}]
   const double bf[10] = {
      - 1.0/4.0,
      + 1.0/36.0,
      - 1.0/3600.0,
      + 1.0/211680.0,
      - 1.0/10886400.0,
      + 1.0/526901760.0,
      - 4.064761645144226e-11,
      + 8.921691020456453e-13,
      - 1.993929586072108e-14,
      + 4.518980029619918e-16
   };

   const double rz = creal(z);
   const double iz = cimag(z);
   const double nz = rz*rz + iz*iz;

   // special cases
   if (iz == 0.0) {
      if (rz <= 1.0) {
         return li2(rz) + 0.0*I;
      }
      if (rz > 1.0) {
         return li2(rz) - PI*log(rz)*I;
      }
   } else if (nz < DBL_EPSILON) {
      return z;
   }

   double _Complex cy = 0.0 + 0.0*I, cz = 0.0 + 0.0*I;
   int jsgn = 0, ipi12 = 0;

   // transformation to |z|<1, Re(z)<=0.5
   if (rz <= 0.5) {
      if (nz > 1.0) {
         const double _Complex lz = clog(-z);
         cy = -0.5 * lz*lz;
         cz = -clog(1.0 - 1.0 / z);
         jsgn = -1;
         ipi12 = -2;
      } else { // nz <= 1
         cy = 0;
         cz = -clog(1.0 - z);
         jsgn = 1;
         ipi12 = 0;
      }
   } else { // rz > 0.5
      if (nz <= 2*rz) {
         cz = -clog(z);
         cy = cz * clog(1.0 - z);
         jsgn = -1;
         ipi12 = 2;
      } else { // nz > 2*rz
         const double _Complex lz = clog(-z);
         cy = -0.5 * lz*lz;
         cz = -clog(1.0 - 1.0 / z);
         jsgn = -1;
         ipi12 = -2;
      }
   }

   // the dilogarithm
   const double _Complex cz2 = cz*cz;
   const double _Complex sum =
      cz +
      cz2 * (bf[0] +
      cz  * (bf[1] +
      cz2 * (bf[2] +
      cz2 * (bf[3] +
      cz2 * (bf[4] +
      cz2 * (bf[5] +
      cz2 * (bf[6] +
      cz2 * (bf[7] +
      cz2 * (bf[8] +
      cz2 * (bf[9]))))))))));

   return (double)jsgn * sum + cy + ipi12 * PI * PI / 12.0;
}

/** C++ wrapper for cli2 */
void cli2_(double re, double im, double* res_re, double* res_im)
{
   const double _Complex result = cli2(re + I*im);
   *res_re = creal(result);
   *res_im = cimag(result);
}
