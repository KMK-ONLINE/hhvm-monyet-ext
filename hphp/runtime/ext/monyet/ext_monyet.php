<?hh

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
