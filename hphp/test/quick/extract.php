<?php

print "monyet=" . extension_loaded('monyet') . PHP_EOL;
print "my_extract=" . function_exists('my_extract'). PHP_EOL;

$x = ['a' => 1, 'b' => 2];

echo 'isset($a) = ' . (isset($a) ? 'yes' : 'no') . PHP_EOL;
echo 'isset($b) = ' . (isset($b) ? 'yes' : 'no') . PHP_EOL;

extract_intercept();

extract($x);

echo 'isset($a) = ' . (isset($a) ? 'yes' : 'no') . PHP_EOL;
echo 'isset($b) = ' . (isset($b) ? 'yes' : 'no') . PHP_EOL;

echo '$a = ' . $a . PHP_EOL;
echo '$b = ' . $b . PHP_EOL;
