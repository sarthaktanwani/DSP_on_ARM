#include "arm_math.h"                   // ARM::CMSIS:DSP

#define		NUM_TAPS	29

float32_t impulse_response[NUM_TAPS] = 
{
  -0.0018225230f, -0.0015879294f, +0.0000000000f, +0.0036977508f, +0.0080754303f, +0.0085302217f, -0.0000000000f, -0.0173976984f,
  -0.0341458607f, -0.0333591565f, +0.0000000000f, +0.0676308395f, +0.1522061835f, +0.2229246956f, +0.2504960933f, +0.2229246956f,
  +0.1522061835f, +0.0676308395f, +0.0000000000f, -0.0333591565f, -0.0341458607f, -0.0173976984f, -0.0000000000f, +0.0085302217f,
  +0.0080754303f, +0.0036977508f, +0.0000000000f, -0.0015879294f, -0.0018225230f
};

float32_t inputSignal_f32_1kHz_15kHz[320] =
{
+0.0000000000f, +0.5924659585f, -0.0947343455f, +0.1913417162f, +1.0000000000f, +0.4174197128f, +0.3535533906f, +1.2552931065f, 
+0.8660254038f, +0.4619397663f, +1.3194792169f, +1.1827865776f, +0.5000000000f, +1.1827865776f, +1.3194792169f, +0.4619397663f, 
+0.8660254038f, +1.2552931065f, +0.3535533906f, +0.4174197128f, +1.0000000000f, +0.1913417162f, -0.0947343455f, +0.5924659585f, 
-0.0000000000f, -0.5924659585f, +0.0947343455f, -0.1913417162f, -1.0000000000f, -0.4174197128f, -0.3535533906f, -1.2552931065f, 
-0.8660254038f, -0.4619397663f, -1.3194792169f, -1.1827865776f, -0.5000000000f, -1.1827865776f, -1.3194792169f, -0.4619397663f, 
-0.8660254038f, -1.2552931065f, -0.3535533906f, -0.4174197128f, -1.0000000000f, -0.1913417162f, +0.0947343455f, -0.5924659585f, 
+0.0000000000f, +0.5924659585f, -0.0947343455f, +0.1913417162f, +1.0000000000f, +0.4174197128f, +0.3535533906f, +1.2552931065f, 
+0.8660254038f, +0.4619397663f, +1.3194792169f, +1.1827865776f, +0.5000000000f, +1.1827865776f, +1.3194792169f, +0.4619397663f, 
+0.8660254038f, +1.2552931065f, +0.3535533906f, +0.4174197128f, +1.0000000000f, +0.1913417162f, -0.0947343455f, +0.5924659585f, 
+0.0000000000f, -0.5924659585f, +0.0947343455f, -0.1913417162f, -1.0000000000f, -0.4174197128f, -0.3535533906f, -1.2552931065f, 
-0.8660254038f, -0.4619397663f, -1.3194792169f, -1.1827865776f, -0.5000000000f, -1.1827865776f, -1.3194792169f, -0.4619397663f, 
-0.8660254038f, -1.2552931065f, -0.3535533906f, -0.4174197128f, -1.0000000000f, -0.1913417162f, +0.0947343455f, -0.5924659585f, 
+0.0000000000f, +0.5924659585f, -0.0947343455f, +0.1913417162f, +1.0000000000f, +0.4174197128f, +0.3535533906f, +1.2552931065f, 
+0.8660254038f, +0.4619397663f, +1.3194792169f, +1.1827865776f, +0.5000000000f, +1.1827865776f, +1.3194792169f, +0.4619397663f, 
+0.8660254038f, +1.2552931065f, +0.3535533906f, +0.4174197128f, +1.0000000000f, +0.1913417162f, -0.0947343455f, +0.5924659585f, 
+0.0000000000f, -0.5924659585f, +0.0947343455f, -0.1913417162f, -1.0000000000f, -0.4174197128f, -0.3535533906f, -1.2552931065f, 
-0.8660254038f, -0.4619397663f, -1.3194792169f, -1.1827865776f, -0.5000000000f, -1.1827865776f, -1.3194792169f, -0.4619397663f, 
-0.8660254038f, -1.2552931065f, -0.3535533906f, -0.4174197128f, -1.0000000000f, -0.1913417162f, +0.0947343455f, -0.5924659585f, 
-0.0000000000f, +0.5924659585f, -0.0947343455f, +0.1913417162f, +1.0000000000f, +0.4174197128f, +0.3535533906f, +1.2552931065f, 
+0.8660254038f, +0.4619397663f, +1.3194792169f, +1.1827865776f, +0.5000000000f, +1.1827865776f, +1.3194792169f, +0.4619397663f, 
+0.8660254038f, +1.2552931065f, +0.3535533906f, +0.4174197128f, +1.0000000000f, +0.1913417162f, -0.0947343455f, +0.5924659585f, 
-0.0000000000f, -0.5924659585f, +0.0947343455f, -0.1913417162f, -1.0000000000f, -0.4174197128f, -0.3535533906f, -1.2552931065f, 
-0.8660254038f, -0.4619397663f, -1.3194792169f, -1.1827865776f, -0.5000000000f, -1.1827865776f, -1.3194792169f, -0.4619397663f, 
-0.8660254038f, -1.2552931065f, -0.3535533906f, -0.4174197128f, -1.0000000000f, -0.1913417162f, +0.0947343455f, -0.5924659585f, 
+0.0000000000f, +0.5924659585f, -0.0947343455f, +0.1913417162f, +1.0000000000f, +0.4174197128f, +0.3535533906f, +1.2552931065f, 
+0.8660254038f, +0.4619397663f, +1.3194792169f, +1.1827865776f, +0.5000000000f, +1.1827865776f, +1.3194792169f, +0.4619397663f, 
+0.8660254038f, +1.2552931065f, +0.3535533906f, +0.4174197128f, +1.0000000000f, +0.1913417162f, -0.0947343455f, +0.5924659585f, 
+0.0000000000f, -0.5924659585f, +0.0947343455f, -0.1913417162f, -1.0000000000f, -0.4174197128f, -0.3535533906f, -1.2552931065f, 
-0.8660254038f, -0.4619397663f, -1.3194792169f, -1.1827865776f, -0.5000000000f, -1.1827865776f, -1.3194792169f, -0.4619397663f, 
-0.8660254038f, -1.2552931065f, -0.3535533906f, -0.4174197128f, -1.0000000000f, -0.1913417162f, +0.0947343455f, -0.5924659585f, 
-0.0000000000f, +0.5924659585f, -0.0947343455f, +0.1913417162f, +1.0000000000f, +0.4174197128f, +0.3535533906f, +1.2552931065f, 
+0.8660254038f, +0.4619397663f, +1.3194792169f, +1.1827865776f, +0.5000000000f, +1.1827865776f, +1.3194792169f, +0.4619397663f, 
+0.8660254038f, +1.2552931065f, +0.3535533906f, +0.4174197128f, +1.0000000000f, +0.1913417162f, -0.0947343455f, +0.5924659585f, 
+0.0000000000f, -0.5924659585f, +0.0947343455f, -0.1913417162f, -1.0000000000f, -0.4174197128f, -0.3535533906f, -1.2552931065f, 
-0.8660254038f, -0.4619397663f, -1.3194792169f, -1.1827865776f, -0.5000000000f, -1.1827865776f, -1.3194792169f, -0.4619397663f, 
-0.8660254038f, -1.2552931065f, -0.3535533906f, -0.4174197128f, -1.0000000000f, -0.1913417162f, +0.0947343455f, -0.5924659585f, 
-0.0000000000f, +0.5924659585f, -0.0947343455f, +0.1913417162f, +1.0000000000f, +0.4174197128f, +0.3535533906f, +1.2552931065f, 
+0.8660254038f, +0.4619397663f, +1.3194792169f, +1.1827865776f, +0.5000000000f, +1.1827865776f, +1.3194792169f, +0.4619397663f, 
+0.8660254038f, +1.2552931065f, +0.3535533906f, +0.4174197128f, +1.0000000000f, +0.1913417162f, -0.0947343455f, +0.5924659585f, 
+0.0000000000f, -0.5924659585f, +0.0947343455f, -0.1913417162f, -1.0000000000f, -0.4174197128f, -0.3535533906f, -1.2552931065f, 
};

float32_t _640_points_ecg_[640]=
{0,0.0010593,0.0021186,0.003178,0.0042373,0.0052966,0.0063559,0.0074153,0.0084746,0.045198,
0.081921,0.11864,0.15537,0.19209,0.22881,0.26554,0.30226,0.33898,0.30226,0.26554,0.22881,
0.19209,0.15537,0.11864,0.081921,0.045198,0.0084746,0.0077684,0.0070621,0.0063559,0.0056497,
0.0049435,0.0042373,0.0035311,0.0028249,0.0021186,0.0014124,0.00070621,0,-0.096045,-0.19209,
-0.28814,-0.073446,0.14124,0.35593,0.57062,0.78531,1,0.73729,0.47458,0.21186,-0.050847,-0.31356,
-0.57627,-0.83898,-0.55932,-0.27966,0,0.00073692,0.0014738,0.0022108,0.0029477,0.0036846,0.0044215,
0.0051584,0.0058954,0.0066323,0.0073692,0.0081061,0.008843,0.00958,0.010317,0.011054,0.011791,0.012528,
0.013265,0.014001,0.014738,0.015475,0.016212,0.016949,0.03484,0.052731,0.070621,0.088512,0.1064,0.12429,
0.14218,0.16008,0.17797,0.16186,0.14576,0.12966,0.11356,0.097458,0.081356,0.065254,0.049153,0.033051,0.016949,
0.013559,0.010169,0.0067797,0.0033898,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.0010593,0.0021186,
0.003178,0.0042373,0.0052966,0.0063559,0.0074153,0.0084746,0.045198,0.081921,0.11864,0.15537,0.19209,0.22881,
0.26554,0.30226,0.33898,0.30226,0.26554,0.22881,0.19209,0.15537,0.11864,0.081921,0.045198,0.0084746,0.0077684,
0.0070621,0.0063559,0.0056497,0.0049435,0.0042373,0.0035311,0.0028249,0.0021186,0.0014124,0.00070621,0,-0.096045,
-0.19209,-0.28814,-0.073446,0.14124,0.35593,0.57062,0.78531,1,0.73729,0.47458,0.21186,-0.050847,-0.31356,-0.57627,
-0.83898,-0.55932,-0.27966,0,0.00073692,0.0014738,0.0022108,0.0029477,0.0036846,0.0044215,0.0051584,0.0058954,
0.0066323,0.0073692,0.0081061,0.008843,0.00958,0.010317,0.011054,0.011791,0.012528,0.013265,0.014001,0.014738,
0.015475,0.016212,0.016949,0.03484,0.052731,0.070621,0.088512,0.1064,0.12429,0.14218,0.16008,0.17797,0.16186,
0.14576,0.12966,0.11356,0.097458,0.081356,0.065254,0.049153,0.033051,0.016949,0.013559,0.010169,0.0067797,
0.0033898,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.0010593,0.0021186,0.003178,0.0042373,0.0052966,
0.0063559,0.0074153,0.0084746,0.045198,0.081921,0.11864,0.15537,0.19209,0.22881,0.26554,0.30226,0.33898,
0.30226,0.26554,0.22881,0.19209,0.15537,0.11864,0.081921,0.045198,0.0084746,0.0077684,0.0070621,0.0063559,
0.0056497,0.0049435,0.0042373,0.0035311,0.0028249,0.0021186,0.0014124,0.00070621,0,-0.096045,-0.19209,
-0.28814,-0.073446,0.14124,0.35593,0.57062,0.78531,1,0.73729,0.47458,0.21186,-0.050847,-0.31356,
-0.57627,-0.83898,-0.55932,-0.27966,0,0.00073692,0.0014738,0.0022108,0.0029477,0.0036846,
0.0044215,0.0051584,0.0058954,0.0066323,0.0073692,0.0081061,0.008843,0.00958,0.010317,
0.011054,0.011791,0.012528,0.013265,0.014001,0.014738,0.015475,0.016212,0.016949,0.03484,
0.052731,0.070621,0.088512,0.1064,0.12429,0.14218,0.16008,0.17797,0.16186,0.14576,0.12966,
0.11356,0.097458,0.081356,0.065254,0.049153,0.033051,0.016949,0.013559,0.010169,0.0067797,
0.0033898,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.0010593,0.0021186,0.003178,
0.0042373,0.0052966,0.0063559,0.0074153,0.0084746,0.045198,0.081921,0.11864,0.15537,0.19209,
0.22881,0.26554,0.30226,0.33898,0.30226,0.26554,0.22881,0.19209,0.15537,0.11864,0.081921,
0.045198,0.0084746,0.0077684,0.0070621,0.0063559,0.0056497,0.0049435,0.0042373,0.0035311,
0.0028249,0.0021186,0.0014124,0.00070621,0,-0.096045,-0.19209,-0.28814,-0.073446,0.14124,
0.35593,0.57062,0.78531,1,0.73729,0.47458,0.21186,-0.050847,-0.31356,-0.57627,-0.83898,-0.55932,
-0.27966,0,0.00073692,0.0014738,0.0022108,0.0029477,0.0036846,0.0044215,0.0051584,0.0058954,
0.0066323,0.0073692,0.0081061,0.008843,0.00958,0.010317,0.011054,0.011791,0.012528,0.013265,
0.014001,0.014738,0.015475,0.016212,0.016949,0.03484,0.052731,0.070621,0.088512,0.1064,0.12429,
0.14218,0.16008,0.17797,0.16186,0.14576,0.12966,0.11356,0.097458,0.081356,0.065254,0.049153,0.033051,
0.016949,0.013559,0.010169,0.0067797,0.0033898,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.0010593,
0.0021186,0.003178,0.0042373,0.0052966,0.0063559,0.0074153,0.0084746,0.045198,0.081921,0.11864,0.15537,0.19209,
0.22881,0.26554,0.30226,0.33898,0.30226,0.26554,0.22881,0.19209,0.15537,0.11864,0.081921,0.045198,0.0084746,
0.0077684,0.0070621,0.0063559,0.0056497,0.0049435,0.0042373,0.0035311,0.0028249,0.0021186,0.0014124,0.00070621,
0,-0.096045,-0.19209,-0.28814,-0.073446,0.14124,0.35593,0.57062,0.78531,1,0.73729,0.47458,0.21186,-0.050847,
-0.31356,-0.57627,-0.83898,-0.55932,-0.27966,0,0.00073692,0.0014738,0.0022108,0.0029477,0.0036846,0.0044215,
0.0051584,0.0058954,0.0066323,0.0073692,0.0081061,0.008843,0.00958,0.010317,0.011054,0.011791,0.012528,0.013265,
0.014001,0.014738,0.015475,0.016212,0.016949,0.03484,0.052731,0.070621,0.088512,0.1064,0.12429,0.14218,0.16008,
0.17797,0.16186,0.14576,0.12966,0.11356,0.097458,0.081356,0.065254,0.049153,0.033051,0.016949,0.013559,0.010169,
0.0067797,0.0033898,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};
