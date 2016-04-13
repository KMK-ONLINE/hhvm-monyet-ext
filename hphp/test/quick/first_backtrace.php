<?hh

print "monyet=" . extension_loaded('monyet') . PHP_EOL;
print "first_backtrace=" . function_exists('first_backtrace'). PHP_EOL;

include __DIR__.'/data/a.php';

include __DIR__.'/data/b.php';
