<?hh

print "monyet=" . extension_loaded('monyet') . PHP_EOL;
print "my_get_defined_vars=" . function_exists('my_get_defined_vars'). PHP_EOL;

get_defined_vars_intercept();

function scoped() {
  $x = 'x';
  $y = 'y';

  $ary = get_defined_vars();

  print_r($ary);
}

scoped();
