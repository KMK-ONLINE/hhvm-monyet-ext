<?hh

print "monyet=" . extension_loaded('monyet') . PHP_EOL;
print "my_compact=" . function_exists('my_compact'). PHP_EOL;

$a = 1;
$b = 2;

compact_intercept();

print_r(compact('a', 'b'));
