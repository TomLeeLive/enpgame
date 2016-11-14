$modelname "C:\Program Files (x86)\Steam\steamapps\common\Half-Life\gearbox\models\weapon\shotgun\v_shotgun.mdl"
$cd "\Program Files (x86)\Steam\steamapps\common\Half-Life\gearbox\models\weapon\shotgun\"
$cdtexture "\Program Files (x86)\Steam\steamapps\common\Half-Life\gearbox\models\weapon\shotgun\"
$cliptotextures

$scale 1.0

// 1 attachments
$attachment 0 "Bip01 R Hand" 30.000000 1.000000 6.000000 

// 0 bone controllers

// 6 hit boxes
$hbox 0 "Bip01 R Hand" 0.000000 -0.620000 0.000000  26.420000 1.530000 6.270000
$hbox 0 "Bone01" -1.900000 -2.480000 -1.490000  7.100000 1.490000 1.700000
$hbox 0 "Bip01 L Arm2" -0.360000 -1.470000 -1.700000  11.370000 1.660000 2.580000
$hbox 0 "Bip01 L Hand" 0.000000 -1.040000 -2.140000  3.790000 0.880000 1.860000
$hbox 0 "Bip01 L Finger0" 0.000000 -0.920000 -0.580000  3.730000 0.450000 0.790000
$hbox 0 "Bip01 L Finger31" 0.000000 -0.700000 -0.480000  1.136840 0.450000 0.530000

$bodygroup studio
{
studio "v_shotgun_reference"
}

$bodygroup studio
{
studio "shell"
}

$bodygroup studio
{
studio "v_shotgun_hands_reference"
}

// 10 sequences
$sequence sm_idle "sm_idle" loop fps 9 
$sequence shoot "shoot" fps 20 { event 5001 0 "31" } 
$sequence shoot_big "shoot_big" fps 13 { event 5001 0 "41" } 
$sequence reload "reload" fps 16 
$sequence pump "pump" fps 13 
$sequence start_reload "start_reload" fps 12 
$sequence draw "draw" fps 24 
$sequence reholster "reholster" fps 30 
$sequence idle4 "idle4" loop fps 9 
$sequence deepidle "deepidle" loop fps 12 
