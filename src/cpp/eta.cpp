// ====================================================================
// This file is part of Polylogarithm.
//
// Polylogarithm is licenced under the MIT License.
// ====================================================================

#include "eta.hpp"
#include <limits>

namespace polylogarithm {

namespace {

// Table[PolyLog[n,-1], {n,1,54}]
const double NEG_ETA[54] = {
    -0.69314718055994531, -0.82246703342411322, -0.90154267736969571,
    -0.94703282949724592, -0.97211977044690931, -0.98555109129743510,
    -0.99259381992283028, -0.99623300185264790, -0.99809429754160533,
    -0.99903950759827157, -0.99951714349806075, -0.99975768514385819,
    -0.99987854276326512, -0.99993917034597972, -0.99996955121309924,
    -0.99998476421490611, -0.99999237829204101, -0.99999618786961011,
    -0.99999809350817168, -0.99999904661158152, -0.99999952325821554,
    -0.99999976161323082, -0.99999988080131844, -0.99999994039889239,
    -0.99999997019885696, -0.99999998509923200, -0.99999999254955048,
    -0.99999999627475340, -0.99999999813736942, -0.99999999906868228,
    -0.9999999995343403 , -0.9999999997671699 , -0.9999999998835849 ,
    -0.9999999999417924 , -0.9999999999708962 , -0.9999999999854481 ,
    -0.9999999999927240 , -0.9999999999963620 , -0.9999999999981810 ,
    -0.9999999999990905 , -0.9999999999995453 , -0.9999999999997726 ,
    -0.9999999999998863 , -0.9999999999999432 , -0.9999999999999716 ,
    -0.9999999999999858 , -0.9999999999999929 , -0.9999999999999964 ,
    -0.9999999999999982 , -0.9999999999999991 , -0.9999999999999996 ,
    -0.9999999999999998 , -0.9999999999999999 , -0.9999999999999999
};

// Table[PolyLog[-2n+1,-1], {n,1,109}]
const double NEG_ETA_NEG_N[] = {
   -0.25, 0.125           , -0.25                  ,  1.0625                ,
   -7.75                  ,  86.375                , -1365.25               ,
    29049.03125           , -800572.75             ,  2.7741322625e7        ,
   -1.18052913025e9       ,  6.05239800516875e10   , -3.67941677853775e12   ,
    2.6170760990658388e014, -2.1531418140800295e016,  2.0288775575173016e018,
   -2.1708009902623771e020,  2.6173826968455815e022, -3.5324148876863878e024,
    5.3042033406864907e026, -8.8138218364311577e028,  1.6128065107490779e031,
   -3.2355470001722734e033,  7.0876727476537493e035, -1.6890450341293966e038,
    4.3639690731216831e040, -1.2185998827061261e043,  3.6670584803153006e045,
   -1.1859898526302099e048,  4.1120769493584015e050, -1.5249042436787620e053,
    6.0349693196941307e055, -2.5437161764210696e058,  1.1396923802632288e061,
   -5.4180861064753979e063,  2.7283654799994374e066, -1.4529750514918543e069,
    8.1705519371067450e071, -4.8445781606678368e074,  3.0246694206649519e077,
   -1.9858807961690493e080,  1.3694474620720087e083, -9.9070382984295808e085,
    7.5103780796592646e088, -5.9598418264260881e091,  4.9455988887500020e094,
   -4.2873596927020241e097,  3.8791952037716163e100, -3.6600317773156342e103,
    3.5978775704117284e106, -3.6818662617467813e109,  3.9192743066421374e112,
   -4.3363921885063858e115,  4.9833162711780838e118, -5.9438653020209606e121,
    7.3533439019770134e124, -9.4293465716973561e127,  1.2525196404154548e131,
   -1.7223787163994400e134,  2.4505178680729537e137, -3.6051616659014189e140,
    5.4813803836499771e143, -8.6083892012122616e146,  1.3957139354298160e150,
   -2.3350508860591630e153,  4.0291297374794860e156, -7.1669946227411534e159,
    1.3136385964069363e163, -2.4799083462304252e166,  4.8198083696385558e169,
   -9.6400031196958281e172,  1.9833611905147644e176, -4.1959717912682865e179,
    9.1243724595750010e182, -2.0386902382464212e186,  4.6786408066350383e189,
   -1.1024400389046488e193,  2.6662916424238258e196, -6.6165585014771755e199,
    1.6841726974970032e203, -4.3957474813006951e206,  1.1760766011899571e210,
   -3.2245094671360478e213,  9.0570855543185808e216, -2.6054618058433054e220,
    7.6741449421726560e223, -2.3136880427961752e227,  7.1382598572408242e230,
   -2.2530900128907084e234,  7.2736404696018159e237, -2.4010608416429639e241,
    8.1026279414941787e244, -2.7945745738098571e248,  9.8485095122481192e251,
   -3.5456055356238575e255,  1.3036999220919921e259, -4.8948166866453784e262,
    1.8761736309852136e266, -7.3399918877807488e269,  2.9303136033539038e273,
   -1.1935494277949469e277,  4.9589310621971370e280, -2.1012240064879845e284,
    9.0784179834777353e287, -3.9987113012775244e291,  1.7952380922182709e295,
   -8.2136799002055846e298,  3.8290431596908477e302, -1.8184610414701105e306
};

constexpr bool is_even(int64_t n) noexcept { return n % 2 == 0; }

} // anonymous namespace

/// negative Dirichlet eta function
double neg_eta(int64_t n) noexcept
{
   if (n < 0) {
      if (is_even(n)) {
         return 0.0;
      } else if (-(1 + n)/2 < sizeof(NEG_ETA_NEG_N)/sizeof(NEG_ETA_NEG_N[0])) {
         return NEG_ETA_NEG_N[-(1 + n)/2];
      } else if (is_even((1 - n)/2)) {
         return std::numeric_limits<double>::infinity();
      } else {
         return -std::numeric_limits<double>::infinity();
      }
   } else if (n == 0) {
      return -0.5;
   } else if (n <= sizeof(NEG_ETA)/sizeof(NEG_ETA[0])) {
      return NEG_ETA[n - 1];
   } else {
      return -1.0;
   }
}

} // namespace polylogarithm
