echo 'Please enter glslValidator.exe path : '
read validatorPath

$validatorPath -V shader.vert
$validatorPath -V shader.frag
