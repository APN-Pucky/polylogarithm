(*
  Approximations of Cl2[2,x] by economized Pade approximations
  on the intervals [0, Pi/2) and [Pi/2, Pi).
 *)

Needs["FunctionApproximations`"];

Get["../test/math/clausenBernoulli.m"];

(* maximum number of terms in Cl2 series *)
nMax = 100;

(* output precision *)
outPrec = 17;

(* bring rational function to standard form *)
PolynomialStandardForm[expr_, x_] :=
    Module[{n = Numerator[expr], d = Denominator[expr], c},
           c = d /. x -> 0;
           Expand[n/c] / Expand[d/c]
    ]

FormatCoeffs[expr_, x_, prec_] :=
    ScientificForm @ CForm @ N[#, prec]& /@ CoefficientList[expr, x]

CalcPade[fn_, interval_, nTerms_] :=
    Module[{half = interval[[1]] + (interval[[2]] - interval[[1]])/2,
            approx, diff, maxErr, y, range},
           approx = EconomizedRationalApproximation[fn[x], {x, interval, nTerms, nTerms}] /. (-half + x) -> y;
           approx = PolynomialStandardForm[approx, y];
           Print["Pade approximant for ", InputForm[fn], " on the interval ", InputForm[interval]];
           Print["Numerator coefficients: ",
                 FormatCoeffs[#,y,outPrec]& @ Numerator[approx]];
           Print["Denominator coefficients: ",
                 FormatCoeffs[#,y,outPrec]& @ Denominator[approx]];
           (* calculate maximum deviation *)
           diff = (approx - fn[x]) /. y -> x - half;
           range = Range[interval[[1]] + 10^(-outPrec), interval[[2]], (interval[[2]] - interval[[1]])/100];
           maxErr = Max @ Abs @ N[diff /. x -> #, outPrec]& @ range;
           Print["max error: ", InputForm @ maxErr];
           approx
    ]

(* interval = {0, Pi/2}; *)
fLo[x_] := 2/x^2 (Cl2Lo[x, nMax]/x - 1 + Log[x])

fnLo[x_] := fLo[Sqrt[x]]

CalcPade[N[fnLo[#], 10*outPrec]&, {0, Pi/2}, 3];

(* interval = {Pi/2, Pi}; *)
fnHi[x_] := Cl2Hi[x, nMax]/(Pi - x)

CalcPade[N[fnHi[#], 10*outPrec]&, {Pi/2, Pi}, 10];
