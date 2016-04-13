<?hh

print "monyet=" . extension_loaded('monyet') . PHP_EOL;
print "get_template_source=" . function_exists('get_template_source'). PHP_EOL;

echo "0.txt = '" . get_template_source(__DIR__ . '/data/0.txt') . "'" . PHP_EOL;
echo "1.php = '" . get_template_source(__DIR__ . '/data/1.php') . "'" . PHP_EOL;
echo "2.php = '" . get_template_source(__DIR__ . '/data/2.php') . "'" . PHP_EOL;
echo "3.php = '" . get_template_source(__DIR__ . '/data/3.php') . "'" . PHP_EOL;
echo "4 = '" . get_template_source(__DIR__ . '/data/4') . "'" . PHP_EOL;

