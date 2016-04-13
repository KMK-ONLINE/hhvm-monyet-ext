<?hh

<<__Native>>
function first_backtrace(): string;

<<__Native>>
function compact_intercept(): void;

<<__Native>>
function my_compact(mixed $varname, ...$argv): array;

<<__Native>>
function my_compact_sl(mixed $varname, ...$argv): array;

<<__Native>>
function extract_intercept(): void;

<<__Native>>
function my_extract(mixed &$var_array,
                 int $extract_type = EXTR_OVERWRITE,
                 string $prefix = ""): int;

<<__Native>>
function my_extract_sl(mixed &$var_array,
                   int $extract_type = EXTR_OVERWRITE,
                   string $prefix = ""): int;

<<__Native>>
function get_defined_vars_intercept(): void;

<<__Native>>
function my_get_defined_vars(): array;

<<__Native>>
function my_get_defined_vars_sl(): array;


function get_template_source(string $scriptfile): string
{
  if (preg_match("/\/[0-9a-z]+(\.php)?$/", $scriptfile)) {
    $f = fopen($scriptfile, 'r');
    $hhtag = fgets($f);
    if (preg_match("/^<\?(php|hh)/", $hhtag)) {
      $src = fgets($f);
      if (preg_match("/\/\* source: (.+) \*\//", $src, $m)) {
        return $m[1];
      }
    }
    fclose($f);
  }
  return "";
}
